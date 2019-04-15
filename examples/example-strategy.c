#include "backtest.h"   // for getting history data, backtest lib
#include "indicators.h" // for calculating indicators, external lib

int main(int argc, char const *argv[])
{
	BT_WALLET*  bt_wallet   = bt_create_wallet(); // your trade portfolio
	BT_OPTIONS* bt_options  = bt_create_options(argv, argc); // backtest details

	// default values

	strcpy(bt_options->history_filepath_csv, "data/DAT_ASCII_EURUSD_M1_2018.csv");
	
	bt_init(bt_options);

	BT_CANDLE buffer[bt_options->batch_candles_count];
	int candles_n_read = 0;
	while((candles_n_read = bt_read_history(buffer, bt_options)) > 0)
	{
		// your EA code here - calculate indicators, make trades, etc
		// for (int i = 0; i < candles_n_read; i++) bt_print_candle(&buffer[i]);
	}

	// bt_output(wallet, options); // output trades, according ot options

	printf("%s\n", "[ok] example strategy can process history");
	return 0;
}
