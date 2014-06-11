#include <iostream>
using namespace std;

int desp_4[3][4] = { {10,11,19,20}, {8,10,17,19}, {7,8,16,17}};
int desp_2[3][2] = { {10,11}, {8,10}, {7,8} };

int main (int argc, char* argv[]) {

  /* Clausulas para las filas */
  for (int i = 1; i<=729; i=i+9) { 
    for (int j = i; j<i+9; j++) { 
      for (int k = j+1; k<i+9; k++) { 
        cout << -j << " " << -k << " " << 0 << endl;
      }
    }
  }

  /* Clausulas para las columnas */
  for (int i = 1; i<=729; i=i+81) { 
    for (int j = i; j<i+9; j++) {
      for (int l = j; l<=72+j; l=l+9) {
        for (int k = l+9; k<=72+j; k=k+9) {
          cout << -l << " " << -k << " " << 0 << endl;
        }
      }
    }
  }

  /* Desplazamientos Cuadrado:
     1: 10,11,19,20
     2: 8,10,17,19
     3: 7,8,16,17
     4: 10,11
     5: 8,10
     6: 7,8
  */
  /* Clausulas para el cuadrado */
  int aux = 0;
  for (int i = 1; i < 729; i=i+27) {
    for (int j = i; j < i+9; j++) {
      for (int k = 0; k < 4; k++) {
        cout << -j << " " << -(j+desp_4[aux%3][k]) << " " << 0 << endl;
      }
      aux++;
    }
    aux = 0;
    for (int j = i+9; j < i+18; j++) {
      for (int k = 0; k < 2; k++) {
        cout << -j << " " << -(j+desp_2[aux%3][k]) << " " << 0 << endl;
      }
      aux++;
    }
  }

}
