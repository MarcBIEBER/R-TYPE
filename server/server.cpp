#ifdef _WIN64
   #include "server.hpp"
#elif _WIN32
   #include "server.hpp"
#elif __APPLE__
    #include "multipleServers.hpp"
#elif __linux
    #include "multipleServers.hpp"
#elif __unix 
    #include "multipleServers.hpp"
#elif __posix

#endif

void server::startReceive()
{
    std::lock_guard<std::mutex> lock(_mutexReceive);
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buf, MAXLENGTH), _endpoint,
        boost::bind(&server::handleReceive, this, _endpoint,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void server::handleReceive(udp::endpoint endpoint, const boost::system::error_code& error, size_t bytes_recvd)
{
    if (!error) {
        _queue.Push(std::string(_recv_buf));
        startSend(endpoint);
        startReceive();
    } else {
        std::cerr << "Error in handling send: " << error << std::endl;
	}
}

void server::startSend(udp::endpoint endpoint)
{
    std::string message = _queue.Pop();
    if ((message[0] >= '1' && message[0] <= '4') || message[0] == 'B' || message[0] == 'M' || message[0] == 'l' || message[0] == 'n')  {
        sendToAllPlayers(message);
    } else if (message[0] == 'P') {
        sendToAllPlayers(message + " " + std::to_string(_progressPos) + " " + std::to_string(_acctualStage));
    }
    else if (message == "CONNECT") {addNewPlayer(_endpoint);}
    else if (message == "bossS" + std::to_string(_acctualStage)) {createBossThread();}
    else if (message == "miniboss") {createMiniBossThread();}
    else if (message == "bosskill") {_bossIsAlive.set(false);_bossIsDead.set(true);if (_acctualStage > 5) _acctualStage = 5;}
    else if (message == "minibosskill") {_miniBossIsAlive.set(false);_progressPos++;}
    else if (message == "start") { _stopAcceptingClients.set(true); sendToAllPlayers("start"); }
    else if (message[0] == 'k') {checkPlayerPing(message);}
    else if (message[0] == 'Q') {
        _nbPlayers.decrement();
        int id = message[1] - '0';
        int i = 0;
        if (id < 1 || id > 4) {
            memset(_recv_buf, 0, MAXLENGTH);
            std::cout << "Invalid player id" << std::endl;
            return;
        }
        for (std::pair<int, udp::endpoint> player : _players) {
            if (player.second == _endpoint) {
                _players.erase(_players.begin() + i);
                break;
            }
            i++;
        }
        _connected_players.at(id - 1).second = false;
        std::string new_message = "L " + std::to_string(_connected_players[0].second) + ' ' + std::to_string(_connected_players[1].second) + ' ' + std::to_string(_connected_players[2].second) + ' ' + std::to_string(_connected_players[3].second);
        sendToAllPlayers(new_message);
        printPlayers();
        if(_nbPlayers.get() == 0) {
            _stopAcceptingClients.set(false);
            _bossIsAlive.set(false);
            _bossIsDead.set(false);
            _acctualStage = 1;
            _progressPos = 0;
            for (int i = 0; i < NB_ENNEMIES; i++) {
                _clockDurationEnemy[i].restart();
            }
            for (int i = 0; i < NB_BONUS; i++) {
                _clockDurationBonus[i].restart();
            }
            _miniBossIsAlive.set(false);
            _players.clear();
        }
    }
    memset(_recv_buf, 0, MAXLENGTH);
}

void server::sendToAllPlayers(std::string message)
{
    for (std::pair<int, udp::endpoint> player : _players) {
            _socket.async_send_to(boost::asio::buffer(message), player.second,
                boost::bind(&server::handleSend, this, message, player.second,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

void server::addNewPlayer(udp::endpoint endpoint)
{
    // std::cout << "server port: " << _socket.local_endpoint().port() << std::endl;
    if (_stopAcceptingClients.get()) {
        std::string msgCannot = "CANNOT";
            _socket.async_send_to(boost::asio::buffer(msgCannot), endpoint,
                boost::bind(&server::handleSend, this, msgCannot, endpoint,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        return;
    }
    for (auto _player : _players) {
        if (_player.second == endpoint) {
            return;
        }
    }
    if (_nbPlayers.get() == MAX_CONNECTED_PLAYER) return;
    _nbPlayers.increment();
    int playerId = getAvailableId();
    int i = 0;
    std::string messageId = std::to_string(playerId);
    _players.push_back(std::pair(playerId, endpoint));
    for (std::pair<int, bool> connected_player : _connected_players) {
        if (connected_player.first == playerId) {
            _connected_players[i].second = true;
            break;
        }
        i++;
    }
    
    std::string new_message = "L " + std::to_string(_connected_players[0].second) + ' ' + std::to_string(_connected_players[1].second) + ' ' + std::to_string(_connected_players[2].second) + ' ' + std::to_string(_connected_players[3].second);

    _socket.async_send_to(boost::asio::buffer(messageId), endpoint,
                boost::bind(&server::handleSend, this, new_message, endpoint,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    sendToAllPlayers(new_message);
    printPlayers();
}

void server::handleSend(std::string message, udp::endpoint _endpoint, const boost::system::error_code& error, size_t bytes_recvd)
{
    // std::cout << "Sent " << bytes_recvd << " bytes to " << _endpoint << " with data: " << message << std::endl;
}

int server::getAvailableId() {
    for (size_t i = 0; i < _connected_players.size(); i++) {
        if (_connected_players[i].second == false) {
            return _connected_players[i].first;
        }
    }
    return -1;
}

void server::printPlayers()
{
    std::cout << "Players: " << std::endl;
    for (std::pair<int, bool> player : _connected_players) {
        std::cout << player.first << " " << player.second << std::endl;
    }
}

void server::runIos()
{
    std::cout << "Serveur now running on port: " << _serverPort << std::endl;
    _io_service.run();
}

void server::clearServerStatus()
{
    for (size_t i = 0; i < _players.size(); i++) {
        _players.erase(_players.begin() + i);
    }
    for (size_t i = 0; i < _connected_players.size(); i++) {
        _connected_players[i].second = false;
    }
}

int main(int ac, char *av[])
{
    if (ac != 2 && ac != 3) {
        std::cerr << "Usage: ./server <port> [nb_servers]" << std::endl;
        return 84;
    }
    try {
        if (ac == 2) {
            server s(std::atoi(av[1]));
            s.enterThreadsAndRunIos();
            s.getPrompt();
        }
        #ifdef _WIN64
        #elif _WIN32
        #elif __APPLE__
        if (ac == 3) {
            multipleServer servers(std::atoi(av[1]), std::atoi(av[2]));
            servers.run();
        }
        #elif __linux
        if (ac == 3) {
            multipleServer servers(std::atoi(av[1]), std::atoi(av[2]));
            servers.run();
        }
        #elif __unix
        if (ac == 3) {
            multipleServer servers(std::atoi(av[1]), std::atoi(av[2]));
            servers.run();
        }
        #elif __posix
        #endif
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}