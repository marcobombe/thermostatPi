#ifndef SLIDINGSTACKEDWIDGET_H
#define SLIDINGSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QWidget>
#include <QDebug>
#include <QStack>

class SlidingStackedWidget : public QStackedWidget {
    Q_OBJECT

public:
    // The Constructor and Destructor
    SlidingStackedWidget(QWidget *parent);
    ~SlidingStackedWidget(void);

    int addWidget(QWidget *widget);
    void setCurrentWidget(QWidget *widget);
    int setRootWidget(QWidget *widget);
    void setPreviousWidget();

    QWidget *m_mainwindow;
    QWidget *rootWidget;
    QWidget *poppedWidget;

    QStack<QWidget*> widgetStack;

};

#endif // SLIDINGSTACKEDWIDGET_H
