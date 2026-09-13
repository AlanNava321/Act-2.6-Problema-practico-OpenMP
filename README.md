# Busqueda Exhaustiva Secuencial y Paralela con OpenMP

## Integrantes
* Alan Santiago Nava Gutiérrez (Universidad de Guadalajara)

## Descripción de la Solución
Esta práctica implementa un sistema de búsqueda exhaustiva (fuerza bruta) para encontrar una clave de prueba dentro de un espacio de combinaciones masivo. Para evitar el desbordamiento de memoria y la creación simultánea de todas las combinaciones, se utiliza una representación numérica interna basada en **conversión a Base 36**. Cada número entero de 64 bits (`unsigned long long`) se mapea directamente a una cadena de caracteres única mediante divisiones sucesivas. La solución cuenta con dos versiones: una **secuencial** y una **paralela** utilizando **OpenMP**, la cual divide el espacio de trabajo de forma equitativa entre los hilos disponibles e implementa un mecanismo de detención temprana con sincronización crítica para abortar la ejecución en cuanto un hilo encuentra la clave ganadora.

## Caracteres Utilizados
* Letras mayúsculas: `A - Z` (26 caracteres)
* Números: `0 - 9` (10 caracteres)
* **Total:** 36 caracteres permitidos.

## Algoritmos Implementados
* **Conversión Numérica a Base 36:** Transformación directa de un índice numérico a una cadena de caracteres sin almacenamiento previo en memoria.
* **Búsqueda Lineal Secuencial:** Recorrido iterativo de todo el espacio de búsqueda utilizando un único hilo de ejecución.
* **Búsqueda Paralela Segmentada:** División geométrica del espacio total de combinaciones basada en el número de hilos activos de OpenMP.

## Directivas y Funciones OpenMP Utilizadas
* `#pragma omp parallel`: Creación y gestión de la región paralela compartiendo variables de control global.
* `#pragma omp critical`: Sección crítica para proteger el flujo de escritura en consola (`std::cout`) y evitar condiciones de carrera al actualizar la bandera de éxito y el hilo ganador.
* `omp_get_wtime()`: Medición de tiempos de ejecución de alta precisión en segundos.
* `omp_get_num_threads()`: Obtención del número total de hilos en ejecución.
* `omp_get_thread_num()`: Identificador único (ID) de cada hilo activo.

## Estructura del Proyecto
El código fuente se encuentra modularizado en tres archivos principales:
1. **`BuscadorClaves.h`**: Declaración de la clase, atributos privados, punteros para manejo estricto de arreglos dinámicos y firmas de métodos.
2. **`BuscadorClaves.cpp`**: Implementación de la lógica matemática, validaciones de entrada, algoritmos de búsqueda y directivas OpenMP.
3. **`main.cpp`**: Menú interactivo de consola, captura de datos y cálculo métrico de rendimiento (Speedup).

## Instrucciones de Compilación y Ejecución (Code::Blocks / Windows)

1. **Creación del Proyecto:**
   * Abre Code::Blocks y crea un nuevo proyecto tipo *Console application* en C++.
   * Agrega los tres archivos del proyecto (`main.cpp`, `BuscadorClaves.cpp` y `BuscadorClaves.h`) en la misma carpeta del workspace.

2. **Configuración de OpenMP en el Compilador:**
   * Ve al menú superior y selecciona **Settings > Compiler...**
   * En la pestaña **Compiler settings**, entra a **Other compiler options** y escribe: `-fopenmp`
   * Cambia a la pestaña **Linker settings**, y en **Other linker options**, escribe: `-fopenmp` (si el enlazador lo requiere, puedes añadir `-lgomp` al lado). Haz clic en *OK*.

3. **Ejecución:**
   * Presiona **F9** (*Build and Run*).
   * Ingresa la longitud de la clave (ej. `3` para la prueba rápida inicial, o `7`-`10` para pruebas de mayor escala).
   * Introduce la clave de prueba en mayúsculas (ej. `ABC`) cuando el programa lo solicite en la consola.