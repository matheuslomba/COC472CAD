#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//para buildar: gcc main.c -o run
//para rodar: ./run

//-------------------------------------------------------------------------------

double multiplicaij (int ordemN, double **matrizA, double *vetorX) {

    double *vetorB = (double *) malloc(ordemN * sizeof(double));
    int i, j, b;

    clock_t t;

    printf("Primeira ordem de execução:\n");

    t = clock();

    for (i = 0; i < ordemN; i++) {
        b = 0;
        for (j = 0; j < ordemN; j++) {
            
            b += matrizA[i][j] * vetorX[j];

        }
        vetorB[i] = b;
    }

    //Printa o resultado vetorB, mas coloquei como comentário visto o tamanho dos arrays
    /*
    printf("Vetor B: [ ");
    for (int i = 0; i < ordemN; i++) {
        printf("%d ", vetorB[i]);
    }
    printf("]\n");
    */

    t = clock() - t;
    printf("Tempo de execução: %lf segundos.\n", ((double)t)/((CLOCKS_PER_SEC))); //conversão do tempo para double
    
    return t;
}

//-------------------------------------------------------------------------------

double multiplicaji (int ordemN, double **matrizA, double *vetorX) {

    double *vetorB = (double *) malloc(ordemN * sizeof(double));
    
    int i, j, b;

    clock_t t;

    printf("Segunda ordem de execução:\n");

    t = clock();

    for (j = ordemN-1; j >= 0; j--) {
        b = 0;
        for (i = ordemN-1; i >= 0; i--) {
            
            b += matrizA[i][j] * vetorX[j];

        }
        vetorB[i] = b;
    }

    //Printa o resultado vetorB, mas coloquei como comentário visto o tamanho dos arrays
    /*
    printf("Vetor B: [ ");
    for (int i = 0; i < ordemN; i++) {
        printf("%d ", vetorB[i]);
    }
    printf("]\n");
    */

    t = clock() - t;
    printf("Tempo de execução: %lf segundos.\n", ((double)t)/((CLOCKS_PER_SEC))); //conversão do tempo para double

    return t;
}

//-------------------------------------------------------------------------------

int main () {

    double *vetorX;
    double **matrizA;
    double tij, tji;
    int i, j, ordemN;

    srand(time(NULL));

    FILE *cresultados = fopen("cresultados.csv", "w");
    fprintf(cresultados,"OrdemN, IJ, JI\n");

    for (int max = 0; max <= 30000; max = max+1000) {
        
        printf("Iteração %d\n", 1+(max/1000));
        ordemN = (rand() %101) + max;
        printf("Tamanho dos arrays: %d\n", ordemN);
        printf("-------------------------------\n");

        //Alocação de ponteiros para criar os vetores e a matriz
        vetorX = (double *) malloc(ordemN * sizeof(double));
        matrizA = (double **) malloc(ordemN * sizeof(double *));

        for (i = 0; i < ordemN; i++) {
            
            matrizA[i] = (double *) malloc(ordemN * sizeof(double));

            for (j = 0; j < ordemN; j++) {

                matrizA[i][j] = rand() %100;

            }
            vetorX[i] = rand() %100;
        }

        //Printa matrizA e vetorX, mas coloquei como comentário visto o tamanho dos arrays
        /*
        printf("Matriz A:\n");
        for (int i = 0; i < ordemN; i++) {
            for (int j = 0; j < ordemN; j++) {

                printf("%lf ", matrizA[i][j]);

            }
            printf("\n");
        }

        printf("Vetor X: [ ");
        for (int i = 0; i < ordemN; i++) {

            printf("%lf ", vetorX[i]);
        
        }
        printf("]\n"); 
        printf("-------------------------------\n");
        */

        tij = multiplicaij(ordemN, matrizA, vetorX);
        printf("-------------------------------\n");
        tji = multiplicaji(ordemN, matrizA, vetorX);
        fprintf(cresultados,"%d, %lf, %lf\n", ordemN, tij/1000000, tji/1000000);
        printf("=======================================================================\n");
        
        //Liberar memória
        for (i = 0; i < ordemN-1; i++) {
            free(matrizA[i]);
        }
        free(matrizA);
        free(vetorX);

    }
    fclose(cresultados);
    return 0;
}

