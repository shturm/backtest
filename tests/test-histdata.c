#include "../backtest.h"
#include "../history.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	const char*	line   = "20180101 170000;1.234567;1.345678;1.456789;1.567891;0";
	BT_CANDLE*  result = bt_parse_line_histdata(line);

	struct tm* expected_time = (struct tm*)malloc(sizeof(struct tm));

	assert(memcmp(expected_time, &result->time, sizeof(struct tm)) == 0); 
	assert(result->price_open  == 1.234567);
	assert(result->price_high  == 1.345678);
	assert(result->price_low   == 1.456789);
	assert(result->price_close == 1.567891);

	return 0;
}
