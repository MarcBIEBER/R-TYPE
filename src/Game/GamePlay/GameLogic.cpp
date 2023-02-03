#include "GamePlay.hpp"
#define HIT_POWER 1

sf::IntRect _rectPos = sf::IntRect(0, 0, 412, 62);

/**
 * @brief Do some stuff with the server command
 */
void GamePlay::handleServerCommand()
{
    std::string msg;
    while (!_window->getClient().isMsgQueueEmpty()) {
        msg = _window->getClient().popMsgQueue();
        if (hasPlayerId == false && msg[0] >= '1' && msg[0] <= '4' && msg[1] == 0) {
            getIntoLobby(std::atoi(&msg[0]));
        }
        if (msg == "CANNOT") { lobbyFull(); return; }
        if (is_connected == false)
            break;
        else if (msg[0] >= '1' && msg[0] <= '4' && msg[1] >= '1' && msg[1] <= '4' && msg[2] == 0) {
            movePlayers(msg);
        }
        else if (msg == "bossS1") createBoss(1);
        else if (msg == "bossS2") createBoss(2);
        else if (msg == "bossS3") createBoss(3);
        else if (msg == "bossS4") createBoss(4);
        else if (msg == "bossS5") createBoss(5);
        else if (msg == "b2S1") {GET_MINI_BOSS.setStage(1); GET_MINI_BOSS.setLifePoints(100); createMiniBoss(1);}
        else if (msg == "b2S2") {GET_MINI_BOSS.setStage(2); GET_MINI_BOSS.setLifePoints(200); createMiniBoss(2);}
        else if (msg == "b2S3") {GET_MINI_BOSS.setStage(3); GET_MINI_BOSS.setLifePoints(300); createMiniBoss(3);}
        else if (msg == "b2S4") {GET_MINI_BOSS.setStage(4); GET_MINI_BOSS.setLifePoints(400); createMiniBoss(4);}
        else if (msg == "b2S5") {GET_MINI_BOSS.setStage(5); GET_MINI_BOSS.setLifePoints(500); createMiniBoss(5);}
        else if (msg == "start") {isPlayerReady = true; GET_CONSOLE.getCommands().push_back("Game started"); GET_LOBBY_TEXT.setDrawable(false); GET_LOBBY.setDrawable(false);}
        else if (msg[0] == '+') {createNewBonus(msg);}
        else if (msg[0] == 'B') createNewBullet(msg);
        else if (msg[0] == 'b') createFinalBossBullet(msg);
        else if (msg[0] == 'E') createNewEnnemy(msg);
        else if (msg[0] == '+') createNewBonus(msg);
        else if (msg[0] == 'P') resetPlayerPosition(msg);
        else if (msg[0] == 'L') activePlayers(msg);
        else if (msg[0] == 'M') receiveMessageFromPlayer(msg);
        else if (msg[0] == 'S') updateStage(msg);
        else if (msg[0] == 'p') addProgression(msg);
        else if (msg[0] == 'k') _window->getClient().sender("k" + std::to_string(_player_id));
        else if (msg[0] == 'K') getPing(msg);
        else if (msg[0] == 'm') createMiniBossBullet(msg);
        else if (msg[0] == 'l') setLifePlayers(msg);
        else if (msg[0] == 'n') setPlayersName(msg);
    }
}

/**
 * @brief Set the Space Ship object if the player is connect to the server
 * 
 */
void GamePlay::activePlayers(std::string msg)
{ 
    token_t tokens = getTokens(msg);
    for (int i = 1; i < tokens.tokens.size(); i++) {
        if (tokens.tokens.at(i) == "1") {
            _system->getManager().getEntity("player" + std::to_string(i)).get()->getComponent<SpaceShip>().setActive(true);
        } else {
            _system->getManager().getEntity("player" + std::to_string(i)).get()->getComponent<SpaceShip>().setActive(false);
        }
    }
    sendPlayerNameToServer();
}

/**
 * @brief generate space ship depending on the player set by the server
 */
void GamePlay::getIntoLobby(int playerId)
{
    _window->getClient().setPlayerId(playerId);
    _player_id = playerId;
    setSpaceShip();
    _system->getManager().getEntity("player" + std::to_string(playerId)).get()->getComponent<SpaceShip>().setActive(true);
    hasPlayerId = true;
    is_connected = true;
    GET_PLAYER_TEXT.setText("Your Player Id: " + std::to_string(playerId));
    GET_WAITING_SPRITE.setDrawable(false);
    GET_WAITING_TEXT.setDrawable(false);
    _gamePlayClocks[CHECK_PING].restart();
    sendPlayerNameToServer();
}

/**
 * @brief move the players depending on the server message
 * 
 * @param msg message from the server
 */
void GamePlay::movePlayers(std::string msg)
{
    char c = msg[0];
    if (_system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().isBonusSpeedActive() == true) {
        _system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().setSpeed(2);
    }
    if (msg[1] == '1')
        _system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().move(-_system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().getSpeed(), 0);
    if (msg[1] == '2')
        _system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().move(_system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().getSpeed(), 0);
    if (msg[1] == '3')
        _system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().move(0, -_system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().getSpeed());
    if (msg[1] == '4')
        _system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().move(0, SPEED);
    sf::Vector2f pos = _system->getManager().getEntity("player" + std::to_string(std::atoi(&c))).get()->getComponent<SpaceShip>().getPosition();
    _window->setShipMusicPosition(pos);
}

/**
 * @brief create a new bullet depending on the server message
 *
 * @param msg message from the server
 */
void GamePlay::createNewBullet(std::string msg)
{
    token_t tokens = getTokens(msg);
    std::string sprite = "";
    if (tokens.id == 0) {
        sprite = "bullet";
    } else {
        sprite = "bullet_bonus";
    }
    SpaceShip &starship = GETCOMP("player" + std::to_string(_window->getClient().getPlayerId()), SpaceShip);
    sf::Sprite bullet = AssetManager::getInstance().getSprite(sprite);
    bullet.setPosition(tokens.posX, tokens.posY);
    std::vector<sf::Sprite> &bullets = starship.getBullets();
    // Erase bullets out of screen:
    for (int i = 0; i < bullets.size(); i++) {
        sf::Vector2f pos = bullets.at(i).getPosition();
        if (pos.x < 0 || pos.x > 1920 || pos.y < 0 || pos.y > 1080) {
            bullets.erase(bullets.begin() + i);
        }
    }
    if (sprite == "bullet")
        this->shot_bonus_bullet = false;

    // Erase boss bullets out of screen:
    std::vector<sf::Sprite> bossBullet = GET_FINAL_BOSS.getBullets();
    for (int i = 0; i < bossBullet.size(); i++) {
        if (bossBullet.at(i).getPosition().x <= -100) {
            bossBullet.erase(bossBullet.begin() + i);
        }
    }
    sf::Vector2f pos(tokens.posX, tokens.posY);
    GET_SHOOT_SOUND.setPosition(pos);
    GET_SHOOT_SOUND.playSound();
    bullets.push_back(bullet);
}

/**
 * @brief create a new ennemy depending on the server message
 *
 * @param msg message from the server
 */
void GamePlay::createNewEnnemy(std::string msg)
{
    token_t tokens = getTokens(msg);
    Ennemy &ennemy = GETCOMP("enemy" + std::to_string(tokens.id), Ennemy);
    sf::Sprite ennemy_sprite = AssetManager::getInstance().getSprite("enemy"+ std::to_string(tokens.id));
    if (tokens.id == 1)
        ennemy_sprite.setScale(0.5, 0.5);
    else if (tokens.id == 2)
        ennemy_sprite.setScale(2, 2);
    else if (tokens.id == 3)
        ennemy_sprite.setScale(1.5, 1.5);
    else ennemy_sprite.setScale(0.5, 0.5);
    ennemy_sprite.setPosition(tokens.posX, tokens.posY);
    ennemy.getSprite().push_back(ennemy_sprite);
    // Erase ennemies out of screen:
    for (int i = 0; i < ennemy.getSprite().size(); i++) {
        if (ennemy.getSprite().at(i).getPosition().x <= -100) {
            ennemy.getSprite().erase(ennemy.getSprite().begin() + i);
        }
    }
}

/**
 * @brief create a new bonus depending on the server message
 *
 * @param msg message from the server
 */
void GamePlay::createNewBonus(std::string msg)
{

    std::vector<std::string> tokens;
    std::istringstream iss(msg);
    std::string sprite_str = "";
    for (std::string s; iss >> s; )
        tokens.push_back(s);
    int id = std::atoi(tokens[1].c_str());
    int posX = std::atoi(tokens[2].c_str());
    int posY = std::atoi(tokens[3].c_str());
    if (id == 0) {
        sprite_str = "hearth_bonus";
    }
    else if (id == 1)
        sprite_str = "bonus_speed";
    else if (id == 2)
        sprite_str = "bonus_power";
    Sprite &bonus = GET_BONUS(sprite_str, Sprite);
    bonus.setPosition(posX, posY);
    bonus.setScale(0.25, 0.25);
    _isBonusActive = true;
    // std::cout << "End create new bonus" << std::endl;
    // if (GET_BONUS(sprite_str, Sprite).getDrawableHearth() == false) {
    //     GET_BONUS(sprite_str, Sprite).getSprite().setPosition(-1000, -1000);
    //     GET_BONUS(sprite_str, Sprite).setDrawableHearth(true);
    // }
}

/**
 * @brief reset the player position
 *
 * @param msg message from the server
 */
void GamePlay::resetPlayerPosition(std::string msg)
{
    token_t tokens = getTokens(msg);
    std::vector<std::string> message;
    std::istringstream iss(msg);
    for (std::string s; iss >> s; )
        message.push_back(s);
    
    GETCOMP("progression_bar", ProgressionBar).spriteProgression(std::atoi(message[4].c_str()));
    GETCOMP("text", Text).setText("STAGE " + message[5]);
    SpaceShip &starship = GETCOMP("player" + std::to_string(tokens.id), SpaceShip);

    starship.getSprite().setPosition(tokens.posX, tokens.posY);
}

/**
 * @brief Use to move ennemy (like asteroids)
 *
 */
void GamePlay::handleEnnemyMovement()
{
}

/**
 * @brief Generic function to get collision between two sprites
 * @param sprite1 the sprite to check
 * @param sprite2 the sprite to check
 *
 */
bool GamePlay::getCollision(sf::Sprite &spriteOne, sf::Sprite &spriteTwo)
{
    sf::FloatRect spriteOneRect = spriteOne.getGlobalBounds();
    sf::FloatRect spriteTwoRect = spriteTwo.getGlobalBounds();
    if (spriteOneRect.intersects(spriteTwoRect)) {
        // GET_HIT_SOUND.playSound();
        return true;
    }
    return false;
}

/**
 * @brief Use to handle the messages
 *
 */
void GamePlay::receiveMessageFromPlayer(std::string msg)
{
    token_t token;
    std::string newMessage = "";
    std::istringstream iss(msg);
    for (std::string s; iss >> s;)
        token.tokens.push_back(s);

    for (int i = 1; i < token.tokens.size(); i++) {
        newMessage += token.tokens.at(i) + " ";
    }
    GET_CONSOLE.addCommand(newMessage);
}

/**
 * @brief Use to handle the parallax movement
 *
 */
void GamePlay::handleParallax()
{
    if (_gamePlayTime[PARALLAX_ONE].asMilliseconds() > 1) {
        GETCOMP("parallax1", Parallax).move(-1, 0);
        if (GETCOMP("parallax1", Parallax).getSprite().getPosition().x <= -1920)
            GETCOMP("parallax1", Parallax).getSprite().setPosition(0, 0);
        _gamePlayClocks[PARALLAX_ONE].restart();
    }
    if (_gamePlayTime[PARALLAX_TWO].asMilliseconds() > 1) {
        GETCOMP("parallax2", Parallax).move(-2, 0);
        if (GETCOMP("parallax2", Parallax).getSprite().getPosition().x <= -1920)
            GETCOMP("parallax2", Parallax).getSprite().setPosition(1920, 0);
        _gamePlayClocks[PARALLAX_TWO].restart();
    }
    if (_gamePlayTime[PARALLAX_THREE].asMilliseconds() > 1) {
        GETCOMP("parallax3", Parallax).move(-3, 0);
        if (GETCOMP("parallax3", Parallax).getSprite().getPosition().x <= -1920)
            GETCOMP("parallax3", Parallax).getSprite().setPosition(1920, 0);
        _gamePlayClocks[PARALLAX_THREE].restart();
    }
    if (_gamePlayTime[PARALLAX_FOUR].asMilliseconds() > 1) {
        GETCOMP("parallax4", Parallax).move(-4, 0);
        if (GETCOMP("parallax4", Parallax).getSprite().getPosition().x <= -1920)
            GETCOMP("parallax4", Parallax).getSprite().setPosition(1920, 0);
        _gamePlayClocks[PARALLAX_FOUR].restart();
    }
}

/**
 * @brief Use to create the boss 
 *
 */
void GamePlay::createBoss(int stage)
{
    setStage(stage);
    GET_FINAL_BOSS.setStage(stage);
    GET_FINAL_BOSS.init();
    GET_FINAL_BOSS.setDrawable(true);
    GET_YOU_DONT_KNOW.setPosition(GET_FINAL_BOSS.getPosition());
    GET_YOU_DONT_KNOW.playSound();
}

void GamePlay::createMiniBoss(int stage)
{
    // Add a init() for the miniBoss.
    // GET_MINI_BOSS.init();
    GET_MINI_BOSS.setDrawable(true);
    // Add a sound here:
}

/**
 * @brief Use to create the boss bullets and add them to the vector
 *
 */
void GamePlay::createFinalBossBullet(std::string msg)
{
    token_t tokens = getTokens(msg);
    int angle = std::stoi(tokens.tokens.at(1));
    GET_FINAL_BOSS.addBulletSpecial(angle);
}

/**
 * @brief Use to update the current stage displayed on the screen
 *
 */
void GamePlay::updateStage(std::string msg)
{
    token_t tokens = getTokens(msg);
    int stage = std::stoi(tokens.tokens.at(1));
    _system->getManager().getEntity("text").get()->getComponent<Text>().setText("STAGE " + std::to_string(stage));
    // GET_STAGE.setStage(stage);
}

/**
 * @brief Use to update the progress bar before the next stage / boss
 *
 */
void GamePlay::addProgression(std::string msg)
{
    token_t tokens = getTokens(msg);
    int progression = std::stoi(tokens.tokens.at(1));
    _system->getManager().getEntity("progression_bar").get()->getComponent<ProgressionBar>().spriteProgression(progression);
}

/**
 * @brief Get the ping of the client/server
 *
 */
void GamePlay::getPing(std::string msg)
{
    token_t tokens = getTokens(msg);
    _ping = std::stoi(tokens.tokens.at(1));
}

void GamePlay::createMiniBossBullet(std::string msg)
{
    // return;
    if (GET_MINI_BOSS.getDrawable()) {
        token_t tokens = getTokens(msg);
        int x = std::stoi(tokens.tokens.at(1));
        int y = std::stoi(tokens.tokens.at(2));
        GET_MINI_BOSS.createRealCircles(x, y);
    }
}

void GamePlay::setLifePlayers(std::string msg)
{
    token_t tokens = getTokens(msg);
    int id = std::stoi(tokens.tokens.at(1));
    int life = std::stoi(tokens.tokens.at(2));
    
    if (GET_STARSHIP(id).getActive()) {
        GET_STARSHIP(id).setLifePoints(life);
    }
}

void GamePlay::setPlayersName(std::string msg)
{
    token_t tokens = getTokens(msg);
    int id = std::stoi(tokens.tokens.at(1));
    std::string name = tokens.tokens.at(2);
    GET_STARSHIP(id).setPlayerName(name);


    std::string newLobbyText = "Press 'SPACE' to start the lobby.\nYour are connected to the loby\nwith the players:\n\n";
    for (int i = 1; i < 5; i++) {
        if (GET_STARSHIP(i).getActive()) {
            newLobbyText += "Player: " + GET_STARSHIP(i).getPlayerName() + " is ready.\n";
        }
    }
    GET_LOBBY_TEXT.setText(newLobbyText);
}

void GamePlay::sendPlayerNameToServer()
{
    std::string msg = "n " + std::to_string(_player_id) + " " + GET_STARSHIP(_player_id).getPlayerName();
    _window->getClient().sender(msg);
}

void GamePlay::lobbyFull()
{
    std::string newLobbyText = "The Lobby is full, please go back\nto the main Menu and find\na new lobby.\n";
    
    GET_LOBBY_TEXT.setText(newLobbyText);
    _window->setLobbyFull(true);
}