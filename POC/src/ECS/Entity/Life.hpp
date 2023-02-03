/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** Text
*/

#ifndef LIFE_HPP_
#define LIFE_HPP_

#include "../../AssetManager/AssetManager.hpp"

class Life : public IComponent {
    public:
        Entity *entity;
        Life();
        /**
         * @brief Construct a new Life:: Life object
         * @param id The id of the entity
         * @param str The string of the text
         * @param window The window of the game
         */
        Life(std::string id, std::string str, sf::RenderWindow &window) : _id(id), _str(str), _window(window) {
            _life.setStyle(sf::Text::Regular);
            _font.loadFromFile("./assets/font/arial.ttf");
            _str = str;
        };
        ~Life() = default;

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            _life = AssetManager::getInstance().getText(_id);
            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            _window.draw(_life);
        }

        /**
         * @brief Update the sprite
         */
        void update() override {

        }

        /**
         * @brief Set the position of the sprite
         * @param x The x position of the sprite (sf::Vector2f)
         * @param y The y position of the sprite (sf::Vector2f)
         */
        void setPosition(float x, float y) {
            _life.setPosition(x, y);
        }

        /**
         * @brief Set the size of the text
         * @param size The size of the text
         */
        void setFontSize(int size) {
            _life.setCharacterSize(size);
        }

        /**
         * @brief Set the style of the text
         * @param style The style of the text
         */
        void setStyle(sf::Uint32 style) {
            _life.setStyle(style);
        }

        /**
         * @brief Set the position of the sprite
         * @return The position of the sprite (sf::Vector2f)
         */
        sf::Vector2f getPosition() {
            return _life.getPosition();
        }

        /**
         * @brief return the size of the text
         * @return The size of the text
         */
        int getFontSize() {
            return _life.getCharacterSize();
        }

        /**
         * @brief Set the text
         * @param text text to set
         */
        void setText(std::string text) {
            _life.setString(text);
        }

        /**
         * @brief Set the font of the text
         * @param id The id of the font
         */
        void setFont(std::string id) {
            _life.setFont(_font);
        }

        /**
         * @brief Use to set the player life easily
         * @param life The life of the player
         */
        void setLife(int life) {
            _str = "Life: " + std::to_string(life);
            _life.setString(_str);
        }

    protected:
    private:
        std::string _id;
        std::string _str;
        sf::Vector2f _pos;
        int fontSize;
        sf::Text _life;
        sf::Font _font;

        sf::RenderWindow &_window;
};

#endif /* !LIFE_HPP_ */
