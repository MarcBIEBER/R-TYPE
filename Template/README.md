Our game engine is easy to use.

It is made for `SFML and ONLY SFML`.

<br />
<br />

Let's check step by step how to use it!


### Load all of the assets needed for the game


1. Load the texture you want
```c++
AssetManager::getInstance().loadTexture("id_to_give", "path_to_png");
```

2. 1 Load the sprites you want
```c++
AssetManager::getInstance().loadSprite("id_to_give", "texture_id");
```

2. 2 Load the fonts you want
```c++
AssetManager::getInstance().loadFont("id_to_give_", "path_to_ttf");
```

### Initialize the game

1. Create a system and initialize it
```c++
System *system = new System(SFML_Window);
```

2. Create our entities to display
    
    a) Load the entity manager
    ```c++
    EntityManager &manager = getSystem->getManager();
    ```
    b) Create our entities
    ```c++
    Entity *entity = new Entity();
    ```
    c) Give it a component
    ```c++
    entity->addComponent<TypeDeComposantACree>(Sprite_id_to_give, ... (depend on what type of Component to add), SFML_window);
    ```
    d) Add the entity to the manager
    ```c++
    manager.addEntity(id_to_give, entity_previously_create);
    ```

