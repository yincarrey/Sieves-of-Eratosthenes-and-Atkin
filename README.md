# Algoritmos para la Determinación de Números Primos

## Descripción

Este proyecto se centra en abordar la desafiante problemática de determinar los números primos en conjuntos de datos de gran magnitud. Para ello, se realizó una exhaustiva investigación que exploró diversas metodologías y algoritmos empleados en esta tarea.

Durante la fase de investigación, se llevó a cabo un análisis detallado de dos algoritmos fundamentales:

- La Criba de Atkin
- La Criba de Eratóstenes

Estos algoritmos son ampliamente reconocidos en el ámbito de las matemáticas y la informática por su eficiencia en la identificación de números primos dentro de un rango
dado.

Además de profundizar en el aspecto teórico de los algoritmos, se procedió a su implementación práctica en el lenguaje de programación C++, haciendo uso de la biblioteca
OpenMP. Esta elección estratégica permitió explorar el potencial de la programación multiproceso y paralela, con el objetivo de mejorar el rendimiento y agilizar el
proceso de búsqueda de números primos en sistemas que disponen de múltiples núcleos de procesamiento.

Durante la implementación, se abordaron diversas problemáticas relacionadas con el rendimiento y la posible sobrecarga del sistema al ejecutar los algoritmos en conjuntos
de datos extensos. Se realizaron evaluaciones comparativas entre la Criba de Atkin y la Criba de Eratóstenes para determinar cuál de ellos ofrecía un mejor desempeño en
diferentes escenarios.

A través del análisis de la complejidad temporal, expresada mediante la notación Big O, se obtuvieron conclusiones sólidas sobre la eficiencia relativa de los algoritmos,
permitiendo seleccionar la opción más adecuada para la búsqueda de números primos en el contexto de la problemática planteada.

Con esta investigación detallada y rigurosa, se espera proporcionar un enfoque sólido y fundamentado para abordar el desafío de encontrar números primos en grandes
conjuntos de datos, allanando el camino hacia futuros avances en el ámbito de la computación y las matemáticas.

A través del análisis de la complejidad temporal, expresada mediante la notación Big O, se obtuvieron conclusiones sólidas sobre la eficiencia relativa de los algoritmos,
permitiendo seleccionar la opción más adecuada para la búsqueda de números primos en el contexto de la problemática planteada.

Con esta investigación detallada y rigurosa, se espera proporcionar un enfoque sólido y fundamentado para abordar el desafío de encontrar números primos en grandes
conjuntos de datos, allanando el camino hacia futuros avances en el ámbito de la computación y las matemáticas.

## Algoritmos para determinar números primos

### Criba de Eratóstenes

La Criba de Eratóstenes es un antiguo algoritmo que permite encontrar todos los números primos en un rango determinado de valores. Fue desarrollado por el matemático griego
Eratóstenes de Cirene alrededor del siglo III a.C. Este algoritmo es eficiente para encontrar números primos hasta un límite predefinido y se basa en el principio de eliminar
los múltiplos de cada número primo encontrado.

#### Metodología

El algoritmo de la Criba de Eratóstenes sigue los siguientes pasos:

1. Crear una lista de números desde 2 hasta el valor máximo deseado.
2. Inicializar una variable llamada "p" en 2, que será el primer número primo.
3. Iterar sobre la lista de números y, para cada número, realizar lo siguiente:
4. Si el número actual no ha sido marcado como múltiplo de otro número primo previamente encontrado, se considera como un número primo válido.
5. Marcar todos los múltiplos del número actual como compuestos (no primos). Esto se logra eliminando los múltiplos del número actual de la lista.
6. Avanzar al siguiente número no marcado en la lista y repetir el paso anterior.

Al finalizar el proceso, los números que queden en la lista serán los números primos encontrados.
