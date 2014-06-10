#!/bin/bash

# Verificamos el numero de argumentos
if [ "$#" -ne 2 ]; then
    echo "Ejecute el Script de la siguiente manera:"
    echo "    ./sudoku_solver <archivo_instancias> <archivo_soluciones>"
    exit
fi

# Imprimimos al usuario de donde se leera y donde se escribira
echo "Sudoku Solver"
echo "    Input File: $1"
echo "    Output File: $2"

echo "* Traduciendo instancias de Sudoku a CNF *"

# Creamos un directorio temporal en donde almacenar las instancias en CNF
mkdir "sudoku_cnf_tmp"

# Generamos las instancias en CNF
g++ encoder/main.cc
cp a.out "sudoku_cnf_tmp"
rm a.out
cp encoder/teoria_general_2 "sudoku_cnf_tmp"
cp $1 "sudoku_cnf_tmp"
cd "sudoku_cnf_tmp"
$(./a.out $1)
cd ..

# Pasamos las instancias en CNF por el SAT solver
echo "* Compilando Zchaff *"

cd zchaff
make clean > /dev/null
make > /dev/null
cd ..

echo "* Resolviendo instancias en CNF*"
cp zchaff/zchaff ./zchaff_solver
g++ decoder/decoder.cc
mkdir "sudoku_cnf_soluciones_tmp"
numero_casos=$(ls "sudoku_cnf_tmp" | wc -l)
for i in $(seq 1 $numero_casos)
do
  $(echo $(./zchaff_solver "sudoku_cnf_tmp/sudoku_$i.cnf") > "sudoku_cnf_soluciones_tmp/sudoku_$i.out")
  $(echo $(./a.out "sudoku_cnf_soluciones_tmp/sudoku_$i.out") > $2)
done

rm zchaff_solver
rm a.out

# Eliminamos el directorio temporal con instancias en CNF
#rm -r "sudoku_cnf_soluciones_tmp"
#rm -r "sudoku_cnf_tmp"
