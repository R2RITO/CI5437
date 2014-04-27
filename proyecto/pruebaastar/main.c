#include <stdio.h>
#include "idastar.h"

#define BUFFER_SIZE 80
int main  (int argc, char *argv[]) {

    /*La invocacion debe tener exactamente 2 argumentos: el nombre del programa
     *y el archivo de entrada*/
    if (argc!=2) {
        printf("Modo de uso: ./main <nombre_archivo>\n");
        exit(1);
    }

    FILE *file;
    char* file_name = argv[1];
    char instance[BUFFER_SIZE];
    /*se hace apertura del archivo de entrada*/
    file = fopen(file_name,"r"); 
    if (!file) {
       perror("Error al abrir el archivo de entrada: ");
       exit(1);
    }
    list res2;
    /*resolucion linea por linea de las instancias suministradas en el
     *archivo de prueba*/
    box act;
    clock_t start2 ,end2;
    int i;
    printf("TAM DE NODO: %d\n", sizeof(struct nodo_struct));
    printf("TAM DE ESTADO: %d\n", sizeof(struct _state));
    while ( fgets (instance, BUFFER_SIZE, file)) {
        /*------------------ IDA* -------------------------*/
        state initial_state = init(instance);
      /*  printf("EMPIEZO IDA* \n");
        start2 = clock();
        res2 = NULL;
        res2 = (list) idastar(initial_state);
        end2 = clock();
        printf("TERMINO IDA*\n");
        printf("IDA* se tardo: %f\n", (float)(end2-start2)/CLOCKS_PER_SEC);
        if (res2) {
          printf("Lista 2: %d", res2->size);
          act = res2 -> first;
          i;
          for (i=0; i<res2->size; i++) {
              printf("%s ", getElemBox(act));
              act = getNextBox(act);
          }
          printf("\n");
        }*/
        /*------------------ A* -------------------------*/
        printf("EMPIEZO A* \n");
        
        res2 =NULL;
        start2 = clock();
        res2 = (list) astar(initial_state);
        end2 = clock();
        
        printf("A* se tardo: %f\n", (float)(end2-start2)/CLOCKS_PER_SEC);
        if (res2) {
          printf("Lista 2: %d", res2->size);
          act = res2 -> first;
          for (i=0; i<res2->size; i++) {
              printf("%s ", getElemBox(act));
              act = getNextBox(act);
          }
          printf("\n");
        }
        free_state(initial_state);
        initial_state = NULL;
    }
    /*cierre del archivo de entrada*/
    fclose(file);
/*    printf("EMPIEZO IDA*!!\n");
    clock_t start = clock(); 
    list res = idastar();
    clock_t end = clock();
    printf("TERMINO IDA*!!\n");

    printf("EMPIEZO A* \n");
    clock_t start2 = clock();
    list res2 = (list) astar();
    clock_t end2 = clock();
    printf("TERMINO A*\n");

    int tam = res -> size;
    int i;

    box act;

    printf("IDA* se tardo: %f\n", (float)(end-start)/CLOCKS_PER_SEC);
    printf("Tiempo invertido en manhattan: %f\n", (float)mte/CLOCKS_PER_SEC);
    printf("Tiempo invertido sacando sucesores: %f\n", (float)ste/CLOCKS_PER_SEC);
    printf("A* se tardo: %f\n", (float)(end2-start2)/CLOCKS_PER_SEC);
    printf("\nTam de la lista: %d %d\n", tam, res2->size);

    printf("Lista 1: "); 
    act = res -> first;
    for (i=0; i<tam; i++) {
        printf("%s ", getElemBox(act));
        act = getNextBox(act);
    }
    printf("\n");

    printf("Lista 2: ");
    act = res2 -> first;
    for (i=0; i<res2->size; i++) {
        printf("%s ", getElemBox(act));
        act = getNextBox(act);
    }
    printf("\n");*/
}
