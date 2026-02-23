// SPDX-License-Identifier: GPL-2.0-or-later
#include <MqttSettings.h>
#include <battery/pylontech/Stats.h>
#include "MqttHandleInverter.h"

namespace Batteries::Pylontech {

void Stats::getLiveViewData(JsonVariant& root) const
{
    ::Batteries::Stats::getLiveViewData(root);

    // values go into the "Status" card of the web application
    addLiveViewValue(root, "chargeVoltage", _chargeVoltage, "V", 1);
    addLiveViewValue(root, "dischargeVoltageLimitation", _dischargeVoltageLimitation, "V", 1);
    addLiveViewValue(root, "stateOfHealth", _stateOfHealth, "%", 0);
    addLiveViewValue(root, "temperature", _temperature, "°C", 1);
    addLiveViewValue(root, "modules", _moduleCount, "", 0);

    addLiveViewTextValue(root, "chargeEnabled", (_chargeEnabled?"yes":"no"));
    addLiveViewTextValue(root, "dischargeEnabled", (_dischargeEnabled?"yes":"no"));
    addLiveViewTextValue(root, "chargeImmediately", (_chargeImmediately?"yes":"no"));

    // alarms and warnings go into the "Issues" card of the web application
    addLiveViewWarning(root, "highCurrentDischarge", _warningHighCurrentDischarge);
    addLiveViewAlarm(root, "overCurrentDischarge", _alarmOverCurrentDischarge);

    addLiveViewWarning(root, "highCurrentCharge", _warningHighCurrentCharge);
    addLiveViewAlarm(root, "overCurrentCharge", _alarmOverCurrentCharge);

    addLiveViewWarning(root, "lowTemperature", _warningLowTemperature);
    addLiveViewAlarm(root, "underTemperature", _alarmUnderTemperature);

    addLiveViewWarning(root, "highTemperature", _warningHighTemperature);
    addLiveViewAlarm(root, "overTemperature", _alarmOverTemperature);

    addLiveViewWarning(root, "lowVoltage", _warningLowVoltage);
    addLiveViewAlarm(root, "underVoltage", _alarmUnderVoltage);

    addLiveViewWarning(root, "highVoltage", _warningHighVoltage);
    addLiveViewAlarm(root, "overVoltage", _alarmOverVoltage);

    addLiveViewWarning(root, "bmsInternal", _warningBmsInternal);
    addLiveViewAlarm(root, "bmsInternal", _alarmBmsInternal);
}

auto inv = Hoymiles.getInverterByPos(1);
const String subtopic = inv->serialString();

void Stats::mqttPublish() const
{
    ::Batteries::Stats::mqttPublish();

    MqttSettings.publish(subtopic + "battery/settings/chargeVoltage", String(_chargeVoltage));
    MqttSettings.publish(subtopic + "battery/settings/dischargeVoltageLimitation", String(_dischargeVoltageLimitation));
    MqttSettings.publish(subtopic + "battery/stateOfHealth", String(_stateOfHealth));
    MqttSettings.publish(subtopic + "battery/temperature", String(_temperature));
    MqttSettings.publish(subtopic + "battery/alarm/overCurrentDischarge", String(_alarmOverCurrentDischarge));
    MqttSettings.publish(subtopic + "battery/alarm/overCurrentCharge", String(_alarmOverCurrentCharge));
    MqttSettings.publish(subtopic + "battery/alarm/underTemperature", String(_alarmUnderTemperature));
    MqttSettings.publish(subtopic + "battery/alarm/overTemperature", String(_alarmOverTemperature));
    MqttSettings.publish(subtopic + "battery/alarm/underVoltage", String(_alarmUnderVoltage));
    MqttSettings.publish(subtopic + "battery/alarm/overVoltage", String(_alarmOverVoltage));
    MqttSettings.publish(subtopic + "battery/alarm/bmsInternal", String(_alarmBmsInternal));
    MqttSettings.publish(subtopic + "battery/warning/highCurrentDischarge", String(_warningHighCurrentDischarge));
    MqttSettings.publish(subtopic + "battery/warning/highCurrentCharge", String(_warningHighCurrentCharge));
    MqttSettings.publish(subtopic + "battery/warning/lowTemperature", String(_warningLowTemperature));
    MqttSettings.publish(subtopic + "battery/warning/highTemperature", String(_warningHighTemperature));
    MqttSettings.publish(subtopic + "battery/warning/lowVoltage", String(_warningLowVoltage));
    MqttSettings.publish(subtopic + "battery/warning/highVoltage", String(_warningHighVoltage));
    MqttSettings.publish(subtopic + "battery/warning/bmsInternal", String(_warningBmsInternal));
    MqttSettings.publish(subtopic + "battery/charging/chargeEnabled", String(_chargeEnabled));
    MqttSettings.publish(subtopic + "battery/charging/dischargeEnabled", String(_dischargeEnabled));
    MqttSettings.publish(subtopic + "battery/charging/chargeImmediately", String(_chargeImmediately));
    MqttSettings.publish(subtopic + "battery/modulesTotal", String(_moduleCount));
}




} // namespace Batteries::Pylontech
