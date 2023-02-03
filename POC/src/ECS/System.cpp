/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-bsrtype-marc.bieber
** File description:
** System
*/

#include "System.hpp"

/**
 * @brief Construct a new System:: System object
 */
// System* System::_instance = nullptr;

/**
 * @brief Construct a new System:: System object
 */
System::~System()
{
}

/**
 * @brief Initialize the systems with all basic entities
 * load sprites and texture here to avoid loading them multiple times
 */
void System::init()
{
    _manager = new EntityManager;
}

/**
 * @brief Draw all the entities
 */
void System::draw()
{
    _manager->draw();
}

/**
 * @brief Update all the entities
 */
void System::update()
{
    _manager->update();
}
