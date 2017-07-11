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

    //Set hostname
    if (!host.isEmpty())
    {
        ui->hostnameLineEdit->setText(host);
    }

    //Set database name
    if (!dbs.isEmpty()){
        ui->databaseLineEdit->setText(dbs);
    }

    //Set user name
    if (!user.isEmpty()){
        ui->usernameLineEdit->setText(user);
    }

    //Set password
    if (!pass.isEmpty()){
        ui->passwordLineEdit->setText(pass);
    }

    /**
    registerField("driver",ui->driverComboBox);
    setField("driver",driverIndex);
    registerField("hostname", ui->hostnameLineEdit);
    registerField("database", ui->databaseLineEdit);
    registerField("username", ui->usernameLineEdit);
    registerField("password", ui->passwordLineEdit);
**/
}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::on_driverComboBox_currentIndexChanged(int index)
{
    if (index == 1)
    {
        ui->hostnameLineEdit->setDisabled(1);
        ui->usernameLineEdit->setDisabled(1);
        ui->passwordLineEdit->setDisabled(1);
        ui->showPasswordCheck->setDisabled(1);
    } else {
        ui->hostnameLineEdit->setEnabled(1);
        ui->usernameLineEdit->setEnabled(1);
        ui->passwordLineEdit->setEnabled(1);
        ui->showPasswordCheck->setEnabled(1);
    }

}

void Wizard::on_showPasswordCheck_stateChanged(int arg1)
{
    ui->passwordLineEdit->setEchoMode(arg1 == 2 ?
                                          QLineEdit::Normal :
                                          QLineEdit::Password);
}
