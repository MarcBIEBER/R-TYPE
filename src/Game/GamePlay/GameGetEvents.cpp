#include "GamePlay.hpp"

/**
 * @brief Get the player input and send it to the server
 * 
 */
void GamePlay::getPlayerInput(sf::Event event)
{
    SpaceShip &starship = GETCOMP("player" + std::to_string(_player_id), SpaceShip);
    sf::Vector2f pos = starship.getSprite().getPosition();
    if (event.type == sf::Event::KeyPressed) {
        // CHANGE HERE LATER IF NEEDED:
        // pushKeyIntoQueue(event.key.code);
        sf::Keyboard::Key key = event.key.code;
        if (key == sf::Keyboard::Left || key == sf::Keyboard::Key::Q && pos.x > 0)
            _window->getClient().sender(std::to_string(_player_id) + "1");
        if (key == sf::Keyboard::Right || key == sf::Keyboard::Key::D && pos.x < 1870)
            _window->getClient().sender(std::to_string(_player_id) + "2");
        if (key == sf::Keyboard::Up || key == sf::Keyboard::Key::Z && pos.y > 0)
            _window->getClient().sender(std::to_string(_player_id) + "3");
        if (key == sf::Keyboard::Down || key == sf::Keyboard::Key::S && pos.y < 1060)
            _window->getClient().sender(std::to_string(_player_id) + "4");
        if (_gamePlayTime[PLAYER_SHOOT].asSeconds() >= 0.1)
            if (key == sf::Keyboard::RShift) {
                int id = 0; int posX = pos.x + 100; int posY = pos.y + 5;
                _window->getClient().sender("B " + std::to_string(id) + " " + std::to_string(posX) + " " + std::to_string(posY));
                _gamePlayClocks[PLAYER_SHOOT].restart();
            }
        for (int i = 1; i < 5; i++)
        {
            SpaceShip &player = GETCOMP("player" + std::to_string(i), SpaceShip);
            if (player.getActive() == false)
                continue;
            if (_gamePlayTime[PLAYER_SHOOT].asSeconds() >= 0.1)
                if (key == sf::Keyboard::LShift && GETCOMP("player" + std::to_string(i), SpaceShip).isBonusPowerActive()) {
                    int id = 1; int posX = pos.x + 100; int posY = pos.y + 5;
                    _window->getClient().sender("B " + std::to_string(id) + " " + std::to_string(posX) + " " + std::to_string(posY));
                    _gamePlayClocks[PLAYER_SHOOT].restart();
                    this->nbr_occ_bonus_bullet++;
                    this->shot_bonus_bullet = true;
                    if (this->nbr_occ_bonus_bullet == 3) {
                        GETCOMP("player" + std::to_string(i), SpaceShip).setBonusPower(false);
                        this->nbr_occ_bonus_bullet = 0;
                    }
                }
        }
    }
}

/**
 * @brief Main loop of the poll event check basic action and send all other to other function to be handled
 * 
 */
void GamePlay::makePollEvent()
{
    sf::Event event;
    handleCollision();
    if (getPlayerLife() == 0)
        _window->setGameScene(END);

    while (_window->getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->getWindow().close();
        if (event.type == sf::Event::Closed) {
                _window->setGameScene(END);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (!isPlayerReady && event.key.code == sf::Keyboard::Space) {
                _window->getClient().sender("start");
            }
            if (event.key.code == sf::Keyboard::Escape) {
                _window->setGameScene(END);
            }
            if (event.key.code == 53) {
                if (isTyping == false) {
                    isTyping = !isTyping;
                    GET_CONSOLE.setDrawable(true);
                } else {
                    isTyping = false;
                    GET_CONSOLE.setDrawable(false);
                }
            }
        }
        if (is_connected && hasPlayerId && isTyping == false && isPlayerReady)
            getPlayerInput(event);
        if (isTyping)
            getInputKeysForConsole(event);
    }
}

/**
 * @brief Get the commands from the console in game
 * 
 */
void GamePlay::getInputKeysForConsole(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        // std::cout << "Key pressed: " << event.key.code << std::endl;
        if (event.key.code == sf::Keyboard::BackSpace) {
            GET_CONSOLE.deleteLastChar();
        }
        else if (event.key.code == sf::Keyboard::Return) {
            checkConsoleCommand();
        } else {
            if (event.key.code >= 0 && event.key.code <= 25 || event.key.code >= 26 && event.key.code <= 51) {
                GET_CONSOLE.addChar(event.key.code + 97);
            }
            if (event.key.code == 57)
                GET_CONSOLE.addChar(' ');
        }
    }
}

/**
 * @brief Check the command from the console and send it to the server (like a chat, cheat, ...)
 * 
 */
void GamePlay::checkConsoleCommand()
{
    std::string command = GET_CONSOLE.getCommand();
    if (command == "quit") {
        _window->setGameScene(END);
        _window->setIsClientConnected(false);
        return;
    }
    if (command == "clear") {
        GET_CONSOLE.clearCommands(); return;
    }
    if (command == "max") {
        GET_CONSOLE.setText(""); maxBullets = !maxBullets;
        leaveConsole(); return;
    }
    if (command == "boss") {
        GET_CONSOLE.setText(""); leaveConsole();
        _window->getClient().sender("boss"); return;
    }
    if (command == "miniboss") {
        GET_CONSOLE.setText(""); leaveConsole();
        _window->getClient().sender("miniboss");
        GET_MINI_BOSS.setDrawable(true); return;
    }
    _window->getClient().sender("M Player " + std::to_string(_player_id) + ": " + command);
    GET_CONSOLE.setText("");

}

/**
 * @brief Use to quit the game console
 * 
 */
void GamePlay::leaveConsole()
{
    if (isTyping) {
        isTyping = false;
        GET_CONSOLE.setDrawable(false);
    }
}