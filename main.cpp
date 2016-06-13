#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ddview.h"
#include "ddquickview.h"
#include "drivermodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    YbQuickView view;
    view.setFlags(Qt::FramelessWindowHint);
    view.setHasMouse(false);
#ifdef USE_YOUZAN
    view.setMaximumWidth(500);
    view.setMaximumHeight(460);
#ifdef Q_OS_MACX
    view.setSourceAndRegsiterObj(QUrl::fromLocalFile("../../../youzan/main.qml"));
#else
    view.setSourceAndRegsiterObj(QUrl::fromLocalFile("youzan/main.qml"));
#endif
#elif USE_DRIVER
#ifdef Q_OS_MACX
    //测试C++的Model在QML中的使用
    DriverModel model;
    model.addDriverItem(DriverItem("Wolf", "http://download.easyicon.net/png/1174391/32/","Hello World"));
    model.addDriverItem(DriverItem("Bear", "http://download.easyicon.net/png/1174390/32/","Large Big Data"));
    model.addDriverItem(DriverItem("Quoll", "http://download.easyicon.net/png/1174341/32/","aaaaaaaaaaaaaa"));
    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("driverModel", &model);

    view.setSourceAndRegsiterObj(QUrl::fromLocalFile("../../../Driver/DDDriverView.qml"));
#else
    view.setSourceAndRegsiterObj(QUrl::fromLocalFile("Driver/DDDriverView.qml"));
#endif
#else
    view.setSourceAndRegsiterObj(QUrl::fromLocalFile("../../../XunLei/DDXunLei.qml"));
#endif
    view.show();
    return app.exec();
}
