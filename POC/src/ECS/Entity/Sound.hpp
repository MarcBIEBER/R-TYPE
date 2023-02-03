/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** Text
*/

#ifndef Sound_HPP_
#define Sound_HPP_

#include "../../AssetManager/AssetManager.hpp"

class Sound : public IComponent {
    public:
        Entity *entity;
        Sound();
        /**
         * @brief Construct a new Sound:: Sound object
         * @param id The id of the entity
         */
        Sound(std::string id) : _id(id) {};
        ~Sound() = default;

        /**
         * @brief Init the sound from buffer
         */
        bool init() override {
            _buffer = AssetManager::getInstance().getSound(_id);
            _sound.setBuffer(_buffer);
            return true;
        }

        sf::Sound &getSound() { return _sound; };

        /**
         * @brief Play the sound
         */
        void draw() override {
        }

        /**
         * @brief Update
         */
        void update() override {

        }

        void setPosition(sf::Vector2f pos) {
            _sound.setPosition(pos.x, pos.y, 0);
        }

        /**
         * @brief Play the sound
         */
        void playSound() {
            _sound.play();
        }

    protected:
    private:
        std::string _id;
        sf::SoundBuffer _buffer;
        sf::Sound _sound;

};

#endif /* !LIFE_HPP_ */