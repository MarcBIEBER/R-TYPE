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
            return true;
        }

        /**
         * @brief Draw the Button
         */
        void draw() override {
            _window.draw(_button);
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
        }

        /**
         * @brief Set the position of the Button
         * @param x The x position of the Button (sf::Vector2f)
         * @param y The y position of the Button (sf::Vector2f)
         */
        void setPosition(float x, float y) {
            _button.setPosition(x, y);
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

        // int getClick(clickEnum click, sf::Vector2i pos) {
        //     if (_button.getGlobalBounds().contains(pos.x, pos.y)) {
        //         if (click == PLAY) {
        //             return 1;
        //         }
        //     }
        //     return 0;
        // }

    private:
        std::string _id;
        sf::Sprite _button;
        buffBonus _bonus;

        sf::RenderWindow &_window;
};

#endif /* !Button_HPP_ */