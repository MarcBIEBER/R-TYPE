#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "../../AssetManager/AssetManager.hpp"

/**
 * @brief Class containing all the sprites of the game
 */
class Sprite : public IComponent {
    public:
        Entity *entity;
        Sprite();
        virtual ~Sprite() = default;
        /**
         * @brief Init the sprite
         * @param id The id of the sprite
         * @param pos The x and y position of the sprite (sf::Vector2f)
         * @param scale The scale of the sprite (sf::Vector2f)
         * @param window The window of the game
         */
        Sprite(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _pos(pos), _scale(scale), _window(window){}

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            _sprite = AssetManager::getInstance().getSprite(_id);
            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            _window.draw(_sprite);
        }

        /**
         * @brief Update the sprite
         */
        void update() override {
            if (_id == "hearth_bonus")
                _sprite.move(-9, 0);
            if (_id == "bonus_speed")
                _sprite.move(-7, 0);
            if (_id == "bonus_power")
                _sprite.move(-5, 0);
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

        sf::RenderWindow &_window;
};

#endif /* !SPRITE_HPP_ */