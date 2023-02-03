/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "../ECS/System.hpp"

class Window {
    public:
        Window();
        ~Window();

        sf::RenderWindow &getWindow() { return this->_window; };
        sceneEnum getScene() { return this->_scene; };

        void setGameScene(sceneEnum scene) { this->_scene = scene; };
        void clearWindow();
        void refreshWindow();
        void draw(System &system);
        void update(System &system);
        sf::Music *getMusic () { return &gameMusic; }
        sf::SoundBuffer *getSoundBuffer () { return &gameSoundBuffer; }
        sf::Sound *getSound () { return &gameSound; }

    protected:
    private:
        sf::RenderWindow _window;
        sceneEnum _scene;
        sf::Music gameMusic;
        sf::SoundBuffer gameSoundBuffer;
        sf::Sound gameSound;
};

#endif /* !WINDOW_HPP_ */
