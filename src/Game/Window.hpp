/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "../ECS/System.hpp"
#include "../Client/Client.hpp"

class Window {
    public:
        Window();
        /**
         * @brief Construct a new Window object
         * @param client the curent client of the game
         */
        Window(client &client);
        ~Window();

        /**
         * @brief Return the window
         * @return sf::RenderWindow current window
         */
        sf::RenderWindow &getWindow() { return this->_window; };

        /**
         * @brief Return the current scene
         * @return sceneEnum current scene
         */
        sceneEnum getScene() { return this->_scene; };

        /**
         * @brief Get the client
         * @return client& 
         */
        client &getClient() { return _client; }

        /**
         * @brief Set the scene
         * @param scene 
         */
        void setGameScene(sceneEnum scene) { this->_scene = scene; };

        /**
         * @brief Use to know if the client is connected
         * @return true if the client is connected
         */
        bool getIsClientConnected() { return _isClientConnected; }

        /**
         * @brief Set the Is Client Connected variable
         * @param bool true / false
         */
        void setIsClientConnected(bool isClientConnected) { _isClientConnected = isClientConnected; }
        void clearWindow();
        void setShipMusicPosition(sf::Vector2f pos);
        void refreshWindow();
        void draw(System &system);
        void update(System &system);

        /**
         * @brief Return the music
         * @return sf::Music& 
         */
        sf::Music *getMusic () { return &gameMusic; }

        /**
         * @brief Return the music of space ship
         * @return sf::Music& 
         */
        sf::Music *getMusicShip () { return &spaceshipMusic; }

        /**
         * @brief Increase the number of boss killed
         */
        void increaseBossKilled() { _nbBossKilled++; }

        /**
         * @brief Return the number of boss killed
         * @return int : number of boss killed
         */
        int getBossKilled() { return _nbBossKilled; }

        /**
         * @brief Increase the score 
         */
        void increaseScore() { _score += 1; }

        /**
         * @brief Return the score
         * @return int : acctual score
         */
        int getScore() { return _score; }
        bool getLobbyFull() { return _lobbyFull; }
        void setLobbyFull(bool lobbyFull) { _lobbyFull = lobbyFull; }

    protected:
    private:
        sf::RenderWindow _window;
        client &_client;
        sceneEnum _scene;
        sf::Music gameMusic;
        bool _lobbyFull = false;
        sf::Music spaceshipMusic;
        bool _isClientConnected = false;
        int _nbBossKilled = 0;
        int _score = 0;
};

#endif /* !WINDOW_HPP_ */
