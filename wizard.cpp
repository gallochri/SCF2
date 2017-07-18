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
    //Set form fields
    ui->hostnameLineEdit->setText(host.isEmpty() ? "" : host);
    ui->databaseLineEdit->setText(dbs.isEmpty() ? "" : dbs);
    ui->usernameLineEdit->setText(user.isEmpty() ? "" : user);
    ui->passwordLineEdit->setText(pass.isEmpty() ? "" : pass);

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

void Wizard::on_testConnection_pressed()
{
    {
        config conf;

        //Create string for test connection with edited fields
        QString driver = ui->driverComboBox->currentText();
        int driverIndex = ui->driverComboBox->currentIndex();
        QString database = ui->databaseLineEdit->text();
        if (driverIndex == 1){
            database = conf.configPath()+"/"+database;
            qDebug() << __func__ << ":database path=" << database;
        }
        //Test connection to DB with edited fields
        QSqlDatabase db = QSqlDatabase::addDatabase(driver,"testConnection");
        db.setHostName(ui->hostnameLineEdit->text());
        db.setDatabaseName(database);
        db.setUserName(ui->usernameLineEdit->text());
        db.setPassword(ui->passwordLineEdit->text());


        if (!db.open() || database.isEmpty()){
            qDebug() << __func__ << ":Connection problem!";
            ui->connectionStatusResult->setStyleSheet(
                        "QLineEdit { background-color : red;}");
            ui->connectionStatusResult->setText("Connection problem!");
            /**testConnection->setStyleSheet(
                        "QPushButton { background-color : red;}");
            connectionStatusLabel->setText("<b>Connection problem!</b>");**/
        } else {
            qDebug() << __func__ << ":Connection OK!";
            /**
            testConnection->setStyleSheet(
                        "QPushButton { background-color : green;}");
            connectionStatusLabel->setText("<b>Connection successfull!</b>");
            **/
            if (driverIndex == 1){
                QString dbFilePath = database;
                QFileInfo dbFile(dbFilePath);
                if (!dbFile.isFile()){
                    QFile *dbFile = new QFile(dbFilePath);
                    dbFile->open(QIODevice::ReadWrite | QIODevice::Text);
                    dbFile->close();
                }
            }
            /**
            //Connection to DB ok, now test DB tables
            //TODO add more tables tests
            if (db.tables().contains("testata_listino")){
                createDB->setStyleSheet(
                            "QPushButton { background-color : green;}");
                dbStatusLabel->setText("<b>DB tables OK!</b>");
            } else {
                createDB->setStyleSheet(
                            "QPushButton { background-color : red;}");
                dbStatusLabel->setText("<b>Tables not present!</b>");
                createDB->setDisabled(false);
            }**/
        }
        //Close DB and destroy connection
        db.close();
    }
    QSqlDatabase::removeDatabase("testConnection");

}
