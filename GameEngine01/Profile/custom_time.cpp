/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */

#include <Windows.h>
#include <mmsystem.h>
#include <ctime>
#include <time.h>

double g_StartTime = -1.0f;
double g_CurrentTime = -1.0f;
double g_TimeLastTick = -1.0f;

void InitTime( void )
{
	g_StartTime = ((double)timeGetTime()) / 1000.0f;
	g_CurrentTime = 0.0f;
	g_TimeLastTick = 0.001f;
}

void MarkTimeThisTick( void )
{
	double newTime = (((double)timeGetTime()) / 1000.0f) - g_StartTime;
	g_TimeLastTick = newTime - g_CurrentTime;
	g_CurrentTime = newTime;

	if( g_TimeLastTick <= 0.0f ) {
		g_TimeLastTick = 0.001f;
	}
}

double GetElapsedTime( void )
{
	return( g_TimeLastTick );
}


double GetExactTime( void )
{
	return( ((double)timeGetTime()) );
	//return(((double) timeGetTime()) / 1000.0);
}

