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

void Dashboard::on_pushButton_clicked()
{
    QApplication::quit();
}

void Dashboard::on_pushButton_2_clicked()
{
    MainWindow::getInstance()->getStakedWidget()->setPreviousWidget();
}
