/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** SemiBoss
*/

#ifndef SEMIBOSS_HPP_
#define SEMIBOSS_HPP_

#include "../../AssetManager/AssetManager.hpp"
#include <random>

#define MINI_BOSS_LIFE_POINTS   100
#define RECTANGLE_SIZE          300
#define RECTANGLE_SIZE_Y        20

class SemiBoss : public IComponent {
    public:
        Entity *entity;
        SemiBoss();
        virtual ~SemiBoss() = default;
        /**
         * @brief Init the SemiBoss
         * @param id The id of the SemiBoss
         * @param window The window of the game
         */
        SemiBoss(std::string id, sf::RenderWindow &window) : _id(id), _window(window){
        }

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            _sprite = AssetManager::getInstance().getSprite(_id);
            _life = MINI_BOSS_LIFE_POINTS;
            greenRectangle.setSize(sf::Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE_Y));
            greenRectangle.setFillColor(sf::Color::Green);

            redRectangle.setSize(sf::Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE_Y));
            redRectangle.setFillColor(sf::Color::Red);
            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            if (_isDrawable) {
                _window.draw(_sprite);
                for (sf::CircleShape &circle : _Circles) {
                    _window.draw(circle);
                }
                for (sf::CircleShape &circle : _RealCircles) {
                    _window.draw(circle);
                }
                _window.draw(redRectangle);
                _window.draw(greenRectangle);
            }
        }

        void deleteCircle() {
            int i = 0;
            for (sf::CircleShape &circle : _Circles) {
                if (circle.getPosition().x < 0 || circle.getPosition().x > 1920 || circle.getPosition().y < 0 || circle.getPosition().y > 1080) {
                    _Circles.erase(_Circles.begin() + i);
                    _moveValuesCircles.erase(_moveValuesCircles.begin() + i);
                    break;
                }
                i++;
            }
            i = 0;
            for (sf::CircleShape &circle : _RealCircles) {
                if (circle.getPosition().x < 0 || circle.getPosition().x > 1920 || circle.getPosition().y < 0 || circle.getPosition().y > 1080) {
                    _RealCircles.erase(_RealCircles.begin() + i);
                    _moveRealValuesCircles.erase(_moveRealValuesCircles.begin() + i);
                    break;
                }
                i++;
            }
        }

        /**
         * @brief Update the sprite
         */
        void update() override {
            if (!_isDrawable)
                return;
            rotateSprite();
            int i = 0;
            if (_clockCircles.getElapsedTime().asSeconds() > 0.4) {
                _clockCircles.restart();
                for (int j = 0; j != 10; j++) {
                    sf::CircleShape circle;
                    circle.setPosition(_sprite.getPosition().x - 100, _sprite.getPosition().y);
                    circle.setRadius(10);
                    circle.setFillColor(getRandomColorWithAlpha());
                    _Circles.push_back(circle);
                    _moveValuesCircles.push_back(sf::Vector2f(getRandomValue(-30, -20), getRandomValue(-30, 30)));
                }
            }
            for (sf::CircleShape &circle : _Circles) {
                circle.move(_moveValuesCircles.at(i));
                i += 1;
            }
            i = 0;
            for (sf::CircleShape &circle : _RealCircles) {
                circle.move(_moveRealValuesCircles.at(i));
                i += 1;
            }
            deleteCircle();
            greenRectangle.setPosition(_sprite.getPosition().x - 120, _sprite.getPosition().y - 300);
            redRectangle.setPosition(_sprite.getPosition().x - 120, _sprite.getPosition().y - 300);
        }

        void createRealCircles(int moveX, int moveY)
        {
            int i = 0;
            sf::CircleShape bigCircle;
            bigCircle.setPosition(_sprite.getPosition().x - 100, _sprite.getPosition().y);
            bigCircle.setRadius(30);
            bigCircle.setFillColor(getRandomColor());
            _RealCircles.push_back(bigCircle);
            _moveRealValuesCircles.push_back(sf::Vector2f(moveX, moveY));
        }

        /**
         * @brief Set the scale of the sprite
         * @param x The x scale of the sprite (sf::Vector2f)
         * @param y The y scale of the sprite (sf::Vector2f)
         */
        void setScale(float x, float y) {
            _sprite.setScale(x, y);
        }

        /**
         * @brief Set position of the SemiBoss
         * @param x The new x position of the SemiBoss
         * @param y The new y position of the SemiBoss
         */
        void setPosition(float x, float y) {
            _sprite.setPosition(x, y);
        }

        /**
         * @brief Get the position of the SemiBoss
         * @return The position of all the SemiBoss
         */
        sf::Vector2f getPosition() {
            return _sprite.getPosition();
        }
        /**
         * @brief Get the sprite of the SemiBoss
         * @return The sprite of all the SemiBoss
         */
        sf::Sprite &getSprite() {
            return _sprite;
        }

        void clear_spr(sf::Sprite spr) {
            // spr.
        }

        /**
         * @brief Set the drawable state of the SemiBoss
         * @param isDrawable The new drawable state of the SemiBoss
         */
        void setDrawable(bool isDrawable) {
            _isDrawable = isDrawable;
        }

        /**
         * @brief Get the drawable state of the SemiBoss
         * @return The drawable state of the SemiBoss
         */
        bool getDrawable() {
            return _isDrawable;
        }

        /**
         * @brief Remove one life to the SemiBoss
         * @param lifePoints the number of life points to remove
         */
        int removeLifePoints(int lifePoints) {
            _life -= lifePoints;
            greenRectangle.setSize(sf::Vector2f(_life * 3 / _stage, RECTANGLE_SIZE_Y));
            if (_life <= 0) {
                _life = 0;
                _isDrawable = false;
                return 0;
            }
            return _life;
        }

        /**
         * @brief Set the life of the SemiBoss
         * @param lifePoints the number of life points to set
         */
        void setLifePoints(int lifePoints) {
            _life = lifePoints;
            greenRectangle.setSize(sf::Vector2f(_life * 3 / _stage, RECTANGLE_SIZE_Y));
        }

        // Rotate sprite:
        void rotateSprite() {
            _angle += 1;
            if (_angle > 360) {
                _angle = 0;
            }
            _sprite.setRotation(_angle);
            _sprite.rotate(_angle);
        }

        /**
         * @brief get all the bullets of the SemiBoss
         * @return The bullets of the SemiBoss (vector<Sprite>)
         */
        std::vector<sf::CircleShape> &getCircles() { return _RealCircles; }

        inline int getRandomValue(int min, int max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(min, max);
            return dis(gen);
        }

        sf::Color getRandomColor() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 255);
            return sf::Color(dis(gen), dis(gen), dis(gen));
        }

        sf::Color getRandomColorWithAlpha() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 255);
            return sf::Color(dis(gen), dis(gen), dis(gen), 100);
        }

        /**
         * @brief Update the stage
         */
        void setStage(int stage) {
            _stage = stage;
        }

        /**
         * @brief Get the stage
         * @return The stage
         */

        int getStage() {
            return _stage;
        }

    private:
        std::string _id;
        int _life = 300;
        int _angle = 0;
        sf::RenderWindow &_window;
        sf::Sprite _sprite;
        bool _isDrawable = false;
        sf::Text _text;
        sf::Font _font;
        int _stage = 1;

        sf::Clock _clockRotation;
        sf::Clock _clockCircles;

        std::vector<sf::Vector2f> _moveValuesCircles;
        std::vector<sf::Vector2f> _moveRealValuesCircles;
        std::vector<sf::CircleShape> _Circles;
        std::vector<sf::CircleShape> _RealCircles;

        sf::RectangleShape greenRectangle;
        sf::RectangleShape redRectangle;
};

#endif /* !SEMIBOSS_HPP_ */
