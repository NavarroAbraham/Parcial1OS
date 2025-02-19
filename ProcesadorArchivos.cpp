#include "ProcesadorArchivos.h"
#include "Compress.h"
#include "Encrypt.h"

// Imprime la ayuda del programa
void printHelp() {
    std::cout << "Uso: procesador_archivos [OPCION] [ARCHIVO]\n";
    std::cout << "Opciones:\n";
    std::cout << "  -c, --compress <archivo>     Comprime el archivo\n";
    std::cout << "  -x, --decompress <archivo>   Descomprime el archivo\n";
    std::cout << "  -e, --encrypt <archivo>      Encripta el archivo\n";
    std::cout << "  -d, --decrypt <archivo>      Desencripta el archivo\n";
    std::cout << "  -r, --read-compressed <archivo>  Lee el contenido del archivo comprimido\n";
    std::cout << "  -l, --read-encrypted <archivo>   Lee el contenido del archivo encriptado\n";
    std::cout << "  -h, --help                   Muestra esta ayuda\n";
    std::cout << "  -v, --version                Muestra la versión del programa\n";
}

// Imprime la versión del programa
void printVersion() {
    std::cout << "Procesador de Archivos v1.0\n";
}

// Función principal que maneja los argumentos y llama a las funciones correspondientes
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 1;
    }
    
    std::string option = argv[1];
    if (option == "-h" || option == "--help") {
        printHelp();
    } else if (option == "-v" || option == "--version") {
        printVersion();
    } else if ((option == "-c" || option == "--compress") && argc == 3) {
        return compressFile(argv[2]);
    } else if ((option == "-x" || option == "--decompress") && argc == 3) {
        return decompressFile(argv[2]);
    } else if ((option == "-e" || option == "--encrypt") && argc == 3) {
        return encryptFile(argv[2]);
    } else if ((option == "-d" || option == "--decrypt") && argc == 3) {
        return decryptFile(argv[2]);
    } else if ((option == "-r" || option == "--read-compressed") && argc == 3) {
        return readCompressedFile(argv[2]);
    } else if ((option == "-l" || option == "--read-encrypted") && argc == 3) {
        return readEncryptedFile(argv[2]);
    } else {
        std::cerr << "Error: Argumentos inválidos." << std::endl;
        printHelp();
        return 1;
    }
}