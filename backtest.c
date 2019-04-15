#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "backtest.h"
#include "history.h"

BT_WALLET* bt_create_wallet() {
	BT_WALLET* wallet = (BT_WALLET*)malloc(sizeof(BT_WALLET));
	return wallet;
}

BT_OPTIONS* bt_create_options(char const * cli_args[], int cli_args_count) {
	
	BT_OPTIONS* popts = (BT_OPTIONS*)malloc(sizeof(BT_OPTIONS));

	popts->is_initiated = 0;	
	popts->batch_candles_count = 2000;
	strcpy(popts->history_filepath_csv, "");
	strcpy(popts->history_filepath_bth, "");

		if (cli_args != NULL)
		{
			// TODO: read args options
		}

	return popts;
}

void _bt_csv_to_bth(const char* filepath_csv, const char* filepath_bth)
{	
	FILE* fcsv = fopen(filepath_csv, "r");
	FILE* fbth = fopen(filepath_bth, "w");
	
	assert(fcsv != NULL);
	assert(fbth != NULL);

	const int MAX_LINE_LENGTH = 256;
	char line[MAX_LINE_LENGTH];
	
	BT_CANDLE* candle;
	while(fgets(line, MAX_LINE_LENGTH, fcsv) !=  NULL)
	{
		candle = bt_parse_line_histdata(line); // TODO: paremetrize
		fwrite(candle, sizeof(BT_CANDLE), 1, fbth);
	}
	free(candle);
	fclose(fcsv);
	fclose(fbth);
}



void bt_init(BT_OPTIONS* o) {	
	if (o->is_initiated == 1) return;

	assert(strlen(o->history_filepath_csv) > 0 ||
           strlen(o->history_filepath_bth) > 0);

	// bth present
	if (strlen(o->history_filepath_bth) > 0)
	{
		o->is_initiated = 1;
		return;
	}

	// csv present, but not bth
	if (strlen(o->history_filepath_csv) >  0 &&
        strlen(o->history_filepath_bth) == 0)
	{
		strcpy(o->history_filepath_bth, o->history_filepath_csv);
		strcat(o->history_filepath_bth, ".bth");
		
		o->history_file_bth = fopen (o->history_filepath_bth, "r");
		if (!o->history_file_bth)
		{
			_bt_csv_to_bth(o->history_filepath_csv, o->history_filepath_bth);
		}
	}
// TODO ensure bth file corresponds to csv file
	o->is_initiated = 1;
}


int bt_read_history(BT_CANDLE buffer[], const BT_OPTIONS* options) {
	if (options->is_initiated != 1)        return -1;
	if (feof(  options->history_file_bth)) return -2;
	if (ferror(options->history_file_bth)) return -3;

	int read = fread(buffer, 
					sizeof(BT_CANDLE), 
				 	options->batch_candles_count,
				 	options->history_file_bth);
	
	return read;
}

void bt_print_candle(BT_CANDLE* c) {
	printf("[%d-%02d-%02d %02d:%02d:%02d] %.6f;%.6f;%.6f;%.6f\n", 
		c->datetime.year,
		c->datetime.month,
		c->datetime.day,
		c->datetime.hour,
		c->datetime.minute,
		c->datetime.second,
		c->price_open,
		c->price_high,
		c->price_low,
		c->price_close
	);
}
