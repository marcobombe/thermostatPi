#include "thermostatmodel.h"
#include <dbmanager.h>
#include "QTimer.h"
#include <QDebug>

ThermostatModel::ThermostatModel()
{
    qDebug() << Q_FUNC_INFO <<"Created thermostat model (" << this << ")";
    temperature = 1.0;
    qDebug() << Q_FUNC_INFO <<"Initial temperature is " << temperature;
    dbm.openDB("model.db");
    dbm.createTables();
}

float ThermostatModel::getCurrentTemperature()
{
   qDebug() << Q_FUNC_INFO <<"Temperature from model (" << this << ") is" << temperature;
   return temperature;
}

void ThermostatModel::incrementTemperature()
{
    qDebug() << Q_FUNC_INFO <<"Incremented temperature from model (" << this << ") is" << temperature;
    temperature = temperature + 0.5;
    emit temperatureChanged(temperature);
    return;
}

void ThermostatModel::decrementTemperature()
{
    qDebug() << Q_FUNC_INFO <<"Decremented temperature from model (" << this << ") is" << temperature;
    temperature = temperature - 0.5;
    emit temperatureChanged(temperature);
    return;
}

ThermostatModel::~ThermostatModel()
{
    temperature = 1.0;
}
