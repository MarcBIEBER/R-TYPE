#include <iostream>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
// #include <boost/thread.hpp>
#include "../SafeQueue.hpp"
#include <queue>
#include "../safeVariable.hpp"

using boost::asio::ip::udp;
#define MAX_READ 2048

class client {
    public:
        client();
        ~client();

        void startReceive();
        void handleReceive(const boost::system::error_code& error, size_t bytes_recvd);
        void startConnectionWithServer();
        void closeConnectionWithServer();
        void resetReceived();
        void sender(std::string msg);
        void startClientThread();
        void runClientThread();

        void init(std::string host, std::string port);

        bool getClientConnected() { return _client_connected; };
        boost::asio::io_service &getIOservice() { return _ios; }
        bool isMsgQueueEmpty() { return _msg_queue.isEmpty(); }
        std::string popMsgQueue() { return _msg_queue.Pop(); }
        void setPlayerId(int player_id) { this->_player_id = player_id; }
        void setClientConnected(bool connected) { _client_connected = connected; }
        bool isClientConnected() { return _client_connected; }
        void setThreadRunning(bool value) { _client_thread_running.set(value); }
        int getPlayerId() { return _player_id; }

        // std::string bitToStr(std::bitset<120> bitset);

    private:
        boost::asio::io_service _ios;
        udp::socket _socket;
        udp::endpoint _sender_endpoint;
        std::string _host;
        std::string _port;
        SafeQueue<std::string> _msg_queue;
        std::thread _client_thread1;
        safeVariable<bool> _client_thread_running;

        int _player_id;
        bool _client_connected = false;
        char _recv_buf[MAX_READ] = {0};
};