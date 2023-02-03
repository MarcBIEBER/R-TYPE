#include "Menu.hpp"

/**
 * @brief Get the events of multiplayer scene
 * 
 */
void Menu::getEventMultiplayer()
{
    handleParallax(_systemMultiplayer);
    sf::Event event;
    while (_window->getWindow().pollEvent(event)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window->getWindow());
        if (event.type == sf::Event::Closed)
            _window->getWindow().close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                setScene(MAIN);
        }
        GETSYSCOMP(_systemMultiplayer, "buttonQuit", Button).handleHover(mousePos);
        GETSYSCOMP(_systemMultiplayer, "createButton", Button).handleHover(mousePos);
        GETSYSCOMP(_systemMultiplayer, "joinButton", Button).handleHover(mousePos);
        if (event.type == sf::Event::MouseButtonReleased) {
            for (int i = 0; i != _nbServer; i++) {
                if (GETSYSCOMP(_systemMultiplayer, "serverBox" + std::to_string(i), ServerBox).isClick(mousePos))
                    _currentClick = GETSYSCOMP(_systemMultiplayer, "serverBox" + std::to_string(i), ServerBox).getClick(mousePos);
            }
            if (GETSYSCOMP(_systemMultiplayer, "joinButton", Button).getClick(mousePos)) {
                if (_nbServer > 0)
                    setScene(JOINSERVER);
            }
            if (GETSYSCOMP(_systemMultiplayer, "createButton", Button).getClick(mousePos))
                setScene(CREATESERVER);
            if (GETSYSCOMP(_systemMultiplayer, "buttonQuit", Button).getClick(mousePos))
                setScene(MAIN);
        }
        if (event.type == sf::Event::MouseWheelMoved) {
            for (int i = 0; i != _nbServer; i++) {
                GETSYSCOMP(_systemMultiplayer, "serverBox" + std::to_string(i), ServerBox).move(0, event.mouseWheel.delta * 2);
            }

        }
    }
}

/**
 * @brief loop of multiplayer scene
 * 
 * @param system current system for multiplayer scene
 */
void Menu::loopMultiplayer(System &system)
{
    getEventMultiplayer();
    _window->clearWindow();
    _window->update(system);
    _window->draw(system);
    _window->refreshWindow();
}