#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include "../../AssetManager/AssetManager.hpp"

class  Text : public IComponent {
    public:
        Entity *entity;
        Text();
        /**
         * @brief Construct a new text:: text object
         * @param id The id of the entity
         * @param str The string of the text
         * @param window The window of the game
         */
        Text(std::string id, std::string str, sf::RenderWindow &window) : _id(id), _str(str), _window(window) {
            _text.setStyle(sf::Text::Regular);
            _font.loadFromFile("./assets/font/arial.ttf");
            _text.setFont(_font);
            _str = str;
        };
        ~Text() = default;

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            _text = AssetManager::getInstance().getText(_id);
            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            if (_isDrawable)
                _window.draw(_text);
        }

        /**
         * @brief Set if the text is drawable
         */
        void setDrawable(bool isDrawable) {
            _isDrawable = isDrawable;
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
            _text.setPosition(x, y);
        }

        /**
         * @brief Set the size of the text
         * @param size The size of the text
         */
        void setFontSize(int size) {
            _text.setCharacterSize(size);
        }

        /**
         * @brief Set the style of the text
         * @param style The style of the text
         */
        void setStyle(sf::Uint32 style) {
            _text.setStyle(style);
        }

        /**
         * @brief Set the position of the sprite
         * @return The position of the sprite (sf::Vector2f)
         */
        sf::Vector2f getPosition() {
            return _text.getPosition();
        }

        /**
         * @brief return the size of the text
         * @return The size of the text
         */
        int getFontSize() {
            return _text.getCharacterSize();
        }

        /**
         * @brief Set the font of the text
         * @param id The id of the font
         */
        void setFont(std::string id) {
            _font = AssetManager::getInstance().getFont(id);
            _text.setFont(_font);
        }

        /**
         * @brief Use to set the player text easily
         * @param text The text of the player
         */
        void setText(std::string text) {
            _str = text;
            _text.setString(_str);
        }

        std::string getTextString() {
            return _str;
        }

        /**
         * @brief Set the text origin
         * @param x The x position of the origin
         * @param y The y position of the origin
         */
        void setOrigin(float x, float y) {
            _text.setOrigin(x, y);
        }

        /**
         * @brief Return the text object
         * @return The text object
         */
        sf::Text *getText() {
            return &_text;
        }

    protected:
    private:
        std::string _id;
        std::string _str;
        sf::Vector2f _pos;
        int fontSize;
        sf::Text _text;
        sf::Font _font;

        bool _isDrawable = true;

        sf::RenderWindow &_window;
};

#endif /* _TEXT_HPP_ */
