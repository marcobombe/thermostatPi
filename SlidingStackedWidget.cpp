#include "SlidingStackedWidget.h"

SlidingStackedWidget::SlidingStackedWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    if (parent != 0) {
        m_mainwindow = parent;
    }
    else {
        m_mainwindow = this;
        qDebug() << "ATTENTION: untested mainwindow case !";
    }
    // parent should not be 0; not tested for any other case yet !!
    widgetStack.clear();
}

SlidingStackedWidget::~SlidingStackedWidget() {
}

int SlidingStackedWidget::addWidget(QWidget *widget){
    qDebug() << Q_FUNC_INFO <<" " << widgetStack;
    //widgetStack.push(widget);
    return QStackedWidget::addWidget(widget);
}

void SlidingStackedWidget::setCurrentWidget(QWidget *widget){
    widgetStack.push(widget);
    qDebug() << Q_FUNC_INFO <<" " << widgetStack;
    QStackedWidget::setCurrentWidget(widget);
}

int SlidingStackedWidget::setRootWidget(QWidget *widget){
    rootWidget = widget;
    qDebug() << Q_FUNC_INFO <<" " << widgetStack;
    return 1;
}

void SlidingStackedWidget::setPreviousWidget(){
    if (!widgetStack.isEmpty()){
        if (!widgetStack.isEmpty())
            poppedWidget = widgetStack.pop();
        if (!widgetStack.isEmpty())
            poppedWidget = widgetStack.pop();
        qDebug() << Q_FUNC_INFO <<" " << widgetStack;
        QStackedWidget::setCurrentWidget(poppedWidget);
    }
    else {
        widgetStack.clear();
        QStackedWidget::setCurrentWidget(rootWidget);
        qDebug() << Q_FUNC_INFO <<" " << rootWidget;
    }
}
