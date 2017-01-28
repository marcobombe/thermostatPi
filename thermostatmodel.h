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
    void incrementTemperature(QString name);

private:
    float temperature;
    DbManager dbm;
};

#endif // THERMOSTATMODEL_H
