#include <iostream>
#include <cmath>
#include <random>
#include <stdint.h>


/** Eleva a a la b recortando con mod */
uint64_t potenciaMod(uint64_t a, uint64_t b, uint64_t mod){
    uint64_t res = 1;
    a %= mod;
    while(b){
        if(b&1) res = ((__uint128_t)res*a)%mod;
        a = ((__uint128_t)a*a)%mod, b >>= 1;
    }
    return res;
}

/**Encuentra la combinación lineal de a y b que resulta en 1. */
int64_t mcde(uint64_t a, uint64_t b, int64_t &x, int64_t &y){
    if(b==0){
        x = 1, y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t d = mcde(b, a%b, x1, y1);
    x = y1,
    y = x1 - y1 * (a/b);
    return d;
}

/** Encuentra el inverso multiplicativo módulo M. Es mejor obtenerlo
    con el algoritmo de euclides extendido */
uint64_t invMult(uint64_t a, uint64_t mod){
  // Esto trono a la mera hora. Hay desbordamiento.
  // Le moveré en fa. Voy a usar int128 y hacerlo iterativo mejor.

  // La respuesta final, y la construcción de la misma.
  __int128_t res = 0, construccion = 1;
  // Nuestro modulo y la llave publica.
  __int128_t modulo = mod, llaveP = a;
    
  while (llaveP != 0) {
    // Calculamos el cociente
    __int128_t cociente = modulo / llaveP;
    // Guardamos resultado viejo
    __int128_t tempRes = res;
    // Trabajo actual
    res = construccion;
    // Lo que falta por hacer
    construccion = tempRes - cociente * construccion;

    // MCD
    __int128_t tempModulo = modulo;
    modulo = llaveP;
    llaveP = tempModulo - cociente * llaveP;
  }

  // Manejo de errores matematicos
  if (modulo > 1)
    return 0;
  
  if (res < 0)
    res = res + mod;
    
  return (uint64_t)res;
}


/** Encuentra el máximo común divisor entre a y b. */
int64_t mcd(uint64_t a, uint64_t b){
    // alg de euclides 
    return b ? mcd(b, a%b) : a;
}

/** Nos dice si un número es primo o no */
bool esPrimo(uint64_t n){
    for (uint64_t d = 2; d * d <= n; d++) {
        if (n % d == 0)
            return false;
    }
    return n >= 2;
}


/** Nos dice si 2 números son coprimos o primos relativos */
bool coprimos(uint64_t a, uint64_t b){
    return mcd(a,b) == 1;
}

/** Nos regresa la función phi de euler de un número n */
uint64_t phiEuler(uint64_t n){
    uint64_t res = n;
    for (uint64_t p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            res -= res / p;
        }
    }
    if (n > 1)
        res -= res / n;
    return res;

}

/** Función auxiliar para generar números aleatorios pequeños */
uint rand(uint start, uint end){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(start, end-1);
    return dist(rng);
}
