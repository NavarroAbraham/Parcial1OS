#ifndef ProcesadorArchivos_h
#define ProcesadorArchivos_h

#include <iostream> // Librería de entrada y salida
#include <string>  // Librería de cadenas de texto
#include <fcntl.h>     // Para usar `open()`, `O_RDONLY`, `O_WRONLY`, `O_CREAT`
#include <unistd.h>    // Para usar `read()`, `write()`, `close()`
#include <bitset>      // Para representar cada byte en su forma binaria (8 bits)
#include <cstdint>     // Para usar tipos de datos de tamaño fijo como uint8_t

// Prototipos de funciones (Declaraciones)
void PrintHelp();
void PrintVersion();
int compressFile(const std::string& filename);
int decompressFile(const std::string& filename);
int encryptFile(const std::string& filename);
int decryptFile(const std::string& filename);

#endif // ProcesadorArchivos.h