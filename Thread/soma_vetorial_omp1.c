#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <omp.h>

double waste_time(long n);

int main(int argc, char **argv)
{
	FILE *inp_a, *inp_b, *out_c;
	long int size = atol(argv[4]);
	long int i;
	double *a, *b, *c;
	a = (double *) malloc(sizeof(double) * size);
	b = (double *) malloc(sizeof(double) * size);
	c = (double *) malloc(sizeof(double) * size);
	inp_a = fopen(argv[1], "r");
	inp_b = fopen(argv[2], "r");
	for (i=0; i<size; i++) 
	{
		fscanf(inp_a, "%lf\n", &a[i]);
		fscanf(inp_b, "%lf\n", &b[i]);
	}
	fclose(inp_a);
	fclose(inp_b);

	//Calculating output vector
	#pragma omp parallel private(i)
	{
		int nt = omp_get_num_threads();
		int tid = omp_get_thread_num();
		//printf("%d - %d - %ld - %ld\n", nt, tid, size/nt*tid, size/nt*(tid+1));
		for (i=size/nt*tid; i<size/nt*(tid+1); i++)
			c[i]=waste_time(abs(a[i]))+waste_time(abs(b[i]));
	}

	out_c = fopen(argv[3], "w");
	for (i=0; i<size; i++) 
	{
		fprintf(out_c, "%lf\n", c[i]);
	}
	fclose(out_c);
	return 0;
}

double waste_time(long n)
{
    double res = 0;
    long i = 0;
    while(i <n * 200) {
        i++;
        res += sqrt (i);
    }
    return res;
}


