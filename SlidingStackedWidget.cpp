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
    widgetStack.push(widget);
    return QStackedWidget::addWidget(widget);
}


void SlidingStackedWidget::setRootWidget(QWidget *widget){
    rootWidget = widget;
    qDebug() << Q_FUNC_INFO <<" " << widgetStack;
}

void SlidingStackedWidget::setPreviousWidget(){
    if (!widgetStack.isEmpty()){
        poppedWidget = widgetStack.pop();
        if (!widgetStack.isEmpty())
            poppedWidget = widgetStack.pop();
        qDebug() << Q_FUNC_INFO <<"°°°°°°°°°°°popped°°°°°°°°°° " << widgetStack;
        QStackedWidget::setCurrentWidget(poppedWidget);
    }
    else {
        widgetStack.clear();
        QStackedWidget::setCurrentWidget(rootWidget);
        qDebug() << Q_FUNC_INFO <<"°°°°°°°°°°°default°°°°°°°°°° " << rootWidget;
    }
}
