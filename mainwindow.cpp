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

    stackedWidget = new SlidingStackedWidget (this);

    Dashboard *dashboard = Dashboard::getInstance();
    stackedWidget->addWidget(Dashboard::getInstance());
    stackedWidget->setRootWidget(Dashboard::getInstance());
    dashboard->setModel(thermostatModel);

    Login *login = Login::getInstance();
    stackedWidget->addWidget(Login::getInstance());
    login->setModel(thermostatModel);

    stackedWidget->setCurrentWidget(login);
    setCentralWidget(stackedWidget);
    stackedWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModel(ThermostatModel *newthermostatModel)
{
    this->thermostatModel = newthermostatModel;
    return;
}

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
