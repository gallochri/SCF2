#include "wizard.h"
#include "ui_wizard.h"

Wizard::Wizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Wizard)
{
    ui->setupUi(this);
    setWindowTitle(QString(APP_NAME).replace("_"," "));
}

Wizard::~Wizard()
{
    delete ui;
}
