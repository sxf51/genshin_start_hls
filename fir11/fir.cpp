/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.

	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"

void fir (
  data_t *y,
  data_t x
  )
{
	coef_t h[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0,53};
	// Write your code here

	// kria
	#pragma HLS interface mode=s_axilite port=y
    #pragma HLS interface mode=s_axilite port=x
    #pragma HLS interface mode=s_axilite port=return
    #pragma HLS interface mode=ap_ctrl_chain port=return
	
	static data_t shift_reg[N];
    acc_t ans = 0;

    // shift + MAC
    for (int i = N - 1; i > 0; i--) {
#pragma HLS pipeline 
        shift_reg[i] = shift_reg[i - 1];
    }
    shift_reg[0] = x;

    for (int i = 0; i < N; i++) {
#pragma HLS pipeline 
        ans += shift_reg[i] * h[i];
    }
    *y = ans;
}



