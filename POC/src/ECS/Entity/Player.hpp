#ifndef Player_HPP_
#define Player_HPP_

#include "../../AssetManager/AssetManager.hpp"

class Player : public IComponent {
    public:
        Entity *entity;
        Player();
        virtual ~Player() = default;
        /**
         * @brief Init the sprite
         * @param id The id of the sprite
         * @param pos The x and y position of the sprite (sf::Vector2f)
         * @param scale The scale of the sprite (sf::Vector2f)
         * @param window The window of the game
         */
        Player(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _pos(pos), _scale(scale), _window(window){}

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
            for (sf::Sprite &bullet : _bullets) {
                _window.draw(bullet);
            }
        }

        /**
         * @brief Update the sprite
         */
        void update() override {
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

        /**
         * @brief Get the bullets
         * @return The bullets (std::vector<sf::Sprite>)
         */
        std::vector<sf::Sprite> &getBullets() {
            return _bullets;
        }

        /**
         * @brief Remove bullet if he go out of screen (memory managment)
         */
        void removeBullet() {
            // _bullets.erase(_bullets.begin() + index);
        }

    private:
        std::string _id;
        sf::Vector2f _pos;
        sf::Vector2f _scale;
        sf::Sprite _sprite;
        std::vector<sf::Sprite> _bullets;
        buffBonus _bonus;

        sf::RenderWindow &_window;
};

#endif /* !Player_HPP_ */