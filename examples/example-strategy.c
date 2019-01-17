#include "backtest.h"   // for getting history data, backtest lib
#include "indicators.h" // for calculating indicators, external lib

int main(int argc, char const *argv[])
{
	BT_WALLET*  bt_wallet   = bt_create_wallet(); // your trade portfolio
	BT_OPTIONS* bt_options  = bt_create_options(argv, argc); // backtest details
	bt_init(bt_options);

	double buffer[bt_options->batch_periods_count];
	int periods_n_read = 0;
	while((periods_n_read = bt_read_history(buffer, bt_options)) > 0)
	{
		// your EA code here - calculate indicators, make trades, etc
	}

	// bt_output(wallet, options); // output trades, according ot options
	return 0;
}