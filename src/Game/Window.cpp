/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** Window
*/

#include "Window.hpp"

/**
 * @brief Construct a new Window:: Window object
 * 
 */
Window::Window(client &client) : _client(client)
{
    this->_window.create(sf::VideoMode(1920, 1080), "R-Type");
    this->_window.setFramerateLimit(60);
	this->_window.setVerticalSyncEnabled(true);
	this->_window.setKeyRepeatEnabled(true);
    this->_window.requestFocus();
    this->_scene = sceneEnum::MENU;

    getMusic()->openFromFile("./assets/sound/starWarsMusic.ogg");
    getMusic()->setLoop(true);
    getMusic()->setVolume(7.f); 
    getMusic()->play();

    getMusicShip()->openFromFile("./assets/sound/turbine.ogg");
    getMusicShip()->setLoop(true);
    getMusicShip()->setVolume(0);
    getMusicShip()->play();
}

/**
 * @brief Destroy the Window:: Window object
 * 
 */
Window::~Window()
{
    gameMusic.stop();
}

void Window::setShipMusicPosition(sf::Vector2f pos) {
    float tmp = (pos.x / 100) - 10;
    if (tmp <= -5) {
        spaceshipMusic.setPosition(-0.25f, 0, 0);
        return;
    }
    if (tmp <= -1) {
        spaceshipMusic.setPosition(-0.125f, 0, 0);
        return;
    }
    if (tmp <= 3) {
        spaceshipMusic.setPosition(0.0f, 0, 0);
        return;
    }
    if (tmp <= 5) {
        spaceshipMusic.setPosition(0.125f, 0, 0);
        return;
    }
    spaceshipMusic.setPosition(.25f, 0, 0);
}

/**
 * @brief Clear the window
 * 
 */
void Window::clearWindow()
{
    this->_window.clear();
}

/**
 * @brief Refresh the window
 * 
 */
void Window::refreshWindow()
{
    if (this->_window.isOpen())
        this->_window.display();
}

/**
 * @brief Update the window and all of the elements
 * 
 * @param system current system
 */
void Window::update(System &system)
{
    system.update();
}

/**
 * @brief Draw the window and all the elements
 * 
 * @param system current system
 */
void Window::draw(System &system)
{
    system.draw();
}
