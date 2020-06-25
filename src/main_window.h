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
private:
    Q_SLOT void startButtonHandle();
    Q_SLOT void stopButtonHandle();
    Q_SLOT void backButtonHandle();
    Q_SLOT void nextButtonHandle();

    QVBoxLayout *basicLayout;

    QWidget *buttonRow;
    QHBoxLayout *buttonRowLayout;

    QPixmap *raspicamImage;
    QLabel *raspicamImageWidget;

    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *backButton;
    QPushButton *nextButton;

    DataExchangeThread dataExchangeThread;

    void createLayout();
};

#endif

