// basic file operations
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <list>

#define NUM_CLAUSULAS_TEORIA_BASE 7371
#define NUM_VARIABLES 729

using namespace std;

int main (int argc, char* argv[]) {

  string line;

  if (argc < 2) {
    cout << "Ejecutar: ./main <archivo.txt>" << endl;
    return 0;
  }

  ifstream teoria ("teoria_general_2");
  ifstream myfile (argv[1]);

  int cont = 1;
  ofstream outfile;
  ostringstream filename;
  
  if (myfile.is_open())  {
    while ( getline (myfile,line) ) {

      ifstream teoria ("teoria_general_2");

      /* Se abre un archivo en donde escribir la instancia en formato CNF*/
      filename << "sudoku_" << cont << ".cnf";
      outfile.open(filename.str().c_str());

      /* Se obtienen los literales de la instancia */
      list<int> literales;
      for (int i = 1; i <= 81; i++) {
        if (line[i-1] != '.') {
            literales.push_back((line[i-1]-49)*81 + i);
        }
      }

      /* Se coloca el encabezado */
      outfile << "p cnf 729 " 
              <<  NUM_CLAUSULAS_TEORIA_BASE + literales.size() << endl;

      /* Se agregan las clausulas unitarias*/
      for(std::list<int>::iterator list_iter = literales.begin(); 
          list_iter != literales.end(); list_iter++) {
          outfile << *list_iter << " 0" << endl;
      }

      /* Se copia la teoria base */
      while ( getline (teoria,line) ) {
        outfile << line << endl;
      }

      /* Se prepara para el siguiente archivo */
      teoria.close();
      outfile.close();
      filename.str(string());
      cont++;
    }
    myfile.close();
  } else { 
    cout << "Unable to open file" << endl; 
  }

  return 0;

}
