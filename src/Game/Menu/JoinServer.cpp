#include "Menu.hpp"

/**
 * @brief Get the Event in part JoinServer
 * 
 */
void Menu::getEventJoinServer()
{
    sf::Event event;
    while (_window->getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->getWindow().close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                setScene(MULTIPLAYER);
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window->getWindow());
            if (GETSYSCOMP(_systemJoinServer, "joinButton", Button).getClick(mousePos)) {
                connectClient(GETSYSCOMP(_systemJoinServer, "serverBox" + std::to_string(_currentClick), ServerBox).getHost(), GETSYSCOMP(_systemJoinServer, "serverBox" + std::to_string(_currentClick), ServerBox).getPort());
                _window->setIsClientConnected(true);
                setScene(MAIN);
                _window->setGameScene(GAME);
                break;
            }
            if (GETSYSCOMP(_systemCreateServer, "buttonQuit", Button).getClick(mousePos))
                setScene(MULTIPLAYER);
        }
    }
}

/**
 * @brief loop of join server scene
 * 
 * @param system current system for join server scene
 */
void Menu::loopJoinServer(System &system)
{
    connectClient(GETSYSCOMP(_systemMultiplayer, "serverBox" + std::to_string(_currentClick), ServerBox).getHost(), GETSYSCOMP(_systemMultiplayer, "serverBox" + std::to_string(_currentClick), ServerBox).getPort());
    _window->setGameScene(GAME);
    setScene(MAIN);
    // getEventJoinServer();
    // _window->clearWindow();
    // _window->update(system);
    // _window->draw(system);
    // _window->refreshWindow();
}