#include <iostream>
#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <thread>
#include "../src/SafeQueue.hpp"
#include "../src/safeVariable.hpp"

using boost::asio::ip::udp;
#define MAXLENGTH 2048
#define NB_ENNEMIES 4
#define NB_BONUS 3
#define MAX_CONNECTED_PLAYER 4
#define ASTEROISD_SPAWN_TIME 6
#define ENNEMY_1_SPAWN_TIME 6
#define ENNEMY_2_SPAWN_TIME 10
#define ENNEMY_3_SPAWN_TIME 15
#define BONUS_1_SPAWN_TIME 20
#define BONUS_2_SPAWN_TIME 27
#define BONUS_3_SPAWN_TIME 34

enum ennemyType {
    ASTEROIDS
};

enum serverClocks {
    BOSS_CLOCK,
    STAGE_CLOCK,
    PROGRESS_CLOCK,
    MINI_BOSS_CLOCK,
    NB_CLOCKS
};

enum pingPlayerClocks {
    PING_PLAYER_1,
    PING_PLAYER_2,
    PING_PLAYER_3,
    PING_PLAYER_4,
    NB_PING_CLOCKS
};

struct playerPing {
    int id;
    sf::Int32 ping;
    bool pingReceived;
};

/**
 * @brief This class is used to handle the server side of the game
 * 
 */
class server {
    public:
        /**
         * @brief Construct a new server object
         * 
         * @param port The port on which the server will listen
         */
        server(int _port) : _socket(_io_service, udp::endpoint(udp::v4(), _port))
        {
            _nbPlayers.set(0);
            _serverPort = _port;
            for (int i = 1; i < MAX_CONNECTED_PLAYER + 1; i++) {
                _connected_players.push_back(std::pair<int, bool>(i, false));
                _playerPings.push_back(playerPing{i, 0, false});
            }
            for (int i = 0; i < NB_ENNEMIES; i++) {
                _clockDurationEnemy.push_back(sf::Clock());
                _timeDurationEnemy.push_back(sf::Time());
            }
            for (int i = 0; i < NB_CLOCKS; i++) {
                _serverClocks.push_back(sf::Clock());
                _serverTimes.push_back(sf::Time());
            }
            for (int i = 0; i < NB_PING_CLOCKS; i++) {
                _serverPingClocks.push_back(sf::Clock());
                _serverPingTimes.push_back(sf::Time());
            }
            _nb_bonus = 3;
            for (int i = 0; i < _nb_bonus; i++) {
                _clockDurationBonus.push_back(sf::Clock());
                _timeDurationBonus.push_back(sf::Time());
            }
            _bossIsAlive.set(false);
            _miniBossIsAlive.set(false);
            _stopAcceptingClients.set(false);
            startReceive();
        }

        /**
         * @brief Destroy the server object (threads, ...)
         * 
         */
        ~server() {
            if (_threadCreateEnnemies.joinable())
                _threadCreateEnnemies.join();   
            if (_threadIosRunning.joinable())
                _threadIosRunning.join();   
            if (_threadBoss.joinable())
                _threadBoss.join();   
            std::cout << "Server with port:" << _serverPort << " closed" << std::endl;
        }

        /**
         * @brief This function is used to start the server receive thread
         * 
         */
        void startReceive();

        /**
         * @brief This function is used to start the server send thread
         * 
         */
        void startSend(udp::endpoint endpoint);

        /**
         * @brief This function is used to handle the receive of a packet
         * 
         */
        void handleReceive(udp::endpoint endpoint, const boost::system::error_code& error, size_t bytes_recvd);

        /**
         * @brief Used to handle the send of a packet
         * 
         */
        void handleSend(std::string message, udp::endpoint _endpoint, const boost::system::error_code& error, size_t bytes_recvd);

        /**
         * @brief Used to send information to all the connected players
         * 
         */
        void sendToAllPlayers(std::string message);

        /**
         * @brief Used to add new players to the game
         * 
         */
        void addNewPlayer(udp::endpoint endpoint);

        /**
         * @brief Start IoService
         * 
         */
        void runIos();

        /**
         * @brief Get the player connected
         * @return the number of player connected
         */
        int getAvailableId();

        /**
         * @brief Get the player and print the state of connection
         * 
         */
        void printPlayers();

        /**
         * @brief Create ennemy with clock
         */
        void createEnnemies();

        /**
         * @brief Send to all players the ennemies
         * @param ennemyId the id of the ennemy to send
         * @param seconds the time to wait before sending the ennemy
         * @param the clock to use
         * @param the time to use
         */
        void spawnEnnemy(int ennemyId, float seconds, sf::Clock &clockDurationEnemy, sf::Time &timeDurationEnemy);

        /**
         * @brief Get the port opened by the server
         * @return the port opened by the server (int)
         */
        int getPort() { return _serverPort; }

        /**
         * @brief Stop the server
         */
        void stopServer() { _io_service.stop(); }

        /**
         * @brief Start the thread and IoService
         */
        void enterThreadsAndRunIos();


        void getPrompt();
        
        /**
         * @brief Get the player input and handle it
         * 
         */
        int dealWithInput(std::string input);
    
        /**
         * @brief Enter in the main thread
         * 
         */
        void enterThreads();

        /**
         * @brief Start the boss thread
         * 
         */
        void createBossThread();
        void createMiniBossThread();

        /**
         * @brief Clear the server message
         * 
         */
        void clearServerStatus();

        /**
         * @brief Handle the boss thread
         * 
         */
        void bossThread();
        void miniBossThread();

        /**
         * @brief Get the thread id
         * @return the thread id (std::thread::id)
         */
        std::thread::id getThreadId() { return _threadCreateEnnemies.get_id(); }

        /**
         * @brief Get the player ping
         * @param message the message received
         */
        void checkPlayerPing(std::string &message);

        /**
         * @brief Create a Bonus object
         * 
         * @param _clockDurationBonus 
         * @param _timeDurationBonus 
         */
        void createBonus(int bonusId, float seconds, sf::Clock &clockDurationBonus, sf::Time &timeDurationBonus);
        // std::bitset<120> toBitset(std::string str);

    private:
        boost::asio::io_service _io_service;
        udp::socket _socket;
        udp::endpoint _endpoint;
        SafeQueue<std::string> _queue;
        std::mutex _mutexReceive;
        char _recv_buf[MAXLENGTH] = "";
        safeVariable<int> _nbPlayers;
        std::vector<sf::Clock> _clockDurationBonus;
        std::vector<sf::Time> _timeDurationBonus;
        int _nb_bonus;
        int _nb_enemy;
        bool _isRunning = false;
        bool _bossThreadLunched = false;
        bool _miniBossThreadLunched = false;
        int _serverPort;
        int _acctualStage = 1;
        int _progressPos = 0;
        bool bossIsDead = false;
        float _bullet_spawn_time = 1.0;

        //sender

        // std::bitset<120> _bitset;

        std::vector<std::pair<int, udp::endpoint>> _players;
        std::vector<std::pair<int, bool>> _connected_players;
        std::vector<sf::Clock> _serverClocks;
        std::vector<sf::Time> _serverTimes;
        std::vector<sf::Clock> _serverPingClocks;
        std::vector<sf::Time> _serverPingTimes;
        std::vector<playerPing> _playerPings;

        // clocks for ennemies:
        std::vector<sf::Clock> _clockDurationEnemy;
        std::vector<sf::Time> _timeDurationEnemy;
        std::thread _threadCreateEnnemies;
        std::thread _threadIosRunning;
        std::thread _threadBoss;
        std::thread _threadMiniBoss;
        safeVariable<bool> _bossIsAlive;
        safeVariable<bool> _miniBossIsAlive;
        safeVariable<bool> _bossIsDead;
        safeVariable<bool> _stopAcceptingClients;
        std::vector<float> _ennemySpawnTime = { ASTEROISD_SPAWN_TIME, ENNEMY_1_SPAWN_TIME, ENNEMY_2_SPAWN_TIME, ENNEMY_3_SPAWN_TIME };
        std::vector<float> _bonusSpawnTime = { BONUS_1_SPAWN_TIME, BONUS_2_SPAWN_TIME, BONUS_3_SPAWN_TIME};
};