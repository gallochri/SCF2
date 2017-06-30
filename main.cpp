#include <QApplication>
#include <QDebug>

#include "mainwindow.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Set app name and organization
    qApp->setApplicationVersion(APP_VERSION);
    qApp->setApplicationName(QString(APP_NAME).replace("_"," "));
    qApp->setOrganizationName("gallochri.com");
    qApp->setOrganizationDomain("www.gallochri.com");

    //Create mainwindow
    MainWindow *mainWin = new MainWindow;
    mainWin->setWindowTitle (QString(APP_NAME).replace("_"," "));
    mainWin->show();

    //Create config
    config conf;

    //Test DB connection and start wizard if necessary
    if (!conf.createConnection()){
        qDebug() << __func__ << ":Connection problem!";
        mainWin->startWizard(mainWin);
    } else {
        qDebug() << __func__ <<":Connection successfull!";
    }
    return a.exec();
}
