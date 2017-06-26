#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "thermostatmodel.h"
#include "qdebug.h"
#include "login.h"
#include "dashboard.h"
#include <QStyleFactory>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <SlidingStackedWidget.h>

MainWindow* MainWindow::instance = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    instance = this;
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::FramelessWindowHint);
    this->move(QPoint(0,0));

    thermostatModel = new ThermostatModel();

    stackedWidget = new SlidingStackedWidget (this);

    Dashboard *dashboard = Dashboard::getInstance();
    dashboard->setModel(thermostatModel);
    stackedWidget->addWidget(Dashboard::getInstance());
    stackedWidget->setRootWidget(Login::getInstance());
    dashboard->setModel(thermostatModel);

    Login *login = Login::getInstance();
    stackedWidget->addWidget(Login::getInstance());
    login->setModel(thermostatModel);

    stackedWidget->setCurrentWidget(login);
    setCentralWidget(stackedWidget);
    stackedWidget->show();

    /*QObject::connect(thermostatModel, SIGNAL(temperatureChanged(float value)),
                         dashboard, SLOT(updateTemperatureDisplay(float temperature)));*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::setModel(ThermostatModel *newthermostatModel)
{
    this->thermostatModel = newthermostatModel;
    qDebug() << Q_FUNC_INFO <<"Assigned thermostat model" << this->thermostatModel;
    return;
}*/

SlidingStackedWidget* MainWindow::getStakedWidget()
{
    return stackedWidget;
}

MainWindow* MainWindow::getInstance() {

    if(!instance) {
        instance = new MainWindow();
        return instance;
    }
    else {
        return instance;
    }
}
