#include "server.hpp"

void server::enterThreads()
{
    _threadCreateEnnemies = std::thread(&server::createEnnemies, this);
}

void server::enterThreadsAndRunIos()
{
    _threadCreateEnnemies = std::thread(&server::createEnnemies, this);
    _threadIosRunning = std::thread(&server::runIos, this); 
}

void server::getPrompt()
{
    std::string input;
    while (true) {
        std::cin >> input;
        if (dealWithInput(input) == 1)
            break;
    }
    _io_service.stop();
}

int server::dealWithInput(std::string input)
{
    std::cout << "Input: " << input << std::endl;
    if (input == "exit") {
        return 1;
    }
    if (input == "status") {
        printPlayers();
    }
    if (input == "clear") {
        clearServerStatus();
    }
    return 0;
}