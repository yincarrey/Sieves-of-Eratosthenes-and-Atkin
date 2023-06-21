#include "headers/header.h"
#define LIMITE 500000000


int main() {

  if(verificarEntero(LIMITE)){
    int limite = LIMITE;
    int numThreads = omp_get_num_procs();

    /* Calcular el 70% de los hilos y ajustar al entero mas cercano
      , asegurarse de que numThreads sea al menos 1
      y asignar el numero de hilos que se utilizaran */
    numThreads = static_cast<int>(round(numThreads * 0.7));
    numThreads = std::max(numThreads, 1);
    omp_set_num_threads(numThreads);

    // Calcular los números primos de forma paralela
    //criba de Atkin
    std::vector<int> primos = obtenerPrimos(cribaAtkin(limite), limite);
    /* //criba de Eratostenes (opcional)
    std::vector<int> primos = obtenerPrimos(cribaDeEratostenes(limite), limite); */

    // Mostrar los números primos
    mostrarPrimos(primos);
  }

  return 0;
}