/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** ServerBox
*/

#ifndef ServerBox_HPP_
#define ServerBox_HPP_

#include "../../AssetManager/AssetManager.hpp"

#define SPACE 250 //y = SPACE * nbBox

class ServerBox : public IComponent {
    public:
        Entity *entity;
        ServerBox();
        virtual ~ServerBox() = default;
        /**
         * @brief Init the ServerBox
         * @param id The id of the ServerBox
         * @param window The window of the game
         */
        ServerBox(std::string id, sf::RenderWindow &window, std::string host, std::string port, int nbOfBox) : _id(id), _window(window), _host(host), _port(port), _nbOfBox(nbOfBox) {
            _rectangle.setSize(sf::Vector2f(1000, 150));
            _rectangle.setFillColor(sf::Color::Black);
            _rectangle.setPosition(500, 200 + (SPACE * _nbOfBox));
            _rectangle.setOutlineThickness(5);
            _rectangle.setOutlineColor(sf::Color::Transparent);

            _font.loadFromFile("./assets/font/Aloevera-OVoWO.ttf");

            _textHost.setStyle(sf::Text::Regular);
            _textPort.setStyle(sf::Text::Regular);
            _textHost.setFont(_font);
            _textPort.setFont(_font);
            _textHost.setCharacterSize(50);
            _textPort.setCharacterSize(50);
            _textHost.setFillColor(sf::Color::White);
            _textPort.setFillColor(sf::Color::White);
            _textHost.setPosition(550, 210 + SPACE * _nbOfBox);
            _textPort.setPosition(550, 270 + SPACE * _nbOfBox);
            _textHost.setString(_host);
            _textPort.setString(_port);
        }

        /**
         * @brief Init the ServerBox with previous data
         * @param id The id of the ServerBox
         * @param window The window of the game
         */
        ServerBox(std::string id, sf::RenderWindow &window, std::string host, std::string port, int nbOfBox, int lastBoxPos) : _id(id), _window(window), _host(host), _port(port), _nbOfBox(nbOfBox) {
            _rectangle.setSize(sf::Vector2f(1000, 150));
            _rectangle.setFillColor(sf::Color::Black);

            _rectangle.setPosition(500, lastBoxPos + SPACE);
            _rectangle.setOutlineThickness(5);
            _rectangle.setOutlineColor(sf::Color::Transparent);

            _font.loadFromFile("./assets/font/Aloevera-OVoWO.ttf");

            _textHost.setStyle(sf::Text::Regular);
            _textHost.setFont(_font);
            _textHost.setCharacterSize(50);
            _textHost.setFillColor(sf::Color::White);
            _textHost.setPosition(550, lastBoxPos + 10 + SPACE);
            _textHost.setString(_host);

            _textPort.setStyle(sf::Text::Regular);
            _textPort.setFont(_font);
            _textPort.setCharacterSize(50);
            _textPort.setFillColor(sf::Color::White);
            _textPort.setPosition(550, lastBoxPos + 60 + SPACE);
            _textPort.setString(_port);

        }

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            
            
            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            if (_rectangle.getGlobalBounds().top < 858) {
                _window.draw(_rectangle);
                _window.draw(_textHost);
                _window.draw(_textPort);
                _window.draw(_bestScore);
                _window.draw(_BestBossKill);
            }
        }

        /**
         * @brief Update the sprite
         */
        void update() override {

        }

        /**
         * @brief Return the host wrote in the box
         * @return std::string the host
         */
        std::string getHost() { return _host; }

        /**
         * @brief Return the port wrote in the box
         * @return std::string the port
         */
        std::string getPort() { return _port; }

        /**
         * @brief Return if the serverBox is selected
         * @return true if the serverBox is selected
         * @return false if the serverBox is not selected
         */
        bool isClick(sf::Vector2i mousePos) {
            int posX = mousePos.x;
            int posY = mousePos.y;
            if (posY > 858)
                return false;
            if (posX >= _rectangle.getPosition().x && posX <= _rectangle.getPosition().x + _rectangle.getSize().x && posY >= _rectangle.getPosition().y && posY <= _rectangle.getPosition().y + _rectangle.getSize().y) {
                return true;
            }
            _rectangle.setOutlineColor(sf::Color::Transparent);
            return false;
        }

        /**
         * @brief Select the serverBox
         * @return int the serverBox id
         */
        int getClick(sf::Vector2i mousePos) {
            setIsClick(true);
            _rectangle.setOutlineColor(sf::Color::White);
            return _nbOfBox;
        }

        /**
         * @brief Set the Is Click object
         * @param isClick true if the serverBox is selected
         */
        void setIsClick(bool isClick) {
            _isClick = isClick;
            if (_isClick)
                _rectangle.setOutlineColor(sf::Color::White);
            else
                _rectangle.setOutlineColor(sf::Color::Transparent);
        }

        /**
         * @brief Return the position of the serverBox
         * @return sf::Vector2f the position of the serverBox
         */
        sf::Vector2f getPosition() { return _rectangle.getPosition(); }

        /**
         * @brief Use to move the serverBox when scrolling
         * @param x the x position
         * @param y the y position
         */
        void move(int x, int y) {
            _rectangle.move(x, y);
            _textHost.move(x, y);
            _textPort.move(x, y);
        }

    private:
        int _nbOfBox;
        std::string _id;
        sf::RenderWindow &_window;
        bool _isClick = false;

        sf::Text _textHost;
        sf::Text _textPort;


        sf::Text _bestScore;
        sf::Text _BestBossKill;


        sf::Font _font;

        sf::RectangleShape _rectangle;
        std::string _host;
        std::string _port;
};

#endif /* !ServerBox_HPP_ */
