/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-bsrtype-marc.bieber
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "EntityManager.hpp"

/**
 * @brief Class containing all the systems of the game
 */
class System {
    public:
        System();
        System(sf::RenderWindow &window):  _window(window){
            _running = true;
            _instance = this;
        };
        ~System();
        void init();
        void draw();
        void update();

        EntityManager &getManager() {
            return *_manager;
        }

        inline System &getInstance() {
            return *_instance;
        }

        inline bool isRunning() const { return _running; }
    protected:
    private:
        System *_instance;
        bool _running;
        EntityManager *_manager;
        sf::RenderWindow &_window;
};

#endif /* !SYSTEM_HPP_ */
