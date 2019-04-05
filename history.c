#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "history.h"

BT_CANDLE* bt_parse_line_histdata(const char* line)
{
	BT_CANDLE* result = (BT_CANDLE*)malloc(sizeof(BT_CANDLE));

	// "20181125 114800;1.203630;1.203770;1.203630;1.203720;0";
	// yyyymmdd hhMMss
	
	unsigned int thedate,thetime, y,m,d, h,M,s;	

	sscanf(line, "%u %u;%f;%f;%f;%f;0", &thedate, &thetime, &(result->price_open), &(result->price_high), &(result->price_low), &(result->price_close));

	y=(int)(thedate/10000);
	m=(int)((thedate%10000)/100);
	d=thedate%100;

	h=(int)(thetime/10000);
	M=(int)((thetime%10000)/100);
	s=thetime%100;

	result->time.tm_sec=s;
	result->time.tm_min=M;
	result->time.tm_hour=h;
	// calendar
	result->time.tm_mday=d;
	result->time.tm_mon=m-1;
	result->time.tm_year=y;
	
	return result;
}


