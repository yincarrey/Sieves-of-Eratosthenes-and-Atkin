#include "header.h"

std::vector<bool> cribaAtkin(int limite) {
  std::vector<bool> esPrimo(limite + 1, false); // Inicializar todos los números como compuestos
  esPrimo[2] = esPrimo[3] = true; // Definir valores iniciales como primos

  // Pasos de la Criba de Atkin
  int raizLimite = static_cast<int>(std::sqrt(limite));

  #pragma omp parallel
  {
    #pragma omp for
    for (int x = 1; x <= raizLimite; ++x) {
      for (int y = 1; y <= raizLimite; ++y) {
        int n = (4 * x * x) + (y * y);
        if (n <= limite && (n % 12 == 1 || n % 12 == 5)) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n];
        }

        n = (3 * x * x) + (y * y);
        if (n <= limite && n % 12 == 7) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n];
        }

        n = (3 * x * x) - (y * y);
        if (x > y && n <= limite && n % 12 == 11) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n];
        }
      }
    }

    #pragma omp for nowait // Permitir que otros hilos continúen sin bloqueo
    for (int n = 5; n <= raizLimite; ++n) {
      if (esPrimo[n]) {
        int x = n * n;
        for (int k = x; k <= limite; k += x) {
          #pragma omp critical
          esPrimo[k] = false;
        }
      }
    }
  }

  return esPrimo;
}

std::vector<bool> cribaDeEratostenes(int limite) {
  std::vector<bool> esPrimo(limite + 1, true); // Inicializar todos los números como primos

  int sqrtLimite = static_cast<int>(std::sqrt(limite));

  #pragma omp parallel
  {
    #pragma omp for
    for (int p = 2; p <= sqrtLimite; ++p) {
      #pragma omp critical
      {
        if (esPrimo[p]) {
          for (int i = p * p; i <= limite; i += p) {
            esPrimo[i] = false;
          }
        }
      }
    }
  }

  return esPrimo;
}

std::vector<int> obtenerPrimos(const std::vector<bool>& esPrimo, int limite) {
  std::vector<int> primos;

  // Obtener los números primos del vector booleano en orden
  #pragma omp parallel
  {
    #pragma omp for ordered
    for (int n = 2; n <= limite ; ++n) {
      if (esPrimo[n]) {
        #pragma omp ordered
        primos.push_back(n);
      }
    }
  }

  return primos;
}


void mostrarPrimos(const std::vector<int>& primos) {
  // Imprimir los números primos encontrados en filas de 10

  std::vector<std::stringstream> resultados(omp_get_max_threads());

  #pragma omp parallel
  {
    std::stringstream& localStream = resultados[omp_get_thread_num()];

    #pragma omp for
    for (int i = 0; i < primos.size(); ++i) {
      localStream << primos[i] << " ";
      if ((i + 1) % 10 == 0) {
        localStream << std::endl;
      }
    }
  }

  // Imprimir los resultados en orden
  for (const auto& stream : resultados) {
    std::cout << stream.str();
  }

  std::cout 
    << std::endl 
    << std::endl  
    << "numeros encontrados: " 
    << primos.size() 
    << std::endl;
}

bool verificarEntero(int valor) {

  // Verificar si el valor es mayor que 0
  if (valor >= 2) {
    return true;
  }

  std::cout << "No existen numeros primos" << std::endl;
  return false;
}
