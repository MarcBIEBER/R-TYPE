#include "Menu.hpp"

void Menu::getEventSingleplayer()
{
    sf::Event event;
    while (_window->getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->getWindow().close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _window->getWindow().close();
        }
    }
}

void Menu::loopSingleplayer(System &system)
{
    getEventSingleplayer();
    _window->clearWindow();
    _window->update(system);
    _window->draw(system);
    _window->refreshWindow();
}