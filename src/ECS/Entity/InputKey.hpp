#ifndef INPUTKEY_HPP_
#define INPUTKEY_HPP_

#include "../../AssetManager/AssetManager.hpp"

class InputKey : public IComponent {
    public:
        Entity *entity;
        InputKey();
        virtual ~InputKey() = default;
        /**
         * @brief Construct a new Input Key object (object to enter text)
         * @param id id of the sprite
         * @param pos position of the sprite
         * @param scale scale of the sprite
         * @param window window to draw
         */
        InputKey(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _pos(pos), _scale(scale), _window(window){
            _textInConsole.setCharacterSize(40);
            _textInConsole.setFillColor(sf::Color::White);
            _textInConsole.setPosition(405, 1020);

            _rectangle.setSize(sf::Vector2f(1000, 50));
            _rectangle.setFillColor(sf::Color::Black);
            _rectangle.setPosition(_pos.x, _pos.y);
            _rectangle.setOutlineThickness(3);
            _rectangle.setOutlineColor(sf::Color::White);

            _font.loadFromFile("./assets/font/arial.ttf");
            _textInConsole.setFont(_font);
        }

        /**
         * @brief Init the console fix a sprite
         */
        bool init() override {
            // _sprite = AssetManager::getInstance().getSprite(_id);
            return true;
        }

        /**
         * @brief Draw the console
         */
        void draw() override {
            if (isDrawable) {
                // _window.draw(_sprite);
                _window.draw(_rectangle);
                _window.draw(_textInConsole);
            }
        }

        /**
         * @brief Update the console
         */
        void update() override {

        }

        /**
         * @brief Set the scale of the console
         * @param x scale x
         * @param y scale y
         */
        void setScale(float x, float y) {
            _rectangle.setScale(sf::Vector2f(x, y));
        }

        /**
         * @brief Set the position of the console
         * @param x position x
         * @param y position y
         */
        void setPosition(float x, float y) {
            _rectangle.setPosition(x, y);
        }
        
        /**
         * @brief Set the text of the console to empty
         */
        void clear() {
            _textInConsole.setString("");
            _text = "";
        }

        /**
         * @brief Get the position of the console
         * @return sf::Vector2f position of the console
         */
        sf::Vector2f getPosition() {
            return _rectangle.getPosition();
        }

        /**
         * @brief Get the scale of the console
         * @return sf::Vector2f scale of the console
         */
        sf::Vector2f getScale() {
            return _rectangle.getScale();
        }

        /**
         * @brief Get the size of the console
         * @return sf::Vector2f size of the console
         */
        sf::Vector2f getSize() {
            return sf::Vector2f(_rectangle.getGlobalBounds().width, _sprite.getGlobalBounds().height);
        }

        void move(float x, float y) {
        }

        /**
         * @brief Get the sprite of inputKey
         * @return sf::Sprite sprite of inputKey
         */
        sf::Sprite &getSprite() {
            return _sprite;
        }

        /**
         * @brief Set the drawable state of the console
         * @param state state of the console
         */
        void setDrawable(bool drawable) {
            isDrawable = drawable;
        }

        /**
         * @brief Delete the last character of the console
         */
        void deleteLastChar() {
            if (_text.size() > 0)
                _text.pop_back();
            _textInConsole.setString(_text);
        }

        /**
         * @brief Get if the consol was clicked
         * @param sf::Vector2i position of the mouse
         */
        bool getClick(sf::Vector2i pos) {
            if (_rectangle.getGlobalBounds().contains(pos.x, pos.y)) {
                _rectangle.setFillColor(_colorGrey);
                return true;
            }
            _rectangle.setFillColor(sf::Color::Black);
            return false;
        }

        /**
         * @brief Add a character to the console
         * @param c character to add
         */
        void addChar(char c) {
            _text += c;
            _textInConsole.setString(_text);
        }

        /**
         * @brief Get the text of the console
         * @return std::string text of the console
         */
        std::string getCommand() {
            return _text;
        }

        /**
         * @brief Return the command
         * @return vector<string> command
         */
        std::vector<std::string> getCommands() {
            return _commands;
        }

        /**
         * @brief Add a command to the console
         * @param command command to add
         */
        void setText(std::string text) {
            _text = text;
            _textInConsole.setString(_text);
        }

        /**
         * @brief Set the text position of the console
         * @param x position x
         * @param y position y
         */
        void setTextPosition(float x, float y) {
            _textInConsole.setPosition(x, y);
        }

        /**
         * @brief Set the origine of the console
         * @param x origine x
         * @param y origine y
         */
        void setOrigine(float x, float y) {
            _rectangle.setOrigin(x, y);
        }

    private:
        std::string _id;
        sf::Vector2f _pos;
        sf::Vector2f _scale;
        sf::RectangleShape _rectangle;
        sf::Sprite _sprite;
        sf::Color _colorGrey = sf::Color(100, 100, 100);
        bool isDrawable = true;

        sf::RenderWindow &_window;

        std::vector<std::string> _commands;
        std::string _text;

        sf::Text _textInConsole;
        sf::Font _font;


};

#endif /* !INPUTKEY_HPP_ */
