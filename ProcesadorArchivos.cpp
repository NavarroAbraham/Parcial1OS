#include "ProcesadorArchivos.h"

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

// Comprime el archivo especificado usando Run-Length Encoding (RLE)
int compressFile(const std::string& fileName) {
    int inputFile = open(fileName.c_str(), O_RDONLY);
    if (inputFile == -1) {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return -1;
    }
    
    std::string outputFileName = fileName + ".rle";
    int outputFile = open(outputFileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFile == -1) {
        std::cerr << "Error: No se pudo crear el archivo comprimido." << std::endl;
        close(inputFile);
        return -1;
    }
    
    char current, previous;
    unsigned char count = 0;
    ssize_t bytesRead;
    bytesRead = read(inputFile, &previous, 1);
    if (bytesRead <= 0) {
        close(inputFile);
        close(outputFile);
        return -1;
    }
    count = 1;
    
    while ((bytesRead = read(inputFile, &current, 1)) > 0) {
        if (current == previous && count < 255) {
            count++;
        } else {
            write(outputFile, &previous, 1);
            write(outputFile, &count, 1);
            previous = current;
            count = 1;
        }
    }
    
    write(outputFile, &previous, 1);
    write(outputFile, &count, 1);
    
    close(inputFile);
    close(outputFile);
    
    std::cout << "Archivo comprimido exitosamente: " << outputFileName << std::endl;
    return 0;
}

// Descomprime el archivo especificado usando Run-Length Encoding (RLE)
int decompressFile(const std::string& fileName) {
    int inputFile = open(fileName.c_str(), O_RDONLY);
    if (inputFile == -1) {
        std::cerr << "Error: No se pudo abrir el archivo comprimido." << std::endl;
        return -1;
    }
    
    std::string outputFileName = fileName.substr(0, fileName.find_last_of("."));
    int outputFile = open(outputFileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFile == -1) {
        std::cerr << "Error: No se pudo crear el archivo descomprimido." << std::endl;
        close(inputFile);
        return -1;
    }
    
    char character;
    unsigned char count;
    ssize_t bytesRead;
    
    while ((bytesRead = read(inputFile, &character, 1)) > 0) {
        if (read(inputFile, &count, 1) != 1) break;
        for (int i = 0; i < count; i++) {
            write(outputFile, &character, 1);
        }
    }
    
    close(inputFile);
    close(outputFile);
    
    std::cout << "Archivo descomprimido exitosamente: " << outputFileName << std::endl;
    return 0;
}

// Encripta el archivo especificado usando XOR
int encryptFile(const std::string& fileName) {
    int inputFile = open(fileName.c_str(), O_RDONLY);
    if (inputFile == -1) {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return -1;
    }

    std::string outputFileName = fileName + ".xor";
    int outputFile = open(outputFileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFile == -1) {
        std::cerr << "Error: No se pudo crear el archivo encriptado." << std::endl;
        close(inputFile);
        return -1;
    }

    char tempChar;
    char key = 'Z'; 
    ssize_t bytesRead;

    while ((bytesRead = read(inputFile, &tempChar, 1)) > 0) {
        tempChar = tempChar ^ key;
        write(outputFile, &tempChar, 1);
    }

    close(inputFile);
    close(outputFile);

    std::cout << "Archivo encriptado exitosamente: " << outputFileName << std::endl;
    return 0;
}

// Desencripta el archivo especificado usando XOR
int decryptFile(const std::string& fileName) {
    int inputFile = open(fileName.c_str(), O_RDONLY);
    if (inputFile == -1) {
        std::cerr << "Error: No se pudo abrir el archivo encriptado." << std::endl;
        return -1;
    }

    std::string outputFileName = fileName.substr(0, fileName.find_last_of("."));
    int outputFile = open(outputFileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFile == -1) {
        std::cerr << "Error: No se pudo crear el archivo desencriptado." << std::endl;
        close(inputFile);
        return -1;
    }

    char tempChar;
    char key = 'Z'; 
    ssize_t bytesRead;

    while ((bytesRead = read(inputFile, &tempChar, 1)) > 0) {
        tempChar = tempChar ^ key;
        write(outputFile, &tempChar, 1);
    }

    close(inputFile);
    close(outputFile);

    std::cout << "Archivo desencriptado exitosamente: " << outputFileName << std::endl;
    return 0;
}

// Lee y muestra el contenido de un archivo comprimido
int readCompressedFile(const std::string& fileName) {
    int inputFile = open(fileName.c_str(), O_RDONLY);
    if (inputFile == -1) {
        std::cerr << "Error: No se pudo abrir el archivo comprimido." << std::endl;
        return -1;
    }
    
    char character;
    unsigned char count;
    ssize_t bytesRead;
    
    while ((bytesRead = read(inputFile, &character, 1)) > 0) {
        if (read(inputFile, &count, 1) != 1) break;
        std::cout << "Caracter: " << character << ", Conteo: " << (int)count << std::endl;
    }
    
    close(inputFile);
    return 0;
}

// Lee y muestra el contenido de un archivo encriptado
int readEncryptedFile(const std::string& fileName) {
    int inputFile = open(fileName.c_str(), O_RDONLY);
    if (inputFile == -1) {
        std::cerr << "Error: No se pudo abrir el archivo encriptado." << std::endl;
        return -1;
    }

    char tempChar;
    char key = 'Z'; 
    ssize_t bytesRead;
    
    std::cout << "Contenido del archivo encriptado (en hexadecimal):" << std::endl;
    while ((bytesRead = read(inputFile, &tempChar, 1)) > 0) {
        tempChar = tempChar ^ key;
        std::cout << std::hex << std::uppercase << (int)(unsigned char)tempChar << " ";
    }
    std::cout << std::dec << std::endl; 

    close(inputFile);
    return 0;
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