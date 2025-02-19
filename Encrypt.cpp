#include "ProcesadorArchivos.h"

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