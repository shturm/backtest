#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "history.h"

BT_CANDLE* bt_parse_line_histdata(const char* line)
{
	BT_CANDLE* result = (BT_CANDLE*)malloc(sizeof(BT_CANDLE));

	// 20181231 171259;1.234567;1.345678;1.456789;1.567891;0
	unsigned int thedate,thetime, y,m,d, h,M,s;
	result->price_open=result->price_high=result->price_low=result->price_close=0.0f;
	float open,high,low,close;
	open = high = low = close = 0;

	sscanf(line, "%u %u;%f;%f;%f;%f;0", &thedate, &thetime, &open, &high, &low, &close);

	y=(int)(thedate/10000);
	m=(int)((thedate%10000)/100);
	d=thedate%100;

	h=(int)(thetime/10000);
	M=(int)((thetime%10000)/100);
	s=thetime%100;

	result->price_open = open;
	result->price_high = high;
	result->price_low = low;
	result->price_close = close;


	result->datetime.second=s;
	result->datetime.minute=M;
	result->datetime.hour=h;
	result->datetime.day=d;
	result->datetime.month=m;
	result->datetime.year=y;

	return result;
}


