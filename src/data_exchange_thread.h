#ifndef ___DATAEXCHANGETHREAD_H___
#define ___DATAEXCHANGETHREAD_H___

#include <QtCore>
#include <QThread>
#include <QStringList>
#include <stdlib.h>
#include <QMutex>
#include <iostream>
#include "assert.h"

#include <ros/ros.h>
#include <ros/network.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "visy_sorting_app_pkg/StartSorting.h"
#include "visy_sorting_app_pkg/StopSorting.h"
#include "visy_detector_pkg/SelectImage.h"
#include "visy_sorting_app_pkg/GraspData.h"

using namespace cv;
using namespace std;

class DataExchangeThread : public QObject {
  Q_OBJECT
public:
  DataExchangeThread(int argc, char **pArgv);
  virtual ~DataExchangeThread();

  bool init();

  void imageCb(const sensor_msgs::ImageConstPtr& image);
  void graspDataCb(const visy_sorting_app_pkg::GraspDataConstPtr& msg);

  void startSortingApp();
  void stopSortingApp();
  void changeImageNext();
  void changeImageBack();

  Q_SLOT void run();

  Q_SIGNAL void newImage(cv::Mat);
  Q_SIGNAL void newGraspdata(visy_sorting_app_pkg::GraspData);
private:
  int initArgc;
  char** initArgv;

  QThread * rosNodeThread;

  ros::ServiceClient startSortingClient;
  ros::ServiceClient stopSortingClient;
  ros::ServiceClient selectImageClient;
  image_transport::Subscriber imageSub;
  cv::Mat imagework;
  visy_sorting_app_pkg::GraspData graspData;

};
#endif

