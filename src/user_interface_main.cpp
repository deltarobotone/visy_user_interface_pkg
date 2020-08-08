#include <QApplication>
#include "main_window.h"

int main(int argc, char** argv) {

    qRegisterMetaType< cv::Mat >("cv::Mat");
    qRegisterMetaType< visy_sorting_app_pkg::GraspData >("visy_sorting_app_pkg::GraspData");

    QApplication app(argc, argv);

    MainWindow mainWindow(argc, argv);

    mainWindow.setFixedSize(480,320);
    mainWindow.showFullScreen();

	return app.exec();
}

