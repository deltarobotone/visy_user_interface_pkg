#include "main_window.h"


MainWindow::MainWindow(int argc, char **argv, QWidget *parent)
  : QWidget(parent),
    dataExchangeThread(argc, argv)
{
  basicLayout = new QVBoxLayout(this);
  buttonGroupboxLayout = new QHBoxLayout;
  buttonGroupbox = new QGroupBox;

  graspDataLayout = new QVBoxLayout;
  graspDataWidget = new QWidget;

  mainGroupbox = new QGroupBox;
  mainGroupboxLayout = new QHBoxLayout;

  infoGroupbox = new QGroupBox;
  infoGroupboxLayout = new QHBoxLayout;

  startButton = new QPushButton;
  stopButton = new QPushButton;
  backButton = new QPushButton;
  nextButton = new QPushButton;
  infoButton = new QPushButton;
  closeButton = new QPushButton;
  updateButton = new QPushButton;

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
  mainGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
  buttonGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");
  infoGroupbox->setStyleSheet("QGroupBox {border-radius: 10px; border: 2px solid rgb(200, 200, 200);}");

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

  closeButton->setIcon(QIcon(":/images/icons/disconnect.png"));
  closeButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  closeButton->setIconSize(btnSize);
  connect(closeButton, &QPushButton::clicked,this,&MainWindow::closeButtonHandle);

  infoButton->setIcon(QIcon(":/images/icons/info.png"));
  infoButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  infoButton->setIconSize(btnSize);
  connect(infoButton, &QPushButton::clicked,this,&MainWindow::infoButtonHandle);

  updateButton->setIcon(QIcon(":/images/icons/refresh.png"));
  updateButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
  updateButton->setIconSize(btnSize);
  connect(updateButton, &QPushButton::clicked,this,&MainWindow::updateButtonHandle);

  QFont font("Arial Rounded MT Bold", 10);

  detectedMetalChips->setText("Detected metalchips: -");
  detectedMetalChips->setFont(font);
  velocity->setText("Velocity (pixel/ses): -");
  velocity->setFont(font);
  lastDetectedPosition->setText("Last position (pixel): -");
  lastDetectedPosition->setFont(font);
  hue->setText("Hue value: -");
  hue->setFont(font);
  colour->setText("Selected colour: -");
  colour->setFont(font);
  latencyMilliseconds->setText("Latency (ms): -");
  latencyMilliseconds->setFont(font);
  latencyDistance->setText("Latency dist. (pixel): -");
  latencyDistance->setFont(font);
  delayTime->setText("Delay until stop (ms): -");
  delayTime->setFont(font);

  graspDataLayout->addWidget(detectedMetalChips);
  graspDataLayout->addWidget(velocity);
  graspDataLayout->addWidget(lastDetectedPosition);
  graspDataLayout->addWidget(hue);
  graspDataLayout->addWidget(colour);
  graspDataLayout->addWidget(latencyMilliseconds);
  graspDataLayout->addWidget(delayTime);
  graspDataWidget->setLayout(graspDataLayout);
  graspDataWidget->setFixedSize(200,200);

  buttonGroupboxLayout->addWidget(startButton);
  buttonGroupboxLayout->addWidget(stopButton);
  buttonGroupboxLayout->addWidget(backButton);
  buttonGroupboxLayout->addWidget(nextButton);
  buttonGroupboxLayout->addWidget(infoButton);
  buttonGroupboxLayout->addWidget(closeButton);
  buttonGroupboxLayout->addWidget(updateButton);

  buttonGroupbox->setLayout(buttonGroupboxLayout);

  raspicamImage->load(":/images/icons/oneicon.png");
  raspicamImageWidget->setFixedSize(200,200);
  raspicamImageWidget->setPixmap(raspicamImage->scaled(200,200,Qt::KeepAspectRatio, Qt::SmoothTransformation));

  mainGroupboxLayout->addWidget(raspicamImageWidget);
  mainGroupboxLayout->addWidget(graspDataWidget);
  mainGroupbox->setLayout(mainGroupboxLayout);

  mainGroupbox->setFixedSize(460,220);
  infoGroupbox->setFixedSize(460,220);
  buttonGroupbox->setFixedSize(460,70);

  basicLayout->addWidget(mainGroupbox);
  basicLayout->addWidget(buttonGroupbox);

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
    mainGroupbox->hide();
    basicLayout->removeWidget(mainGroupbox);
    basicLayout->removeWidget(buttonGroupbox);

    infoGroupbox->show();
    basicLayout->addWidget(infoGroupbox);
    basicLayout->addWidget(buttonGroupbox);
    setLayout(basicLayout);
    this->update();
  }
  else
  {
    info = false;
    infoGroupbox->hide();
    basicLayout->removeWidget(infoGroupbox);
    basicLayout->removeWidget(buttonGroupbox);

    mainGroupbox->show();
    basicLayout->addWidget(mainGroupbox);
    basicLayout->addWidget(buttonGroupbox);
    setLayout(basicLayout);
    this->update();
  }
}

void MainWindow::closeButtonHandle()
{
  this->close();
}

void MainWindow::updateButtonHandle()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Update", "An update overrides all data! If you have no development done on the system you can update without worrys. Please connect the system to the internet. Do you want to update now?", QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    try {
      QProcess *process = new QProcess(this);
      process->start("lxterminal --working-directory=/home/ubuntu/catkin_ws/src/visy_user_interface_pkg/scripts --command './update.sh'");
      this->hide();
      process->waitForFinished(-1);
      process->close();
      reply = QMessageBox::information(this, "Update", "Please reboot the system");
      this->close();
    }
    catch(const std::exception& e){
      this->show();
    }
  }
}

void MainWindow::updateImage(cv::Mat image)
{
  if (info == false)
  {
    cvtColor(image, image, CV_BGR2RGB);
    QPixmap pm = QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888).scaled(200,200,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QTransform trans;
    trans.rotate(90);
    raspicamImageWidget->setPixmap(pm.transformed(trans));
    update();
  }
}

void MainWindow::updateGraspData(visy_sorting_app_pkg::GraspData data)
{
  detectedMetalChips->setText("Detected metalchips: " + QString::number(data.detectedMetalChips));
  velocity->setText("Velocity (pixel/sec): " + QString::number(double(data.velocity),  'g',  3));
  lastDetectedPosition->setText("Last position (pixel): " + QString::number(double(data.lastDetectedPosition),  'g',  3));
  hue->setText("Hue value: " + QString::number(data.hue));
  colour->setText("Selected colour: " + QString::fromStdString(data.colour));
  latencyMilliseconds->setText("Latency (ms): "+ QString::number(double(data.latencyMilliseconds),  'g',  3));
  latencyDistance->setText("Latency dist. (pixel): " + QString::number(double(data.latencyDistance),  'g',  3));
  delayTime->setText("Delay until stop (ms): " + QString::number(double(data.delayTime),  'g',  3));
  update();
}
