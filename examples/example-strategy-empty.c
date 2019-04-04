#include <stdio.h>
#include "backtest.h"

int main(int argc, char const *argv[])
{
	BT_CANDLE candle; // <---- backtest api
	printf("%s\n", "[ok] example strategy can use backtest api");
	return 0;
}