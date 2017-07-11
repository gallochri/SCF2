#include "wizard.h"
#include "ui_wizard.h"
#include "config.h"

Wizard::Wizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Wizard)
{
    ui->setupUi(this);

    setPixmap(QWizard::WatermarkPixmap,
              QPixmap(":/watermark/images/watermark/yattaman.jpg"));
    setPixmap(QWizard::LogoPixmap,
              QPixmap(":/icon/images/icon/logo.png"));

    setWindowTitle(QString(APP_NAME).replace("_"," "));

    //Read qsettings file for DB connection
    config conf;
    QString driver = conf.loadConfig(KEY_DBDRIVER);
    QString host = conf.loadConfig(KEY_DBHOST);
    QString dbs = conf.loadConfig(KEY_DBNAME);
    QString user = conf.loadConfig(KEY_DBUSER);
    QString pass = conf.loadConfig(KEY_DBPWD);

    //Set drivers combobox list
    QStringList drivers;
    drivers << "QMYSQL" << "QSQLITE";
    int driverIndex = drivers.indexOf(driver);
    ui->driverComboBox->addItems(drivers);
    ui->driverComboBox->setCurrentIndex(driverIndex);
    if (driver.isEmpty())
    {
        ui->driverComboBox->setCurrentIndex(1);
    }

    //TODO
    //Set hostname
    if (host.isEmpty())
    {
        ui->hostnameLineEdit->setPlaceholderText("www.example.com");
    }
    ui->hostnameLineEdit->setText(host);

    //Set database name
    if (dbs.isEmpty()){
        ui->databaseLineEdit->setPlaceholderText("My_database");
    }
    ui->databaseLineEdit->setText(dbs);

    //Set user name
    if (!user.isEmpty()){
        ui->usernameLineEdit->setText(user);
    }
    ui->usernameLineEdit->setText(user);
    //Set password
    if (!pass.isEmpty()){
        ui->passwordLineEdit->setText(pass);
    }
}

Wizard::~Wizard()
{
    delete ui;
}
