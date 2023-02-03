#include "GamePlay.hpp"

sf::IntRect rect = sf::IntRect(0, 0, 110, 110);

void GamePlay::makePollEvent(System &system)
{
    sf::Event event;
    Player &player = system.getManager().getEntity("player").get()->getComponent<Player>();

    eventGameHandler(system);
    handleCollision(system);
    while (_window->getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->getWindow().close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _window->getWindow().close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            GET_SHOOT_SOUND.playSound();
        }
    }
    handleEvents(system);
    mousePos = sf::Mouse::getPosition(_window->getWindow());
    player.getSprite().setPosition(mousePos.x - 140, mousePos.y - 120);

}

void GamePlay::eventGameHandler(System &system)
{
    // animation sprite and random move
    Ennemy &enemy1 = system.getManager().getEntity("enemy1").get()->getComponent<Ennemy>();
    enemy1.spriteAnimation("enemy1", 0, &rect, 220, 110, 150000);
    for (sf::Sprite &spr: enemy1.getSprite()) {
        if (spr.getPosition().x <= 2100) {
            spr.move(5, 0);
        }
        else {
            spr.setPosition(-150, 0);
            removeOneLife(system);
        }
    }
    Ennemy &bullet = system.getManager().getEntity("bullet").get()->getComponent<Ennemy>();
    for (sf::Sprite &spr: bullet.getSprite()) {
        if (spr.getPosition().x >= 2100) {
            bullet.getSprite().erase(bullet.getSprite().begin());
        }
    }
    if (getLife() == 0)
        _window->getWindow().close();
}

/**
 * @brief Handle all events in game
 *
 * @param key Key pressed
 * @param window Window
 * @param system System
 */
void GamePlay::handleEvents(System &system)
{
    Ennemy &enemy = system.getManager().getEntity("enemy1").get()->getComponent<Ennemy>();
    Player &player = system.getManager().getEntity("player").get()->getComponent<Player>();
    sf::Event event;

		try {
            for (sf::Sprite &spr: enemy.getSprite()) {
                if (this->getCollision(player.getSprite(), spr) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    this->_kill++;
                    enemy.getSprite().erase(enemy.getSprite().begin());
                }
            }
            if (_timeShootEnemy.at(0).asMilliseconds() > 4500) {
                system.getManager().getEntity("enemy1").get()->getComponent<Ennemy>().createBullet("bullet", 30);
                _clockShootEnemy.at(0).restart();
            }
        }
		catch (std::exception &e) {
            std::cout << e.what() << std::endl;
		}
}