#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "Ejecutar: ./main <archivo.txt>" << std::endl;
        return 0;
    }

    std::fstream salida;
    salida.open(argv[1]);

    if (!salida.good()) 
        return 1;

    std::string linea;

    for (int i=0; i<5; i++) {        
        std::getline(salida,linea);
    }

    std::getline(salida,linea);

    salida.close();

    std::string delimitador = " ";

    size_t pos = 0;
    int valor, aux;
    std::string token;
    int tablero[9][9] = { 0 };

    pos = linea.find("Random");
    linea = linea.substr(0,pos);
    
    pos = 0;

    while ((pos = linea.find(delimitador)) != std::string::npos) {
        token = linea.substr(0, pos);
        std::stringstream convert(token);

        if ( !(convert >> valor) )
            valor = 0;

        if (valor > 0) {            

            // Obtener el valor del numero a escribir
            aux = ((valor-1) / 81) + 1;

            // Obtener la fila.
            int fila = 1;
            int val_normal = valor; // Modificar valor para que vaya de 1 a 81

            while (val_normal > 81)
                val_normal = val_normal - 81;

            while (val_normal > 9) {
                val_normal = val_normal - 9;
                fila++;
            }

            tablero[fila-1][val_normal-1] = aux;

        }

        linea.erase(0, pos + delimitador.length());
    }
    // Imprimir el tablero
    for (int f=0; f<9; f++) {

        for (int c=0; c<9; c++) {
            std::cout << tablero[f][c] << "  ";
        }
        std::cout << std::endl;
    }
}

