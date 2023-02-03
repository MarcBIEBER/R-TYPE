/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "../../AssetManager/AssetManager.hpp"

class Text : public IComponent {
    public:
        Entity *entity;
        Text();
        /**
         * @brief Construct a new Life:: Life object
         * @param window The window of the game
         */
        Text(std::string str, sf::RenderWindow &window) : _window(window) {
            _font.loadFromFile("./assets/font/arial.ttf");
            _str = str;
        };
        ~Text() = default;

        /**
         * @brief Init the text and fix it to the entity
         */
        bool init() override {
            for (auto &i : _text) {
                i.setFont(_font);
                i.setString(_str);
                i.setCharacterSize(24);
                i.setFillColor(sf::Color::White);
                i.setStyle(sf::Text::Regular);
            }
            return true;
        }

        /**
         * @brief Draw the text
         */
        void draw() override {
            for (auto &i : _text)
                _window.draw(i);
        }

        /**
         * @brief Update the text
         */
        void update() override {

        }

        /**
         * @brief Set the position of the text
         * @param x The x position of the text (sf::Vector2f)
         * @param y The y position of the text (sf::Vector2f)
         */
        void setPosition(float x, float y) {
            for (auto &i : _text)
                i.setPosition(x, y);
            // _life.setPosition(x, y);
        }

        /**
         * @brief Set the size of the text
         * @param size The size of the text
         */
        void setFontSize(int size) {
            for (auto &i : _text)
                i.setCharacterSize(size);
            // _life.setCharacterSize(size);
        }

        /**
         * @brief Set the style of the text
         * @param style The style of the text
         */
        void setStyle(sf::Uint32 style) {
            for (auto &i : _text)
                i.setStyle(style);
        }

        /**
         * @brief Set the position of the text
         * @return The position of the text (sf::Vector2f)
         */
        sf::Vector2f getPosition() {
            for (auto &i : _text)
                return i.getPosition();
            return sf::Vector2f(0, 0);
        }

        /**
         * @brief return the size of the text
         * @return The size of the text
         */
        int getFontSize() {
            for (auto &i : _text)
                return i.getCharacterSize();
            return 0;
        }

        /**
         * @brief Set the text
         * @param text text to set
         */
        void setText(std::string text) {
            for (auto &i : _text)
                i.setString(text);
        }

        /**
         * @brief Set the font of the text
         * @param id The id of the font
         */
        void setFont(std::string id) {
            for (auto &i : _text)
                i.setFont(AssetManager::getInstance().getFont(id));
        }

    protected:
    private:
        std::vector<sf::Text> _text;
        std::string _id;
        std::string _str;
        sf::Vector2f _pos;
        int fontSize;
        // sf::Text _text;
        sf::Font _font;
        sf::RenderWindow &_window;
};

#endif /* !TEXT_HPP_ */
