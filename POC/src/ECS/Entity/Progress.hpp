#ifndef progression_bar_HPP_
#define progression_bar_HPP_

#include "../../AssetManager/AssetManager.hpp"

/**
 * @brief Class containing all the progression_bars of the game
 */
class ProgressionBar : public IComponent {
    public:
        Entity *entity;
        ProgressionBar();
        virtual ~ProgressionBar() = default;
        /**
         * @brief Init the progression_bar
         * @param id The id of the progression_bar
         * @param pos The x and y position of the progression_bar (sf::Vector2f)
         * @param scale The scale of the progression_bar (sf::Vector2f)
         * @param window The window of the game
         */
        ProgressionBar(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _pos(pos), _scale(scale), _window(window){}

        /**
         * @brief Init the progression_bar and fix it to the entity
         */
        bool init() override {
            _progression_bar = AssetManager::getInstance().getSprite(_id);
            return true;
        }

        /**
         * @brief Draw the progression_bar
         */
        void draw() override {
            _window.draw(_progression_bar);
        }

        /**
         * @brief Update the progression_bar
         */
        void update() override {

        }

        /**
         * @brief Set the scale of the progression_bar
         * @param x The x scale of the progression_bar (sf::Vector2f)
         * @param y The y scale of the progression_bar (sf::Vector2f)
         */
        void setScale(float x, float y) {
            _progression_bar.setScale(sf::Vector2f(x, y));
        }

        /**
         * @brief Set the position of the progression_bar
         * @param x The x position of the progression_bar (sf::Vector2f)
         * @param y The y position of the progression_bar (sf::Vector2f)
         */
        void setPosition(float x, float y) {
            _progression_bar.setPosition(x, y);
        }

        /**
         * @brief Set the texture of the progression_bar
         * @param id The id of the texture
         * @param rect The rectangle of the texture
         * @param offset The offset of the texture
         */
        void spriteProgression(std::string id, sf::IntRect *rect, float offset) {
            sf::Sprite my_sprite = AssetManager::getInstance().getSprite(id);
            rect->top += offset;
            // std::cout << "top "<< rect->top << std::endl;
            if (rect->top >= 244 && end_bar == false) {
                end_bar = true;
                rect->top = 0;
                rect->left += 408;
            }
            _progression_bar.setTextureRect(*rect);
        }

        /**
         * @brief Set the position of the progression_bar
         * @return The position of the progression_bar (sf::Vector2f)
         */
        sf::Vector2f getPosition() {
            return _progression_bar.getPosition();
        }

        /**
         * @brief Set the scale of the progression_bar
         * @return The sclae of the progression_bar (sf::Vector2f)
         */
        sf::Vector2f getScale() {
            return _progression_bar.getScale();
        }

        /**
         * @brief Set the size of the progression_bar
         * @return The size of the progression_bar (sf::Vector2f)
         */
        sf::Vector2f getSize() {
            return sf::Vector2f(_progression_bar.getGlobalBounds().width, _progression_bar.getGlobalBounds().height);
        }

        /**
         * @brief Set the texture of the progression_bar
         * @param x The x position of the progression_bar (sf::Vector2f)
         * @param y The y position of the progression_bar (sf::Vector2f)
         */
        void move(float x, float y) {
            _progression_bar.move(x, y);
        }

        /**
         * @brief Get the progression_bar
         * @return The progression_bar (sf::progression_bar)
         */
        sf::Sprite &getprogression_bar() {
            return _progression_bar;
        }

    private:
        std::string _id;
        sf::Vector2f _pos;
        sf::Vector2f _scale;
        sf::Sprite _progression_bar;
        buffBonus _bonus;
        bool end_bar = false;

        sf::RenderWindow &_window;
};

#endif /* !progression_bar_HPP_ */