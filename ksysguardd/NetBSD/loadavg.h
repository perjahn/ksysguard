/*
    KSysGuard, the KDE System Guard
   
	Copyright (c) 2001 Tobias Koenig <tokoe@kde.org>
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

	$Id$
*/

#ifndef _loadavg_h_
#define _loadavg_h_

void initLoadAvg(struct SensorModul* sm);
void exitLoadAvg(void);

int updateLoadAvg(void);

void printLoadAvg1(const char*);
void printLoadAvg1Info(const char*);
void printLoadAvg5(const char*);
void printLoadAvg5Info(const char*);
void printLoadAvg15(const char*);
void printLoadAvg15Info(const char*);

#endif
