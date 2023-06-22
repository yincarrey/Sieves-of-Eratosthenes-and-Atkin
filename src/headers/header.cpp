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
        //Implementación del teorema de los residuos
        if (n <= limite && (n % 12 == 1 || n % 12 == 5)) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n]; // Marcar números candidatos como primos
        }

        n = (3 * x * x) + (y * y);
        if (n <= limite && n % 12 == 7) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n]; // Marcar números candidatos como primos
        }

        n = (3 * x * x) - (y * y);
        if (x > y && n <= limite && n % 12 == 11) {
          #pragma omp critical
          esPrimo[n] = !esPrimo[n]; // Marcar números candidatos como primos
        }
      }
    }

    #pragma omp for nowait // Permitir que otros hilos continúen sin bloqueo
    for (int n = 5; n <= raizLimite; ++n) {
      if (esPrimo[n]) {
        int x = n * n;
        for (int k = x; k <= limite; k += x) {
          #pragma omp critical
          esPrimo[k] = false; // Marcar múltiplos de números primos encontrados como compuestos
        }
      }
    }
  }

  return esPrimo;
}

std::vector<bool> cribaDeEratostenes(int limite) {
  std::vector<bool> esPrimo(limite + 1, true); // Inicializar todos los números como primos

  int sqrtLimite = static_cast<int>(std::sqrt(limite)); // Calcular la raíz cuadrada entera del límite, Open MP no permite p*p

  #pragma omp parallel
  {
    #pragma omp for
    for (int p = 2; p <= sqrtLimite; ++p) { //Iterar sobre el limite para marcar los numeros
      #pragma omp critical
      {
        if (esPrimo[p]) {
          for (int i = p * p; i <= limite; i += p) {
            esPrimo[i] = false; // Marcar números múltiplos de p como compuestos
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


/* La siguiente funcion utiliza almacenamiento parcial en vectores de flujo de salida 
para imprimir los números primos en filas de 10 elementos. Se divide la tarea entre 
los hilos, cada uno escribiendo en su propio flujo de salida local. Luego, los 
resultados se imprimen en orden y se muestra el número total de primos encontrados. */

void mostrarPrimos(const std::vector<int>& primos) {
  // Almacenamiento parcial en vectores de flujo de salida para imprimir los números primos en filas de 10 elementos
  std::vector<std::stringstream> resultados(omp_get_max_threads());

  #pragma omp parallel
  {
    std::stringstream& localStream = resultados[omp_get_thread_num()];

    // Iterar sobre los números primos y escribirlos en el flujo de salida local
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

  // Imprimir el número total de primos encontrados
  std::cout 
    << std::endl 
    << std::endl  
    << "Números encontrados: " 
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
