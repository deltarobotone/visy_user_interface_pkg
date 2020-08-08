#include "main_window.h"


MainWindow::MainWindow(int argc, char **argv, QWidget *parent)
  : QWidget(parent),
    dataExchangeThread(argc, argv)
{
  basicLayout = new QVBoxLayout(this);
  buttonRowLayout = new QHBoxLayout;
  buttonRow = new QWidget;

  infoLayout = new QVBoxLayout;
  infoWidget = new QWidget;

  startButton = new QPushButton;
  stopButton = new QPushButton;
  backButton = new QPushButton;
  nextButton = new QPushButton;
  infoButton = new QPushButton;

  detectedMetalChips = new QLabel;
  velocity = new QLabel;
  lastDetectedPosition = new QLabel;
  hue = new QLabel;
  colour = new QLabel;
  latencyMilliseconds = new QLabel;
  latencyDistance = new QLabel;
  delayTime = new QLabel;

  raspicamImage = new QPixmap;
  raspicamImageWidget = new QLabel;

  createLayout();

  setStyleSheet("background-color:white;");

  show();

  setWindowTitle(tr("Main Window"));

  connect(&dataExchangeThread, &DataExchangeThread::newImage, this, &MainWindow::updateImage);
  connect(&dataExchangeThread, &DataExchangeThread::newGraspData, this, &MainWindow::updateGraspData);
  dataExchangeThread.init();
}

void MainWindow::createLayout()
{
  QSize btnSize (30, 30);
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

  infoButton->setIcon(QIcon(":/images/icons/info.png"));
  infoButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  infoButton->setIconSize(btnSize);
  connect(infoButton, &QPushButton::clicked,this,&MainWindow::infoButtonHandle);

  detectedMetalChips->setText("Detected metalchips: -");
  velocity->setText("Calculated velocity: -");
  lastDetectedPosition->setText("Last detected position: -");
  hue->setText("Hue value: -");
  colour->setText("Selected colour: -");
  latencyMilliseconds->setText("Latency milliseconds: -");
  latencyDistance->setText("Latency distance: -");
  delayTime->setText("Delay to stop conveyor: -");

  infoLayout->addWidget(detectedMetalChips);
  infoLayout->addWidget(velocity);
  infoLayout->addWidget(lastDetectedPosition);
  infoLayout->addWidget(hue);
  infoLayout->addWidget(colour);
  infoLayout->addWidget(latencyMilliseconds);
  infoLayout->addWidget(delayTime);
  infoWidget->setLayout(infoLayout);
  infoWidget->setFixedSize(220,220);

  buttonRowLayout->addWidget(startButton);
  buttonRowLayout->addWidget(stopButton);
  buttonRowLayout->addWidget(backButton);
  buttonRowLayout->addWidget(nextButton);
  buttonRowLayout->addWidget(infoButton);

  buttonRow->setLayout(buttonRowLayout);

  raspicamImage->load(":/images/icons/oneicon.png");
  raspicamImageWidget->setFixedSize(220,220);
  raspicamImageWidget->setPixmap(raspicamImage->scaled(200,200,Qt::KeepAspectRatio, Qt::SmoothTransformation));
  basicLayout->addWidget(raspicamImageWidget,Qt::AlignCenter);

  basicLayout->addWidget(buttonRow);

  setLayout(basicLayout);
}

void MainWindow::startButtonHandle(){dataExchangeThread.startSortingApp();}
void MainWindow::stopButtonHandle(){dataExchangeThread.stopSortingApp();}
void MainWindow::backButtonHandle(){dataExchangeThread.changeImageBack();}
void MainWindow::nextButtonHandle(){dataExchangeThread.changeImageNext();}
void MainWindow::infoButtonHandle()
{
  if (info == false)
  {
    info = true;
    raspicamImageWidget->hide();
    basicLayout->removeWidget(raspicamImageWidget);
    basicLayout->removeWidget(buttonRow);

    infoWidget->show();
    basicLayout->addWidget(infoWidget);
    basicLayout->addWidget(buttonRow);
    setLayout(basicLayout);
    this->update();
  }
  else
  {
    info = false;
    infoWidget->hide();
    basicLayout->removeWidget(infoWidget);
    basicLayout->removeWidget(buttonRow);

    raspicamImageWidget->show();
    basicLayout->addWidget(raspicamImageWidget);
    basicLayout->addWidget(buttonRow);
    setLayout(basicLayout);
    this->update();
  }
}

void MainWindow::updateImage(cv::Mat image)
{
  if (info == false)
  {
    cvtColor(image, image, CV_BGR2RGB);
    raspicamImageWidget->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888).scaled(200,200,Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    update();
  }
}

void MainWindow::updateGraspData(visy_sorting_app_pkg::GraspData data)
{
  detectedMetalChips->setText("Detected metalchips: " + QString::number(data.detectedMetalChips));
  velocity->setText("Calculated velocity: " + QString::number(double(data.velocity)));
  lastDetectedPosition->setText("Last detected position: " + QString::number(double(data.lastDetectedPosition)));
  hue->setText("Hue value: " + QString::number(data.hue));
  colour->setText("Selected colour: " + QString::fromStdString(data.colour));
  latencyMilliseconds->setText("Latency milliseconds: "+ QString::number(double(data.latencyMilliseconds)));
  latencyDistance->setText("Latency distance: " + QString::number(double(data.latencyDistance)));
  delayTime->setText("Delay to stop conveyor: " + QString::number(double(data.delayTime)));
  update();
}
