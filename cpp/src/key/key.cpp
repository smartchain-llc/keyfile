#include "key.h"

Key::Key() {
    keyfile = new Keyfile();
    attach_to_key_mem();
}
Key::~Key() {
    if ( keyData )
        detach_from_key_mem();
    delete keyfile;
}

void Key::attach_to_key_mem() {
    if( keyfile->mem_key() == -1 )
        std::cout << "MemKey Invalid!" << std::endl;
    
    keyData = static_cast<byte*>( shmat( keyfile->mem_key(), NULL, 0) );
}

void Key::detach_from_key_mem() {
    shmdt( keyData );
}

void Key::print() const {
    std::string byte{};

    std::cout << "== Keyfile Info ==" << std::endl;
    std::cout << "-\tFile Path: " << keyfile->filePath() << std::endl;
    std::cout << "-\tFile Name: " << keyfile->filename() << std::endl;
    std::cout << "-\tMem Key: " << keyfile->mem_key() << std::endl;
    std::cout << std::endl;

    for( size_t i = 0; i < keySize; i+=15 ) {
        for ( int j = i; j < i+15; j++ ) {
            ( keyData[j] <= 0xF )? printf("0x0%x ", keyData[j]) : printf("0x%x ", keyData[j]) ;
        }
        std::cout << std::endl;
    }
    
}

const Key::byte& Key::operator[](int index) const {
    return keyData[index % keySize];
}