// Se debe incuir el archivo en la terminal 
//   ./archivocompilado  sudoku_test.txt 

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 9

char sudoku [9][9];
char resultados [9];

char imprimirSudoku(){
    for(char i=0; i<9; i++){
        for(char j=0; j<9;j++){
            printf("|| %d ", sudoku[i][j]);
        }
        printf("\n");
    }
    return 0;
}

char checarFila(int id){
    char sum =0;
    for(char i=0; i<9; i++){
        sum += sudoku[id][i];
    }
    if(sum==45){
        return 0;
    }
    return 1;
}

char checarColumna(int id){
    char sum=0;
    for(char i=0; i<9;i++){
        sum += sudoku[i][id];
    }
    if(sum==45){
        return 0;
    }
    return 1;
}

char checarCuadrante(int id){
    char sum=0;
    char rows[3], cols[3];

    switch(id){
        case 0: case 1: case 2:
            rows[0]=0;
            rows[1]=1;
            rows[2]=2;
        break;
        case 3: case 4: case 5:
            rows[0]=3;
            rows[1]=4;
            rows[2]=5;
        break;
        default:
            rows[0]=6;
            rows[1]=7;
            rows[2]=8;
        break;

    }
       switch(id){
        case 0: case 3: case 6:
            cols[0]=0;
            cols[1]=1;
            cols[2]=2;
        break;
        case 1: case 4: case 7:
            cols[0]=3;
            cols[1]=4;
            cols[2]=5;
        break;
        default:
            cols[0]=6;
            cols[1]=7;
            cols[2]=8;
        break;

    }

    for(char i=0; i<3;i++){
        char row=rows[i];
        for(char j=0; j<3;j++){
            char column=cols[j];
            sum +=sudoku[row][column];
        }
    }
    if(sum==45){
        return 0;
    }
    return 1;

}

void *checkThread(void *threadid){
    int id= (long)threadid;
    // printf("%d\n",id);
    char result=0;
    
    result=checarFila(id);
    if(result){
        resultados[id]=1;
        //return 1;
    }
    result=checarColumna(id);
    if(result){
        resultados[id]=1;
        //return 1;
    }
    result=checarCuadrante(id);
    if(result){
        resultados[id]=1;
        //return 1;
    }
    
    
}
char leerArchivo(const char* const nombreArchivo){

    FILE* file= fopen(nombreArchivo,"r");
    char line[32];
    short x=0, y=0;
    while(fgets(line, sizeof(line), file)){
        for(int i=0; i<17;i++){
            char temp= line[i];
            if(temp != ' '){
                int valor = atoi(&temp);
                sudoku[x][y]=valor;
                y++;
            }
        }
        x++;
        y=0;
    }
    fclose(file);
    return 0;
}

 