/*
    KSysGuard, the KDE System Guard
   
	Copyright (c) 1999 Chris Schlaeger <cs@kde.org>

	Solaris support by Torsten Kasch <tk@Genetik.Uni-Bielefeld.DE>
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#ifndef _Memory_h_
#define _Memory_h_

typedef unsigned long t_memsize;

#define PAGETOK(a) ((( (t_memsize) sysconf( _SC_PAGESIZE )) / (t_memsize) 1024) * (t_memsize) (a))

void initMemory(struct SensorModul* sm);
void exitMemory(void);

int updateMemory(void);
int updateSwap(int upd);

void printMemFree( const char *cmd );
void printMemFreeInfo( const char *cmd );
void printMemUsed( const char *cmd );
void printMemUsedInfo( const char *cmd );

void printSwapFree( const char *cmd );
void printSwapFreeInfo( const char *cmd );
void printSwapUsed( const char *cmd );
void printSwapUsedInfo( const char *cmd );

#endif /* _Memory_h */
