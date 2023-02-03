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
        /**
         * @brief Construct a new Window object
         */
        Window();
        ~Window();

        /**
         * @brief Return the window
         * @return sf::RenderWindow current window
         */
        sf::RenderWindow &getWindow() { return this->_window; };
        System &getSystem() { return *system; };
        void clearWindow();
        void refreshWindow();
        void draw(System &system);
        void update(System &system);

    protected:
    private:
        sf::RenderWindow _window;
        System *system;
};

#endif /* !WINDOW_HPP_ */
