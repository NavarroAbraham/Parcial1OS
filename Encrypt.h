#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

int encryptFile(const std::string& fileName);
int decryptFile(const std::string& fileName);
int readEncryptedFile(const std::string& fileName);

#endif // ENCRYPT_H