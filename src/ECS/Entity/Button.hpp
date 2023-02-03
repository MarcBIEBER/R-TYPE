#ifndef Button_HPP_
#define Button_HPP_

#include "../../AssetManager/AssetManager.hpp"

/**
 * @brief Class containing all the button of the game
 */
class Button : public IComponent {
    public:
        Entity *entity;
        Button();
        virtual ~Button() = default;
        /**
         * @brief Init the Button
         * @param id The id of the Button
         * @param pos The x and y position of the Button (sf::Vector2f)
         * @param scale The scale of the Button (sf::Vector2f)
         * @param window The window of the game
         */
        Button(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _window(window)
        {
            _button.setPosition(pos);
            _button.setScale(scale);
        };

        /**
         * @brief Init the Button and fix it to the entity
         */
        bool init() override {
            _button = AssetManager::getInstance().getSprite(_id);
            _hover = AssetManager::getInstance().getSprite(_id + "Hover");
            // std::cout << "!!!!!!!!!!!!!!!Button position" << _button.getPosition().x << " " << _button.getPosition().y << std::endl;

            return true;
        }

        /**
         * @brief Draw the Button
         */
        void draw() override {
            if (_isDrawable) {
                if (_isHover)
                    _window.draw(_hover);
                else
                    _window.draw(_button);
            }
        }

        /**
         * @brief Set the state "drawable" of the Button
         */
        void setDrawable(bool isDrawable) {
            _isDrawable = isDrawable;
        }

        /**
         * @brief Update the Button
         */
        void update() override {

        }

        /**
         * @brief Set the scale of the Button
         * @param x The x scale of the Button (sf::Vector2f)
         * @param y The y scale of the Button (sf::Vector2f)
         */
        void setScale(float x, float y) {
            _button.setScale(sf::Vector2f(x, y));
            _hover.setScale(_button.getScale());
        }

        /**
         * @brief Set the position of the Button
         * @param x The x position of the Button (sf::Vector2f)
         * @param y The y position of the Button (sf::Vector2f)
         */
        void setPosition(float x, float y) {
            _button.setPosition(x, y);
            _hover.setPosition(_button.getPosition());
        }

        /**
         * @brief Set the position of the Button
         * @return The position of the Button (sf::Vector2f)
         */
        sf::Vector2f getPosition() {
            return _button.getPosition();
        }

        /**
         * @brief Set the scale of the Button
         * @return The sclae of the Button (sf::Vector2f)
         */
        sf::Vector2f getScale() {
            return _button.getScale();
        }

        /**
         * @brief Set the size of the Button
         * @return The size of the Button (sf::Vector2f)
         */
        sf::Vector2f getSize() {
            return sf::Vector2f(_button.getGlobalBounds().width, _button.getGlobalBounds().height);
        }

        /**
         * @brief Get the Button
         * @return The Button (sf::Button)
         */
        sf::Sprite &getButton() {
            return _button;
        }

        /**
         * @brief Set the origin of the Button
         * @param x The x origin of the Button (sf::Vector2f)
         * @param y The y origin of the Button (sf::Vector2f)
         */
        void setOrigin(float x, float y) {
            _button.setOrigin(x, y);
            _hover.setOrigin(x, y);
        }

        /**
         * @brief Get if the button is clicked
         * @param sf::Vector2i Position of the mouse
         * @return true if the button is clicked
         * @return false if the button is not clicked
         */
        bool getClick(sf::Vector2i pos) {
            if (_button.getGlobalBounds().contains(pos.x, pos.y)) {
                return true;
            }
            return false;
        }

        /**
         * @brief Get if the button is hovered
         * @param sf::Vector2i Position of the mouse
         * @return true if the button is hovered
         * @return false if the button is not hovered
         */
        void handleHover(sf::Vector2i pos) {
            if (_button.getGlobalBounds().contains(pos.x, pos.y)) {
                _isHover = true;
            } else {
                _isHover = false;
            }
        }

    private:
        std::string _id;
        sf::Sprite _button;
        sf::Sprite _hover;
        buffBonus _bonus;
        bool _isDrawable = true;
        bool _isHover = false;
        sf::RenderWindow &_window;
};

#endif /* !Button_HPP_ */