#include "data_exchange_thread.h"

DataExchangeThread::DataExchangeThread(int argc, char** pArgv):
  initArgc(argc),
  initArgv(pArgv)
{
}

DataExchangeThread::~DataExchangeThread()
{
  if (ros::isStarted()){
    ros::shutdown();
    ros::waitForShutdown();
  }
  rosNodeThread->terminate();
  rosNodeThread->wait();

}

bool DataExchangeThread::init()
{
  rosNodeThread = new QThread();

  this->moveToThread(rosNodeThread);

  connect(rosNodeThread, &QThread::started, this, &DataExchangeThread::run);
  ros::init(initArgc, initArgv, "ui_data_exchange");

  if (!ros::master::check())
    return false;

  ros::start();
  ros::Time::init();
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);

  imageSub = it.subscribe("visy_image", 1, &DataExchangeThread::imageCb, this);
  graspDataSub = nh.subscribe("/grasp_data", 1, &DataExchangeThread::graspDataCb, this);
  startSortingClient = nh.serviceClient<visy_sorting_app_pkg::StartSorting>("start_sorting");
  stopSortingClient = nh.serviceClient<visy_sorting_app_pkg::StopSorting>("stop_sorting");
  selectImageClient = nh.serviceClient<visy_detector_pkg::SelectImage>("select_image");

  rosNodeThread->start();

  return true;
}

void DataExchangeThread::imageCb(const sensor_msgs::ImageConstPtr& image)
{
  cv_bridge::CvImagePtr cv_ptr;

  try{cv_ptr = cv_bridge::toCvCopy(image, sensor_msgs::image_encodings::BGR8);}
  catch (cv_bridge::Exception& e){return;}

  QMutex * pMutex = new QMutex();

  pMutex->lock();
  imagework = cv_ptr->image.clone();
  pMutex->unlock();

  delete pMutex;
  Q_EMIT newImage(imagework);
  qApp->processEvents();
}

void DataExchangeThread::graspDataCb(const visy_sorting_app_pkg::GraspDataConstPtr& msg)
{
  QMutex * pMutex = new QMutex();

  pMutex->lock();
  graspData = *msg;
  pMutex->unlock();

  delete pMutex;

  Q_EMIT newGraspData(graspData);
  qApp->processEvents();
}

void DataExchangeThread::run()
{
  while (ros::ok())
  {
    ros::spin();
  }
}

void DataExchangeThread::startSortingApp()
{
  QMutex * pMutex = new QMutex();
  pMutex->lock();
  visy_sorting_app_pkg::StartSorting srv;
  startSortingClient.call(srv);
  pMutex->unlock();
  delete pMutex;
}

void DataExchangeThread::stopSortingApp()
{
  QMutex * pMutex = new QMutex();
  pMutex->lock();
  visy_sorting_app_pkg::StopSorting srv;
  stopSortingClient.call(srv);
  pMutex->unlock();
  delete pMutex;
}

void DataExchangeThread::changeImageBack()
{
  QMutex * pMutex = new QMutex();
  pMutex->lock();
  visy_detector_pkg::SelectImage srv;
  srv.request.direction = srv.request.BACK;
  selectImageClient.call(srv);
  pMutex->unlock();
  delete pMutex;
}

void DataExchangeThread::changeImageNext()
{
  QMutex * pMutex = new QMutex();
  pMutex->lock();
  visy_detector_pkg::SelectImage srv;
  srv.request.direction = srv.request.NEXT;
  selectImageClient.call(srv);
  pMutex->unlock();
  delete pMutex;
}

