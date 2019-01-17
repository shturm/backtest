#include "../backtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

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
	int batch_count = 5;
	double buffer[batch_count];
	//candles[0] = (BT_CANDLE*) malloc(sizeof(BT_CANDLE)*batch_count);
	BT_OPTIONS* options = (BT_OPTIONS*)malloc(sizeof(BT_OPTIONS));
	options->batch_periods_count = batch_count;
	
	assert(5 == bt_read_history(buffer, options)); // 5
	assert(5 == bt_read_history(buffer, options)); // 5
	assert(5 == bt_read_history(buffer, options)); // 5
	assert(3 == bt_read_history(buffer, options)); // 3
	assert(0 == bt_read_history(buffer, options)); // 0

	// free(candles);
	free(options);
}

void test_bt_init()
{
	BT_OPTIONS* options = (BT_OPTIONS*)malloc(sizeof(BT_OPTIONS));
	options->history_filepath_csv   = "data/history.tohlc.csv";
	options->history_filepath_csv_n = 22;

	bt_init(options);

	FILE*  h     = fopen("data/history.tohlc.csv.bth", "r"); // 18 records
	size_t hsize = fpsize(h);

	printf("size of BT_CANDLE: %d\n", sizeof(BT_CANDLE));
	printf("size of bth file : %d\n", hsize);
	assert(NULL != h);
	assert(sizeof(BT_CANDLE)*18  == hsize);

	// remove("data/history.tohlc.csv.bth");
	free(options);

}

int main(int argc, char const *argv[])
{
	
	// test_bt_read_history();
	test_bt_init();

	return 0;
}