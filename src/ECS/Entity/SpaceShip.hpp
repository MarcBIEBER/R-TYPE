#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include "../../AssetManager/AssetManager.hpp"
#include <random>

#define MAX_LEFT 450
#define MAX_TOP 450
#define VALUE_TOP 150
#define VALUE_LEFT 150

#define S_RECTANGLE_SIZE          80
#define S_RECTANGLE_SIZE_Y        4

class SpaceShip : public IComponent {
    public:
        Entity *entity;
        SpaceShip();
        virtual ~SpaceShip() = default;
        /**
         * @brief Init the sprite
         * @param id The id of the sprite
         * @param pos The x and y position of the sprite (sf::Vector2f)
         * @param scale The scale of the sprite (sf::Vector2f)
         * @param window The window of the game
         */
        SpaceShip(std::string id, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow &window) : _id(id), _pos(pos), _scale(scale), _window(window) {
            _textureFlames.loadFromFile("assets/sprites/flamesRtype.png");
            _spriteFlames.setTexture(_textureFlames);
            _spriteFlames.setTextureRect(sf::IntRect(0, 0, VALUE_LEFT, VALUE_TOP));
            _spriteFlames.setScale(sf::Vector2f(0.5, 0.5));
            _spriteFlames.setPosition(sf::Vector2f(_pos.x + 17, _pos.y));
            _spriteFlames.setRotation(270);
            _font.loadFromFile("./assets/font/Aloevera-OVoWO.ttf");
            _textPlayerName.setFont(_font);
            _textPlayerName.setCharacterSize(30);
            _textPlayerName.setFillColor(sf::Color::White);
            _textPlayerName.setPosition(sf::Vector2f(_pos.x - 50, _pos.y + 65));
            _textPlayerName.setString(_playerName);
            setPlayerNameAtStart();
        }

        /**
         * @brief Init the sprite and fix it to the entity
         */
        bool init() override {
            _sprite = AssetManager::getInstance().getSprite(_id);
            greenRectangle.setSize(sf::Vector2f(S_RECTANGLE_SIZE, S_RECTANGLE_SIZE_Y));
            greenRectangle.setFillColor(sf::Color::Green);

            redRectangle.setSize(sf::Vector2f(S_RECTANGLE_SIZE, S_RECTANGLE_SIZE_Y));
            redRectangle.setFillColor(sf::Color::Red);
            return true;
        }

        /**
         * @brief Draw the sprite
         */
        void draw() override {
            if (_isActive) {
                _window.draw(_spriteFlames);
                _window.draw(_sprite);
                _window.draw(_textPlayerName);
                _window.draw(redRectangle);
                _window.draw(greenRectangle);
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
                bullet.move(10, 0);
            }
            if (_isActive) {
                _textPlayerName.setPosition(sf::Vector2f(_pos.x, _pos.y - 60));
                _timeFlames = _clockFlames.getElapsedTime();
                _pos = _sprite.getPosition();
                _spriteFlames.setPosition(sf::Vector2f(_pos.x - 50, _pos.y + 65));
                if (_timeFlames.asSeconds() > 0.1) {
                    _spriteFlames.setTextureRect(sf::IntRect(_spriteFlames.getTextureRect().left + VALUE_LEFT, _spriteFlames.getTextureRect().top, VALUE_LEFT, VALUE_TOP));
                    if (_spriteFlames.getTextureRect().left >= MAX_LEFT) {
                        _spriteFlames.setTextureRect(sf::IntRect(0, _spriteFlames.getTextureRect().top + VALUE_TOP, VALUE_LEFT, VALUE_TOP));
                    }
                    if (_spriteFlames.getTextureRect().top >= MAX_TOP) {
                        _spriteFlames.setTextureRect(sf::IntRect(0, 0, VALUE_LEFT, VALUE_TOP));
                    }
                    _clockFlames.restart();
                }
                greenRectangle.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - 10);
                redRectangle.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - 10);
            }
        }

        /**
         * @brief Use to create a bullet and push it in the vector
         */
        void createBullet() {
            sf::Sprite bullet = AssetManager::getInstance().getSprite("bullet");
            bullet.setPosition(_sprite.getPosition().x + 50, _sprite.getPosition().y + 5);
            _bullets.push_back(bullet);
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
         * @brief is the bonus speed active
         * @return true if the bonus is active
         */
        bool isBonusSpeedActive() {
            return _bonus_speed;
        }

        /**
         * @brief is the bonus speed active
         * @return true if the bonus is active
         */
        void setBonusSpeed(bool bonus_speed) {
            _bonus_speed = bonus_speed;
        }

        /**
         * @brief is the bonus power active
         * @return true if the bonus is active
         */
        bool isBonusPowerActive() {
            return _bonus_power;
        }

        /**
         * @brief is the bonus power active
         * @return true if the bonus is active
         */
        void setBonusPower(bool bonus_power) {
            _bonus_power = bonus_power;
        }

        int getSpeed() {
            return _speed;
        }

        void setSpeed(int speed) {
            _speed = speed * 25;
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

        /**
         * @brief Set the player id
         * @param int The player id
         */
        void setplayerId(int id) { _playerId = id; }

        /**
         * @brief Get the player id
         * @return The player id
         */
        int getplayerId() { return _playerId; }

        /**
         * @brief Set the active state of the sprite
         * @param bool The active state of the sprite
         */
        void setActive(bool active) { _isActive = active; }

        /**
         * @brief Get the active state of the sprite
         * @return bool The active state of the sprite
         */
        bool getActive() { return _isActive; }

        /**
         * @brief Remove one life to the SemiBoss
         * @param lifePoints the number of life points to remove
         */
        int removeLifePoints(int lifePoints) {
            _life -= lifePoints;
            greenRectangle.setSize(sf::Vector2f(_life * 4, S_RECTANGLE_SIZE_Y));
            if (_life <= 0) {
                _life = 0;
                // _isActive = false;
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
            greenRectangle.setSize(sf::Vector2f(_life * 4, S_RECTANGLE_SIZE_Y));
        }

        int getLifePoints() {
            return _life;
        }

        // Operator = :
        SpaceShip &operator=(const SpaceShip &other) {
            return *this;
        }

        void setPlayerName(std::string name) { _playerName = name; _textPlayerName.setString(_playerName); }
        std::string getPlayerName() { return _playerName; }

        void setPlayerNameAtStart() {
            int n = getRandonValue(0, _namesChoices.size() - 1);
            setPlayerName(_namesChoices[n]);
        }

        inline int getRandonValue(int min, int max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(min, max);
            return dis(gen);
        }
        
    private:
        std::string _id;
        sf::Vector2f _pos;
        sf::Vector2f _scale;
        int _life = 20;
        sf::Sprite _sprite;
        std::vector<sf::Sprite> _bullets;
        buffBonus _bonus;
        int _playerId;
        bool _isActive = false;
        bool _bonus_speed = false;
        bool _bonus_power = false;
        int _speed = 25;
        sf::Sprite _spriteFlames;
        sf::Texture _textureFlames;
        sf::Clock _clockFlames;
        sf::Time _timeFlames;
        std::string _playerName = "";
        sf::Text _textPlayerName;
        sf::Font _font;
        std::vector<std::string> _namesChoices = {"Billy", "Bob", "Napoléon", "John-Cena", "EpiDuck", "LeChevalier", "Bantz'", "Clemikoun", "TheRock", "Unaimabit", "Pastore", "SukaSuka", "Gertrude", "Asterix", "Obelix", "Idéfix", "Cleopathre", "Belinda", "Falbala", "Benoit", "Graindemais", "Panoramix", "Assureancetourix", "Abraracourcix", "Titanix", "Abdelmalix", "Barberouge", "Radius", "Perfidus", "Malotrux", "Cesar", "PatesAlaSauceTomate", "FortinePlayer", "LaChancla", "Issou"};

        sf::RectangleShape greenRectangle;
        sf::RectangleShape redRectangle;

        sf::RenderWindow &_window;
};

#endif /* !SPACESHIP_HPP_ */