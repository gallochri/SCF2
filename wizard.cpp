#include "wizard.h"
#include "ui_wizard.h"

Wizard::Wizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Wizard)
{
    ui->setupUi(this);

    ui->IntroPage->setPixmap(BannerPixmap,QPixmap(":/icon/images/icon/logo.png"));
    ui->DbConfigPage->setPixmap(LogoPixmap,QPixmap(":/icon/images/icon/logo.png"));
    setPixmap(QWizard::WatermarkPixmap,
              QPixmap(":/watermark/images/watermark/yattaman.jpg"));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/icon/images/icon/logo.png"));
    setWindowTitle(QString(APP_NAME).replace("_"," "));
}

Wizard::~Wizard()
{
    delete ui;
}
