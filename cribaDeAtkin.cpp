#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <omp.h>

#define LIMITE 300000000

std::vector<int> cribaAtkin() {
  std::vector<bool> esPrimo(LIMITE + 1, false); // Inicializar todos los números como compuestos
  esPrimo[2] = esPrimo[3] = true;
  std::vector<std::vector<int>> primos_temp(omp_get_max_threads());

  // Pasos de la Criba de Atkin
  int raizLimite = static_cast<int>(std::sqrt(LIMITE));

  #pragma omp parallel
  {
    #pragma omp for
    for (int x = 1; x <= raizLimite; ++x) {
      for (int y = 1; y <= raizLimite; ++y) {
        int n = (4 * x * x) + (y * y);
        if (n <= LIMITE && (n % 12 == 1 || n % 12 == 5)) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n];
        }

        n = (3 * x * x) + (y * y);
        if (n <= LIMITE && n % 12 == 7) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n];
        }

        n = (3 * x * x) - (y * y);
        if (x > y && n <= LIMITE && n % 12 == 11) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n];
        }
      }
    }

    #pragma omp for nowait // Permitir que otros hilos continúen sin bloqueo
    for (int n = 5; n <= raizLimite; ++n) {
      if (esPrimo[n]) {
        int x = n * n;
        for (int k = x; k <= LIMITE; k += x) {
          #pragma omp critical
          esPrimo[k] = false;
        }
      }
    }

    #pragma omp for
    for (int n = 2; n <= LIMITE; ++n) {
      if (esPrimo[n]) {
        primos_temp[omp_get_thread_num()].push_back(n);
      }
    }
  }

  // Fusionar los vectores de primos de cada hilo en uno solo
  std::vector<int> primos;
  for (const auto& p : primos_temp) {
    primos.insert(primos.end(), p.begin(), p.end());
  }

  return primos;
}


void mostrarPrimos(const std::vector<int>& primos) {
  // Imprimir los números primos encontrados en columnas de 10

#pragma omp parallel
  {
    #pragma omp for ordered
    for (int i = 0; i < primos.size(); ++i) {
      #pragma omp ordered
      {
        std::cout << primos[i] << " ";
        if ((i + 1) % 10 == 0) {
          std::cout << std::endl;
        }
      }
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

  unsigned comienzo, final;

  comienzo = clock();

  int numThreads = omp_get_num_procs();

  numThreads = static_cast<int>(numThreads * 0.8);  // Calcular el 80% de los hilos
  // Asegurarse de que numThreads sea al menos 1
  numThreads = std::max(numThreads, 1);
  // Ajustar numThreads al número entero más cercano
  numThreads = static_cast<int>(std::round(numThreads));
  
  omp_set_num_threads(numThreads);
  // Calcular los números primos de forma paralela
  std::vector<int> primos = cribaAtkin();

  // Mostrar los números primos
  mostrarPrimos(primos);

  final = clock();

  double tiempoEjecucion = (double(final-comienzo)/CLOCKS_PER_SEC);
  std::cout << "Tiempo de ejecucion [seg]: " << tiempoEjecucion << std::endl;

  return 0;
}

