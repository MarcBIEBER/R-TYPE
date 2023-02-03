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
Window::Window()
{
    this->_window.create(sf::VideoMode(1920, 1080), "R-Type");
    this->_window.setFramerateLimit(60);
	this->_window.setVerticalSyncEnabled(true);
	this->_window.setKeyRepeatEnabled(true);
    this->_window.requestFocus();
    system = new System();
}

/**
 * @brief Destroy the Window:: Window object
 * 
 */
Window::~Window()
{
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
