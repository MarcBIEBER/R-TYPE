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
            float tmp = (pos.x / 100) - 10;
            if (tmp <= -5) {
                _sound.setPosition(-3.0f, 0, 0);
                return;
            }
            if (tmp <= -1) {
                _sound.setPosition(-1.5f, 0, 0);
                return;
            }
            if (tmp <= 3) {
                _sound.setPosition(0.0f, 0, 0);
                return;
            }
            if (tmp <= 5) {
                _sound.setPosition(1.5f, 0, 0);
                return;
            }
            _sound.setPosition(3.0f, 0, 0);
        }

        /**
         * @brief Play the sound
         */
        void playSound() {
            _sound.play();
        }

        /**
         * @brief Set the sound loop
         */
        void setLoopSound(bool loop) {
            _sound.setLoop(loop);
        }

    protected:
    private:
        std::string _id;
        sf::SoundBuffer _buffer;
        sf::Sound _sound;

};

#endif /* !LIFE_HPP_ */
