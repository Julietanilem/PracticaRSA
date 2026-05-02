#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <stdint.h>

class Entidad {

private:
    std::tuple<uint64_t, uint64_t> priv {};

public:
    std::string nombre {};
    std::tuple<uint64_t, uint64_t> pub {};
    std::unordered_map<std::string, std::tuple<uint64_t, uint64_t>> entidades;

    Entidad(std::string nombre, uint64_t p, uint64_t q);
    Entidad(std::string nombre, uint64_t p, uint64_t q, uint64_t e);

    void agregaLlave(std::string nombre, std::tuple<uint64_t, uint64_t> llave);
    uint64_t cifraCaracter(std::string nombre, unsigned char c);
    unsigned char descifraCaracter(uint64_t i);
    std::vector<uint64_t> cifraMensaje(std::string nombre, std::string mensaje);
    std::vector<uint64_t> descifraMensaje(std::vector<uint64_t> cifrado);
    std::string decodificarMensaje(std::vector<uint64_t> cifrado);
};


#endif
