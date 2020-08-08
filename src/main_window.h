#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QtWidgets>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextStream>
#include <QLineEdit>
#include <QPalette>
#include <QIcon>
#include "data_exchange_thread.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget * parent = 0);

    Q_SLOT void updateImage(cv::Mat image);
    Q_SLOT void updateGraspData(visy_sorting_app_pkg::GraspData data);
private:
    Q_SLOT void startButtonHandle();
    Q_SLOT void stopButtonHandle();
    Q_SLOT void backButtonHandle();
    Q_SLOT void nextButtonHandle();
    Q_SLOT void infoButtonHandle();
    Q_SLOT void closeButtonHandle();

    uint info = false;

    QVBoxLayout *basicLayout;

    QGroupBox *buttonGroupbox;
    QHBoxLayout *buttonGroupboxLayout;

    QWidget *graspDataWidget;
    QVBoxLayout *graspDataLayout;

    QPixmap *raspicamImage;
    QLabel *raspicamImageWidget;

    QGroupBox *mainGroupbox;
    QHBoxLayout *mainGroupboxLayout;

    QGroupBox *infoGroupbox;
    QHBoxLayout *infoGroupboxLayout;

    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *backButton;
    QPushButton *nextButton;
    QPushButton *infoButton;
    QPushButton *closeButton;

    QLabel *detectedMetalChips;
    QLabel *velocity;
    QLabel *lastDetectedPosition;
    QLabel *hue;
    QLabel *colour;
    QLabel *latencyMilliseconds;
    QLabel *latencyDistance;
    QLabel *delayTime;

    DataExchangeThread dataExchangeThread;

    void createLayout();
};

#endif

