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
  backButton = new QPushButton;
  nextButton = new QPushButton;

  raspicamImage = new QPixmap;
  raspicamImageWidget = new QLabel;

  createLayout();

  setStyleSheet("background-color:white;");

  show();

  setWindowTitle(tr("Main Window"));

  connect(&dataExchangeThread, &DataExchangeThread::newImage, this, &MainWindow::updateImage);
  dataExchangeThread.init();
}

void MainWindow::createLayout()
{
  QSize btnSize (40, 40);
  startButton->setIcon(QIcon(":/images/icons/play.png"));
  startButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  startButton->setIconSize(btnSize);
  connect(startButton, &QPushButton::clicked,this,&MainWindow::startButtonHandle);

  stopButton->setIcon(QIcon(":/images/icons/stop.png"));
  stopButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  stopButton->setIconSize(btnSize);
  connect(stopButton, &QPushButton::clicked,this,&MainWindow::stopButtonHandle);

  backButton->setIcon(QIcon(":/images/icons/back.png"));
  backButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  backButton->setIconSize(btnSize);
  connect(backButton, &QPushButton::clicked,this,&MainWindow::backButtonHandle);

  nextButton->setIcon(QIcon(":/images/icons/next.png"));
  nextButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  nextButton->setIconSize(btnSize);
  connect(nextButton, &QPushButton::clicked,this,&MainWindow::nextButtonHandle);

  buttonRowLayout->addWidget(startButton);
  buttonRowLayout->addWidget(stopButton);
  buttonRowLayout->addWidget(backButton);
  buttonRowLayout->addWidget(nextButton);

  buttonRow->setLayout(buttonRowLayout);

  raspicamImage->load(":/images/icons/oneicon.png");
  raspicamImageWidget->setPixmap(raspicamImage->scaled(200,200,Qt::KeepAspectRatio, Qt::SmoothTransformation));

  basicLayout->addWidget(raspicamImageWidget,Qt::AlignCenter);
  basicLayout->addWidget(buttonRow);

  setLayout(basicLayout);
}

void MainWindow::startButtonHandle(){dataExchangeThread.startSortingApp();}
void MainWindow::stopButtonHandle(){dataExchangeThread.stopSortingApp();}
void MainWindow::backButtonHandle(){dataExchangeThread.changeImageNext();}
void MainWindow::nextButtonHandle(){dataExchangeThread.changeImageBack();}
void MainWindow::updateImage(cv::Mat image)
{
  cvtColor(image, image, CV_BGR2RGB);
  //cv::resize(image, image, cv::Size(int(image.cols * 0.75),int(image.rows * 0.75)), 0, 0, CV_INTER_LINEAR);
  raspicamImageWidget->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888).scaled(200,200,Qt::KeepAspectRatio, Qt::SmoothTransformation)));
  raspicamImageWidget->update();
  raspicamImageWidget->repaint();
  this->repaint();
  this->update();
  QApplication::processEvents();
}

