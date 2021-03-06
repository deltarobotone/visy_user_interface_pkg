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
  Q_SIGNAL void newGraspData(visy_sorting_app_pkg::GraspData);
private:
  int initArgc;
  char** initArgv;

  QThread * rosNodeThread;

  //Client to start sorting application for metal chips including Delta-Robot One, conveyor system and vision system.
  ros::ServiceClient startSortingClient;
  //Client to stop sorting application.
  ros::ServiceClient stopSortingClient;
  //Client to change image at processing state via buttons on user interface to select displayed image processing state.
  ros::ServiceClient selectImageClient;
  //Subscribe image at the end of a detection loop published by conveyor detector or metal chip detetctor.
  image_transport::Subscriber imageSub;
  //Subscribe grasp data including the time until grasp, colour of chip, number of detetcted chips, latency, velocity, last chip position, etc.
  ros::Subscriber graspDataSub;
  cv::Mat imagework;
  visy_sorting_app_pkg::GraspData graspData;

};
#endif

