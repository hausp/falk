/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#include "Connection.hpp"
#include <iostream>

Connection::Connection(Connection&& other) {
    writable = other.writable;
    readable = other.readable;
    pendingWrite = other.pendingWrite;
    other.writable = 0;
    other.readable = 0;
    pendingWrite = false;
}

Connection::~Connection() {
    close(writable);
    close(readable);
}

void Connection::flush() const {
    if (pendingWrite) {
        close(writable);
    }
}

void Connection::send(const std::string& content) {
    const char* cont = content.c_str();
    size_t size = strlen(cont);
    assert(write(writable, cont, size) == size);
    pendingWrite = true;
}

std::string Connection::receive() const {
    flush();
    int outputSize;
    char readbuffer[80];
    std::string result;
    while (true) {
        outputSize = read(readable, readbuffer, sizeof(readbuffer));
        if (outputSize <= 0) {
            break;
        }
        result += std::string(readbuffer).substr(0, outputSize);
    }
    return result;
}
