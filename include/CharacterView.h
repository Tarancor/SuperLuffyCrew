#ifndef CHARACTERVIEW_H
#define CHARACTERVIEW_H

#include "Character.h"
#include "GroundView.h"
#include "EnemyView.h"
#include "PowerView.h"
#include "MeatView.h"
#include "EndLevelView.h"

class CharacterView
{
    private:
        //Game logic
        Character character;
        bool jumpDone;
        GroundView* groundView;
        EnemyView* enemyView;
        PowerView* powerView;
        MeatView* meatView;
        EndLevelView* endLevelView;
        int advancementState = 7;
        float startingY;

        //Images
        sf::Texture* characterTextures[2][3];
        sf::Sprite characterSprite;
//SOUND
        sf::SoundBuffer buffer;
        sf::Sound sound;
//----
        time_t momentCollision;
        //Constants
        const float XPOS = 368.f;
        const float JUMP_HEIGHT = 192.f;
        const int NB_TYPE_MOVEMENT = 2;
        const int NB_IMAGES_PER_MOVEMENT = 3;

        const float CHARACTER_WIDTH = 45.f;

    public:
        CharacterView();
        virtual ~CharacterView();
        CharacterView(const CharacterView& other);
        CharacterView& operator=(const CharacterView& rhs);

        //Accessors
        Character getCharacter() const;
        int getAdvancementState()const;
        void setAdvancementState(int advancementState);
        void setGroundView(GroundView* groundView);
        void setPowerView(PowerView* powerView);
        void setEnemyView(EnemyView* enemyView);
        void setMeatView(MeatView* meatView);
        void setEndLevelView(EndLevelView* endLevelView);
        //Methods
        void render(sf::RenderWindow* window);
        void moveCharacter(const int movement);
        void jump();
        const bool isJumping() const;
        const int checkCollision(int movement=0);
        const int checkCollisionWithEnemies(int movement=0);
        const int checkCollisionWithPowers(int movement=0);
        const int checkCollisionWithMeats(int movement=0);
        const int checkCollisionWithEndLevel(int movement=0);
        const int checkIfLuffyOrEnemyDie()const;
        const int getCollisionIndex(std::vector<MovableObject*> objects, int movement);
};

#endif // CHARACTERVIEW_H
