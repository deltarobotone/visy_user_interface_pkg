#include <QApplication>
#include "main_window.h"

int main(int argc, char** argv) {

    qRegisterMetaType< cv::Mat >("cv::Mat");

    QApplication app(argc, argv);

    MainWindow mainWindow(argc, argv);

    //mainWindow.showFullScreen();

	return app.exec();
}

