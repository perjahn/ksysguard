/*
    KTop, the KDE Task Manager and System Monitor

	Copyright (c) 2001 Tobias Koenig <tokoe82@yahoo.de>
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

	KTop is currently maintained by Chris Schlaeger <cs@kde.org>. Please do
	not commit any changes without consulting me first. Thanks!
*/

#ifndef _ListView_h_
#define _ListView_h_

#include <qlistview.h>

#include <SensorDisplay.h>

class QLabel;
class QBoxGroup;
class ListViewSettings;

class MyListView : public QListView
{
public:
	MyListView(QWidget *parent = 0);

	void setGridColor(QColor color) { gridColor = color; }
	void setTextColor(QColor color) { textColor = color; }
	QColor getGridColor(void) { return gridColor; }
	QColor getTextColor(void) { return textColor; }
private:
	QColor gridColor;
	QColor textColor;
};	

class ListViewItem : public QListViewItem
{
public:
	ListViewItem(MyListView *parent);

	void paintCell(QPainter *p, const QColorGroup &cg, int column, int width, int alignment);
	void paintFocus(QPainter *, const QColorGroup &cg, const QRect &r);

private:
	QColor gridColor;
	QColor textColor;
};	

class ListView : public SensorDisplay
{
	Q_OBJECT

public:
	ListView(QWidget* parent = 0, const char* name = 0,
			const QString& = QString::null, int min = 0, int max = 0);
	~ListView()
	{
	}

	bool addSensor(const QString& hostName, const QString& sensorName, const QString& sensorDescr);
	void answerReceived(int id, const QString& answer);
	void resizeEvent(QResizeEvent*);
	void updateList();

	bool load(QDomElement& domEl);
	bool save(QDomDocument& doc, QDomElement& display);

	virtual bool hasSettingsDialog()
	{
		return (TRUE);
	}

	virtual void timerEvent(QTimerEvent*)
	{
		updateList();
	}

	void settings();

	virtual void sensorError(bool err);

public slots:
	void applySettings();

private:
	QFrame* frame;
	QLabel* errorLabel;
	MyListView* mainList;
	ListViewSettings* lvs;

	QString title;
	bool modified;
};

#endif
