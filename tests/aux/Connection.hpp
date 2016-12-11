/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <cassert>
#include <cstring>
#include <unistd.h>
#include <string>

class Connection {
public:
    template<typename... Args>
    explicit Connection(const std::string&, Args&&...);
    Connection(const Connection&) = delete;
    Connection(Connection&&);
    ~Connection();
    void flush() const;
    void send(const std::string&);
    std::string receive() const;

private:
    int writable;
    int readable;
    bool pendingWrite = false;
};

template<typename... Args>
Connection::Connection(const std::string& command, Args&&... args) {
    int toChild[2];
    int fromChild[2];

    assert(pipe(toChild) >= 0);
    assert(pipe(fromChild) >= 0);
    pid_t childpid = fork();

    assert(childpid >= 0);
    if (childpid == 0) {
        assert(dup2(toChild[0], 0) >= 0);
        assert(dup2(fromChild[1], 1) >= 0);
        assert(dup2(fromChild[1], 2) >= 0);
        close(toChild[0]);
        close(toChild[1]);
        close(fromChild[0]);
        close(fromChild[1]);

        const char* cmd = command.c_str();
        execl(cmd, cmd, args..., (char*) 0);
        exit(0);
    }

    close(toChild[0]);
    close(fromChild[1]);
    writable = toChild[1];
    readable = fromChild[0];
}

#endif
