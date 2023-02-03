/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** GamePlay
*/

#ifndef GAMEPLAY_HPP_
#define GAMEPLAY_HPP_

#include "../Window.hpp"

#define SPEED 25
#define GET_SHOOT_SOUND _system->getManager().getEntity("shoot").get()->getComponent<Sound>()

enum Clocks {
    PLAYER_POSITION,
    FPS_CLOCK,
    BULLET_CLOCK,
    NB_CLOCKS
};

class GamePlay {
    public:
        GamePlay(Window &window);
        ~GamePlay();
        void loop();
        void init();
        System &getSystem() { return *_system; };
        void makePollEvent(System &system);
        void handleCollision(System &system);
        void movePlayers(std::string msg);
        void getPlayerInput(sf::Event event);
        bool getCollision(sf::Sprite &spriteOne, sf::Sprite &spriteTwo);
        void handleGame(System &system);
        void handleEvents(System &system);

        void eventGameHandler(System &system);
        void removeOneLife(System &system);
        void oneKill(System &system);
        int getLife();

        int nb_enemy;
        int random_number_stop;
        int min_number_stop;
        int max_number_stop;
        int _life;
        sf::Vector2i mousePos;
        int _kill;
        int spawnEnemy;
        int speed_level;
        int speed;

        sf::Clock _clockGame;
        sf::Time _timeGame;

        sf::Clock _clockDuration;
        sf::Time _timeDuration;
        std::vector<sf::Clock> _clockDurationEnemy;
        std::vector<sf::Time> _timeDurationEnemy;
        std::vector<sf::Clock> _clockDurationBonus;
        std::vector<sf::Time> _timeDurationBonus;

        sf::Clock _clockShoot;
        sf::Time _timeShoot;
        std::vector<sf::Clock> _clockShootEnemy;
        std::vector<sf::Time> _timeShootEnemy;
    protected:
    private:
        Window *_window;
        System *_system;
        std::vector<sf::Clock> _gamePlayClocks;
        std::vector<sf::Time> _gamePlayTime;
        int _kill_manage_bar;
        int min = -5;
        int rand_value = -3;
        int max = 4;
};

#endif /* !GAMEPLAY_HPP_ */
