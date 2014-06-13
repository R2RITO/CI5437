#include <iostream>
using namespace std;

int desp_4[3][4] = { {10,11,19,20}, {8,10,17,19}, {7,8,16,17}};
int desp_2[3][2] = { {10,11}, {8,10}, {7,8} };

int main (int argc, char* argv[]) {

  /*
     1  2  3  4  5  6  7  8  9  
     10 11 12 13 14 15 16 17 18
     19 20 21 22 23 24 25 26 27
     28 29 30 31 32 33 34 35 36
     37 38 39 40 41 42 43 44 45
     46 47 48 49 50 51 52 53 54
     55 56 57 58 59 60 61 62 63
     64 65 66 67 68 69 70 71 72
     73 74 75 76 77 78 79 80 81
  */
  /* Clausulas de Arturo */
  for (int i = 1; i <= 81; i++) {
    for (int j = i; j <= 729; j=j+81) {
        cout << j << " ";
    }
    cout << "0\n";
  }

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
