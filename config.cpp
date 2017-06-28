#include "config.h"

config::config()
{
    QSettings settings;
    if (!QFile(QSettings().fileName()).exists())
    {
        settings.beginGroup(KEY_DB);
        settings.setValue(KEY_DBDRIVER, "");
        settings.setValue(KEY_DBHOST, "");
        settings.setValue(KEY_DBNAME, "");
        settings.setValue(KEY_DBUSER, "");
        settings.setValue(KEY_DBPWD, "");
        settings.endGroup();
    }
}

QString config::loadConfig(QString key)
{
    QSettings settings;
    settings.beginGroup(KEY_DB);
    QString configValue = settings.value(key).toString();
    settings.endGroup();
    return configValue;
}

QString config::configPath()
{
    QSettings settings;
    QFileInfo file(settings.fileName());
    QString path = file.absolutePath();
    return path;
}

void config::writeConfig(QString key, QString val)
{
    QSettings settings;
    settings.beginGroup(KEY_DB);
    settings.setValue(key,val);
    settings.endGroup();
}

bool config::createConnection()
{
    {
        //Read qsettings file for DB connection
        qDebug() << __func__<< ":Load config";
        config conf;
        QString driver = conf.loadConfig(KEY_DBDRIVER);
        if (driver.isEmpty())
        {
            conf.writeConfig(KEY_DBDRIVER,"QSQLITE");
            driver = conf.loadConfig(KEY_DBDRIVER);
        }
        QString host = conf.loadConfig(KEY_DBHOST);
        QString dbs = conf.loadConfig(KEY_DBNAME);
        if (driver == "QSQLITE"){
            dbs = conf.configPath()+"/"+dbs;
        }
        QString user = conf.loadConfig(KEY_DBUSER);
        QString pass = conf.loadConfig(KEY_DBPWD);

        QSqlDatabase db = QSqlDatabase::addDatabase(driver, "mainConnection");
        db.setHostName(host);
        db.setDatabaseName(dbs);
        db.setUserName(user);
        db.setPassword(pass);
        if (!db.open() || dbs.isEmpty()) {
            QMessageBox::critical(0,"Cannot open database",
                                  "Unable to establish a database"
                                  "connection.\n"
                                  "Click Ok to start config Wizard.",
                                  QMessageBox::Ok);
            return false;
        }
        db.close();
    }
    QSqlDatabase::removeDatabase("mainConnection");
    return true;
}
