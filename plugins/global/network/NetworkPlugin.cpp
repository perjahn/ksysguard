/*
    Copyright (c) 2020 Arjen Hiemstra <ahiemstra@heimr.nl>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "NetworkPlugin.h"

#include <QDebug>

#include <KLocalizedString>
#include <KPluginFactory>

#include <SensorContainer.h>

#include "NetworkDevice.h"
#include "NetworkBackend.h"
#include "AllDevicesObject.h"

#ifdef NETWORKMANAGER_FOUND
#include "NetworkManagerBackend.h"
#endif

class NetworkPrivate
{
public:
    SensorContainer *container = nullptr;

    AllDevicesObject *allDevices = nullptr;

    NetworkBackend *backend = nullptr;

    QVector<NetworkDevice *> devices;
};

NetworkPlugin::NetworkPlugin(QObject *parent, const QVariantList &args)
    : SensorPlugin(parent, args)
    , d(std::make_unique<NetworkPrivate>())
{
    d->container = new SensorContainer(QStringLiteral("network"), i18nc("@title", "Network Devices"), this);

    d->allDevices = new AllDevicesObject(d->container);

#ifdef NETWORKMANAGER_FOUND
    d->backend = new NetworkManagerBackend(this);
#endif
    if (!d->backend || !d->backend->isSupported()) {
        delete d->backend;
        qWarning() << "Unable to start backend, network information not available.";
        return;
    }

    connect(d->backend, &NetworkBackend::deviceAdded, this, &NetworkPlugin::onDeviceAdded);
    connect(d->backend, &NetworkBackend::deviceRemoved, this, &NetworkPlugin::onDeviceRemoved);

    d->backend->start();
}

void NetworkPlugin::onDeviceAdded(NetworkDevice *device)
{
    d->container->addObject(device);
}

void NetworkPlugin::onDeviceRemoved(NetworkDevice *device)
{
    d->container->removeObject(device);
}

NetworkPlugin::~NetworkPlugin() = default;

K_PLUGIN_CLASS_WITH_JSON(NetworkPlugin, "metadata.json")

#include "NetworkPlugin.moc"
