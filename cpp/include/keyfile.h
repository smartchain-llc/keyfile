#pragma once

#include <iostream>
#include <istream>
#include <fstream>
#include <filesystem>
#include <cstddef>

#define PAGE_SIZE 4096

using byte = unsigned char;
struct Key{
    Key(){

    };
    ~Key(){ delete data; };

    const byte& operator[](int index){
        return data[index % size];
    }

    private:
        byte* data  = nullptr;
        size_t size = PAGE_SIZE;

};
class Keyfile{
    using path = std::filesystem::path;
    public:
        static inline const path        defaultDirectory    { std::getenv("HOME") };
        static inline const path        defaultOutDir       { "/tmp" };
        static inline const std::string filename            { ".key" };
        static inline const path        defaultFile         { Keyfile::defaultOutDir / Keyfile::filename };
        static Key* generate_key();
        static Key* load_key();
};