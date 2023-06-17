#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <omp.h>

#define LIMITE 50000000

std::vector<int> cribaDeEratostenes() {
  std::vector<bool> esPrimo(LIMITE + 1, true); // Inicializar todos los números como primos
  std::vector<std::vector<int>> primos_temp(omp_get_max_threads());

  int sqrtLimite = static_cast<int>(std::sqrt(LIMITE));

  #pragma omp parallel
  {
    #pragma omp for
    for (int p = 2; p <= sqrtLimite; ++p) {
      if (esPrimo[p]) {
        for (int i = p * p; i <= LIMITE; i += p) {
          esPrimo[i] = false;
        }
      }
    }

    #pragma omp for
    for (int p = 2; p <= LIMITE; ++p) {
      if (esPrimo[p]) {
        primos_temp[omp_get_thread_num()].push_back(p);
      }
    }
  }

  std::vector<int> primos;
  for (const auto& p : primos_temp) {
    primos.insert(primos.end(), p.begin(), p.end());
  }

  return primos;
}

void mostrarPrimos(const std::vector<int>& primos) {
  // Imprimir los números primos encontrados en filas de 10
  for (int i = 0; i < primos.size(); ++i) {
    std::cout << primos[i] << " ";
    if ((i + 1) % 10 == 0) {
      std::cout << std::endl;
    }
  }

  std::cout 
  << std::endl 
  << std::endl  
  << "numeros encontrados: " 
  << primos.size() 
  << std::endl;
}

int main() {
  int numThreads = omp_get_num_procs();

  unsigned comienzo, final;

  comienzo = clock();

  numThreads = static_cast<int>(numThreads * 0.8);  // Calcular el 80% de los hilos
  // Asegurarse de que numThreads sea al menos 1
  numThreads = std::max(numThreads, 1);
  // Ajustar numThreads al número entero más cercano
  numThreads = static_cast<int>(std::round(numThreads));

  omp_set_num_threads(numThreads);
  
  std::vector<int> primos = cribaDeEratostenes();

  mostrarPrimos(primos);

  final = clock();

  double tiempoEjecucion = (double(final-comienzo)/CLOCKS_PER_SEC);
  std::cout << "Tiempo de ejecucion [seg]" << tiempoEjecucion << std::endl;

  return 0;
}