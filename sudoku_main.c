#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "sudoku_methods.c"

int c;
FILE *file;

int main(int argc,char const *argv[]){
    if(argc<2){
        file = fopen("vaquitaerror.txt", "r");
        if (file) {
            while ((c = getc(file)) != EOF)
                putchar(c);
            fclose(file);
        };
    }
    leerArchivo(argv[1]);
    imprimirSudoku();

    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for( t=0; t<NUM_THREADS; t++){
        rc= pthread_create(&threads[t], NULL,checkThread, (void *)t);
        if(rc){
            printf("ERROR");
        }
    }

    for(t=0; t<NUM_THREADS; t++){
       pthread_join(threads[t],NULL);
    }

    for(char i = 0;i<NUM_THREADS;i++){
        if(resultados[i]==1){
            file = fopen("vaquitaincorrecto.txt", "r");
            if (file) {
                while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    };
            return 1;
        }
    }

    file = fopen("vaquitaCorrecto.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    };
    return 0;}
