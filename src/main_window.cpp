#include "main_window.h"


MainWindow::MainWindow(int argc, char **argv, QWidget *parent)
  : QWidget(parent),
    dataExchangeThread(argc, argv)
{
  basicLayout = new QVBoxLayout(this);
  buttonRowLayout = new QHBoxLayout;
  buttonRow = new QWidget;

  startButton = new QPushButton;
  stopButton = new QPushButton;

  raspicamImage = new QPixmap;
  raspicamImageWidget = new QLabel;

  createLayout();

  show();

  setWindowTitle(tr("Main Window"));

  /*connect(p_quitButton,  &QPushButton::clicked, this, &MainWindow::close);
    connect(p_upButton,    &QPushButton::clicked, this, &MainWindow::goForward);
    connect(p_leftButton,  &QPushButton::clicked, this, &MainWindow::goLeft);
    connect(p_rightButton, &QPushButton::clicked, this, &MainWindow::goRight);
    connect(p_downButton,  &QPushButton::clicked, this, &MainWindow::goBackward);
    connect(p_stopButton,  &QPushButton::clicked, this, &MainWindow::halt);*/

  connect(&dataExchangeThread, &DataExchangeThread::newImage, this, &MainWindow::updateImage);
  dataExchangeThread.init();
}

void MainWindow::createLayout()
{

  startButton->setIcon(QIcon(":/images/icons/play.png"));
  startButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  startButton->setIconSize(QSize(60, 60));
  connect(startButton, &QPushButton::clicked,this,&MainWindow::startButtonHandle);

  stopButton->setIcon(QIcon(":/images/icons/stop.png"));
  stopButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  stopButton->setIconSize(QSize(60, 60));
  connect(stopButton, &QPushButton::clicked,this,&MainWindow::stopButtonHandle);

  buttonRowLayout->addWidget(startButton);
  buttonRowLayout->addWidget(stopButton);

  buttonRow->setLayout(buttonRowLayout);

  raspicamImage->load(":/images/icons/oneicon.png");
  raspicamImageWidget->setPixmap(*raspicamImage);

  basicLayout->addWidget(raspicamImageWidget,Qt::AlignCenter);
  basicLayout->addWidget(buttonRow);

  setLayout(basicLayout);
}

void MainWindow::startButtonHandle(){dataExchangeThread.startSortingApp();}
void MainWindow::stopButtonHandle(){dataExchangeThread.stopSortingApp();}

void MainWindow::updateImage(cv::Mat image)
{
  cvtColor(image, image, CV_BGR2RGB);
  raspicamImageWidget->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888)));
}

