#ifndef BUSCADOR_CLAVES_H
#define BUSCADOR_CLAVES_H

class BuscadorClaves {
private:
    // Atributos para la gestion del espacio de busqueda (Arreglos dinamicos estrictos)
    char* caracteresPermitidos;
    int totalCaracteres;
    int longitudClave;

    // Atributos para la clave a buscar y el limite de iteraciones
    char* clavePrueba;
    unsigned long long totalCombinaciones;

    // Metodo auxiliar matematico interno para calcular el espacio
    unsigned long long calcularPotencia(int base, int exponente);

public:
    // Constructor y Destructor
    BuscadorClaves(int longitud);
    ~BuscadorClaves();

    // Metodos de configuracion y validacion
    void calcularEspacio();
    bool validarClave(const char* ingreso);

    // Metodo fundamental: Convierte un indice numerico a su combinacion en texto (Base 36)
    void indiceACombinacion(unsigned long long indice, char* combinacionDestino);

    // Metodos principales de busqueda
    // Ambos retornan un double que representa el tiempo total de ejecucion en segundos
    double busquedaSecuencial();
    double busquedaParalela();
};

#endif // BUSCADOR_CLAVES_H
