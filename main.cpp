/*
 Actividad 2.6 - Problema práctico en OpenMP
 Integrantes:
 Hernandez Garcia Hector Gabriel
 Hernandez Morales Cristobal Giovanni
 Nava Gutierrez Alan Santiago
*/

#include <iostream>
#include "BuscadorClaves.h"

int main() {
    std::cout << "Hernandez Garcia Hector Gabriel\n";
    std::cout << "Hernandez Morales Cristobal Giovanni\n";
    std::cout << "Nava Gutierrez Alan Santiago\n\n";

    int longitud;
    // Buffer estático solo para capturar la entrada de la consola.
    // La clase se encarga de pasarlo a un arreglo dinámico después.
    char bufferIngreso[100];

    std::cout << "========================================================\n";
    std::cout << "   Busqueda Exhaustiva Secuencial y Paralela   \n";
    std::cout << "========================================================\n\n";

    // 1. Configuración de longitud
    std::cout << "Ingrese la longitud de la clave a probar: ";
    std::cin >> longitud;

    // Instanciar el objeto
    BuscadorClaves buscador(longitud);
    buscador.calcularEspacio();

    // 2. Ingreso y validación de la clave
    bool esValida = false;
    while (!esValida) {
        std::cout << "\nIngrese la clave de prueba de " << longitud << " caracteres (Solo A-Z y 0-9): ";
        std::cin >> bufferIngreso;

        // Verifica requisitos y la almacena si es correcta
        esValida = buscador.validarClave(bufferIngreso);
    }

    std::cout << "\n========================================================\n";
    std::cout << "Iniciando pruebas de rendimiento para la clave: " << bufferIngreso << "\n";
    std::cout << "========================================================\n";

    // 3. Ejecución Secuencial
    double tSecuencial = buscador.busquedaSecuencial();

    std::cout << "\n--------------------------------------------------------\n";

    // 4. Ejecución Paralela
    double tParalelo = buscador.busquedaParalela();

    std::cout << "\n========================================================\n";
    std::cout << "                  COMPARACION DE RENDIMIENTO            \n";
    std::cout << "========================================================\n";
    std::cout << "Tiempo version secuencial : " << tSecuencial << " segundos.\n";
    std::cout << "Tiempo version paralela   : " << tParalelo << " segundos.\n";

    // 5. Cálculo y análisis de Speedup
    if (tParalelo > 0) {
        double speedup = tSecuencial / tParalelo;
        std::cout << "Speedup (Aceleracion)     : " << speedup << "x\n\n";

        if (speedup > 1.0) {
            std::cout << "Analisis: El paralelismo represento una mejora significativa, "
                      << "siendo " << speedup << " veces mas rapido.\n";
        } else {
            std::cout << "Analisis: No hubo mejora. Esto es normal en claves muy cortas (ej. 3 caracteres) "
                      << "donde la sobrecarga de crear hilos en OpenMP toma mas tiempo que la busqueda en si.\n";
        }
    }

    std::cout << "\nPractica finalizada correctamente.\n";

    std::cout << "Hernandez Garcia Hector Gabriel\n";
    std::cout << "Hernandez Morales Cristobal Giovanni\n";
    std::cout << "Nava Gutierrez Alan Santiago\n\n";

    return 0;
}
