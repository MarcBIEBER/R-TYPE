/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** GamePlay
*/

#ifndef GAMEPLAY_HPP_
#define GAMEPLAY_HPP_

#include "../Window.hpp"

#define SPEED 25

#define GETCOMP(ennemyID, compType)     _system->getManager().getEntity(ennemyID).get()->getComponent<compType>()
#define GET_BONUS(bonusID, compType)    _system->getManager().getEntity(bonusID).get()->getComponent<compType>()
#define GET_CONSOLE                     _system->getManager().getEntity("console").get()->getComponent<consoleInGame>()
#define GET_STARSHIP(id)                GETCOMP("player" + std::to_string(id), SpaceShip)
#define GET_PLAYER_TEXT                 _system->getManager().getEntity("player_text").get()->getComponent<Text>()
#define GET_FINAL_BOSS                  _system->getManager().getEntity("finalBoss").get()->getComponent<FinalBoss>()
#define GET_MINI_BOSS                   _system->getManager().getEntity("miniBoss").get()->getComponent<SemiBoss>()
#define GET_HIT_SOUND                   _system->getManager().getEntity("shoothit").get()->getComponent<Sound>()
#define GET_SHOOT_SOUND                 _system->getManager().getEntity("shoot").get()->getComponent<Sound>()
#define GET_NOOO                        _system->getManager().getEntity("nooo").get()->getComponent<Sound>()
#define GET_YOU_DONT_KNOW               _system->getManager().getEntity("youDontKnow").get()->getComponent<Sound>()
#define GET_THE_POWER_OF                _system->getManager().getEntity("thePowerOf").get()->getComponent<Sound>()
#define GET_WAITING_SPRITE              _system->getManager().getEntity("waiting_server").get()->getComponent<WaitingSprite>()
#define GET_WAITING_TEXT                _system->getManager().getEntity("text_waiting_server").get()->getComponent<Text>()
#define GET_LOBBY_TEXT                  _system->getManager().getEntity("lobbyText").get()->getComponent<Text>()
#define GET_LIFE                        _system->getManager().getEntity("life").get()->getComponent<Life>()
#define GET_LOBBY                       _system->getManager().getEntity("lobbyBoard").get()->getComponent<LobyBoard>()

typedef struct {
    std::vector<std::string> tokens;
    int id;
    int posX;
    int posY;
} token_t;

enum Clocks {
    PLAYER_POSITION,
    FPS_CLOCK,
    BULLET_CLOCK,
    PARALLAX_ONE,
    PARALLAX_TWO,
    PARALLAX_THREE,
    PARALLAX_FOUR,
    PLAYER_SHOOT,
    CHECK_PING,
    NB_CLOCKS
};

class GamePlay {
    public:
        GamePlay() {};
        GamePlay(client &client, Window &window);
        ~GamePlay();
        void loop();
        void init();
        void handleServerCommand();
        void tryConnectToServer();

        /**
         * @brief Get the system object
         * 
         * @return System &
         */
        System &getSystem() { return *_system; };

        void getIntoLobby(int playerId);
        void movePlayers(std::string msg);
        void createNewBullet(std::string msg);
        void createNewEnnemy(std::string msg);
        void createNewBonus(std::string msg);
        void updateStage(std::string msg);
        void createBoss(int stage);
        void createMiniBoss(int stage);
        void resetPlayerPosition(std::string msg);
        void activePlayers(std::string msg);
        void receiveMessageFromPlayer(std::string msg);
        void setSpaceShip();
        void getPlayerInput(sf::Event event);
        bool getCollision(sf::Sprite &spriteOne, sf::Sprite &spriteTwo);
        void getCollisionBetweenPlayersAndMBosses();
        void getCollisionBetweenBossAndWindow();
        void createMiniBossBullet(std::string msg);

        token_t getTokens(std::string msg);
        void getTimeFromClocks();

        void handleParallax();

        void handleEnnemyMovement();
        void handleCollision();
        void sendSpecificCommandToServer();

        void addProgression(std::string msg);

        void makePollEvent();

        /**
         * @brief Set the player id
         * 
         * @param int player id
         */
        void setPlayerId(int player_id) { this->_player_id = player_id; }

        /**
         * @brief Get the first element of the safe queue
         * 
         * @return 
         */
        sf::Keyboard::Key getEventQueueFront() {sf::Keyboard::Key key = this->_events.front(); this->_events.pop(); return key;};

        /**
         * @brief Push a event in a safe queue
         * 
         * @param sf::Keyboard::Key key
         */
        void pushKeyIntoQueue(sf::Keyboard::Key key) {this->_events.push(key);};

        /**
         * @brief Use to know if the safe queue is empty
         * 
         * @return true / false
         */
        bool isEventQueueEmpty() {return _events.empty();};
        void createFinalBossBullet(std::string msg);

        void getInputKeysForConsole(sf::Event event);
        void checkConsoleCommand();
        void leaveConsole();

        /**
         * @brief Get the player current life
         * 
         * @return int player life
         */
        int getPlayerLife() { return _playerLife; };

        /**
         * @brief Update the player life when he take damage take the acctual value and substract one
         * 
         */
        void setPlayerLife() { 
            _playerLife--;
            _window->getClient().sender("l " + std::to_string(_player_id) + " " + std::to_string(_playerLife));
        };


        /**
         * @brief Update the player life when he take damage take the acctual value and substract one
         * 
         */
        void setPlayerLifeBonus() { _playerLife++; };

        /**
         * @brief Get stage
         *
         */
        int getStage(){return actualStage;};

        /**
         * @brief Set stage
         *
         */
        void setStage(int stage){actualStage = stage;};

        /**
         * @brief Get up or down
         * 
         * @return int up or down
         */
        int getUpOrDown(){return _up_or_down;};

        /**
         * @brief Set up or down
         *
         */
        void setUpOrDown(int up_or_down){_up_or_down = up_or_down;};

        /**
         * @brief Get left or right
         * 
         * @return int left or right
         */ 
        int getLeftOrRight(){return _left_or_right;};

        /**
         * @brief Set left or right
         *
         */
        void setLeftOrRight(int left_or_right){_left_or_right = left_or_right;};

        /**
         * @brief Get if touch the boss
         * 
         * @return bool touch
         */
        bool getTouch(){return _touch;};

        /**
         * @brief Set if touch the boss
         *
         */
        void setTouch(bool touch){_touch = touch;};

        void getPing(std::string msg);

        void setLifePlayers(std::string msg);

        void setPlayersName(std::string msg);

        void sendPlayerNameToServer();

        void lobbyFull();

    protected:
    private:
        Window *_window;
        System *_system;
        SpaceShip *_starship;

        bool _touch = false;
        int _up_or_down = -4;
        int _left_or_right = 0;
        int actualStage = 0;
        bool is_connected = false;
        bool hasPlayerId = false;
        bool sentConnect = false;
        bool isTyping = false;
        bool maxBullets = false;
        bool playedMiddleSound = false;
        bool isPlayerReady = false;
        bool _isBonusActive = false;
        int nbr_occ_bonus_bullet = 0;
        bool shot_bonus_bullet = false;

        int _player_id;
        int _fpsCounter = 0;
        int _ping = 9999;
        int _bonus_speed = 1;

        int _playerLife = 20;

        std::queue<sf::Keyboard::Key> _events;
        // clokcs:
        std::vector<sf::Clock> _gamePlayClocks;
        std::vector<sf::Time> _gamePlayTime;
};

#endif /* !GAMEPLAY_HPP_ */
