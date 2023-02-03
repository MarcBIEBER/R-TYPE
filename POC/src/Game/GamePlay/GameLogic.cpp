#include "GamePlay.hpp"

/**
 * @brief Part of the game loop that contains game
 * 
 * @param g graphics object
 * @param game game object
 * @param system System object
 */
void GamePlay::handleGame(System &system)
{
    _timeGame = _clockGame.getElapsedTime();
    _timeDuration = _clockDuration.getElapsedTime();
    _timeShoot = _clockShoot.getElapsedTime();
    if (_kill >= 8 && spawnEnemy > 0) {
        spawnEnemy -= 1;
        _kill = 0;
        if (speed_level <= 3)
            speed_level += 1;
    }
    for (int i = 0; i < nb_enemy; i++) {
        _timeDurationEnemy[i] = _clockDurationEnemy[i].getElapsedTime();
        _timeShootEnemy[i] = _clockShootEnemy[i].getElapsedTime();
    }
    if (_timeDurationEnemy[0].asSeconds() >= spawnEnemy) {
        speed = system.getManager().getEntity("enemy1").get()->getComponent<Ennemy>().createEnnemy(1, "enemy1", false, speed_level);
        _clockDurationEnemy[0].restart();
    }
}

/**
 * @brief use to handle the collision between every sprite of the game
 *
 * @param game &game
 * @param graphics graphics
 * @param System System
 */

void GamePlay::handleCollision(System &system)
{
    Ennemy &enemy1 = system.getManager().getEntity("enemy1").get()->getComponent<Ennemy>();

    for (sf::Sprite &spr: enemy1.getBullets()) {
        if (getCollision(spr, system.getManager().getEntity("player").get()->getComponent<Player>().getSprite())) {
            spr.setPosition(2100, 2100);
            enemy1.getBullets().erase(enemy1.getBullets().begin());
            removeOneLife(system);
        }
    }
}

