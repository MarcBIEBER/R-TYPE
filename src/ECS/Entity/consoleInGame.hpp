#ifndef CONSOLEINGAME_HPP_
#define CONSOLEINGAME_HPP_

#include "../../AssetManager/AssetManager.hpp"

class consoleInGame : public IComponent {
    public:
        Entity *entity;
        consoleInGame();
        virtual ~consoleInGame() = default;
        consoleInGame(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _pos(pos), _scale(scale), _window(window){
            _textInConsole.setCharacterSize(20);
            _textInConsole.setFillColor(sf::Color::White);
            _textInConsole.setPosition(405, 1020);

            _textAllCommands.setCharacterSize(20);
            _textAllCommands.setFillColor(sf::Color::White);
            _textAllCommands.setPosition(405, 430);
            _font.loadFromFile("./assets/font/arial.ttf");
            _textInConsole.setFont(_font);
            _textAllCommands.setFont(_font);
        }

        /**
         * @brief Init the console fix a sprite and a color
         */
        bool init() override {
            _console_in_game = AssetManager::getInstance().getSprite(_id);
            _console_in_game.setColor(sf::Color(255, 255, 255, 170));
            return true;
        }

        /**
         * @brief Draw the console
         */
        void draw() override {
            if (isDrawable) {
                _window.draw(_console_in_game);
                _window.draw(_textInConsole);
                _window.draw(_textAllCommands);
            }
        }

        void update() override {

        }

        /**
         * @brief Set the scale of the console
         * @param x scale x
         * @param y scale y
         */
        void setScale(float x, float y) {
            _console_in_game.setScale(sf::Vector2f(x, y));
        }

        /**
         * @brief Set the position of the console
         * @param x position x
         * @param y position y
         */
        void setPosition(float x, float y) {
            _console_in_game.setPosition(x, y);
        }

        /**
         * @brief Get the console position
         * @return sf::Vector2f the console position
         */
        sf::Vector2f getPosition() {
            return _console_in_game.getPosition();
        }

        /**
         * @brief Get the console scale
         * @return sf::Vector2f the console scale
         */
        sf::Vector2f getScale() {
            return _console_in_game.getScale();
        }

        /**
         * @brief Get the console size
         * @return sf::Vector2f the console size
         */
        sf::Vector2f getSize() {
            return sf::Vector2f(_console_in_game.getGlobalBounds().width, _console_in_game.getGlobalBounds().height);
        }

        void move(float x, float y) {
        }

        /**
         * @brief Get the sprite of the console
         * @return sf::Sprite & the sprite of the console
         */
        sf::Sprite &_console_inGame() {
            return _console_in_game;
        }

        /**
         * @brief Set the console drawable or not
         * @param bool true or false
         */
        void setDrawable(bool drawable) {
            isDrawable = drawable;
        }

        bool getDrawable() {
            return isDrawable;
        }
        
        /**
         * @brief Delet the last char of the string
         */
        void deleteLastChar() {
            if (_text.size() > 0)
                _text.pop_back();
            _textInConsole.setString(_text);
        }

        /**
         * @brief Send the command to the server
         * @param command the command to send
         */
        void sendCommand(std::string command) {
            if (_text.size() > 0) {
                _text = "";
                _textInConsole.setString(_text);
            }
            _allCommands = "";
            transformAllCommandsIntoAText();
        }

        /**
         * @brief Add the previous command to the history
         * @param command the command to add
         */
        void addCommand(std::string command) {
            _commands.push_back(command);
            _allCommands = "";
            transformAllCommandsIntoAText();
        }
        
        /**
         * @brief Add a char to the string
         * @param c the char to add
         */
        void addChar(char c) {
            _text += c;
            _textInConsole.setString(_text);
        }

        /**
         * @brief Get the command
         * @return std::string the command
         */
        std::string getCommand() {
            return _text;
        }

        /**
         * @brief Get the all commands
         * @return std::vector<std::string> the all commands
         */
        std::vector<std::string> getCommands() {
            return _commands;
        }

        /**
         * @brief Clear all the command history
         */
        void clearCommands() {
            _text = "";
            _textInConsole.setString(_text);
            _commands.clear();
            _textAllCommands.setString("");
        }

        /**
         * @brief Transform all the commands into a text
         */
        void transformAllCommandsIntoAText() {
            for (auto &i : _commands) {
                _allCommands += i;
                _allCommands += '\n';
            }
            _textAllCommands.setString(_allCommands);
        }

        /**
         * @brief set the text of the console
         * @param std::string the text to set
         */
        void setText(std::string text) {
            _text = text;
            _textInConsole.setString(_text);
        }

    private:
        std::string _id;
        sf::Vector2f _pos;
        sf::Vector2f _scale;
        sf::Sprite _console_in_game;
        bool isDrawable = false;

        sf::RenderWindow &_window;

        std::vector<std::string> _commands;
        std::string _text;
        std::string _allCommands;

        sf::Text _textInConsole;
        sf::Text _textAllCommands;
        sf::Font _font;


};

#endif /* !CONSOLEINGAME_HPP_ */
