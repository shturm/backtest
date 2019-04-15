#include "../backtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

long int fpsize(FILE* f)
{
	// stdio.h
	// #define SEEK_SET	0	/* Seek from beginning of file.  */
	// #define SEEK_CUR	1	/* Seek from current position.  */
	// #define SEEK_END	2	/* Seek from end of file.  */
	if (!f) return 0;

	long int current = ftell(f); // save current position
	fseek(f, 0, SEEK_END); // seek to end, 2nd param is offset
	long int size = ftell(f); // read position = byte count from beginning of file
	// printf("fpsize(): size %ld\n", size);
	
	fseek(f, current, SEEK_SET);

	return size;
}

void test_bt_read_history() {
	printf("test_bt_read_history()\n");
	const int BATCH_COUNT = 5;
	BT_CANDLE buffer[BATCH_COUNT];
	BT_OPTIONS* options = bt_create_options(NULL, 0);
	
	options->batch_candles_count = BATCH_COUNT;

	strcpy(options->history_filepath_bth, "data/histdata.csv.bth");
	options->history_file_bth = fopen(options->history_filepath_bth,"r");
	
	assert(10 == bt_read_history(buffer, options)); // 10 lines
	assert(0 == bt_read_history(buffer, options)); // 0 lines

	free(options);
}

void test_bt_init()
{
	printf("test_bt_init()\n");
	BT_OPTIONS* options = (BT_OPTIONS*)malloc(sizeof(BT_OPTIONS));
	
	strcpy(options->history_filepath_csv,"data/histdata.csv");

	bt_init(options);

	FILE*  h     = fopen("data/histdata.csv.bth", "r"); // 10 records
	size_t hsize = fpsize(h);

	printf("size of BT_CANDLE: %d\n", sizeof(BT_CANDLE));
	printf("size of bth file : %d\n", hsize);
	printf("file size mod candle size == %d\n", hsize % sizeof(BT_CANDLE));
	assert(hsize % sizeof(BT_CANDLE) == 0);
	assert(NULL != h);
	assert(sizeof(BT_CANDLE)*10  == hsize); // there are 10 lines in the file

	// remove("data/history.tohlc.csv.bth");
	free(options);

}

int main(int argc, char const *argv[])
{
	
	test_bt_init();
	test_bt_read_history();

	return 0;
}
