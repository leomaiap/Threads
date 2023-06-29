#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define __USE_GNU
#include <sched.h>
#undef __USE_GNU
#include <errno.h>
#include <math.h>

//gcc -o s soma.c
//./s a_d.in 10000 10

                                 //  1     2   3
int main(int argc, char **argv){ //[file] [K] [N]
    FILE *arq;
    arq = fopen(argv[1], "r");
    int K = atoi(argv[2]);
    int N = atoi(argv[3]);
    pid_t paiID = getppid();
    printf("ID pai: %d\n", paiID);
    double *a;
    a = (double *) malloc(sizeof(double) * K);
    int SID_PARCIAL = shmget(IPC_PRIVATE, sizeof(double)*N, SHM_R|SHM_W|IPC_CREAT);
    double *PARCIAL;
    PARCIAL = (double *) shmat(SID_PARCIAL, NULL, 0);

    //ler pro vetor
    for (int i=0; i<K; i++) {
		fscanf(arq, "%lf\n", &a[i]);
	}
    fclose(arq);

    //Criar N processos
    for (int i=0; i<N; i++){
        if((fork()) == 0){
           int ini = (i*(K/N)), fim = ((i+1)*(K/N));
           double somatorio = 0;
           PARCIAL = (double *) shmat(SID_PARCIAL, NULL, 0);
           //soma
           for(int s=ini; s<fim; s++){
                somatorio += a[s];
           }
           
           PARCIAL[i] = somatorio;
           printf("PARCIAL filho[%d] (%d) = %f\n", i+1, getpid(), PARCIAL[i]);
           shmdt(PARCIAL);
           exit(0);
        }

    }

    for(int i=0;i<N;i++) wait(NULL);//pai espera

    double total = 0;
    for (int i=0; i<N; i++) total += PARCIAL[i];
    printf("A soma total e = %f\n", total);
    shmdt(PARCIAL);

    return 0;

}