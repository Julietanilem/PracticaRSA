#include "Entidad.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <stdint.h>

#ifndef IS_TRUE
#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << ": error de prueba en la línea: " << __LINE__ << std::endl; }
#endif

uint rand(uint a, uint b);
uint64_t invMult(uint64_t a, uint64_t mod);
uint64_t mcd(uint64_t a, uint64_t b);
uint64_t esPrimo(uint64_t p);

typedef long long ll;
typedef std::basic_string<unsigned char> ustring;

/* Algunos números primos sacados de http://www.prime-numbers.org */
int primos[] = {6317, 8807, 10657, 13921, 17669, 22567, 25349, 31721, 45191, 51637,
    53899, 58321, 62141, 64567, 67579, 70607, 73679, 77573, 81331, 84437, 86843,
    89017, 91457, 92921, 95947, 99233, 101573, 104717, 110419, 115931, 121123};

/* Para debugear mis propios test lol */
void print(std::vector<uint64_t> v){
    std::cout << '[';
    for (auto i: v)
	std::cout << i << ", ";
    std::cout << "]\n";
}

bool testConstructor(){
    std::string n = "";
    int p {10};
    int q {10};

    try {
	Entidad a("", p, q);
	IS_TRUE(false);
    } catch (const std::invalid_argument& e){}

    q = 97;
    try {
	Entidad a("", p, q);
	IS_TRUE(false);
    } catch (const std::invalid_argument& a){}

    q = 10;
    p = 97;
    try {
	Entidad a("", p, q);
	IS_TRUE(false);
    } catch (const std::invalid_argument& a){}

    try {
	Entidad a("", p, p);
	IS_TRUE(false);
    } catch (const std::invalid_argument& a){}

    q = 101;
   
    try {
	Entidad a("", p, q);
    } catch (const std::invalid_argument& a(const std::string& what_arg)){
	IS_TRUE(false);
    }
    
    Entidad a("test", p, q, 7927);
    IS_TRUE(a.nombre != "");
    IS_TRUE(std::tuple_size<decltype(a.pub)>::value == 2);
    IS_TRUE(mcd(std::get<0>(a.pub), p*q) == 1);
    IS_TRUE(std::get<1>(a.pub) == p*q);
    IS_TRUE(!esPrimo(std::get<1>(a.pub)));
    IS_TRUE(a.entidades.size() == 0);
    
    return true;
}

bool testAnayanzi(){
    int p = 17;
    int q = 11;
    int e = 7;
    
    Entidad a("Alice", p, q, e);
    Entidad b("Beto", 3, 5, 15);

    IS_TRUE(std::get<0>(a.pub) == e && std::get<1>(a.pub) == 187);
    IS_TRUE(mcd(e, 187) == 1);
    IS_TRUE(invMult(e, 160) == 23);
    
    char M { 88 };
    b.agregaLlave(a.nombre, a.pub);
    int cifrado = b.cifraCaracter(a.nombre, M);
    IS_TRUE(cifrado == 11);
    
    char D = a.descifraCaracter((char)cifrado);
    IS_TRUE(D == M);
    return true;
}

bool testMensaje(){
    // Panagrama
    std::string orig("the quick brown fox jumps over the lazy dog");

    int l = sizeof(primos)/sizeof(int);
    int r1 = rand(0, l/2);
    int r2 = rand(l/2+1, l);
    int p = primos[r1];
    int q = primos[r2];

    
    Entidad a("A", p, q);
    std::vector<uint64_t> op;
    for (int i = 0; i < orig.size(); i++)
	op.push_back(orig[i]);

    IS_TRUE(orig == a.decodificarMensaje(op));

    Entidad b("B", q, p);
    
    
    b.agregaLlave(a.nombre, a.pub);
    
    std::vector<uint64_t> cifr = b.cifraMensaje(a.nombre, orig);
    
    IS_TRUE(cifr.size() == orig.size());
    for (int i = 0; i < orig.size(); i++)
	if (i > 2) IS_TRUE(orig[i] != cifr[i]);
    
    std::vector<uint64_t> desc = a.descifraMensaje(cifr);

    for (int i = 0; i < desc.size(); i++)
	IS_TRUE(desc[i] == orig[i]);
    std::string m = a.decodificarMensaje(desc);

    IS_TRUE(m == orig);
    return true;
}

bool testByte(){
    std::vector<uint64_t> v;
    for (int i = 0; i < 1<<8; i++)
	v.push_back(i);
    
    std::string original(v.begin(), v.end());
    const unsigned char* u_str = reinterpret_cast<const unsigned char*>(original.c_str());

    int l = sizeof(primos)/sizeof(int);
    int r1 = rand(0, l/2);
    int r2 = rand(l/2+1, l);
    int p = primos[r1];
    int q = primos[r2];
    
    Entidad a("A", p, q);
    Entidad b("B", q, p);

    b.agregaLlave(a.nombre, a.pub);
    
    std::vector<uint64_t> cifrado = b.cifraMensaje(a.nombre, original);
    
    IS_TRUE(original.size() == cifrado.size());
    for (int i = 0; i < cifrado.size(); i++)
	if (i > 2) IS_TRUE(u_str[i] != cifrado[i]);
    
    std::vector<uint64_t> descifrado = a.descifraMensaje(cifrado);
    
    for (int i = 0; i < descifrado.size(); i++)
	IS_TRUE(descifrado[i] == u_str[i]);
    return true;
}

int mainTest(){
    /* siempre he pensado que es un patito <3 */
    int n = 1<<8;
    std::cout << "Pruebas \n";
    std::cout << "testConstructor():\n";
    testConstructor();
    std::cout << "testAnayanzi():\n";
    testAnayanzi();
    
    std::cout << "testMensaje(): \n";
    for (int i = 0; i < n; i++) testMensaje();
    std::cout << "testBytes(): \n";
    for (int i = 0; i < n; i++) testByte();
    return 0;
}
