/*
	Filename: fir_test.h
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Testbench file
		Calls fir() function from fir.cpp
		Compares the output from fir() with out.gold.dat
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fir.h"

int main ()
{
  const int SAMPLES = 600;
  FILE* fout;
  FILE* fin;

  data_t signal, output;
  int i;
  signal = 0;
  
  fin = fopen("input.dat", "r");
  fout = fopen("out.dat", "w");
  if ( (fin == NULL) || (fout == NULL) )
  {
    fprintf(stderr, "ERROR: could not open input.dat or out.dat");
    return 1;
  }

  for (i = 0; i < SAMPLES; i++)
  {
	  fscanf(fin, "%d", &signal);
	  
    //Call the HLS block
    fir(&output, signal);
    
    // Save the results.
    fprintf(fout, "%d\n", output);
    printf("%i %d %d\n", i, signal, output);
  }

  fclose(fout);
  fclose(fin);

  //Comparing results with the golden output.
  printf ("Comparing against output data.\n");
    if (system("diff -w out.dat out.gold.dat"))
    {
  	  fprintf(stdout, "*********************************************\n");
  	  fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
  	  fprintf(stdout, "*********************************************\n");
      return 1;
    }
    else
    {
  	  fprintf(stdout, "*********************************************\n");
  	  fprintf(stdout, "PASS: The output matches the golden output!\n");
  	  fprintf(stdout, "*********************************************\n");
      return 0;
    }
}