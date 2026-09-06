/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
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

	coef_t h[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	
	// Write your code here
    
	// kria
	#pragma HLS interface mode=s_axilite port=y
    #pragma HLS interface mode=s_axilite port=x
    #pragma HLS interface mode=s_axilite port=return
    #pragma HLS interface mode=ap_ctrl_chain port=return

    
	
	static data_t shift_reg[N];
    #pragma HLS array_partition variable=shift_reg cyclic factor =4
    
    acc_t ans = 0;

    // // shift + MAC
    // #pragma HLS pipeline
    // for (int i = N - 1; i > 0; i--) {
    //     shift_reg[i] = shift_reg[i - 1];
    //     ans += shift_reg[i] * h[i];
    // }
    // shift_reg[0] = x;
    // ans += shift_reg[0] * h[0];

    
    // for (int i = N - 1; i >= 0; i--) {
    //     if (i == 0)
    //         shift_reg[0] = x;
    //     else
    //         shift_reg[i] = shift_reg[i - 1];
    //     ans += shift_reg[i] * h[i];
    // }



    for (int i = N - 1; i > 0; i--) {
        #pragma HLS unroll factor=4
        // #pragma HLS pipeline II=3
        
        shift_reg[i] = shift_reg[i - 1];
    }
    shift_reg[0] = x;




    for (int i = 0; i < N; i++) {
        #pragma HLS unroll factor=4
        // #pragma HLS pipeline II=3
        ans += shift_reg[i] * h[i];
    }
    
    *y = ans;
}


