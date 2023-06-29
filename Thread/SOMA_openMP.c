#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <omp.h>

int main(int argc, char **argv){
    int K, N;
    K = atoi(argv[2]);
    N = atoi(argv[3]);
    double total = 0;
    //ALOCAR VETOR
    double *a = (double *) malloc((K * sizeof(double)));
    //LER ARQUIVO PRO VETOR
    FILE *arq = fopen(argv[1], "r");
    for (int i = 0; i < K; i++){
        fscanf(arq, "%lf\n", &a[i]);
    }
    fclose(arq);

    double somaParcial = 0;

    printf("++++++SOMA VETORIAL USANDO OPENMP+++++++\n\n");
    
    //IMPLEMENTAR SOMATORIO PARCIAL
    omp_set_num_threads(N);
    
    #pragma omp parallel private(somaParcial)
	{
        int iStart, iEnd, id, i;
        //id da thread
        id = omp_get_thread_num();
        iStart = (id*(K/N));
        iEnd = (id+1)*(K/N);
        for(i = iStart;i<iEnd;i++){
            somaParcial += a[i];
        }
        printf("SOMA THREAD %d = %lf\n", id,somaParcial);
        #pragma opm critical
        total += somaParcial;
    }


    printf("\nTOTAL: %lf\n", total);

}

//gcc SOMA_openMP.c -o sum -fopenmp
//./sum a_d.in 2000 10