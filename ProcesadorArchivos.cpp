#include "ProcesadorArchivos.h"

// =====================================
//  FUNCIONES DE PROCESAMIENTO DE ARCHIVOS
// =====================================
// Función que imprime la ayuda del programa
void PrintHelp() {
    std::cout << "Uso: procesador_archivos [OPCION] [ARCHIVO]" << std::endl;
    std::cout << "Opciones:" << std::endl;
    std::cout << "  -c, --comprimir     Comprime el archivo" << std::endl;
    std::cout << "  -d, --descomprimir  Descomprime el archivo" << std::endl;
    std::cout << "  -e, --encriptar     Encripta el archivo" << std::endl;
    std::cout << "  -x, --desencriptar  Desencripta el archivo" << std::endl;
    std::cout << "  -h, --help          Muestra esta ayuda" << std::endl;
    std::cout << "  -v, --version       Muestra la versión del programa" << std::endl;
}