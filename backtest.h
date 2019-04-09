#ifndef H_BACKTEST
#define H_BACKTEST

#include <stdio.h>
#include <time.h>

#define DEBUGLINE printf("%s:%s():%d\n", __FILE__, __FUNCTION__, __LINE__);


typedef struct {
	char*  name;
	char*  version;
	char** indicators;
} BT_STRAT_META;

typedef struct
{
	char**  indicators;
	double* indicator_values;
	int     indicator_count;
} BT_INDICATORS;

typedef struct {
	unsigned short year:12; // unsigned 12bits=max 4095, values e.g. 2019
    unsigned short month:4; // unsigned 4bits=max 15, values 1-12
    unsigned short day:5; // unsigned 5bits=max 31, values 1-31

    unsigned short hour:5; // unsigned 5bits=max 31, values 0-23
    unsigned short minute:6; // unsigned 6bits=max 63, values 0-59
    unsigned short second:6; // unsigned 6bits=max 63, values 0-59
} BT_DATETIME;

typedef struct
{
	BT_DATETIME datetime;
	float price_open;
	float price_high;
	float price_low;
	float price_close;
	
	// when finished, equal to price_close, 
	// when not started or unknown, not usable
	// when started, the actual current price
	// double price_current; 
} BT_CANDLE;
typedef int BT_CANDLE_STATE;
#define BT_CANDLE_STATE_UNKNOWN 0
#define BT_CANDLE_STATE_NOTSTARTED 1
#define BT_CANDLE_STATE_STARTED 2
#define BT_CANDLE_STATE_FINISHED 3

typedef struct 
{

} BT_WALLET;

typedef struct 
{
	short is_initiated;

	int batch_periods_count; // deprecated
	int history_file_batch_read_count;
	
	// csv, to be converted
	FILE*  history_file_csv;
	char*  history_filepath_csv;
	int    history_filepath_csv_n;
	char*  history_file_headers_csv; // e.g. "TOHLC": (T)ime, (O)pen, (H)igh, (L)ow, (C)lose, (I)nstrument
	int    history_file_headers_csv_n;

	// binary, produced by converting from csv
	FILE*  history_file;
	char*  history_filepath;
	int    history_filepath_n;
} BT_OPTIONS;

BT_WALLET* bt_create_wallet();
BT_OPTIONS* bt_create_options(char const * cli_args[], int cli_args_count);

/*
	- convert history file from csv to binary, if necessary
*/
void bt_init(BT_OPTIONS* options);

/*
	buffered reading of binary history file
*/
int  bt_read_history(double buffer[], const BT_OPTIONS* options);

#endif
