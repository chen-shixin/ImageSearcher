#include "MainWindow/MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QObject::tr("ͼ�����ϵͳ"));
    MainWindow w;
    w.show();

    return a.exec();
}
