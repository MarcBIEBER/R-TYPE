#ifndef ENNEMY_HPP_
#define ENNEMY_HPP_

#include "../../AssetManager/AssetManager.hpp"

class Ennemy : public IComponent {
    public:
        Entity *entity;
        Ennemy();
        virtual ~Ennemy() = default;
        /**
         * @brief Init the ennemy
         * @param id The id of the ennemy
         * @param window The window of the game
         */
        Ennemy(std::string id, sf::RenderWindow &window) : _id(id), _window(window){}

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            _sprite = AssetManager::getInstance().getSprite(_id);
            for (int i = 0; i < this->nb_enemy; i++) {
                _clock.push_back(sf::Clock());
            }
            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            for (sf::Sprite &spr: _ennemys) {
                _window.draw(spr);
            }
            for (sf::Sprite &bullet : _bullets) {
                _window.draw(bullet);
            }
        }

        /**
         * @brief Update the sprite
         */
        void update() override {
            for (sf::Sprite &bullet : _bullets) {
                bullet.move(7, 0);
            }
        }

        /**
         * @brief Create the ennemy
         * @param nbEnnemy The number of ennemy to create
         */
        int createEnnemy(int nbEnnemy, std::string spriteId, bool special_enemy, int speed_enemy) {
            sf::Sprite sprite = AssetManager::getInstance().getSprite(spriteId);
            int difficulty = 5;
            for (int i = 0; i < nbEnnemy; i++) {
                if (special_enemy == false) {
                    sprite.setPosition(0 - (rand() %  500), rand() % 1080);
                } else {
                    sprite.setPosition(rand() % 1700, 1080 + (rand() % 500));
                }
                _ennemys.push_back(sprite);
            }
            if (speed_enemy == 1)
                difficulty = 5;
            else if (speed_enemy == 2)
                difficulty = 10;
            else if (speed_enemy == 3)
                difficulty = 15;
            return difficulty;
        }

        /**
         * @brief Create boss
         * @param spriteId The id of the sprite
         */
        void createBoss(std::string spriteId) {
            sf::Sprite sprite = AssetManager::getInstance().getSprite(spriteId);
            sprite.setPosition(2250, 400);
            _ennemys.push_back(sprite);
        }

        /**
         * @brief Create little monster
         * @param spriteId The id of the sprite
         * @param x position x
         * @param y position y
         */
        void createSbire(std::string spriteId, int x, int y) {
            sf::Sprite sprite = AssetManager::getInstance().getSprite(spriteId);
            sprite.setPosition(x, y);
            _ennemys.push_back(sprite);
        }
        /**
         * @brief Move the ennemy
         * @param x The next x position of the ennemy
         * @param y The next y position of the ennemy
         */
        void move(float x, float y) {
            for (sf::Sprite &spr: _ennemys) {
                spr.move(x, y);
            }
        }

        /**
         * @brief animate the ennemy
         * @param id The id of the sprite
         * @param rect The rect of the sprite
         * @param max_value The max value of the rect
         * @param offset The offset of the rect
         * @param speed The speed of the animation
         */
        void spriteAnimation(std::string id, int nbr_clock, sf::IntRect *rect, float max_value, float offset, int speed) {
            sf::Sprite my_sprite = AssetManager::getInstance().getSprite(id);
            // if (id =="bullet3")
            //     std::cout << "okkk"<< std::endl;
            if (_clock[nbr_clock].getElapsedTime().asMicroseconds() > speed) {
                for (sf::Sprite &spr: _ennemys) {
                    // if (nbr_clock == 3) {
                    //     std::cout << "bullets 3 rect : " << rect->left << std::endl;
                    // }
                    if (rect->left >= max_value)
                        rect->left = 0;
                    else
                        rect->left += offset;
                    spr.setTextureRect(*rect);
                }
                _clock[nbr_clock].restart();
            }
        }

        /**
         * @brief boost the little ennemy 
         * @param id The id of the sprite
         * @param rect The rect of the sprite
         * @param max The max value of the rect
         */
        void sbireBoost(std::string id, sf::IntRect *rect, float max) {
            sf::Sprite my_sprite = AssetManager::getInstance().getSprite(id);
            // std::cout << "okkk"<< std::endl;
            for (sf::Sprite &spr: _ennemys) {
                rect->left = max;
                spr.setTextureRect(*rect);
            }
        }

        /**
         * @brief animate the bullet
         * @param id The id of the sprite
         * @param rect The rect of the sprite
         * @param max_value The max value of the rect
         * @param offset The offset of the rect
         * @param speed The speed of the animation
         */
        void bulletAnimation(std::string id, int nbr_clock, sf::IntRect *rect, float max_value, float offset, int speed) {
            sf::Sprite my_sprite = AssetManager::getInstance().getSprite(id);
            if (_clock[nbr_clock].getElapsedTime().asMicroseconds() > speed) {
                for (sf::Sprite &spr: _ennemys) {
                    //std::cout << (float)rect->left << std::endl;
                    if (rect->left >= max_value - offset)
                        rect->left = 0;
                    else
                        rect->left += offset;
                    spr.setTextureRect(*rect);
                }
            }
        }

        /**
         * @brief Create the bullet who was shoot by the ennemy
         * @param id The id of the sprite
         * @param gap The gap between the ennemy and the bullet
         */
        void createBullet(std::string id, float gap) {
            sf::Sprite bullet = AssetManager::getInstance().getSprite(id);
            for (sf::Sprite &spr: _ennemys) {
                bullet.setPosition(spr.getPosition().x + 110, spr.getPosition().y + gap);
                _bullets.push_back(bullet);
            }
        }

        /**
         * @brief Set the scale of the sprite
         * @param x The x scale of the sprite (sf::Vector2f)
         * @param y The y scale of the sprite (sf::Vector2f)
         */
        void setScale(float x, float y) {
            for (sf::Sprite &spr: _ennemys) {
                spr.setScale(sf::Vector2f(x, y));
            }
        }

        /**
         * @brief Set position of the ennemy
         * @param x The new x position of the ennemy
         * @param y The new y position of the ennemy
         */
        void setPosition(float x, float y) {
            for (sf::Sprite &spr: _ennemys) {
                spr.setPosition(x, y);
            }
        }

        /**
         * @brief Get the position of the ennemy
         * @return The position of all the ennemy
         */
        std::vector<sf::Vector2f> getPosition() {
            std::vector<sf::Vector2f> pos;
            for (sf::Sprite &spr: _ennemys) {
                pos.push_back(spr.getPosition());
            }
            return pos;
        }
        sf::Vector2f getPosition_one() {
            return _sprite.getPosition();
        }
        /**
         * @brief Get the bullets
         * @return The bullets (std::vector<sf::Sprite>)
         */
        std::vector<sf::Sprite> &getBullets() {
            return _bullets;
        }
        /**
         * @brief Get the sprite of the ennemy
         * @return The sprite of all the ennemy
         */
        std::vector<sf::Sprite> &getSprite() {
            return _ennemys;
        }

        void clear_spr(sf::Sprite spr) {
            // spr.
        }
    private:
        std::string _id;
        std::vector<sf::Sprite> _ennemys;
        std::vector<int> _life;
        sf::RenderWindow &_window;
        sf::Sprite _sprite;
        static constexpr int nFrames = 4;
        static constexpr float holdTime = 0.1f;
        sf::IntRect frames[nFrames];
        int iFrame = 0;
        float time;
        int nb_enemy = 3;
        std::vector<sf::Clock> _clock;
        std::vector<sf::Sprite> _bullets;
        int speed;
};

#endif /* !ENNEMY_HPP_ */