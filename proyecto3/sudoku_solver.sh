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


# Generamos las instancias en CNF
g++ encoder/main.cc -o encoder_exe
cp  encoder/teoria_general_2 teoria_general_2

# Pasamos las instancias en CNF por el SAT solver
echo "* Compilando Zchaff *"

cd zchaff
make clean > /dev/null
make > /dev/null
cd ..

echo "* Resolviendo instancias en CNF*"
cp zchaff/zchaff ./zchaff_solver
g++ decoder/decoder.cc -o decoder_exe
g++ encoder/total_time.cc -o timer_exe
numero_caso=1
input_file=$1
total_time=0
while read -r line
do
  echo -n "   - Analizando Sudoku # $numero_caso ... "
  echo $line
  echo $line > sudoku_actual.txt 
   
  #generacion del archivo .cnf
  $(./encoder_exe sudoku_actual.txt)
  #rm -r sudoku_actual.txt
  
  #generacion del input para el decoder
  $((./zchaff_solver sudoku.cnf) > sudoku.out)
  #rm -r sudoku.cnf
  
  #obtenemos el tiempo que demoro el solucionador zchaff en operar
  sudoku_time=$(tail -2 sudoku.out | head -1 | awk '{print $4}')
  echo "- Completado en $sudoku_time segundo(s)"
  
  $(echo $(./decoder_exe sudoku.out) >> $2)    
 # rm -r sudoku.out  
  
  total_time=$( (./timer_exe $total_time $sudoku_time) |  awk '{print $1}')

  numero_caso=$(($numero_caso + 1))
done < $input_file

echo "* Analisis completado - Tiempo Total: $total_time segundo(s)*"

#se remueven los archivos generados
rm -r encoder_exe
rm -r decoder_exe
rm -r timer_exe
rm -r zchaff_solver
rm -r teoria_general_2
