#ifndef THERMOSTATMODEL_H
#define THERMOSTATMODEL_H

#include <QObject>
#include <QWidget>
#include <dbmanager.h>


class ThermostatModel
{
public:
    ThermostatModel();
    ~ThermostatModel();
    float getCurrentTemperature();
    void incrementTemperature();
    void decrementTemperature();

private:
    float temperature;
    DbManager dbm;

signals:
    void temperatureChanged(float value);
};

#endif // THERMOSTATMODEL_H
