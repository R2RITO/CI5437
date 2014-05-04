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

    int num = 1;

    while ( fgets (instance, BUFFER_SIZE, file)) {

        printf("%3d : ", num);

        /*------------------ IDA* -------------------------*/
/*        state initial_state = init(instance);
        printf("\tIDA* : ");
        clock_t start2 = clock();
        idastar(initial_state);
        clock_t end2 = clock();
        printf(" Tiempo: %f Segundos.", (float)(end2-start2)/CLOCKS_PER_SEC);
*/

       /*------------------ A* -------------------------*/
        printf("\n\tA*   : ");        
        start2 = clock();
        astar(initial_state);
        end2 = clock();
        
        printf("Tiempo: %f Segundos.\n", (float)(end2-start2)/CLOCKS_PER_SEC);

        //free_state(initial_state);
        initial_state = NULL;
        num++;
    }
    /*cierre del archivo de entrada*/
    fclose(file);
}
