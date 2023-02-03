#include "Client.hpp"

using boost::asio::ip::udp;

/**
 * @brief Construct a new Client::Client object set directcly the socket
 * 
 */
client::client() : _socket(_ios, udp::endpoint(udp::v4(), 0))
{
    _client_thread_running.set(false);
}

/**
 * @brief Destroy the Client::Client object and stop all threads
 * 
 */
client :: ~client() {
    _socket.close();
    _client_thread_running.set(false);
    if (_client_thread1.joinable()) {
        _client_thread1.join();
    }
}

/**
 * @brief Initialize the client
 * 
 * @param host the host of the server
 * @param port the port of the server
 */
void client::init(std::string host, std::string port) {
    _host = host;
    _port = port;
    udp::resolver resolver(_ios);
    udp::resolver::query query(udp::v4(), host, port);
    udp::resolver::iterator itr = resolver.resolve(query);
    _sender_endpoint = *itr;
    startReceive();
}

/**
 * @brief Start the connection to the server and send the first packet
 * 
 */
void client::startConnectionWithServer()
{
    sender("CONNECT");
}

/**
 * @brief Close the connection to the server
 * 
 */
void client::closeConnectionWithServer()
{
    sender("M Player " + std::to_string(_player_id) + " disconnected");
    sender("QUIT");
}

/**
 * @brief Reset the buffer received from the server
 * 
 */
void client::resetReceived() {
    memset(_recv_buf, 0, MAX_READ);
}

/**
 * @brief Send a message to the server
 * @param msg the message to send
 */
void client::sender(std::string msg) {
    _socket.send_to(boost::asio::buffer(msg), _sender_endpoint);
}

/**
 * @brief Start the receive thread
 * 
 */
void client::startReceive()
{
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buf, MAX_READ), _sender_endpoint,
        boost::bind(&client::handleReceive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

/**
 * @brief Handle the message received from the server
 * 
 * @param error the error of the thread
 * @param bytes_transferred the number of bytes transferred
 */
void client::handleReceive(const boost::system::error_code& error, size_t bytes_recvd)
{
    if (!error || error == boost::asio::error::message_size) {
        // std::cout << "Received " << bytes_recvd << " bytes from " << _sender_endpoint << " with data: " << _recv_buf << std::endl;
        _msg_queue.Push(std::string(_recv_buf));
        resetReceived();
        startReceive();
    } else {
        std::cout << "Error in handleReceive: " << error << std::endl;
    }
}

/**
 * @brief Run the client thread
 * 
 */
void client::runClientThread()
{
    _ios.run();
}

/**
 * @brief Start the client thread and set it to true
 * 
 */
void client::startClientThread() {
    if (!_client_thread_running.get()) {
        _client_thread_running.set(true);
        _client_thread1 = std::thread(&client::runClientThread, this);
    }
}

// std::string client::bitToStr(std::bitset<120> bitset)
// {
//     std::string str;
//     for (int i = 0; i < 120; i++) {
//         str += bitset[i] ? '1' : '0';
//     }
//     for (std::size_t i = 0; i < 15; ++i) {
//         bitTmp = std::bitset<8>((permut & bitset).to_ulong());
//         str += static_cast<char>(bitTmp.to_ulong());
//         bitset >>= 8;
//     }
//     return str;
// }