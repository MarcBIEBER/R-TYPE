#ifndef LIFEBAR_HPP_
#define LIFEBAR_HPP_

#include "../../AssetManager/AssetManager.hpp"

/**
 * @brief Class containing all the LifeBars of the game
 */
class LifeBar : public IComponent {
    public:
        Entity *entity;
        LifeBar();
        virtual ~LifeBar() = default;
        /**
         * @brief Init the LifeBar
         * @param id The id of the LifeBar
         * @param pos The x and y position of the LifeBar (sf::Vector2f)
         * @param scale The scale of the LifeBar (sf::Vector2f)
         * @param window The window of the game
         */
        LifeBar(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _pos(pos), _scale(scale), _window(window){}

        /**
         * @brief Init the LifeBar and fix it to the entity
         */
        bool init() override {
            _lifeBar = AssetManager::getInstance().getSprite(_id);
            return true;
        }

        /**
         * @brief Draw the LifeBar
         */
        void draw() override {
            _window.draw(_lifeBar);
        }

        /**
         * @brief Update the LifeBar
         */
        void update() override {

        }

        /**
         * @brief Set the scale of the LifeBar
         * @param x The x scale of the LifeBar (sf::Vector2f)
         * @param y The y scale of the LifeBar (sf::Vector2f)
         */
        void setScale(float x, float y) {
            _lifeBar.setScale(sf::Vector2f(x, y));
        }

        /**
         * @brief Set the position of the LifeBar
         * @param x The x position of the LifeBar (sf::Vector2f)
         * @param y The y position of the LifeBar (sf::Vector2f)
         */
        void setPosition(float x, float y) {
            _lifeBar.setPosition(x, y);
        }

        /**
         * @brief Set the position of the LifeBar
         * @return The position of the LifeBar (sf::Vector2f)
         */
        sf::Vector2f getPosition() {
            return _lifeBar.getPosition();
        }

        /**
         * @brief Set the scale of the LifeBar
         * @return The sclae of the LifeBar (sf::Vector2f)
         */
        sf::Vector2f getScale() {
            return _lifeBar.getScale();
        }

        /**
         * @brief Set the size of the LifeBar
         * @return The size of the LifeBar (sf::Vector2f)
         */
        sf::Vector2f getSize() {
            return sf::Vector2f(_lifeBar.getGlobalBounds().width, _lifeBar.getGlobalBounds().height);
        }

        /**
         * @brief Set the texture of the LifeBar
         * @param x The x position of the LifeBar (sf::Vector2f)
         * @param y The y position of the LifeBar (sf::Vector2f)
         */
        void move(float x, float y) {
            _lifeBar.move(x, y);
        }

        /**
         * @brief Set the texture of the LifeBar
         * @param id The id of the texture
         * @param rect The rect of the texture
         * @param offset The offset of the texture
         */
        void lifeProgression(std::string id, sf::IntRect *rect, float offset) {
            sf::Sprite my_sprite = AssetManager::getInstance().getSprite(id);
            rect->top -= offset;
            _lifeBar.setTextureRect(*rect);
        }

        /**
         * @brief Get the LifeBar
         * @return The LifeBar (sf::LifeBar)
         */
        sf::Sprite &getLifeBar() {
            return _lifeBar;
        }

    private:
        std::string _id;
        sf::Vector2f _pos;
        sf::Vector2f _scale;
        sf::Sprite _lifeBar;

        buffBonus _bonus;

        sf::RenderWindow &_window;
};

#endif /* !LIFEBAR_HPP_ */