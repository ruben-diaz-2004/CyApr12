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


/**
 * Comprueba que al programa se le pasen los parámetros adecuados
 * @param argc, número de argumentos
 * @param argv, cada argumento que se le pasa al programa
 * @param KcorrectNumber, número correcto de parámetros
 * @return true, si todo funciona bien.
*/
bool CheckCorrectParameters(const int argc, char* argv[], const int kCorrectNumber) {
  if (argc > 1) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {
      std::cout << "Modo de empleo: ./EMST input.txt output.dot" << std::endl << std::endl;
      std::cout << "Este programa obtiene el Euclidean minimum spanning tree (EMST)" << std::endl;
      std::cout << "de un conjunto de puntos en dos dimensiones (2D)." << std::endl << std::endl;
      std::cout << "Parámetros:" << std::endl;
      std::cout << "  input.txt: fichero de texto con los puntos en 2D" << std::endl;
      std::cout << "  output.dot: fichero de texto con el árbol de expansión mínima" << std::endl;
      std::cout << "  en formato dot" << std::endl << std::endl;
      std::cout << std::endl << std::endl;
      exit(EXIT_SUCCESS);
    }
  }
  if (argc != kCorrectNumber) {
  std::cout << "Modo de empleo: ./EMST input.txt output.dot" << std::endl;
  std::cout << "Pruebe ./EMST --help para más información" << std::endl;
    exit(EXIT_SUCCESS);
  }
  return true;
}
