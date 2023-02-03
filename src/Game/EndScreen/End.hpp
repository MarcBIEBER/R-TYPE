#ifndef END_HPP_
#define END_HPP_

#include "../Window.hpp"

#define GETSYSCOMP(sys, ennemyID, compType) sys->getManager().getEntity(ennemyID).get()->getComponent<compType>()

class End {
    public:
        End() {};
        End(client &client, Window &window);
        ~End();

        void loop();
        void init();
        void initAsset();
        void getEvent();

        void handleParallax();
        
        void sendQuitAndClose();
        void sendChangeScene();

        void leaderBoardHandler();
    protected:
    private:
        Window *_window;
        System *_system;
        sf::Time _time;
        sf::Clock _clock;
};

#endif /* !END_HPP_ */
