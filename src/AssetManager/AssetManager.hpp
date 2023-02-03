/*
** EPITECH PROJECT, 2022
** test_archi
** File description:
** AssetManager
*/

#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include "../ECS/IComponent.hpp"

/**
 * @brief The AssetManager class
 */
class AssetManager {
    public:
        AssetManager();
        ~AssetManager() = default;

    void cleanAsset();

    sf::Texture getTexture(std::string id);
    sf::Text getText(std::string id);
    sf::Sprite getSprite(std::string id);
    sf::Font getFont(std::string id);
    std::unordered_map<std::string, sf::Sprite> &getAllSprite();
    sf::SoundBuffer getSound(std::string id);
    
    void loadSound(std::string id, std::string path);
    void loadTexture(std::string id, std::string path);
    void loadSprite(std::string id, std::string path);
    void loadAnimateSprite(std::string id, std::string idTexture, int x, int y, int width, int height);
    void loadFont(std::string id, std::string path);
    void animatingSprite(std::string id, int x, int y, int width, int height);
    void setSpritePosition(std::string id, sf::Vector2f position);
    void setSpriteScale(std::string id, sf::Vector2f scale);
    void setSpriteRotation(std::string id, float rotation);

    inline static AssetManager &getInstance() {
         if (_instance == nullptr)
            _instance = new AssetManager();
        return *_instance;
    }

    protected:
    private:
        static AssetManager *_instance;
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Sprite> _sprites;
        std::unordered_map<std::string, sf::Text> _texts;
        std::unordered_map<std::string, sf::Font> _fonts;
        std::unordered_map<std::string, sf::SoundBuffer> _sounds;
        std::vector<std::pair<std::string, sf::Music>> _musics;


};

#endif /* !ASSETMANAGER_HPP_ */
