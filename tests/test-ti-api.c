#include "indicators.h"
#include "../backtest.h"
#include <stdio.h>

void print_array(const double *p, const int size) {
    int i;
    for (i = 0; i < size; ++i) {
        if (i) printf(", ");
        printf("%.1f", p[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
	printf("load ti api\n");
	const double data_in[] = {5,8,12,11,9,8,7,10,11,13};
    const int input_length = sizeof(data_in) / sizeof(double);

    // printf("We have %d bars of input data.\n", input_length);
    // print_array(data_in, input_length);

    const double options[] = {3};
    // printf("Our option array is: ");
    // print_array(options, sizeof(options) / sizeof(double));

    const int start = ti_sma_start(options);
    // printf("The start amount is: %d\n", start);

    const int output_length = input_length - start;
    double *data_out = malloc((unsigned int)output_length * sizeof(double));
    assert(data_out != 0);
    // printf("The output length is: %d\n", output_length);

    const double *all_inputs[] = {data_in};
    double *all_outputs[] = {data_out};
    int error = ti_sma(input_length, all_inputs, options, all_outputs);
    assert(error == TI_OKAY);

    // printf("The output data is: ");
    // print_array(data_out, output_length);
	return 0;
}
