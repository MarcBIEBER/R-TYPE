/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** GamePlay
*/

#include "GamePlay.hpp"
#define SECONDS_TO_SEND_POS 2

GamePlay::GamePlay(Window &window)
{
    this->_window = &window;
    _system = new System(_window->getWindow());
    _system->init();

    _clockGame = sf::Clock();
    _timeGame = sf::Time();
    _clockDuration = sf::Clock();
    _timeDuration = sf::Time();
    _clockShoot = sf::Clock();
    _timeShoot = sf::Time();
    this->spawnEnemy = 6;
    this->_life = 3;
    this->nb_enemy = 1;
    this->_kill = 0;
    this->_kill_manage_bar = 0;
    for (int i = 0; i < NB_CLOCKS; i++) {
        _gamePlayClocks.push_back(sf::Clock());
        _gamePlayTime.push_back(sf::Time());
    }
    for (int i = 0; i < this->nb_enemy; i++) {
        _clockDurationEnemy.push_back(sf::Clock());
        _timeDurationEnemy.push_back(sf::Time());
        _clockShootEnemy.push_back(sf::Clock());
        _timeShootEnemy.push_back(sf::Time());
    }
}

GamePlay::~GamePlay()
{
}

/**
 * @brief Loop of the gameplay
 */
void GamePlay::loop()
{
    makePollEvent(*this->_system);
    handleGame(*this->_system);
    _window->clearWindow();
    _window->update(*this->_system);
    _window->draw(*this->_system);
    _window->refreshWindow();
}

/**
 * @brief Init all the assets of the gameplay
 */
void initAsset()
{
    AssetManager::getInstance().loadSound("forest", "./assets/sound/Forest.ogg");
    AssetManager::getInstance().loadSound("shoot", "./assets/sound/shoot.ogg");
    // load all sprites here
    AssetManager::getInstance().loadTexture("player", "./assets/sprites/viewfinder.png");
    // AssetManager::getInstance().loadTexture("progression_bar", "./assets/sprites/progression_bar.png");
    AssetManager::getInstance().loadTexture("enemy1", "./assets/sprites/daffy.png");
    AssetManager::getInstance().loadTexture("bullet", "./assets/sprites/bullet.png");
    // AssetManager::getInstance().loadTexture("life_bar", "./assets/sprites/Life_bar.png");
	AssetManager::getInstance().loadTexture("para1", "./assets/sprites/forest.png");
    AssetManager::getInstance().loadSprite("player", "player");
    AssetManager::getInstance().loadSprite("para1", "para1");
    AssetManager::getInstance().loadSprite("bullet", "bullet");
    AssetManager::getInstance().loadAnimateSprite("enemy1", "enemy1", 0, 0, 110, 110);
    // AssetManager::getInstance().loadSprite("progression_bar", "progression_bar");
    // AssetManager::getInstance().loadAnimateSprite("progression_bar", "progression_bar", 0, 0, 412, 62);
    // AssetManager::getInstance().loadAnimateSprite("life_bar", "life_bar", 0, 895, 630, 179);
    AssetManager::getInstance().loadFont("font", "./assets/font/arial.ttf");
}

/**
 * @brief Init all entity of the gameplay
 */
void GamePlay::init()
{
    initAsset();

    EntityManager &_manager = _system->getManager();

    // create all entities here
    Entity *life = new Entity();
    Entity *player = new Entity();
    Entity *parallax1 = new Entity();
    Entity *enemy1 = new Entity();
    Entity *text = new Entity();
    Entity *progression_bar = new Entity();
    Entity *bullet = new Entity();
    Entity *back_sound = new Entity();
    Entity *shoot_sound = new Entity();

    // add all components here
    back_sound->addComponent<Sound>("forest");
    shoot_sound->addComponent<Sound>("shoot");
    life->addComponent<Life>("life", "Life: 3", _window->getWindow());
    player->addComponent<Player>("player", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    // text->addComponent<Text>("text", _window);
    // progression_bar->addComponent<ProgressionBar>("progression_bar",sf::Vector2f(500, 100), sf::Vector2f(1, 1), _window);
    enemy1->addComponent<Ennemy>("enemy1", _window->getWindow());
    parallax1->addComponent<Parallax>("para1", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    bullet->addComponent<Ennemy>("bullet", _window->getWindow());

    // Add Components from back plan to front plan (otherwise the back plan will be drawn over the front plan)
    _manager.addEntity("shoot", back_sound);
    _manager.addEntity("forest", back_sound);
    _manager.addEntity("parallax1", parallax1);
    _manager.addEntity("enemy1", enemy1);
    _manager.addEntity("player", player);
    _manager.addEntity("bullet", bullet);
    // _manager.addEntity("progression_bar", progression_bar);
    // _manager.addEntity("text", text);
    _manager.addEntity("life", life);

    // modify paramaters for the entities
    // _manager.getEntity("progression_bar").get()->getComponent<ProgressionBar>().setPosition(750, 0);
    // _manager.getEntity("life_bar").get()->getComponent<LifeBar>().setScale(0.2, 0.2);
    _manager.getEntity("enemy1").get()->getComponent<Ennemy>().createEnnemy(1, "enemy1", false, 1);
    // _manager.getEntity("life_bar").get()->getComponent<LifeBar>().setPosition(-500, 0);
    _manager.getEntity("life").get()->getComponent<Life>().setFont("font");
    _manager.getEntity("life").get()->getComponent<Life>().setFontSize(40);
    _manager.getEntity("life").get()->getComponent<Life>().setStyle(sf::Text::Regular);
    _manager.getEntity("life").get()->getComponent<Life>().setPosition(50, 890);
    _manager.getEntity("life").get()->getComponent<Life>().setText("Life : 3");

    // _manager.getEntity("text").get()->getComponent<Text>().setFont("font");
    // _manager.getEntity("text").get()->getComponent<Text>().setFontSize(100);
    // _manager.getEntity("text").get()->getComponent<Text>().setStyle(sf::Text::Regular);
    // _manager.getEntity("text").get()->getComponent<Text>().setPosition(400, 400);
    // _manager.getEntity("text").get()->getComponent<Text>().setText("BOSS");
}


/**
 * @brief Get the Collision object
 *
 * @param spriteOne Sprite one
 * @param spriteTwo Sprite two
 * @return true if collision
 * @return false if no collision
 */

bool GamePlay::getCollision(sf::Sprite &spriteOne, sf::Sprite &spriteTwo)
{
    sf::FloatRect spriteOneRect = spriteOne.getGlobalBounds();
    sf::FloatRect spriteTwoRect = spriteTwo.getGlobalBounds();
    if (spriteOneRect.intersects(spriteTwoRect)) {
        return true;
    }
    return false;
}

/**
 * @brief use to remove one life to the player
 *
 * @param system System
 */
void GamePlay::removeOneLife(System &system)
{
    this->_life -= 1;
    system.getManager().getEntity("life").get()->getComponent<Life>().setLife(_life);
}

void GamePlay::oneKill(System &system)
{
    this->_kill += 1;
    this->_kill_manage_bar += 1;
}

/**
 * @brief Get the Life of the player
 * 
 * @return int nb of life remaining
 */
int GamePlay::getLife()
{
    return this->_life;
}