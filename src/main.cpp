#include "header/header.h"

#define LIMITE 70000000


int main() {

  unsigned comienzo, final;
  comienzo = clock();

  int limite = LIMITE;
  int numThreads = omp_get_num_procs();

  /* Calcular el 80% de los hilos y ajustar al entero mas cercano
     , asegurarse de que numThreads sea al menos 1
     y asignar el numero de hilos que se utilizaran */
  numThreads = static_cast<int>(round(numThreads * 0.8));
  numThreads = std::max(numThreads, 1);
  omp_set_num_threads(numThreads);

  // Calcular los números primos de forma paralela
  //criba de Atkin
  std::vector<int> primos = obtenerPrimos(cribaAtkin(limite), limite);
  /* //criba de Eratostenes (opcional)
  std::vector<int> primos = obtenerPrimos(cribaDeEratostenes(limite), limite); */

  // Mostrar los números primos
  mostrarPrimos(primos);

  final = clock();

  //Calcular y mostrar el tiempo de ejecucion
  double tiempoEjecucion = (double(final - comienzo) / CLOCKS_PER_SEC);
  int minutos = static_cast<int>(tiempoEjecucion / 60);
  double segundos = tiempoEjecucion - minutos * 60.0;

  std::cout << "Tiempo de ejecucion: " << minutos << " min " << segundos << " seg" << std::endl;

  return 0;
}