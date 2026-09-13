# Actividad 2.6 Problema Practico en OpenMP

## Integrantes
* Hernández Garcia Hector Gabriel
* Hernandez Morales Cristobal Giovanni
* Nava Gutiérrez Alan Santiago

## Descripcion de la Solucion
Esta practica implementa un sistem de búsqueda exhaustiva para encontrar una clave de prueba dentro de un espacio de combinaciones muy grande. Para evitar el desbordamiento de memoria y la creacion simultanea de todas las combinaciones, se utiliza una representación numerica basada en **conversión a Base 36**. Cada numero entero de 64 bits (`unsigned long long`) se mapea directamente a una cadena de caracteres unica mediante divisiones sucesivas. La practica cuenta con dos versiones: una **secuencial** y una **paralela** utilizando **OpenMP**, sedivide el espacio de trabajo de forma equitativa entre los hilos e implementa un mecanismo de detencion con sincronización para abortar la ejecución en cuanto un hilo encuentra la clave ganadora.

## Caracteres Utilizados
* Letras mayúsculas: `A - Z` (26 caracteres)
* Numeros: `0 - 9` (10 caracteres)
* **Total:** 36 caracteres permitidos.

## Algoritmos Implementados
* **Conversion Numérica a Base 36:** Transformación directa de un índice numérico a una cadena de caracteres sin almacenamiento previo en memoria.
* **Búsqueda Lineal Secuencial:** Recorrido iterativo de todo el espacio de búsqueda utilizando un único hilo de ejecución.
* **Búsqueda Paralela Segmentada:** División geométrica del espacio total de combinaciones basada en el número de hilos activos de OpenMP.

## Directivas y Funciones OpenMP
* `#pragma omp parallel`: Crea y gestiona el bloque en paralelo compartiendo variables de control global.
* `#pragma omp critical`: Seccion critica para proteger el flujo de escritura en consola (`std::cout`) y evitar condiciones de carrera al actualizar la bandera de exito y el hilo ganador.
* `omp_get_wtime()`: Medicion de tiempos de ejecucion en segundos.
* `omp_get_num_threads()`: Obtiene el numero total de hilos en ejecucion.
* `omp_get_thread_num()`: ID de cada hilo activo.

## Estructura del Proyecto
El codigo fuente se divide en tres archivos principales:
1. **`BuscadorClaves.h`**: Declaración de la clase, atributos privados, punteros para manejo estricto de arreglos dinamicos y firmas de metodos.
2. **`BuscadorClaves.cpp`**: Implementación de la logica matematica, validaciones de entrada, algoritmos de busqueda y directivas OpenMP.
3. **`main.cpp`**: Menu interactivo de consola, captura de datos y calculo metrico de rendimiento.

## Instrucciones de Compilacion y Ejecuciin (Code::Blocks)

1. **Creacion del Proyecto:**
   * Abrir Code::Blocks y crear un nuevo proyecto tipo *Console application* en C++.
   * Agregar los tres archivos del proyecto (`main.cpp`, `BuscadorClaves.cpp` y `BuscadorClaves.h`) en la misma carpeta.

2. **Configuración de OpenMP en el Compilador:**
   * En el menu superior seleccionar **Settings > Compiler > Compiler settings**, entrar a **Other compiler options** y escribir: `-fopenmp`
   * Hacer lo mismo en la pestaña **Linker settings Other  >linker options**, escribir: `-fopenmp`.

3. **Ejecucion:**
   * Presionar  *Build and Run*.
   * Ingresa la longitud de la clave ejemplo: `3` para la prueba rpida inicial.
   * Introducir la clave de prueba en mayúsculas ejemplo: `ABC` cuando el programa lo solicite en la consola.
