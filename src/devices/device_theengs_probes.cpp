/*
    Theengs - Decode things and devices
    Copyright: (c) Florian ROBERT

    This file is part of Theengs.

    Theengs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Theengs is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "device_theengs_probes.h"

#include <cstdint>
#include <cmath>

#include <QBluetoothUuid>
#include <QBluetoothServiceInfo>
#include <QLowEnergyService>

#include <QSqlQuery>
#include <QSqlError>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDateTime>
#include <QDebug>

/* ************************************************************************** */

DeviceTheengsProbes::DeviceTheengsProbes(const QString &deviceAddr, const QString &deviceName,
                                         const QString &deviceModel, const QString &devicePropsJson,
                                         QObject *parent):
    DeviceTheengs(deviceAddr, deviceName, deviceModel, parent)
{
    m_deviceType = DeviceUtils::DEVICE_THEENGS_PROBES;

    if (deviceName.contains("iBBQ"))
    {
        m_deviceCapabilities = DeviceUtils::DEVICE_BATTERY;
        m_deviceSensors += DeviceUtilsTheengs::SENSOR_PROBES_TEMP;
    }
    else if (deviceName.contains("TPMS"))
    {
        m_deviceSensors += DeviceUtilsTheengs::SENSOR_PROBES_TPMS;
    }
}

DeviceTheengsProbes::DeviceTheengsProbes(const QBluetoothDeviceInfo &d,
                                         const QString &deviceModel, const QString &devicePropsJson,
                                         QObject *parent):
    DeviceTheengs(d, deviceModel, parent)
{
    m_deviceType = DeviceUtils::DEVICE_THEENGS_PROBES;

    if (d.name().contains("iBBQ"))
    {
        m_deviceCapabilities = DeviceUtils::DEVICE_BATTERY;
        m_deviceSensors += DeviceUtilsTheengs::SENSOR_PROBES_TEMP;
    }
    else if (d.name().contains("TPMS"))
    {
        m_deviceSensors += DeviceUtilsTheengs::SENSOR_PROBES_TPMS;
    }
}

DeviceTheengsProbes::~DeviceTheengsProbes()
{
    //
}

/* ************************************************************************** */

void DeviceTheengsProbes::parseAdvertisementTheengs(const QString &json)
{
    qDebug() << "DeviceTheengsProbes::parseAdvertisementTheengs()";
    qDebug() << "JSON:" << json;

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject obj = doc.object();

    if (obj.contains("batt")) setBattery(obj["batt"].toInt());
    if (obj.contains("mac")) setSetting("mac", obj["mac"].toString());

    if (obj["model"].toString() == "TPMS")
    {
        int idx = obj["count"].toInt();
        float pres = obj["pres"].toDouble() * 10.0;
        float temp = obj["tempc"].toDouble();
        int batt = obj["batt"].toInt();
        bool alarm = obj["alarm"].toBool();

        if (idx == 1) {
            m_pressure1 = pres;
            m_temperature1 = temp;
            m_battery1 = batt;
            m_alarm1 = alarm;
        }
        else if (idx == 2) {
            m_pressure2 = pres;
            m_temperature2 = temp;
            m_battery2 = batt;
            m_alarm2 = alarm;
        }
        else if (idx == 3) {
            m_pressure3 = pres;
            m_temperature3 = temp;
            m_battery3 = batt;
            m_alarm3 = alarm;
        }
        else if (idx == 4) {
            m_pressure4 = pres;
            m_temperature4 = temp;
            m_battery4 = batt;
            m_alarm4 = alarm;
        }
    }
    else if (obj["model"].toString().contains("BBQ"))
    {
        if (obj.contains("tempc")) m_temperature1 = obj["tempc"].toDouble();
        if (obj.contains("temp1c")) m_temperature1 = obj["temp1c"].toDouble();
        if (obj.contains("temp2c")) m_temperature2 = obj["temp2c"].toDouble();
        if (obj.contains("temp3c")) m_temperature3 = obj["temp3c"].toDouble();
        if (obj.contains("temp4c")) m_temperature4 = obj["temp4c"].toDouble();
        if (obj.contains("temp5c")) m_temperature5 = obj["temp5c"].toDouble();
        if (obj.contains("temp6c")) m_temperature6 = obj["temp6c"].toDouble();
    }

    //if (x > -99)
    {
        m_lastUpdate = QDateTime::currentDateTime();
        refreshDataFinished(true);

        if (needsUpdateDb())
        {
            // TODO // UPDATE DB
        }
    }
}

/* ************************************************************************** */
