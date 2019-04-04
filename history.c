#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "history.h"

BT_CANDLE* bt_parse_line_histdata(const char* line)
{
	BT_CANDLE* result = (BT_CANDLE*)malloc(sizeof(BT_CANDLE));

	// result->time = (struct tm);

	return result;
}

