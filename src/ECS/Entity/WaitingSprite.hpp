/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** WaitingSprite
*/

#include "Sprite.hpp"

#ifndef WAITINGSPRITE_HPP_
#define WAITINGSPRITE_HPP_

class WaitingSprite: public IComponent {
    public:
        Entity *entity;
        WaitingSprite();
        virtual ~WaitingSprite() = default;
        /**
         * @brief Init the sprite
         * @param id The id of the sprite
         * @param pos The x and y position of the sprite (sf::Vector2f)
         * @param scale The scale of the sprite (sf::Vector2f)
         * @param window The window of the game
         */
        WaitingSprite(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _pos(pos), _scale(scale), _window(window){}

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            _sprite = AssetManager::getInstance().getSprite(_id);
            _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            if (_isDrawable)
                _window.draw(_sprite);
        }

        /**
         * @brief Update the sprite
         */
        void update() override {
            _sprite.rotate(2);
        }

        /**
         * @brief Set the scale of the sprite
         * @param x The x scale of the sprite (sf::Vector2f)
         * @param y The y scale of the sprite (sf::Vector2f)
         */
        void setScale(float x, float y) {
            _sprite.setScale(sf::Vector2f(x, y));
        }

        /**
         * @brief Set the position of the sprite
         * @param x The x position of the sprite (sf::Vector2f)
         * @param y The y position of the sprite (sf::Vector2f)
         */
        void setPosition(float x, float y) {
            _sprite.setPosition(x, y);
        }

        /**
         * @brief Set the position of the sprite
         * @return The position of the sprite (sf::Vector2f)
         */
        sf::Vector2f getPosition() {
            return _sprite.getPosition();
        }

        /**
         * @brief Set the scale of the sprite
         * @return The sclae of the sprite (sf::Vector2f)
         */
        sf::Vector2f getScale() {
            return _sprite.getScale();
        }

        /**
         * @brief Set the size of the sprite
         * @return The size of the sprite (sf::Vector2f)
         */
        sf::Vector2f getSize() {
            return sf::Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
        }

        /**
         * @brief Set the texture of the sprite
         * @param x The x position of the sprite (sf::Vector2f)
         * @param y The y position of the sprite (sf::Vector2f)
         */
        void move(float x, float y) {
            _sprite.move(x, y);
        }

        /**
         * @brief Move the sprite
         */
        void moveSpecial() {
            _sprite.move(_moveX, _moveY);
        }

        /**
         * @brief Set the move value
         * @param x The x value of the move
         * @param y The y value of the move
         */
        void setMoveValues(float x, float y) {
            _moveX = x;
            _moveY = y;
        }

        /**
         * @brief Set the drawable state of the sprite
         * @param bool The drawable state of the sprite
         */
        void setDrawable(bool drawable) {
            _isDrawable = drawable;
        }

        /**
         * @brief Get the sprite
         * @return The sprite (sf::Sprite)
         */
        sf::Sprite &getSprite() {
            return _sprite;
        }

    private:
        std::string _id;
        sf::Vector2f _pos;
        sf::Vector2f _scale;
        sf::Sprite _sprite;

        buffBonus _bonus;
        float _moveX;
        float _moveY;
        bool _isDrawable = true;
        int rotateValue = 0;

        sf::RenderWindow &_window;
};

#endif /* !WAITINGSPRITE_HPP_ */
