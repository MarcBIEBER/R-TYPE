/*
** EPITECH PROJECT, 2022
** test_archi
** File description:
** AssetManager
*/

#include "AssetManager.hpp"
#include "string.h"
#include <vector>

AssetManager* AssetManager::_instance = nullptr;

/**
 * @brief Construct a new Asset Manager:: Asset Manager object
 */
AssetManager::AssetManager()
{
}

/**
 * @brief Destroy the Asset Manager:: Asset Manager object
 */
void AssetManager::cleanAsset()
{
    //todo: unload all assets (texture, texte, sprite, ...)
}

/**
 * @brief Get the Texture object
 * @param id The id of the texture
 * @return The texture
 */
sf::Texture AssetManager::getTexture(std::string id)
{
    for (auto &texture : _textures) {
        if (texture.first == id) {
            return texture.second;
        }
    }

    std::cout << "getTexture not found" << std::endl;
    sf::Texture texture;
    texture.loadFromFile("./assets/sprites/background.jpg");
    return texture;
}

/**
 * @brief Get the Sprite object
 * @param id The id of the sprite
 * @return The sprite
 */
sf::Sprite AssetManager::getSprite(std::string id)
{
    for (auto &sprite : _sprites) {
        if (sprite.first == id) {
            return sprite.second;
        }
    }
    sf::Sprite sprite;
    sprite.setTexture(getTexture("background"));
    return sprite;
}

/**
 * @brief Get all the sprites loaded
 * @return The sprites (unordered_map)
 */ 
std::unordered_map<std::string, sf::Sprite> &AssetManager::getAllSprite()
{
    return _sprites;
}

/**
 * @brief Get sound
 * @param id The id of the sound
 * @return The sound
 */
sf::SoundBuffer AssetManager::getSound(std::string id)
{
    for (auto &sound : _sounds) {
        if (sound.first == id) {
            return sound.second;
        }
    }
    return _sounds.at(0);
}


/**
 * @brief Load a sound
 * @param id The id of the sound
 * @param path path to sound file
 */
void AssetManager::loadSound(std::string id, std::string path)
{
    try {
        sf::SoundBuffer sound;
        if (!sound.loadFromFile(path))
            std::cerr << "File not found" << std::endl;
        _sounds[id] = sound;
    } catch (std::exception &e) {
        std::cout << "Error: sound not found" << std::endl;
    }
}

/**
 * @brief Load the texture
 * @param id The id of the texture to create
 * @param path The path of the texture
 */
void AssetManager::loadTexture(std::string id, std::string path)
{
    try {
        sf::Texture texture;
        texture.loadFromFile(path);
        _textures[id] = texture;
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}


/**
 * @brief Load the Sprite
 * @param id The id of the Sprite to create
 * @param idTexture The id of the texture to use
 */
void AssetManager::loadSprite(std::string id, std::string idTexture)
{
    try {
        sf::Sprite sprite;
        sprite.setTexture(_textures[idTexture]);
        _sprites.emplace(id, sprite);
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void AssetManager::loadAnimateSprite(std::string id, std::string idTexture, int x, int y, int width, int height)
{
    try {
        sf::Sprite sprite;
        sprite.setTexture(_textures[idTexture]);
        sprite.setTextureRect(sf::IntRect(x, y, width, height));
        _sprites.emplace(id, sprite);
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/**
 * @brief Set the rotation of the sprite
 * @param id The id of the sprite to rotate
 * @param angle The angle to rotate
 */
void AssetManager::setSpriteRotation(std::string id, float angle)
{
    _sprites[id].setRotation(angle);
}

/**
 * @brief Use to load font in memory
 * @param id The id of the font to create
 * @param path The path of the font
 */
void AssetManager::loadFont(std::string id, std::string path)
{
    try {
        sf::Font font;
        if (!font.loadFromFile(path))
            std::cerr << "Error: Font not found" << std::endl;
        _fonts[id] = font;
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/**
 * @brief Set the sprite position
 * @param id The id of sprite to set the position
 * @param pos The position to set
 */
void AssetManager::setSpritePosition(std::string id, sf::Vector2f position)
{
    try {
        for (auto &sprite : _sprites) {
            if (sprite.first == id) {
                sprite.second.setPosition(position);
                break;
            }
        }
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/**
 * @brief Set the sprite scale
 * @param id The id of sprite to set the scale
 * @param scale The scale to set
 */
void AssetManager::setSpriteScale(std::string id, sf::Vector2f scale)
{
    try {
        for (auto &sprite : _sprites) {
            if (sprite.first == id) {
                sprite.second.setScale(scale);
                break;
            }
        }
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/**
 * @brief Get the text
 * @param id The id of the text
 * @return The text (sf::Text)s
 */
sf::Text AssetManager::getText(std::string id)
{
    for (auto &text : _texts) {
        if (text.first == id) {
            return text.second;
        }
    }
    sf::Text text = sf::Text();
    text.setString("default");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    return text;
}

/**
 * @brief Get the font
 * @param id The id of font
 * @return The font (sf::Font)
 */
sf::Font AssetManager::getFont(std::string id)
{
    for (auto &font : _fonts) {
        if (font.first == id) {
            return font.second;
        }
    }
    std::cout << "Error: Font not found" << std::endl;
    sf::Font font;
    font.loadFromFile("./assets/font/SkyMidDemoRegular.ttf");
    return font;
}

