#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "backtest.h"

BT_WALLET* bt_create_wallet() {
	BT_WALLET* wallet = (BT_WALLET*)malloc(sizeof(BT_WALLET));
	return wallet;
}

BT_OPTIONS* bt_create_options(char const * cli_args[], int cli_args_count) {
	BT_OPTIONS* popts = (BT_OPTIONS*)malloc(sizeof(BT_OPTIONS));
	
	popts->batch_periods_count = 20;
	return popts;
}

void _bt_csv_to_bth(const BT_OPTIONS* o)
{
	if (o->history_file) fclose(o->history_file);
	FILE* bth_tmp = fopen(o->history_filepath,"r");
	if (bth_tmp) {
		fclose(bth_tmp);
		remove(o->history_filepath);
	}

	FILE* fcsv = fopen(o->history_filepath_csv, "r");
	FILE* fbth = fopen(o->history_filepath,     "w");
	
	assert(fcsv != NULL);
	assert(fbth != NULL);

	int MAX_LINE_LENGTH = 256;
	char line[MAX_LINE_LENGTH];
	char* linecp;
	char* delim = ",";
	char *line_time, *line_open, *line_high, *line_low, *line_close;
	
	long line_time_conv;
	double line_open_conv, line_high_conv, line_low_conv, line_close_conv;
	BT_CANDLE* candle = (BT_CANDLE*)malloc(sizeof(BT_CANDLE));
	while(fgets(line, MAX_LINE_LENGTH, fcsv) !=  NULL)
	{
		linecp     = strdup(line);
		line_time  = strtok(linecp, delim);
		line_open  = strtok(NULL, delim);
		line_high  = strtok(NULL, delim);
		line_low   = strtok(NULL, delim);
		line_close = strtok(NULL, delim);

		candle->time        = strtol(line_time, NULL, 0);
		candle->price_open  = strtod(line_open, NULL);
		candle->price_high  = strtod(line_high, NULL);
		candle->price_low   = strtod(line_low, NULL);
		candle->price_close = strtod(line_close, NULL);

		fwrite(candle, sizeof(BT_CANDLE), 1, fbth);

		free(linecp);
	}
	free(candle);
	fclose(fcsv);
	fclose(fbth);
}

void bt_init(BT_OPTIONS* o) {
	o->history_file_headers_csv   = "TOHLC"; // todo
	o->history_file_headers_csv_n = 5;       // todo

	if (o->history_filepath_csv_n > 0)
	{
		o->history_filepath_n = o->history_filepath_csv_n + sizeof(".bth")-1;
		o->history_filepath   = (char*)realloc(o->history_filepath, o->history_filepath_n);		
		strcpy(o->history_filepath, o->history_filepath_csv);
		strcat(o->history_filepath, ".bth");

		o->history_file = fopen (o->history_filepath, "r");
		if (!o->history_file)
		{
			_bt_csv_to_bth(o);
		}
	}
}

int bt_read_history(double buffer[], const BT_OPTIONS* options) {
	if (!options->is_initiated) return -1;

	if (feof(options->history_file))   return 0;
	if (ferror(options->history_file)) return 0;

	int read = fread(buffer, 
					sizeof(double), 
				 	options->history_file_batch_read_count, 
				 	options->history_file);
	
	return read;
}