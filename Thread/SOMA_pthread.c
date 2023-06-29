#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

//[name.c] [arq_in] [K] [N] 
//   0        1      2   3

struct call_args{
    double *vet;
    double soma;
    int ini, fim, i;
};

void *somaParc(void *myArgs){
    struct call_args *a = (struct call_args *) myArgs;
    int i, ini, fim;
    ini = a->ini; fim = a->fim;
    for(i = ini; i<fim;i++){
        a->soma += a->vet[i];
    }
    printf("SOMA THREAD ");
    printf("%ld ", pthread_self());
    printf("= %lf\n", a->soma);
}

int main(int argc, char **argv){
    int K, N;
    K = atoi(argv[2]);
    N = atoi(argv[3]);
    //vetor de ID de trhead
    pthread_t *thrd = (pthread_t *) malloc(K * sizeof(pthread_t));
    //vetor de argumentos
    struct call_args *args = (struct call_args *) malloc(K * sizeof(struct call_args));
    double *a = (double *) malloc (K * sizeof(double));
    //ler do arquivo para memoria
    FILE *arq = fopen(argv[1], "r");
    for(int i = 0;i < K; i++){
        fscanf(arq, "%lf\n", &a[i]);
    } 
    fclose(arq);

    printf("++++++SOMA VETORIAL USANDO PTHREADS+++++++\n\n");
    
    //inicializa os argumentos e chama funcao para as threads
    for(int i = 0; i<N;i++){
        args[i].soma = 0;
        args[i].ini = (i*(K/N));
        args[i].fim = (i+1)*(K/N);
        args[i].i = K/N;
        args[i].vet = a;

        //funcao thread
        pthread_create(&thrd[i],NULL,(void *)somaParc, &args[i]);
        //printf("= %f\n", args[i].soma);
    }
    //Esperar as threads
    for(int i = 0; i<N;i++){
        pthread_join(thrd[i], NULL);
    }

    //somar resultados parciais
    double total = 0;
    for(int i = 0; i<N;i++){
        total += args[i].soma;
    }

    printf("\nTOTAL: %f\n", total);

}
//gcc -o t -lpthread SOMA_pthread.c
//./t a_d.in 2000 10