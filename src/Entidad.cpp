#include "Entidad.h"

// Forward declarations
uint64_t phiEuler(uint64_t n);
int64_t mcde(uint64_t a, uint64_t b, int64_t &x, int64_t &y);
int64_t mcd(uint64_t a, uint64_t b);
uint64_t potenciaMod(uint64_t a, uint64_t b, uint64_t mod);
uint rand(uint a, uint b);
bool esPrimo(uint64_t a);

///// A
/** Construye una entidad usando dos números primos p y q */
Entidad::Entidad(std::string nombre, uint64_t p, uint64_t q)
    :nombre{nombre} {

}

/** Construye una entidad usando primos y una "semilla" e */
Entidad::Entidad(std::string nombre, uint64_t p, uint64_t q, uint64_t e):
    nombre {nombre}{

}

/** Agrega una llave externa a esta entidad */
void Entidad::agregaLlave(std::string nombre, std::tuple<uint64_t, uint64_t> llave){
    
}

/** Cifra un caracter dependiendo para quien */
uint64_t Entidad::cifraCaracter(std::string nombre, unsigned char c){
    
}
//// B

/** Descifra un caracter que fue cifrado utilizando su llave pública */
unsigned char Entidad::descifraCaracter(uint64_t i){
    
}

/** Cifra una cadena de caracteres */
std::vector<uint64_t> Entidad::cifraMensaje(std::string nombre, std::string mensaje){

}

/** Descifra un vector de números cifrados para esta entidad */
std::vector<uint64_t> Entidad::descifraMensaje(std::vector<uint64_t> cifrado){

};

/** Convierte un vector de números descifrados a una cadena */
std::string Entidad::decodificarMensaje(std::vector<uint64_t> descifrado){

};
