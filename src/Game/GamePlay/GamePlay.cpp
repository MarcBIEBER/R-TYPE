/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** GamePlay
*/

#include "GamePlay.hpp"
#define SECONDS_TO_SEND_POS 2.0
#define SECONDS_TO_SEND_PING_MESSAGE 2.0

/**
 * @brief Construct a new GamePlay::GamePlay object
 * 
 * @param client the current client of the game
 * @param window the current window of the game
 */
GamePlay::GamePlay(client &client, Window &window)
{
    this->_window = &window;
    _system = new System(_window->getWindow());
    _system->init();
    for (int i = 0; i < NB_CLOCKS; i++) {
        _gamePlayClocks.push_back(sf::Clock());
        _gamePlayTime.push_back(sf::Time());
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
    makePollEvent();
    tryConnectToServer();
    handleServerCommand();
    handleEnnemyMovement();
    getTimeFromClocks();
    sendSpecificCommandToServer();
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
    //Musics and sounds:
    AssetManager::getInstance().loadSound("shoot", "./assets/sound/shoot_bullet.ogg");
    AssetManager::getInstance().loadSound("shoothit", "./assets/sound/hurt.wav");
    AssetManager::getInstance().loadSound("youDontKnow", "./assets/sound/YouDontKnow.ogg");
    AssetManager::getInstance().loadSound("thePowerOf", "./assets/sound/thePowerOf.ogg");
    AssetManager::getInstance().loadSound("nooo", "./assets/sound/nooo.ogg");

    // Textures:
    AssetManager::getInstance().loadTexture("finalBoss", "./assets/sprites/spaceBoss.png");
    AssetManager::getInstance().loadTexture("console", "./assets/sprites/console_in_game.png");
    AssetManager::getInstance().loadTexture("player1", "./assets/sprites/starship.png");
    AssetManager::getInstance().loadTexture("player2", "./assets/sprites/starship2.png");
    AssetManager::getInstance().loadTexture("player3", "./assets/sprites/starship3.png");
    AssetManager::getInstance().loadTexture("player4", "./assets/sprites/starship4.png");
    AssetManager::getInstance().loadTexture("enemy0", "./assets/sprites/enemy0.png");
    AssetManager::getInstance().loadTexture("bullet", "./assets/sprites/sprite.png");
    AssetManager::getInstance().loadTexture("bullet2", "./assets/sprites/fire_ball.png");
    AssetManager::getInstance().loadTexture("bullet3", "./assets/sprites/missile.png");
    AssetManager::getInstance().loadTexture("progression_bar", "./assets/sprites/progression_bar.png");
    AssetManager::getInstance().loadTexture("boss1", "./assets/sprites/boss1.png");
    AssetManager::getInstance().loadTexture("bullet_boss", "./assets/sprites/shoot_boss.png");
    AssetManager::getInstance().loadTexture("bullet_bonus", "./assets/sprites/bullet_bonus.png");
    AssetManager::getInstance().loadTexture("para2", "./assets/sprites/parallax-space-big-planet.png");
    AssetManager::getInstance().loadTexture("para3", "./assets/sprites/parallax-space-far-planets.png");
    AssetManager::getInstance().loadTexture("para4", "./assets/sprites/parallax-space-ring-planet.png");
    AssetManager::getInstance().loadTexture("enemy1", "./assets/sprites/enemy1.png");
    AssetManager::getInstance().loadTexture("enemy2", "./assets/sprites/enemy2.png");
    AssetManager::getInstance().loadTexture("enemy3", "./assets/sprites/enemy3.png");
    AssetManager::getInstance().loadTexture("life_bar", "./assets/sprites/Life_bar.png");
	AssetManager::getInstance().loadTexture("para1", "./assets/sprites/parallax-space-backgound.png");
    AssetManager::getInstance().loadTexture("enemy4", "./assets/sprites/enemy_boss.png");
    AssetManager::getInstance().loadTexture("bullet_sbire", "./assets/sprites/bullet_sbire.png");
    AssetManager::getInstance().loadTexture("final_bullet_sbire", "./assets/sprites/final_bullet_sbire.png");
    AssetManager::getInstance().loadTexture("hearth_bonus", "./assets/sprites/bonus_hearth.png");
    AssetManager::getInstance().loadTexture("bonus_speed", "./assets/sprites/bonus_speed.png");
    AssetManager::getInstance().loadTexture("bonus_power", "./assets/sprites/bonus_power.png");
    AssetManager::getInstance().loadTexture("bossBullet", "./assets/sprites/boss_bullets.png");
    AssetManager::getInstance().loadTexture("waiting_server", "./assets/sprites/waiting_server.png");
    AssetManager::getInstance().loadTexture("miniBoss", "./assets/sprites/semi_boss.png");
    AssetManager::getInstance().loadTexture("lobbyBoard", "./assets/sprites/wooden_board.png");
    AssetManager::getInstance().loadTexture("bullet_bonus", "assets/sprites/bullet_bonus.png");

    AssetManager::getInstance().loadSprite("finalBoss", "finalBoss");
    AssetManager::getInstance().loadSprite("console", "console");
    AssetManager::getInstance().loadSprite("player1", "player1");
    AssetManager::getInstance().loadSprite("player2", "player2");
    AssetManager::getInstance().loadSprite("player3", "player3");
    AssetManager::getInstance().loadSprite("player4", "player4");
    AssetManager::getInstance().loadSprite("enemy0", "enemy0");
    AssetManager::getInstance().loadSprite("bullet", "bullet");
    AssetManager::getInstance().loadSprite("bullet2", "bullet2");
    AssetManager::getInstance().loadSprite("para2", "para2");
    AssetManager::getInstance().loadSprite("para3", "para3");
    AssetManager::getInstance().loadSprite("para4", "para4");
    AssetManager::getInstance().loadSprite("para1", "para1");
    AssetManager::getInstance().loadSprite("hearth_bonus", "hearth_bonus");
    AssetManager::getInstance().loadSprite("bonus_speed", "bonus_speed");
    AssetManager::getInstance().loadSprite("bonus_power", "bonus_power");
    AssetManager::getInstance().loadSprite("final_bullet_sbire", "final_bullet_sbire");
    AssetManager::getInstance().loadSprite("bullet_sbire", "bullet_sbire");
    AssetManager::getInstance().loadSprite("bossBullet", "bossBullet");
    AssetManager::getInstance().loadSprite("waiting_server", "waiting_server");
    AssetManager::getInstance().loadSprite("miniBoss", "miniBoss");
    AssetManager::getInstance().loadSprite("lobbyBoard", "lobbyBoard");
    AssetManager::getInstance().loadSprite("bullet_bonus", "bullet_bonus");

    AssetManager::getInstance().loadAnimateSprite("enemy1", "enemy1", 0, 0, 144, 100);
    AssetManager::getInstance().loadAnimateSprite("enemy2", "enemy2", 0, 0, 71, 56);
    AssetManager::getInstance().loadAnimateSprite("enemy3", "enemy3", 0, 0, 32, 35);
    AssetManager::getInstance().loadAnimateSprite("bullet3", "bullet3", 0, 0, 52, 56);
    AssetManager::getInstance().loadAnimateSprite("progression_bar", "progression_bar", 0, 0, 412, 62);
    AssetManager::getInstance().loadAnimateSprite("boss1", "boss1", 0, 0, 66, 134);
    AssetManager::getInstance().loadAnimateSprite("bullet_boss", "bullet_boss", 0, 0, 33, 36);
    AssetManager::getInstance().loadAnimateSprite("life_bar", "life_bar", 0, 895, 630, 179);
    AssetManager::getInstance().loadAnimateSprite("enemy4", "enemy4", 174, 0, 34, 40);

    AssetManager::getInstance().setSpriteRotation("bullet", 90);
    AssetManager::getInstance().setSpriteRotation("bossBullet", 180);

    AssetManager::getInstance().setSpriteScale("bullet", sf::Vector2f(0.1, 0.1));
    AssetManager::getInstance().setSpriteScale("bossBullet", sf::Vector2f(0.05, 0.05));
    
    AssetManager::getInstance().loadFont("font", "./assets/font/Aloevera-OVoWO.ttf");
}

/**
 * @brief Init all entity of the gameplay
 */
void GamePlay::init()
{
    initAsset();

    EntityManager &_manager = _system->getManager();

    // Sounds
    Entity *soundShoot = new Entity();
    Entity *soundHit = new Entity();
    Entity *youDontKnow = new Entity();
    Entity *thePowerOf = new Entity();
    Entity *nooo = new Entity();

    // Others
    Entity *life = new Entity();
    Entity *player1 = new Entity();
    Entity *player2 = new Entity();
    Entity *player3 = new Entity();
    Entity *player4 = new Entity();
    Entity *enemy0 = new Entity();
    Entity *parallax1 = new Entity();
    Entity *parallax2 = new Entity();
    Entity *parallax3 = new Entity();
    Entity *parallax4 = new Entity();
    Entity *enemy1 = new Entity();
    Entity *enemy2 = new Entity();
    Entity *enemy3 = new Entity();
    Entity *boss1 = new Entity();
    Entity *enemy4 = new Entity();
    Entity *bullet3 = new Entity();
    Entity *text = new Entity();
    Entity *progression_bar = new Entity();
    Entity *bullet_boss = new Entity();
    Entity *life_bar = new Entity();
    Entity *bullet_sbire = new Entity();
    Entity *final_bullet_sbire = new Entity();
    Entity *player_text = new Entity();
    Entity *fps_text = new Entity();
    Entity *console = new Entity();
    Entity *finalBoss = new Entity();
    Entity *bossBullet = new Entity();
    Entity *waiting_server = new Entity();
    Entity *text_waiting_server = new Entity();
    Entity *miniBoss = new Entity();
    Entity *lobbyBoard = new Entity();
    Entity *lobbyText = new Entity();
    Entity *hearth_bonus = new Entity();
    Entity *bonus_speed = new Entity();
    Entity *bonus_power = new Entity();
    Entity *bullet_bonus = new Entity();
    
    // add all components here
    soundShoot->addComponent<Sound>("shoot");
    soundHit->addComponent<Sound>("shoothit");
    youDontKnow->addComponent<Sound>("youDontKnow");
    thePowerOf->addComponent<Sound>("thePowerOf");
    nooo->addComponent<Sound>("nooo");

    life->addComponent<Life>("life", "Life: 3", _window->getWindow());
    player1->addComponent<SpaceShip>("player1", sf::Vector2f(100, 100), sf::Vector2f(0.3, 0.3), _window->getWindow());
    player2->addComponent<SpaceShip>("player2", sf::Vector2f(100, 100), sf::Vector2f(0.3, 0.3), _window->getWindow());
    player3->addComponent<SpaceShip>("player3", sf::Vector2f(100, 100), sf::Vector2f(0.3, 0.3), _window->getWindow());
    player4->addComponent<SpaceShip>("player4", sf::Vector2f(100, 100), sf::Vector2f(0.3, 0.3), _window->getWindow());
    text->addComponent<Text>("text","Boss",  _window->getWindow());
    progression_bar->addComponent<ProgressionBar>("progression_bar",sf::Vector2f(500, 100), sf::Vector2f(1, 1), _window->getWindow());
    enemy0->addComponent<Ennemy>("enemy0", _window->getWindow());
    enemy1->addComponent<Ennemy>("enemy1", _window->getWindow());
    enemy2->addComponent<Ennemy>("enemy2", _window->getWindow());
    enemy3->addComponent<Ennemy>("enemy3", _window->getWindow());
    bullet3->addComponent<Ennemy>("bullet3", _window->getWindow());
    life_bar->addComponent<LifeBar>("life_bar", sf::Vector2f(500, 0), sf::Vector2f(1, 1), _window->getWindow());
    boss1->addComponent<Ennemy>("boss1", _window->getWindow());
    bullet_boss->addComponent<Ennemy>("bullet_boss", _window->getWindow());
    enemy4->addComponent<Ennemy>("enemy4", _window->getWindow());
    bullet_sbire->addComponent<Ennemy>("bullet_sbire", _window->getWindow());
    final_bullet_sbire->addComponent<Ennemy>("final_bullet_sbire", _window->getWindow());
    parallax2->addComponent<Parallax>("para2", sf::Vector2f(1000, 400), sf::Vector2f(1, 1), _window->getWindow());
    parallax3->addComponent<Parallax>("para3", sf::Vector2f(150, 100), sf::Vector2f(1, 1), _window->getWindow());
    parallax4->addComponent<Parallax>("para4", sf::Vector2f(20, 250), sf::Vector2f(1, 1), _window->getWindow());
    parallax1->addComponent<Parallax>("para1", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    player_text->addComponent<Text>("player_text", "Player Undefined",  _window->getWindow());
    fps_text->addComponent<Text>("fps_text", "FPS: 0",  _window->getWindow());
    finalBoss->addComponent<FinalBoss>("finalBoss", _window->getWindow());
    bossBullet->addComponent<Ennemy>("bossBullet", _window->getWindow());
    waiting_server->addComponent<WaitingSprite>("waiting_server", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    console->addComponent<consoleInGame>("console", sf::Vector2f(0, 0), sf::Vector2f(0.5, 0.5),  _window->getWindow());
    text_waiting_server->addComponent<Text>("text_waiting_server", "Waiting for the server: ",  _window->getWindow());
    miniBoss->addComponent<SemiBoss>("miniBoss", _window->getWindow());
    lobbyBoard->addComponent<LobyBoard>("lobbyBoard", sf::Vector2f(1000, 0), sf::Vector2f(1, 1), _window->getWindow());
    lobbyText->addComponent<Text>("lobbyText", "Press 'SPACE' to start the lobby.\nYour are connected to the loby with the players: ",  _window->getWindow());
    hearth_bonus->addComponent<Sprite>("hearth_bonus", sf::Vector2f(-800, 0), sf::Vector2f(1, 1), _window->getWindow());
    bonus_speed->addComponent<Sprite>("bonus_speed", sf::Vector2f(-800, 0), sf::Vector2f(1, 1), _window->getWindow());
    bonus_power->addComponent<Sprite>("bonus_power", sf::Vector2f(-800, 0), sf::Vector2f(1, 1), _window->getWindow());
    bullet_bonus->addComponent<Ennemy>("bullet_bonus", _window->getWindow());


    // Add Components from back plan to front plan (otherwise the back plan will be drawn over the front plan)
    _manager.addEntity("shoot", soundShoot);
    _manager.addEntity("shoothit", soundHit);
    _manager.addEntity("youDontKnow", youDontKnow);
    _manager.addEntity("thePowerOf", thePowerOf);
    _manager.addEntity("nooo", nooo);

    _manager.addEntity("parallax1", parallax1);
    _manager.addEntity("parallax4", parallax4);
    _manager.addEntity("parallax3", parallax3);
    _manager.addEntity("parallax2", parallax2);
    _manager.addEntity("enemy0", enemy0);
    _manager.addEntity("bullet3", bullet3);
    _manager.addEntity("life_bar", life_bar);
    _manager.addEntity("enemy3", enemy3);
    _manager.addEntity("enemy2", enemy2);
    _manager.addEntity("enemy1", enemy1);
    _manager.addEntity("boss1", boss1);
    _manager.addEntity("bullet_boss", bullet_boss);
    _manager.addEntity("enemy4", enemy4);
    _manager.addEntity("bullet_sbire", bullet_sbire);
    _manager.addEntity("final_bullet_sbire", final_bullet_sbire);
    _manager.addEntity("player1", player1);
    _manager.addEntity("player2", player2);
    _manager.addEntity("player3", player3);
    _manager.addEntity("player4", player4);
    _manager.addEntity("progression_bar", progression_bar);
    _manager.addEntity("text", text);
    _manager.addEntity("player_text", player_text);
    _manager.addEntity("fps_text", fps_text);
    _manager.addEntity("life", life);
    _manager.addEntity("finalBoss", finalBoss);
    _manager.addEntity("bossBullet", bossBullet);
    _manager.addEntity("console", console);
    _manager.addEntity("waiting_server", waiting_server);
    _manager.addEntity("text_waiting_server", text_waiting_server);
    _manager.addEntity("miniBoss", miniBoss);
    _manager.addEntity("lobbyBoard", lobbyBoard);
    _manager.addEntity("lobbyText", lobbyText);
    _manager.addEntity("hearth_bonus", hearth_bonus);
    _manager.addEntity("bonus_speed", bonus_speed);
    _manager.addEntity("bonus_power", bonus_power);
    _manager.addEntity("bullet_bonus", bullet_bonus);

    // modify paramaters for the entities
    _manager.getEntity("player1").get()->getComponent<SpaceShip>().setPosition(100, 240);
    _manager.getEntity("player1").get()->getComponent<SpaceShip>().setScale(0.2, 0.2);
    _manager.getEntity("player2").get()->getComponent<SpaceShip>().setPosition(100, 700);
    _manager.getEntity("player2").get()->getComponent<SpaceShip>().setScale(0.15, 0.15);
    _manager.getEntity("player3").get()->getComponent<SpaceShip>().setPosition(100, 500);
    _manager.getEntity("player3").get()->getComponent<SpaceShip>().setScale(0.2, 0.2);
    _manager.getEntity("player4").get()->getComponent<SpaceShip>().setPosition(100, 300);
    _manager.getEntity("player4").get()->getComponent<SpaceShip>().setScale(0.2, 0.2);
    _manager.getEntity("progression_bar").get()->getComponent<ProgressionBar>().setPosition(750, -5);

    _manager.getEntity("parallax2").get()->getComponent<Parallax>().setScale(5, 5);
    _manager.getEntity("parallax3").get()->getComponent<Parallax>().setScale(5, 5);
    _manager.getEntity("parallax4").get()->getComponent<Parallax>().setScale(5, 5);
    _manager.getEntity("life_bar").get()->getComponent<LifeBar>().setScale(0.2, 0.2);
    _manager.getEntity("life_bar").get()->getComponent<LifeBar>().setPosition(-500, 0);

    _manager.getEntity("life").get()->getComponent<Life>().setFont("font");
    _manager.getEntity("life").get()->getComponent<Life>().setFontSize(36);
    _manager.getEntity("life").get()->getComponent<Life>().setStyle(sf::Text::Regular);
    _manager.getEntity("life").get()->getComponent<Life>().setPosition(30, 1020);
    _manager.getEntity("life").get()->getComponent<Life>().setText("Life: 20");

    _manager.getEntity("text").get()->getComponent<Text>().setFont("font");
    _manager.getEntity("text").get()->getComponent<Text>().setFontSize(50);
    _manager.getEntity("text").get()->getComponent<Text>().setStyle(sf::Text::Bold);
    _manager.getEntity("text").get()->getComponent<Text>().setPosition(835, 80);
    _manager.getEntity("text").get()->getComponent<Text>().setText("STAGE 1");

    _manager.getEntity("text_waiting_server").get()->getComponent<Text>().setFont("font");
    _manager.getEntity("text_waiting_server").get()->getComponent<Text>().setText("Waiting for the server ");
    _manager.getEntity("text_waiting_server").get()->getComponent<Text>().setPosition(550, 320);
    _manager.getEntity("text_waiting_server").get()->getComponent<Text>().setDrawable(true);
    _manager.getEntity("text_waiting_server").get()->getComponent<Text>().setFontSize(80);

    _manager.getEntity("player_text").get()->getComponent<Text>().setFont("font");
    _manager.getEntity("player_text").get()->getComponent<Text>().setFontSize(32);
    _manager.getEntity("player_text").get()->getComponent<Text>().setStyle(sf::Text::Bold);
    _manager.getEntity("player_text").get()->getComponent<Text>().setPosition(20, 30);
    _manager.getEntity("player_text").get()->getComponent<Text>().setText("Player Undefined");

    _manager.getEntity("fps_text").get()->getComponent<Text>().setFont("font");
    _manager.getEntity("fps_text").get()->getComponent<Text>().setFontSize(32);
    _manager.getEntity("fps_text").get()->getComponent<Text>().setStyle(sf::Text::Bold);
    _manager.getEntity("fps_text").get()->getComponent<Text>().setPosition(30, 75);
    _manager.getEntity("fps_text").get()->getComponent<Text>().setText("FPS: 0");

    _manager.getEntity("lobbyText").get()->getComponent<Text>().setText("Press 'SPACE' to start the lobby.\nYour are connected to the loby\nwith the players:\n\n");
    _manager.getEntity("lobbyText").get()->getComponent<Text>().setFontSize(32);
    _manager.getEntity("lobbyText").get()->getComponent<Text>().getText()->setCharacterSize(32);
    _manager.getEntity("lobbyText").get()->getComponent<Text>().getText()->setFillColor(sf::Color::Black);
    _manager.getEntity("lobbyText").get()->getComponent<Text>().setStyle(sf::Text::Bold);
    _manager.getEntity("lobbyText").get()->getComponent<Text>().setFont("font");
    _manager.getEntity("lobbyText").get()->getComponent<Text>().setPosition(1272, 200);


    _manager.getEntity("finalBoss").get()->getComponent<FinalBoss>().setPosition(4000, 4000);
    _manager.getEntity("finalBoss").get()->getComponent<FinalBoss>().setScale(0.75, 0.75);

    //waiting server parameters:
    _manager.getEntity("waiting_server").get()->getComponent<WaitingSprite>().setScale(0.30, 0.30);
    _manager.getEntity("waiting_server").get()->getComponent<WaitingSprite>().setPosition(950, 550);
    _manager.getEntity("waiting_server").get()->getComponent<WaitingSprite>().setDrawable(false);

    _manager.getEntity("console").get()->getComponent<consoleInGame>().setPosition(375, 390);
    _manager.getEntity("console").get()->getComponent<consoleInGame>().setScale(0.45, 0.30);

    _manager.getEntity("shoot").get()->getComponent<Sound>().getSound().setVolume(25);
    _manager.getEntity("shoothit").get()->getComponent<Sound>().getSound().setVolume(25);
    _manager.getEntity("youDontKnow").get()->getComponent<Sound>().getSound().setVolume(100);
    _manager.getEntity("thePowerOf").get()->getComponent<Sound>().getSound().setVolume(100);
    _manager.getEntity("nooo").get()->getComponent<Sound>().getSound().setVolume(100);

    _manager.getEntity("miniBoss").get()->getComponent<SemiBoss>().setPosition(1600, 500);
    _manager.getEntity("miniBoss").get()->getComponent<SemiBoss>().getSprite().setOrigin(_manager.getEntity("miniBoss").get()->getComponent<SemiBoss>().getSprite().getGlobalBounds().width / 2, _manager.getEntity("miniBoss").get()->getComponent<SemiBoss>().getSprite().getGlobalBounds().height / 2);
    _manager.getEntity("miniBoss").get()->getComponent<SemiBoss>().setScale(0.7, 0.7);

    _manager.getEntity("lobbyBoard").get()->getComponent<LobyBoard>().setScale(2.2, 2.2);
    _manager.getEntity("lobbyBoard").get()->getComponent<LobyBoard>().setPosition(1150, 0);
    // _manager.getEntity("lobbyBoard").get()->getComponent<LobyBoard>().init();

    _manager.getEntity("hearth_bonus").get()->getComponent<Sprite>().setPosition(-1000, -1000);
    _manager.getEntity("bonus_speed").get()->getComponent<Sprite>().setPosition(-1000, -1000);
    _manager.getEntity("bonus_power").get()->getComponent<Sprite>().setPosition(-1000, -1000);

}

/**
 * @brief Generic function to get the tokens from the server message
 *
 * @param msg message from the server
 * @return token_t struct with the tokens vector, id and position
 */
token_t GamePlay::getTokens(std::string msg)
{
    token_t token;
    std::istringstream iss(msg);
    for (std::string s; iss >> s; )
        token.tokens.push_back(s);
    token.id = std::atoi(token.tokens[1].c_str());
    if (token.tokens.size() > 2)
        token.posX = std::atoi(token.tokens[2].c_str());
    if (token.tokens.size() > 3)
        token.posY = std::atoi(token.tokens[3].c_str());
    return token;
}

/**
 * @brief Try to connect to the server if the connection is not established
 *
 */
void GamePlay::tryConnectToServer()
{
    if (_window->getLobbyFull() == true) return;
    if (!sentConnect) {
        _window->getClient().startClientThread();
        sentConnect = true;
    }
    if (!hasPlayerId) {
        GET_WAITING_SPRITE.setDrawable(true);
        _window->getClient().startConnectionWithServer();
    }
    if (!isPlayerReady) {
        // TODO HERE:
    }
}

void GamePlay::setSpaceShip()
{
    return; 
}

/**
 * @brief Update all the clock for the game
 *
 */
void GamePlay::getTimeFromClocks()
{
    for (int i = 0; i < NB_CLOCKS; i++) {
        _gamePlayTime[i] = _gamePlayClocks[i].getElapsedTime();
    }
    _fpsCounter++;
    if (_gamePlayTime[FPS_CLOCK].asSeconds() >= 1) {
        _system->getManager().getEntity("fps_text").get()->getComponent<Text>().setText("FPS: " + std::to_string(_fpsCounter) + '\n' + "Ping: " + std::to_string(_ping));
        _fpsCounter = 0;
        _window->increaseScore();
        _gamePlayClocks[FPS_CLOCK].restart();
    }
    if (_gamePlayTime.at(CHECK_PING).asSeconds() >= SECONDS_TO_SEND_PING_MESSAGE) {
        _window->getClient().sender("k" + std::to_string(_player_id));
        _gamePlayClocks[CHECK_PING].restart();
    }
    handleParallax();
}

/**
 * @brief Send to server the command who wrote the client (boss, maxbullet, ...)
 *
 */
void GamePlay::sendSpecificCommandToServer()
{
    if (!is_connected || !hasPlayerId || !isPlayerReady)
        return;
    SpaceShip &starship = GET_STARSHIP(_player_id);
    sf::Vector2f pos = starship.getSprite().getPosition();
    int x = pos.x; int y = pos.y;
    // FOR TESTING PURPOSES AND CHEATING:
    if (maxBullets && _gamePlayTime[BULLET_CLOCK].asSeconds() > 0.07) {
        _window->getClient().sender("B 0 " + std::to_string(x) + " " + std::to_string(y));
        _gamePlayClocks[BULLET_CLOCK].restart();
    }
    if (_gamePlayTime[PLAYER_POSITION].asSeconds() > SECONDS_TO_SEND_POS) {
        _window->getClient().sender("P " + std::to_string(_player_id) + ' ' + std::to_string(x) + ' ' + std::to_string(y));
        _gamePlayClocks[PLAYER_POSITION].restart();
    }
}