#include "GamePlay.hpp"
#define HIT_POWER 2

/**
 * @brief Use to handle all of the collision
 *
 */
void GamePlay::handleCollision()
{
    try
    {
        if (!hasPlayerId || !is_connected)
            return;
        for (int i = 0; i != 4; i++)
        {
            for (auto &enmy : GETCOMP("enemy" + std::to_string(i), Ennemy).getSprite())
            {
                // collision between player and enemy
                if (getCollision(enmy, GETCOMP("player" + std::to_string(this->_player_id), SpaceShip).getSprite()))
                {
                    GET_HIT_SOUND.playSound();
                    enmy.setPosition(-2000, -2000);
                    setPlayerLife();
                    GET_LIFE.setLife(getPlayerLife());
                }
                for (auto &bullet : GETCOMP("player" + std::to_string(this->_player_id), SpaceShip).getBullets())
                {
                    // collision between bullet player and enemy
                    if (getCollision(enmy, bullet))
                    {
                        enmy.setPosition(-2000, -2000);
                        if (this->shot_bonus_bullet == false)
                            bullet.setPosition(-2000, -2000);
                    }
                }
            }

            for (auto &bossBullet : GET_FINAL_BOSS.getBullets())
            {
                for (int i = 0; i != 4; i++)
                {
                    for (auto &enmy : GETCOMP("enemy" + std::to_string(i), Ennemy).getSprite())
                    {
                        // collision between bullet boss and enemy
                        if (getCollision(enmy, bossBullet))
                        {
                            enmy.setPosition(-2000, -2000);
                            bossBullet.setPosition(-2000, -2000);
                        }
                    }
                }
            }
            // for (int i = 0; i != 4; i++)
            // {
            // std::cout << "Player life: " << getPlayerLife() << std::endl;
            // }
        }
        for (auto &bullet : GETCOMP("player" + std::to_string(this->_player_id), SpaceShip).getBullets())
        {
            int returnHealth = 0;
            // collision between bullet player and boss
            if (getCollision(GET_FINAL_BOSS.getSprite(), bullet))
            {
                if (getTouch() == false && getStage() >= 5 && GET_FINAL_BOSS.getPosition().x < 1600)
                {
                    setLeftOrRight(-5);
                    setTouch(true);
                }
                if (this->shot_bonus_bullet == true)
                    returnHealth = GET_FINAL_BOSS.removeLifePoints(HIT_POWER * 4);
                else
                    returnHealth = GET_FINAL_BOSS.removeLifePoints(HIT_POWER);
                if (returnHealth <= 50 && !playedMiddleSound)
                {
                    GET_THE_POWER_OF.setPosition(GET_FINAL_BOSS.getPosition());
                    GET_THE_POWER_OF.playSound();
                    playedMiddleSound = true;
                }
                if (returnHealth <= 0)
                {
                    playedMiddleSound = false;
                    GET_NOOO.setPosition(GET_FINAL_BOSS.getPosition());
                    GET_NOOO.playSound();
                    _window->getClient().sender("bosskill");
                    _window->increaseBossKilled();
                }
                bullet.setPosition(-2000, -2000);
            }
            // collision between bullet player and mini boss

            if (GET_MINI_BOSS.getDrawable() && getCollision(GET_MINI_BOSS.getSprite(), bullet))
            {
                int returnHealth = 0;
                if (this->shot_bonus_bullet == true)
                    returnHealth = GET_MINI_BOSS.removeLifePoints(HIT_POWER * 4);
                else
                    returnHealth = GET_MINI_BOSS.removeLifePoints(HIT_POWER);
                if (returnHealth <= 0)
                {
                    GET_MINI_BOSS.setDrawable(false);
                    _window->getClient().sender("minibosskill");
                }
                bullet.setPosition(-2000, -2000);
            }
            for (auto &bossBullet : GET_FINAL_BOSS.getBullets())
            {
                // collision between bullet player and bullet boss
                if (getCollision(bossBullet, bullet))
                {
                    GET_HIT_SOUND.playSound();
                    if (this->shot_bonus_bullet == false)
                        bullet.setPosition(-2000, -2000);
                    bossBullet.setPosition(-2000, -2000);
                }
            }
            for (auto &miniBossBullet : GET_MINI_BOSS.getCircles())
            {
                // collision between bullet player and bullet mini boss
                if (bullet.getGlobalBounds().intersects(miniBossBullet.getGlobalBounds()))
                {
                    if (this->shot_bonus_bullet == false)
                        bullet.setPosition(-2000, -2000);
                    miniBossBullet.setPosition(-2000, -2000);
                }
            }
        }
        try {
            // if ((GET_BONUS("hearth_bonus", Sprite).getSprite().getPosition().x < 0 || GET_BONUS("hearth_bonus", Sprite).getSprite().getPosition().x > 1920)
            // && (GET_BONUS("bonus_power", Sprite).getSprite().getPosition().x < 0 || GET_BONUS("bonus_power", Sprite).getSprite().getPosition().x > 1920)
            // && (GET_BONUS("bonus_speed", Sprite).getSprite().getPosition().x < 0 || GET_BONUS("bonus_speed", Sprite).getSprite().getPosition().x > 1920))
            //     _isBonusActive = false;
            if (_isBonusActive == true) {
                for (int i = 1; i < 5; i++)
                {
                    SpaceShip &player = GETCOMP("player" + std::to_string(i), SpaceShip);
                    if (player.getActive() == false)
                        continue;
                    if (getCollision(player.getSprite(), GET_BONUS("hearth_bonus", Sprite).getSprite()))
                        {
                        GET_BONUS("hearth_bonus", Sprite).setPosition(-2000, -2000);
                        setPlayerLifeBonus();
                        GET_LIFE.setLife(getPlayerLife());
                        // GET_BONUS("hearth_bonus", Sprite).setDrawableHearth(false);
                    }
                    if (getCollision(player.getSprite(), GET_BONUS("bonus_power", Sprite).getSprite()))
                    {
                        GET_BONUS("bonus_power", Sprite).setPosition(-2000, -2000);
                        GETCOMP("player" + std::to_string(i), SpaceShip).setBonusPower(true);
                        // GET_BONUS("bonus_power", Sprite).setDrawablePower(false);
                    }
                    if (getCollision(player.getSprite(), GET_BONUS("bonus_speed", Sprite).getSprite()))
                    {
                        GET_BONUS("bonus_speed", Sprite).setPosition(-2000, -2000);
                        GETCOMP("player" + std::to_string(i), SpaceShip).setBonusSpeed(true);
                        // GET_BONUS("bonus_speed", Sprite).setDrawableSpeed(false);
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "Error while handling collision with bonus" << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Error while handling collision" << std::endl;
    }
    // event boss with the window collision depend to the stage
    getCollisionBetweenBossAndWindow();
    getCollisionBetweenPlayersAndMBosses();
}

void GamePlay::getCollisionBetweenBossAndWindow()
{
    try
    {
        if (!hasPlayerId || !is_connected)
            return;
        if (getStage() >= 3)
        {
            int gap = 30;
            int check_y_top = 0;
            int check_y_bottom = 750;
            if (getStage() >= 4)
            {
                gap = 0;
                check_y_top = -75;
                check_y_bottom = 825;
            }
            GET_FINAL_BOSS.setGreenRectanglePosition(GET_FINAL_BOSS.getSprite().getPosition().x + gap, GET_FINAL_BOSS.getSprite().getPosition().y - 80);
            GET_FINAL_BOSS.setRedRectanglePosition(GET_FINAL_BOSS.getSprite().getPosition().x + gap, GET_FINAL_BOSS.getSprite().getPosition().y - 80);
            if (GET_FINAL_BOSS.getSprite().getPosition().y <= check_y_top)
            {
                if (getStage() >= 4)
                    setUpOrDown(7);
                else
                    setUpOrDown(4);
            }
            if (GET_FINAL_BOSS.getSprite().getPosition().y >= check_y_bottom)
            {
                if (getStage() >= 4)
                    setUpOrDown(-7);
                else
                    setUpOrDown(-4);
            }
            if (getStage() >= 5)
            {
                if (GET_FINAL_BOSS.getSprite().getPosition().x <= 500 && getTouch() == true)
                {
                    setLeftOrRight(5);
                }
                if (GET_FINAL_BOSS.getSprite().getPosition().x >= 1410 && getTouch() == true)
                {
                    setLeftOrRight(-5);
                }
            }
            GET_FINAL_BOSS.getSprite().move(getLeftOrRight(), getUpOrDown());
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Error while handling collision between the players and the Boss" << std::endl;
    }
}

void GamePlay::getCollisionBetweenPlayersAndMBosses()
{
    try
    {
        if (!hasPlayerId || !is_connected)
            return;
        // collision between bullet miniBoss and all the players;
        for (int i = 1; i < 5; i++)
        {
            SpaceShip &player = GETCOMP("player" + std::to_string(i), SpaceShip);
            if (player.getActive() == false)
                continue;
            for (int i = 0; i != 4; i++)
            {
                for (auto &enmy : GETCOMP("enemy" + std::to_string(i), Ennemy).getSprite())
                {
                    // collision between players and all ennemies
                    if (getCollision(enmy, player.getSprite()))
                    {
                        GET_HIT_SOUND.playSound();
                        enmy.setPosition(-2000, -2000);
                        if (i == _player_id) {
                            setPlayerLife();
                            GET_LIFE.setLife(getPlayerLife());
                        }
                    }
                }
            }
            // Collision between players and mini boss bullets
            for (auto &bullet : GET_MINI_BOSS.getCircles())
            {
                if (player.getSprite().getGlobalBounds().intersects(bullet.getGlobalBounds()))
                {
                    bullet.setPosition(-2000, -2000);
                    if (i == _player_id) {
                        setPlayerLife();
                        GET_LIFE.setLife(getPlayerLife());
                    }
                }
            }
            // collision between bullet boss and all the players;
            for (auto &bossBullet : GET_FINAL_BOSS.getBullets())
            {
                if (getCollision(bossBullet, player.getSprite()))
                {
                    bossBullet.setPosition(-2000, -2000);
                    if (i == this->_player_id)
                    {
                        GET_HIT_SOUND.playSound();
                        setPlayerLife();
                        GET_LIFE.setLife(getPlayerLife());
                    }
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Error while handling collision between the players and the miniBoss" << std::endl;
    }
    return;
}