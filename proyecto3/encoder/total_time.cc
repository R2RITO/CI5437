// basic file operations
#include <iostream>
#include <stdlib.h>

using namespace std;

int main (int argc, char* argv[]) {

  string line;

  if (argc < 3) {
    return 0;
  }
  
  
  std::string lfloat = argv[1]; //operando flotante izquierdo
  std::string rfloat = argv[2]; //operando flotante derecho

  
  double left_float  = ::atof(lfloat.c_str());
  double right_float = ::atof(rfloat.c_str());
  double result = left_float + right_float;
  std::cout << result;
}
