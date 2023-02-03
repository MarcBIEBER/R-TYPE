#include "server.hpp"

void server::checkPlayerPing(std::string &message)
{
    int id = message[1] - '0';
    std::string msg;
    if (id < 1 || id > 4) {
        return;
    }
    if (!_playerPings.at(id - 1).pingReceived) {
        _playerPings.at(id - 1).pingReceived = true;
        _serverPingClocks.at(id - 1).restart();
        for (std::pair<int, udp::endpoint> player : _players) {
            if (player.first == id) {
                msg = "k";
                _socket.async_send_to(boost::asio::buffer(msg), player.second,
                    boost::bind(&server::handleSend, this, msg, player.second,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
                break;
            }
        }
    } else {
        _playerPings.at(id - 1).pingReceived = false;
        for (std::pair<int, udp::endpoint> player : _players) {
            if (player.first == id) {
                _serverPingTimes.at(id -1) = _serverPingClocks.at(id - 1).getElapsedTime();                
                _playerPings.at(id - 1).ping = _serverPingTimes.at(id - 1).asMilliseconds();
            }
        }
        for (std::pair<int, udp::endpoint> player : _players) {
            if (player.first == id) {
                msg = "K " + std::to_string(_playerPings.at(id - 1).ping);
                _socket.async_send_to(boost::asio::buffer(msg), player.second,
                    boost::bind(&server::handleSend, this, msg, player.second,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
            break;
        }
    }
    }
}