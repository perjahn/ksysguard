/*
    KSysGuard, the KDE System Guard

    Copyright (c) 1999, 2000 Chris Schlaeger <cs@kde.org>

    This program is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

    KSysGuard is currently maintained by Chris Schlaeger <cs@kde.org>. Please do
    not commit any changes without consulting me first. Thanks!

*/

#ifndef KSG_KSYSGUARD_H
#define KSG_KSYSGUARD_H

#include <QEvent>
#include <dbus/qdbus.h>

#include <kapplication.h>
#include <kmainwindow.h>

#include <ksgrd/SensorClient.h>

class KRecentFilesAction;
class KToggleAction;

class QSplitter;
class SensorBrowser;
class Workspace;

class TopLevel : public KMainWindow, public KSGRD::SensorClient
{
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", "org.kde.SystemMonitor")

  public:
    TopLevel( const char *name = 0 );

  virtual void saveProperties( KConfig* );
  virtual void readProperties( KConfig* );

  virtual void answerReceived( int id, const QStringList& );

  void beATaskManager();
  void showRequestedSheets();
  void initStatusBar();

  public Q_SLOTS:
     // calling ksysguard with kwin/kicker hot-key
    Q_SCRIPTABLE Q_ASYNC void showProcesses();
    Q_SCRIPTABLE Q_ASYNC void showOnCurrentDesktop();
    Q_SCRIPTABLE Q_ASYNC void loadWorkSheet( const QString &fileName );
    Q_SCRIPTABLE Q_ASYNC void removeWorkSheet( const QString &fileName );
    Q_SCRIPTABLE QStringList listHosts();
    Q_SCRIPTABLE QStringList listSensors( const QString &hostName );
    Q_SCRIPTABLE QString readSensor( const QString &sensorLocator, const QDBusMessage &msg );
    Q_SCRIPTABLE QStringList readListSensor( const QString &sensorLocator, const QDBusMessage &msg );

    void registerRecentURL( const KUrl &url );
    void resetWorkSheets();

  protected:
    virtual void customEvent( QCustomEvent* );
    virtual void timerEvent( QTimerEvent* );
    virtual bool queryClose();

  protected Q_SLOTS:
    void connectHost();
    void disconnectHost();
    void updateStatusBar();
    void editToolbars();
    void editStyle();
    void slotNewToolbarConfig();

  private:
    void setSwapInfo( long, long, const QString& );

    QDBusMessage mDBusReply;

    QSplitter* mSplitter;
    KRecentFilesAction* mActionOpenRecent;

    SensorBrowser* mSensorBrowser;
    Workspace* mWorkSpace;

    int mTimerId;
};

extern TopLevel* Toplevel;

#endif
