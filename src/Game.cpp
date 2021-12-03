#include "Game.h"

Game::Game()
{
    initVariables();
    initWindow();

    sf::Image winImage;
    if(!winImage.loadFromFile("assets/LevelPassed.png"))
    {
        std::cout << "ERROR::EndLevel IMAGE NOT FOUND !!!" << std::endl;
    }

    this->winTextures.loadFromImage(winImage);
    this->winSprite.setTexture(this->winTextures);
    this->winSprite.setScale(1.f, 1.f);
}

Game::~Game()
{
    delete window;
}

void Game::initWindow()
{
    //Definition of the size of the window
    this->videoMode.width = 800;
    this->videoMode.height = 600;
    //Creation of the window
    this->window = new sf::RenderWindow(this->videoMode, "Super Luffy Crew", sf::Style::Titlebar | sf::Style::Close);
    //Definition of the FPS of the game
    this->window->setFramerateLimit(20);
}

void Game::initVariables()
{
    this->characterView.setGroundView(&groundView);
    //this->enemyView.setGroundView(&groundView);
    this->characterView.setPowerView(&powerView);
    this->characterView.setEnemyView(&enemyView);
    this->characterView.setMeatView(&meatView);
    this->characterView.setEndLevelView(&endLevelView);
    this->enemyView.setPowerView(&powerView);
}

//Accesssors
const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    //Event polling
    while(this->window->pollEvent(this->events))
    {
        switch(this->events.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
        }
        if(characterView.getAdvancementState() == 1){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                int index = this->characterView.checkCollision(1);
                int indexEnemy = this->characterView.checkCollisionWithEnemies(1);
                int indexPower = this->characterView.checkCollisionWithPowers(1);
                int indexMeat = this->characterView.checkCollisionWithMeats(1);
                int indexEndLevel = this->characterView.checkCollisionWithEndLevel(1);
                //Move the obstacles
                if(index == -1 && indexEnemy == -1)
                {
                    this->groundView.moveObjects(1);
                    this->powerView.movePowers(1);
                    this->enemyView.moveEnemy(1);
                    this->meatView.moveMeat(1);
                    this->endLevelView.moveEndLevel(1);
                }
                //Update the image of the character
                this->characterView.moveCharacter(1);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                int index = this->characterView.checkCollision(0);
                int indexPower = this->characterView.checkCollisionWithPowers(0);
                int indexEnemy = this->characterView.checkCollisionWithEnemies(0);
                int indexMeat = this->characterView.checkCollisionWithMeats(0);
                int indexEndLevel = this->characterView.checkCollisionWithEndLevel(0);
                if(index == -1 && indexEnemy == -1)
                {
                    //Move the obstacles
                    this->groundView.moveObjects(0);
                    this->powerView.movePowers(0);
                    this->enemyView.moveEnemy(0);
                    this->meatView.moveMeat(0);
                    this->endLevelView.moveEndLevel(0);
                }
                //Update the image of the character
                this->characterView.moveCharacter(0);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                this->characterView.jump();
            }
        }
        //Display level passed
        else {
            if(characterView.getAdvancementState() == 5){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    std::cout<<"level win" << std::endl;
                }
            } else {
                if(characterView.getAdvancementState() == 0){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        std::cout<<"level lost" << std::endl;
                    }
                }
            }
        }

    }
    if(this->characterView.isJumping())
    {
        this->characterView.jump();
    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    if(characterView.getAdvancementState() == 1){
          //Clear the content of the window
        this->window->clear();
        //Draw the game objects
        this->groundView.render(this->window);
        this->characterView.render(this->window);
        this->powerView.render(this->window);
        this->enemyView.render(this->window);
        this->meatView.render(this->window);
        this->endLevelView.render(this->window);
        this->lifeView.render(this->window, characterView.getCharacter().getLifePoint());
        //std::cout << "hero life before: " << characterView.getCharacter().getLifePoint() << std::endl;
        this->lifeView.updateLifeTxt(characterView.getCharacter().getLifePoint());
    } else{
        if(characterView.getAdvancementState() == 5){
            this->window->clear();
            window->draw(this->winSprite);
        }

    }
    //Display the new content of the window
    this->window->display();
}
