#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "dashboard.h"

Login* Login::instance = 0;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    instance = this;
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::FramelessWindowHint);
    this->move(QPoint(0,0));
    ui->lineEdit->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    MainWindow::getInstance()->getStakedWidget()->setCurrentWidget(Dashboard::getInstance());
}

void Login::setModel(ThermostatModel *newthermostatModel)
{
    this->thermostatModel = newthermostatModel;
    return;
}

Login* Login::getInstance() {
    if(!instance) {
        instance = new Login();
        return instance;
    }
    else {
        return instance;
    }
}
