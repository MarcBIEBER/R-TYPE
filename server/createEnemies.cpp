#include "server.hpp"
#include <random>

inline int getBulletAngle(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void server::spawnEnnemy(int ennemyId, float seconds, sf::Clock &clockDurationEnemy, sf::Time &timeDurationEnemy)
{
    if (clockDurationEnemy.getElapsedTime().asSeconds() > seconds) {
        sendToAllPlayers("E " + std::to_string(ennemyId) + " " + std::to_string(2000 + (rand() %  500)) + " " + std::to_string(rand() % 1080));
        clockDurationEnemy.restart();
    }
}

void server::createEnnemies()
{
    _bossIsDead.set(false);
    while (_stopAcceptingClients.get() == false) {
        for (int i = 0; i < NB_CLOCKS; i++) {
            _serverClocks[i].restart();
        }
    }
    while (1) {
        if (!_bossIsAlive.get() && !_miniBossIsAlive.get() && _nbPlayers.get() > 0) {
            _serverTimes[STAGE_CLOCK] = _serverClocks[STAGE_CLOCK].getElapsedTime();
            _serverTimes[PROGRESS_CLOCK] = _serverClocks[PROGRESS_CLOCK].getElapsedTime();
            if (_progressPos >= 9 && _bossIsDead.get() == true) {
                _acctualStage++;
                _progressPos = 0;
                _serverClocks[STAGE_CLOCK].restart();
                }
            if (_serverTimes[PROGRESS_CLOCK].asSeconds() >= 3) {
                // std::cout << "boss state : " << _bossIsDead.get() << std::endl;
                // std::cout << "progress bar : " << _progressPos << std::endl;
                if (_bossIsAlive.get() == false && _miniBossIsAlive.get() == false)
                    _progressPos++;
                sendToAllPlayers("p " + std::to_string(_progressPos));
                _serverClocks[PROGRESS_CLOCK].restart();
                if (_serverTimes[STAGE_CLOCK].asSeconds() >= 5 && _progressPos == 9) {
                    _ennemySpawnTime = { _ennemySpawnTime[0] /= 1.5, _ennemySpawnTime[1] /= 1.5, _ennemySpawnTime[2] /= 1.5, _ennemySpawnTime[3] /= 1.5 };
                    sendToAllPlayers("S " + std::to_string(_acctualStage));
                    sendToAllPlayers("p " + std::to_string(0));
                    createBossThread();
                }
                if (_progressPos == 5) {
                    // std::cout << "Spawn ennemy" << std::endl;
                    _ennemySpawnTime = { _ennemySpawnTime[0] /= 1.5, _ennemySpawnTime[1] /= 1.5, _ennemySpawnTime[2] /= 1.5, _ennemySpawnTime[3] /= 1.5 };
                    sendToAllPlayers("S " + std::to_string(_acctualStage));
                    sendToAllPlayers("p " + std::to_string(0));
                    createMiniBossThread();
                }
            }
        }
        for (int i = 0; i < NB_ENNEMIES; i++) {
            _timeDurationEnemy[i] = _clockDurationEnemy[i].getElapsedTime();
            spawnEnnemy(i, _ennemySpawnTime.at(i), _clockDurationEnemy[i], _timeDurationEnemy[i]);
        }
        if (_nbPlayers.get() > 0)
            for (int i = 0; i < NB_BONUS; i++) {
                _timeDurationBonus[i] = _clockDurationBonus[i].getElapsedTime();
                createBonus(i, _bonusSpawnTime.at(i), _clockDurationBonus[i], _timeDurationBonus[i]);
            }
        // for (int i = 0; i < NB_BONUS; i++) {
        //     std::cout << "bonus time : " << i << ": " <<_timeDurationBonus[i].asSeconds() << std::endl;
        // }
    }
}

void server::createBonus(int bonusId, float seconds, sf::Clock &clockDurationBonus, sf::Time &timeDurationBonus)
{
    if (clockDurationBonus.getElapsedTime().asSeconds() > seconds) {
        sendToAllPlayers("+ " + std::to_string(bonusId) + " " + std::to_string(2000 + (rand() %  500)) + " " + std::to_string(rand() % 1080));
        clockDurationBonus.restart();
    }
}


void server::bossThread()
{
    int angle;
    bool ready;
    while (1) {
        angle = 0;
        ready = false;
        _serverClocks[BOSS_CLOCK].restart();
        while (_bossIsAlive.get() && _nbPlayers.get() > 0) {
            _serverTimes[BOSS_CLOCK] = _serverClocks[BOSS_CLOCK].getElapsedTime();
            if (!ready && _serverTimes[BOSS_CLOCK].asSeconds() > 5.0) {
                ready = true;
            }
            if (_acctualStage >= 4)
                _bullet_spawn_time = 0.35;
            else if (_acctualStage >= 5)
                _bullet_spawn_time = 0.15;
            if (ready && _serverTimes[BOSS_CLOCK].asSeconds() > _bullet_spawn_time) {
                angle = getBulletAngle(-70, 70) + 180;
                sendToAllPlayers("b " + std::to_string(angle));
                _serverClocks[BOSS_CLOCK].restart();
            }
        }
    }
    _bossThreadLunched = false;
}

void server::miniBossThread()
{
    _serverClocks[MINI_BOSS_CLOCK].restart();
    while (1) {
        if (_miniBossIsAlive.get() && _nbPlayers.get() > 0) {
            _serverTimes[MINI_BOSS_CLOCK] = _serverClocks[MINI_BOSS_CLOCK].getElapsedTime();
            if (_serverTimes[MINI_BOSS_CLOCK].asSeconds() > 0.4) {
                sendToAllPlayers("m " + std::to_string(getBulletAngle(-30, -10)) + " " + std::to_string(getBulletAngle(-20, 20)));
                _serverClocks[MINI_BOSS_CLOCK].restart();
            }
        } else {
            _serverClocks[MINI_BOSS_CLOCK].restart();
        }
    }
}

void server::createBossThread()
{
    sendToAllPlayers("bossS" + std::to_string(_acctualStage));
    _bossIsAlive.set(true);
    if (!_bossThreadLunched) {
        _bossThreadLunched = true;
        _threadBoss = std::thread(&server::bossThread, this);
    }
}

void server::createMiniBossThread()
{
    sendToAllPlayers("b2S" + std::to_string(_acctualStage));
    _miniBossIsAlive.set(true);
    if (!_miniBossThreadLunched) {
        _miniBossThreadLunched = true;
        _threadMiniBoss = std::thread(&server::miniBossThread, this);
    }
}