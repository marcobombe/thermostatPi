#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QStackedWidget>
#include <thermostatmodel.h>
#include <SlidingStackedWidget.h>
#include <login.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    SlidingStackedWidget *stackedWidget;

    void setModel(ThermostatModel *newthermostatModel);
    SlidingStackedWidget* getStakedWidget();
    static MainWindow* getInstance();
    static MainWindow* instance;

    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    ThermostatModel *thermostatModel;
};

#endif // MAINWINDOW_H
