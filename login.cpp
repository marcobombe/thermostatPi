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
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->messageLabel->setText("");ui->messageLabel->setText("");

    QImage myImage;
    myImage.load("C:/workspace/thermostatPi/src/images/y.png");

    QLabel myLabel;
    myLabel.move(QPoint(10,10));
    myLabel.setPixmap(QPixmap::fromImage(myImage));
    myLabel.setVisible(true);
    myLabel.show();

    QLabel myLabel2;
    myLabel2.setText("FFFFF");
    myLabel2.setVisible(true);
    myLabel2.show();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    ui->messageLabel->setText("");

    if (verifyPassword())
        MainWindow::getInstance()->getStakedWidget()->setCurrentWidget(Dashboard::getInstance());
    else
        ui->messageLabel->setText(tr("Wrong password."));
}

void Login::setModel(ThermostatModel *newthermostatModel)
{
    this->thermostatModel = newthermostatModel;
    return;
}

bool Login::verifyPassword()
{
    qDebug() << Q_FUNC_INFO << ui->passwordLineEdit->text();
    if (ui->passwordLineEdit->text().compare("123")==0)
        return true;
    else
        return false;
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
