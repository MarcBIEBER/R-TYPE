/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** FinalBoss
*/

#ifndef FINALBOSS_HPP_
#define FINALBOSS_HPP_

#include "../../AssetManager/AssetManager.hpp"
#include <random>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define BOSS_LIFE_POINTS_S1     100
#define BOSS_LIFE_POINTS_S2     200
#define BOSS_LIFE_POINTS_S3     300
#define BOSS_LIFE_POINTS_S4     400
#define BOSS_LIFE_POINTS_S5     500
#define RECTANGLE_SIZE          300
#define RECTANGLE_SIZE_Y        20
#define MOVE_VIEW_VALUE         3.2
#define ZOOM_SPEED              0.005
#define MOVE_EVERYTHING_SPEED   2.5
#define X_START                 1920
#define ROTATE_V                5
#define BULLETS_SPEED           10

class FinalBoss : public IComponent {
    public:
        Entity *entity;
        FinalBoss();
        virtual ~FinalBoss() = default;
        /**
         * @brief Init the FinalBoss
         * @param id The id of the FinalBoss
         * @param window The window of the game
         */
        FinalBoss(std::string id, sf::RenderWindow &window) : _id(id), _window(window){
        }

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            _sprite = AssetManager::getInstance().getSprite(_id);
            _clockWarning.restart();
            _clockZoom.restart();
            _clockRotation.restart();
            _isDrawable = false;
            _window.setView(_window.getDefaultView());
            zoomValue = 1.0;
            moveCounter = 0;
            rotateCounter = 0;
            _sprite.setPosition(X_START, 380);
            _text.setCharacterSize(80);
            _text.setFillColor(sf::Color::Red);
            _text.setPosition(700, 150);
            _font.loadFromFile("./assets/font/arial.ttf");
            _text.setFont(_font);
            _text.setString("! WARNING !");
            _clockHit.restart();

            if (_stage == 1)
                _life = BOSS_LIFE_POINTS_S1;
            else if (_stage == 2)
                _life = BOSS_LIFE_POINTS_S2;
            else if (_stage == 3)
                _life = BOSS_LIFE_POINTS_S3;
            else if (_stage == 4) {
                _life = BOSS_LIFE_POINTS_S4;
                _sprite.setScale(0.6, 0.6);
            }
            else if (_stage == 5) {
                _sprite.setColor(sf::Color::Red);
                _life = BOSS_LIFE_POINTS_S5;
                _sprite.setScale(0.5, 0.5);
            }

            _textLifePoints.setCharacterSize(20);
            _textLifePoints.setFillColor(sf::Color::White);
            _textLifePoints.setPosition(X_START, 220);
            _textLifePoints.setFont(_font);
            _textLifePoints.setString("Life points: " + std::to_string(_life));

            greenRectangle.setSize(sf::Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE_Y));
            greenRectangle.setFillColor(sf::Color::Green);
            greenRectangle.setPosition(X_START + 40, RECTANGLE_SIZE);

            redRectangle.setSize(sf::Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE_Y));
            redRectangle.setFillColor(sf::Color::Red);
            redRectangle.setPosition(X_START + 40, RECTANGLE_SIZE);

            _view = _window.getDefaultView();


            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            if (_life <= 0)
                return;
            if (_isDrawable) {
                _window.draw(_sprite);
                _window.draw(redRectangle);
                _window.draw(greenRectangle);
                for (sf::Sprite &bullet : _bossBullets) {
                    _window.draw(bullet);
                }
            }
            if (_isTextDrawable && _isDrawable)
                _window.draw(_text);
        }

        /**
         * @brief Update the sprite
         */
        void update() override {
            if (!_isDrawable) {
                _window.setView(_window.getDefaultView());
                return;
            }
            _timeWarning = _clockWarning.getElapsedTime();
            _timeZoom = _clockZoom.getElapsedTime();
            _timeRotation = _clockRotation.getElapsedTime();
            if (_isDrawable && _sprite.getPosition().x > 1420 && _timeZoom.asSeconds() >= 2.0) {
                _sprite.move(-MOVE_EVERYTHING_SPEED, 0);
                greenRectangle.move(-MOVE_EVERYTHING_SPEED, 0);
                redRectangle.move(-MOVE_EVERYTHING_SPEED, 0);
                _view.zoom(1 - ZOOM_SPEED);
                moveCounter += MOVE_VIEW_VALUE;
                _view.move(MOVE_VIEW_VALUE, 0);
                zoomValue -= ZOOM_SPEED;
                _window.setView(_view);
            } else {
                if (_timeZoom.asSeconds() >= 4.0 && zoomValue < 1.0) {
                    _clockHit.restart();
                    zoomValue += ZOOM_SPEED;
                    _view.zoom(1 + ZOOM_SPEED);
                    moveCounter -= MOVE_VIEW_VALUE;
                    _view.move(-MOVE_VIEW_VALUE, 0);
                    _window.setView(_view);
                    _isTextDrawable = false;
                }
            }
            if (_timeWarning.asSeconds() > 0.1 && _isDrawable && _sprite.getPosition().x > 1420) {
                _isTextDrawable = !_isTextDrawable;
                _clockWarning.restart();
            }
            if (_timeRotation.asSeconds() >= 2.5 && _timeRotation.asSeconds() <= 4.0) {
                _clockHit.restart();
                rotateInCircle();
            } else {
                rotateOutCircle();
            }
            for (int i = 0; i < _bossBullets.size(); i++) {
                _bossBullets[i].move(- _moveValuesBullets.at(i).x, _moveValuesBullets.at(i).y);
            }
            updateMoveValue();
        }

        /**
         * @brief Rotate the view in a circle
         */
        void rotateInCircle() {
            _view.rotate(ROTATE_V);
            _window.setView(_view);
            rotateCounter += ROTATE_V;
        }

        /**
         * @brief Rotate the view in the opposite direction
         */
        void rotateOutCircle() {
            if (rotateCounter <= 0) {
                return;
            }
            rotateCounter -= ROTATE_V;
            _window.setView(_view);
            _view.rotate(-ROTATE_V);
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


        /**
         * @brief Set the scale of the sprite
         * @param x The x scale of the sprite (sf::Vector2f)
         * @param y The y scale of the sprite (sf::Vector2f)
         */
        void setScale(float x, float y) {
            _sprite.setScale(x, y);
        }

        /**
         * @brief Set position of the FinalBoss
         * @param x The new x position of the FinalBoss
         * @param y The new y position of the FinalBoss
         */
        void setPosition(float x, float y) {
            _sprite.setPosition(x, y);
        }

        /**
         * @brief Get the position of the FinalBoss
         * @return The position of all the FinalBoss
         */
        sf::Vector2f getPosition() {
            return _sprite.getPosition();
        }
        /**
         * @brief Get the sprite of the FinalBoss
         * @return The sprite of all the FinalBoss
         */
        sf::Sprite &getSprite() {
            return _sprite;
        }

        /**
         * @brief set green rectangle position
         * 
         */
        void setGreenRectanglePosition(float x, float y) {
            greenRectangle.setPosition(x, y);
        }

        /**
         * @brief set red rectangle position
         *
         */
        void setRedRectanglePosition(float x, float y) {
            redRectangle.setPosition(x, y);
        }

        void clear_spr(sf::Sprite spr) {
            // spr.
        }

        /**
         * @brief Set the drawable state of the FinalBoss
         * @param isDrawable The new drawable state of the FinalBoss
         */
        void setDrawable(bool isDrawable) {
            _isDrawable = isDrawable;
        }

        /**
         * @brief Get the drawable state of the FinalBoss
         * @return The drawable state of the FinalBoss
         */
        bool getDrawable() {
            return _isDrawable;
        }

        /**
         * @brief Remove one life to the FinalBoss
         * @param lifePoints the number of life points to remove
         */
        int removeLifePoints(int lifePoints) {
            if (_clockHit.getElapsedTime().asSeconds() >= 0.5 && _sprite.getPosition().x <= 1420) {
                _life -= lifePoints;
                setPositionAndSizeOfRectangle();
            }
            return _life;
        }

        /**
         * @brief Set the life of the FinalBoss
         * @param lifePoints the number of life points to set
         */
        void setLifePoints(int lifePoints) {
            _life = lifePoints;
            setPositionAndSizeOfRectangle();
        }

        /**
         * @brief set the position and the size of the FinalBoss
         */
        void setPositionAndSizeOfRectangle()
        {
            if (_life <= 0) {
                _life = 0;
                _isDrawable = false;
                _isTextDrawable = false;
                _sprite.setPosition(-5000, -5000);
            }
            _textLifePoints.setString("Life points: " + std::to_string(_life));
            greenRectangle.setSize(sf::Vector2f(_life * 3 / _stage, RECTANGLE_SIZE_Y));
        }

        /**
         * @brief Create a bullet
         */
        void addBullet() {
            int angle = getBulletAngle(-70, 70) + 180;
            addBulletSpecial(angle);
        }

        /**
         * @brief Create an special bullet for the FinalBoss
         * @param angle The angle of the bullet
         * @param x The x position of the bullet
         * @param y The y position of the bullet
         */
        void addBulletSpecial(int angle) {
            int x = _sprite.getPosition().x;
            int y = _sprite.getPosition().y + 200;
            sf::Sprite bullet = AssetManager::getInstance().getSprite("bossBullet");
            bullet.setPosition(x, y);
            bullet.setRotation(angle);
            bullet.setScale(0.1, 0.1);
            setBulletsMove(angle);
            _bossBullets.push_back(bullet);
        }

        /**
         * @brief Set the angle value of the bullet randomly
         * @param min The minimum value of the angle
         * @param max The maximum value of the angle
         */
        inline int getBulletAngle(int min, int max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(min, max);
            return dis(gen);
        }
        
        /**
         * @brief Set the move value of the bullet
         * @param angle The angle of the bullet
         */
        void setBulletsMove(int rotation)
        {
            int x = cos(rotation * M_PI / 180) * BULLETS_SPEED;
            int y = sin(rotation * M_PI / 180) * BULLETS_SPEED;
            _moveValuesBullets.push_back(sf::Vector2f(- x, y));
        }

        /**
         * @brief Update the move value of the bullet
         */
        void updateMoveValue() {
            int posY;
            int rotation;
            int x;
            int y;
            for (int i = 0; i < _bossBullets.size(); i++) {
                posY = _bossBullets.at(i).getPosition().y;
                // BAS:
                if (posY >= 1060) {
                    x = cos((360 + _bossBullets.at(i).getRotation()) * M_PI / 180) * BULLETS_SPEED;
                    y = sin((360 + _bossBullets.at(i).getRotation()) * M_PI / 180) * BULLETS_SPEED;
                    rotation = (_bossBullets.at(i).getRotation() - 360) * (-1);
                    _bossBullets.at(i).setRotation(rotation);
                    _moveValuesBullets.at(i) = sf::Vector2f(-x, -y);
                }
                // HAUT:
                if (posY <= 20) {
                    x = cos((360 + _bossBullets.at(i).getRotation()) * M_PI / 180) * BULLETS_SPEED;
                    y = sin((360 + _bossBullets.at(i).getRotation()) * M_PI / 180) * BULLETS_SPEED;
                    rotation = 360 - _bossBullets.at(i).getRotation();
                    _bossBullets.at(i).setRotation(rotation);
                    _moveValuesBullets.at(i) = sf::Vector2f(-x, - y);
                }
            }
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
         * @brief get all the bullets of the FinalBoss
         * @return The bullets of the FinalBoss (vector<Sprite>)
         */
        std::vector<sf::Sprite> &getBullets() { return _bossBullets; }

    private:
        std::string _id;
        int _life;
        int _stage;
        sf::RenderWindow &_window;
        sf::Sprite _sprite;
        bool _isDrawable = true;
        bool _isTextDrawable = true;
        bool _playedMiddleSound = false;
        sf::Text _text;
        sf::Text _textLifePoints;
        sf::Font _font;

        sf::Clock _clockWarning;
        sf::Clock _clockZoom;
        sf::Clock _clockRotation;
        sf::Clock _clockHit;

        sf::Time _timeWarning;
        sf::Time _timeZoom;
        sf::Time _timeRotation;

        float zoomValue = 1.0;
        int moveCounter = 0;
        int rotateCounter = 0;

        sf::RectangleShape greenRectangle;
        sf::RectangleShape redRectangle;

        sf::View _view;

        std::vector<sf::Sprite> _bossBullets;
        std::vector<sf::Vector2f> _moveValuesBullets;
};

#endif /* !FINALBOSS_HPP_ */
