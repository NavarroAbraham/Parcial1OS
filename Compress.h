#ifndef COMPRESS_H
#define COMPRESS_H

#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

int compressFile(const std::string& fileName);
int decompressFile(const std::string& fileName);
int readCompressedFile(const std::string& fileName);

#endif // COMPRESS_H