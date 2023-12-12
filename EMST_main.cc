/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 04/12/2023
  * @brief Este programa obtiene el Euclidean minimum spanning tree (EMST)
  *  de un conjunto de puntos en dos dimensiones (2D)
  */
#include <iostream>
#include <fstream>
#include "parameters.cc"
#include "point_set.h"
#include <sstream>
#include <string>



int main(int argc, char *argv[]) {
  CheckCorrectParameters(argc, argv, 3);

  std::ifstream input_TM{argv[1]};
  std::ofstream output_tape{argv[2]};

  std::string line;
  std::stringstream ss;

  while (std::getline(input_TM, line)) {
    if (line[0] != '#') {
      ss << line << std::endl;
    }
  }


  CyA::point_vector points;
  ss >> points;

  CyA::point_set ps(points);
  ps.write(output_tape);
  
  return 0;
}