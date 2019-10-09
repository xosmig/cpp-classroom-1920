#pragma once

#include <cstddef>
#include <vector>

// add missing consts and references if needed!
char* read(char* data, int& out);
char* write(char* data, int in);

char* read(char* data, size_t& out);
char* write(char* data, size_t in);

char* read(char* data, char*& out);
char* write(char* data, char* in);

char* read(char* input, std::vector<int>& vec);
char* write(char* input, std::vector<int> vec);
