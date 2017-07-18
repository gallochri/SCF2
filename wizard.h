#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>

namespace Ui {
class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT

public:
    explicit Wizard(QWidget *parent = 0);
    ~Wizard();

private slots:

    void on_driverComboBox_currentIndexChanged(int index);

    void on_showPasswordCheck_stateChanged(int arg1);

    void on_testConnection_pressed();

private:
    Ui::Wizard *ui;
};

#endif // WIZARD_H
