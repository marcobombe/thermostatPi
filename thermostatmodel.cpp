#include "thermostatmodel.h"
#include <dbmanager.h>
#include "QTimer.h"

ThermostatModel::ThermostatModel()
{
    temperature = 1.0;
    dbm.openDB("model.db");
    dbm.createTable();
}

float ThermostatModel::getCurrentTemperature()
{
   return temperature;
}

void ThermostatModel::incrementTemperature(QString name)
{
   temperature = temperature + 10;
   dbm.addUser(name, "ps");
   dbm.printAllUsers();
   return;
}

ThermostatModel::~ThermostatModel()
{
    temperature = 1.0;
}
