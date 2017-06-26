#include "dashboard.h"
#include "ui_dashboard.h"
#include "mainwindow.h"

Dashboard* Dashboard::instance = 0;

Dashboard::Dashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    instance = this;
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::FramelessWindowHint);
    this->move(QPoint(0,0));
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::setModel(ThermostatModel *newthermostatModel)
{
    this->thermostatModel = newthermostatModel;
    qDebug() << Q_FUNC_INFO <<"Assigned thermostat model" << this->thermostatModel;
    return;
}

Dashboard* Dashboard::getInstance() {
    if(!instance) {
        instance = new Dashboard();
        return instance;
    }
    else {
        return instance;
    }
}

void Dashboard::updateTemperatureDisplay(float temperature){
    ui->lTempValue->setText(QString::number(temperature));
    return;
}

void Dashboard::on_pbLogoff_clicked()
{
    MainWindow::getInstance()->getStakedWidget()->setCurrentWidget(Login::getInstance());
}

void Dashboard::on_pbQuit_clicked()
{
    QApplication::quit();
}

void Dashboard::on_pbPlus_clicked()
{
    thermostatModel->getCurrentTemperature();
    thermostatModel->incrementTemperature();
}

void Dashboard::on_pbMinus_clicked()
{
    thermostatModel->decrementTemperature();
}
