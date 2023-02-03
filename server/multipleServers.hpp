/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** multipleServers
*/

#ifndef MULTIPLESERVERS_HPP_
#define MULTIPLESERVERS_HPP_

#include "server.hpp"
#include <sys/wait.h>

class multipleServer {
    public:
        multipleServer(int startingPort, int nbServers) : _startingPort(startingPort), _nbServers(nbServers)
        {
        }

        ~multipleServer()
        {
            for (int i = 0; i < _nbServers; i++) {
                wait(NULL);
            }
        }

        void run()
        {
            for (int i = 0; i < _nbServers; i++) {
                _pid = fork();
                if (_pid == 0) {
                    server s(_startingPort + i);
                    s.enterThreads();
                    s.runIos();
                    return;
                }
                else if (_pid < 0) {
                    std::cerr << "Error while forking" << std::endl;
                    return;
                } else {
                    pids.push_back(_pid);
                }
            }
        }
        
    private:
        std::vector<server> servers;
        std::vector<int> pids;
        int _pid;
        int _startingPort;
        int _nbServers;
};

#endif /* !MULTIPLESERVERS_HPP_ */
