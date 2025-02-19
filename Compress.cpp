#include "ProcesadorArchivos.h"

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