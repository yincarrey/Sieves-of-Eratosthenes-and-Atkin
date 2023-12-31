#ifndef HEADER
#define HEADER

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <sstream>
#include <omp.h>

std::vector<bool> cribaAtkin(int limite);
std::vector<bool> cribaDeEratostenes(int limite);
std::vector<int> obtenerPrimos(const std::vector<bool>& esPrimo, int limite);
void mostrarPrimos(const std::vector<int>& primos);
bool verificarEntero(int valor);

#endif