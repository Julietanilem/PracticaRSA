#include "Entidad.h"

// Forward declarations
uint64_t phiEuler(uint64_t n);
int64_t mcde(uint64_t a, uint64_t b, int64_t &x, int64_t &y);
int64_t mcd(uint64_t a, uint64_t b);
uint64_t potenciaMod(uint64_t a, uint64_t b, uint64_t mod);
uint rand(uint a, uint b);
bool esPrimo(uint64_t a);
uint64_t invMult(uint64_t a, uint64_t mod);

///// A
/** Construye una entidad usando dos números primos p y q */
Entidad::Entidad(std::string nombre, uint64_t p, uint64_t q)
    :nombre{nombre} {
    //Validacion para los tests
    if (!esPrimo(p) || !esPrimo(q) || p == q) {
        throw std::invalid_argument("Los valores p y q deben ser primos y diferentes entre sí.");
    }

    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    uint64_t e_publico;
    uint limit = (phi - 1 > 65535) ? 65535 : (uint)(phi - 1);
    do {
        e_publico = rand(2, limit);
    } while (mcd(e_publico, phi) != 1);

    uint64_t d_privado = invMult(e_publico, phi);

    // tuplas (e, n) y (d, n)
    this->pub = {e_publico, n};
    this->priv = {d_privado, n};
}

/** Construye una entidad usando primos y una "semilla" e */
Entidad::Entidad(std::string nombre, uint64_t p, uint64_t q, uint64_t e):
    nombre {nombre}{
        if (!esPrimo(p) || !esPrimo(q) || p == q) {
        throw std::invalid_argument("p y q deben ser primos distintos.");
    }

    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    if (mcd(e, phi) != 1) {
        throw std::invalid_argument("El exponente e proporcionado no es coprimo con phi(n).");
    }

    uint64_t d_privado = invMult(e, phi);

    this->pub = {e, n};
    this->priv ={d_privado, n};
}

/** Agrega una llave externa a esta entidad */
void Entidad::agregaLlave(std::string nombre, std::tuple<uint64_t, uint64_t> llave){
    this->entidades[nombre] = llave;
}

/** Cifra un caracter dependiendo para quien */
uint64_t Entidad::cifraCaracter(std::string nombre, unsigned char c){
    if (entidades.find(nombre) == entidades.end()) {
        throw std::invalid_argument("No se tiene la llave pública de: " + nombre);
    }

    std::tuple<uint64_t, uint64_t> llavePub = entidades[nombre];
    uint64_t e = std::get<0>(llavePub);
    uint64_t n = std::get<1>(llavePub);

    return potenciaMod(static_cast<uint64_t>(c), e, n);
}
//// B

/** Descifra un caracter que fue cifrado utilizando su llave pública */
unsigned char Entidad::descifraCaracter(uint64_t i){
  
  // Primero obtenemos la llave privadisima
  uint64_t x = std::get<0>(priv);
  uint64_t n = std::get<1>(priv);
  
  // m = C^x mod n
  uint64_t m = potenciaMod(i, x, n);
  
  // Pasamos el número a su caracter correspondiente
  return static_cast<unsigned char>(m);
  
}

/** Cifra una cadena de caracteres */
std::vector<uint64_t> Entidad::cifraMensaje(std::string nombre, std::string mensaje){
  
  std::vector<uint64_t> mensajeCifrado;
    
  // Recorremos cada caracter
  for (unsigned char c : mensaje) {
    // Ciframos con la parte A
    mensajeCifrado.push_back(cifraCaracter(nombre, c));
  }
    
  return mensajeCifrado;
  
}

/** Descifra un vector de números cifrados para esta entidad */
std::vector<uint64_t> Entidad::descifraMensaje(std::vector<uint64_t> cifrado){

  std::vector<uint64_t> mensajeDescifrado;
    
  // La llave
  uint64_t x = std::get<0>(priv);
  uint64_t n = std::get<1>(priv);

  // Hacemos la descifración descifraciosa número por número
  for (uint64_t c : cifrado) {
    mensajeDescifrado.push_back(potenciaMod(c, x, n));
  }
    
  return mensajeDescifrado;
    
}

/** Convierte un vector de números descifrados a una cadena */
std::string Entidad::decodificarMensaje(std::vector<uint64_t> descifrado){

  std::string textoOriginal;
    
  for (uint64_t num : descifrado) {
    // Convertimos de número a su caracter
    textoOriginal.push_back(static_cast<char>(num));
  }
    
  return textoOriginal;
    
}
