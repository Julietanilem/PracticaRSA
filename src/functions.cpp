#include <iostream>
#include <cmath>
#include <random>
#include <stdint.h>


// A
/** Eleva a a la b recortando con mod */
uint64_t potenciaMod(uint64_t a, uint64_t b, uint64_t mod){
    uint64_t res = 1;

}

/**Encuentra la combinación lineal de a y b que resulta en 1. */
int64_t mcde(uint64_t a, uint64_t b, int64_t &x, int64_t &y){

}

/** Encuentra el inverso multiplicativo módulo M. Es mejor obtenerlo
    con el algoritmo de euclides extendido */
uint64_t invMult(uint64_t a, uint64_t mod){

}

// B

/** Encuentra el máximo común divisor entre a y b. */
int64_t mcd(uint64_t a, uint64_t b){

}

/** Nos dice si un número es primo o no */
bool esPrimo(uint64_t n){

}


/** Nos dice si 2 números son coprimos o primos relativos */
bool coprimos(uint64_t a, uint64_t b){

}

/** Nos regresa la función phi de euler de un número n */
uint64_t phiEuler(uint64_t n){

}

/** Función auxiliar para generar números aleatorios pequeños */
uint rand(uint start, uint end){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(start, end-1);
    return dist(rng);
}
