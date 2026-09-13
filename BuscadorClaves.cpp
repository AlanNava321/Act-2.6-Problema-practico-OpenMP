#include "BuscadorClaves.h"
#include <iostream>
#include <omp.h>

// ==============================================================================
// CONSTRUCTOR Y DESTRUCTOR
// ==============================================================================

BuscadorClaves::BuscadorClaves(int longitud) {
    longitudClave = longitud;
    totalCaracteres = 36; // 26 letras (A-Z) + 10 numeros (0-9)
    totalCombinaciones = 0;

    // Arreglo dinamico para la clave de prueba (+1 para el caracter nulo '\0')
    clavePrueba = new char[longitudClave + 1];

    // Arreglo dinamico para los caracteres permitidos
    caracteresPermitidos = new char[totalCaracteres];

    // Llenar el arreglo con A-Z
    int indice = 0;
    for (char c = 'A'; c <= 'Z'; c++) {
        caracteresPermitidos[indice++] = c;
    }
    // Llenar el arreglo con 0-9
    for (char c = '0'; c <= '9'; c++) {
        caracteresPermitidos[indice++] = c;
    }
}

BuscadorClaves::~BuscadorClaves() {
    delete[] clavePrueba;
    delete[] caracteresPermitidos;
}

// ==============================================================================
// METODOS MATEMATICOS Y DE VALIDACION
// ==============================================================================

unsigned long long BuscadorClaves::calcularPotencia(int base, int exponente) {
    unsigned long long resultado = 1;
    for (int i = 0; i < exponente; ++i) {
        resultado *= base;
    }
    return resultado;
}

void BuscadorClaves::calcularEspacio() {
    totalCombinaciones = calcularPotencia(totalCaracteres, longitudClave);
    std::cout << "Tamano del espacio de busqueda: " << totalCombinaciones << " combinaciones posibles.\n";
}

bool BuscadorClaves::validarClave(const char* ingreso) {
    if (ingreso == nullptr || ingreso[0] == '\0') {
        std::cout << "Error: La clave no puede estar vacia.\n";
        return false;
    }

    int longitudIngreso = 0;
    while (ingreso[longitudIngreso] != '\0') {
        longitudIngreso++;
    }

    if (longitudIngreso != longitudClave) {
        std::cout << "Error: La longitud de la clave debe ser exactamente de "
                  << longitudClave << " caracteres.\n";
        return false;
    }

    for (int i = 0; i < longitudIngreso; i++) {
        char c = ingreso[i];
        bool esMayuscula = (c >= 'A' && c <= 'Z');
        bool esNumero = (c >= '0' && c <= '9');

        if (!esMayuscula && !esNumero) {
            std::cout << "Error: Caracter invalido '" << c << "'. Solo A-Z y 0-9.\n";
            return false;
        }
    }

    for (int i = 0; i < longitudIngreso; i++) {
        clavePrueba[i] = ingreso[i];
    }
    clavePrueba[longitudIngreso] = '\0';

    return true;
}

void BuscadorClaves::indiceACombinacion(unsigned long long indice, char* combinacionDestino) {
    for (int i = longitudClave - 1; i >= 0; --i) {
        int modulo = indice % totalCaracteres;
        combinacionDestino[i] = caracteresPermitidos[modulo];
        indice /= totalCaracteres;
    }
    combinacionDestino[longitudClave] = '\0';
}

// ==============================================================================
// METODOS DE BUSQUEDA (SECUENCIAL Y PARALELA)
// ==============================================================================

double BuscadorClaves::busquedaSecuencial() {
    char* combinacionActual = new char[longitudClave + 1];
    unsigned long long combinacionesRevisadas = 0;
    bool encontrada = false;

    std::cout << "\n--- Iniciando Busqueda Secuencial ---\n";

    double tiempoInicio = omp_get_wtime();

    for (unsigned long long i = 0; i < totalCombinaciones; ++i) {
        indiceACombinacion(i, combinacionActual);
        combinacionesRevisadas++;

        bool sonIguales = true;
        for (int j = 0; j < longitudClave; ++j) {
            if (combinacionActual[j] != clavePrueba[j]) {
                sonIguales = false;
                break;
            }
        }

        if (sonIguales) {
            encontrada = true;
            break;
        }
    }

    double tiempoFin = omp_get_wtime();
    double tiempoTotal = tiempoFin - tiempoInicio;

    std::cout << "Estado: Busqueda Finalizada\n";
    std::cout << "Combinaciones revisadas: " << combinacionesRevisadas << "\n";

    if (encontrada) {
        std::cout << "Clave encontrada: " << combinacionActual << "\n";
    } else {
        std::cout << "Clave no encontrada en el espacio de busqueda.\n";
    }

    delete[] combinacionActual;
    return tiempoTotal;
}

double BuscadorClaves::busquedaParalela() {
    bool compartidaEncontrada = false;
    int hiloGanador = -1;
    char* combinacionGanadora = new char[longitudClave + 1];

    std::cout << "\n--- Iniciando Busqueda Paralela ---\n";
    double tiempoInicio = omp_get_wtime();

    #pragma omp parallel shared(compartidaEncontrada, hiloGanador, combinacionGanadora)
    {
        int num_hilos = omp_get_num_threads();
        int id_hilo = omp_get_thread_num();

        unsigned long long rango = totalCombinaciones / num_hilos;
        unsigned long long inicio = id_hilo * rango;
        unsigned long long fin = (id_hilo == num_hilos - 1) ? totalCombinaciones : inicio + rango;
        unsigned long long cantidad = fin - inicio;

        char* strInicio = new char[longitudClave + 1];
        char* strFin = new char[longitudClave + 1];
        indiceACombinacion(inicio, strInicio);
        indiceACombinacion(fin - 1, strFin);

        #pragma omp critical
        {
            std::cout << "Hilo " << id_hilo << " -> Inicio: " << strInicio
                      << " -> Fin: " << strFin << " -> Cantidad: " << cantidad << "\n";
        }

        char* combinacionActual = new char[longitudClave + 1];
        unsigned long long combinacionesRevisadasLocal = 0;
        bool encontreLocal = false;

        for (unsigned long long i = inicio; i < fin; ++i) {
            if (compartidaEncontrada) {
                break;
            }

            indiceACombinacion(i, combinacionActual);
            combinacionesRevisadasLocal++;

            bool sonIguales = true;
            for (int j = 0; j < longitudClave; ++j) {
                if (combinacionActual[j] != clavePrueba[j]) {
                    sonIguales = false;
                    break;
                }
            }

            if (sonIguales) {
                #pragma omp critical
                {
                    if (!compartidaEncontrada) {
                        compartidaEncontrada = true;
                        hiloGanador = id_hilo;
                        for(int k = 0; k <= longitudClave; k++) {
                            combinacionGanadora[k] = combinacionActual[k];
                        }
                    }
                }
                encontreLocal = true;
                break;
            }
        }

        #pragma omp critical
        {
            std::cout << "Hilo " << id_hilo << " finaliza. Combinaciones revisadas: "
                      << combinacionesRevisadasLocal;
            if (encontreLocal) {
                std::cout << " [! CLAVE ENCONTRADA POR ESTE HILO !]\n";
            } else {
                std::cout << "\n";
            }
        }

        delete[] strInicio;
        delete[] strFin;
        delete[] combinacionActual;
    }

    double tiempoFin = omp_get_wtime();
    double tiempoTotal = tiempoFin - tiempoInicio;

    std::cout << "\nEstado: Busqueda Paralela Finalizada\n";
    if (compartidaEncontrada) {
        std::cout << "Clave encontrada por el hilo: " << hiloGanador << "\n";
        std::cout << "Clave encontrada: " << combinacionGanadora << "\n";
    } else {
        std::cout << "Clave no encontrada.\n";
    }

    delete[] combinacionGanadora;
    return tiempoTotal;
}
