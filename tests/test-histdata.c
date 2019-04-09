#include "../backtest.h"
#include "../history.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	const char*	line   = "20181231 171259;1.234567;1.345678;1.456789;1.567891;0";
	BT_CANDLE*  result = bt_parse_line_histdata(line);

	BT_DATETIME* expected = (BT_DATETIME*)malloc(sizeof(BT_DATETIME));
	expected->year = 2018;
	expected->month = 12;
	expected->day = 31;
	expected->hour = 17;
	expected->minute = 12;
	expected->second = 59;
	
	BT_DATETIME* actual   = &result->datetime;

	assert(memcmp(expected, actual, sizeof(BT_DATETIME)) == 0); 
	assert(result->price_open  == 1.234567f);
	assert(result->price_high  == 1.345678f);
	assert(result->price_close == 1.567891f);
	assert(result->price_low   == 1.456789f);

	return 0;
}
