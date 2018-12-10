#include <utility>

//
// Created by thibaut on 01.12.18.
//
#include <RoadFighterGame.h>
#include <iostream>

namespace roadfighter{
    RoadFighterGame::RoadFighterGame() {
        m_Factory=std::make_shared<GLL_Entity_Factory>(GLL_Entity_Factory());
        initialize();
    }

    RoadFighterGame::RoadFighterGame(std::shared_ptr<Entity_Factory_base> factory) {
        m_Factory= std::move(factory);
        initialize();
    }


    void RoadFighterGame::tick(double dt) {
        movementTick(dt);
        m_logicTick+=dt;
        while(m_logicTick>1){
            m_logicTick-=1;
            logicTick();
        }
    }

    void RoadFighterGame::movementTick(double dt) {
        m_world->updateMovement(dt);
        normalizeWorld(getYvariance());
    }

    void RoadFighterGame::logicTick() {
        addRandomCars();
        m_world->updateLogic();
        m_Transporter->clear();
    }


    void RoadFighterGame::drawWorld() const{
        m_world->draw();
    }

    void RoadFighterGame::moveLeft() {
        m_MoveController->setHorMove(h_left);
    }

    void RoadFighterGame::moveRight() {
        m_MoveController->setHorMove(h_right);
    }

    void RoadFighterGame::accelerate() {
        m_MoveController->setVertMove(v_accel);
    }

    void RoadFighterGame::decelerate() {
        m_MoveController->setVertMove(v_decel);
    }

    void RoadFighterGame::initialize() {
        m_Transporter=std::make_shared<EntityTransporter>(EntityTransporter());
        m_MoveController=std::make_shared<MoveController>(MoveController());
        m_Factory->setController(m_MoveController);
        m_Factory->setTransporter(m_Transporter);
        m_world=std::dynamic_pointer_cast<World>(m_Factory->createWorld());

        //create player
        std::shared_ptr<Entity> player=m_Factory->createPlayerCar(-0.5,0,1.2,0.02,0.5,100);
        m_Transporter->addEntity(player);
        m_Player=std::dynamic_pointer_cast<PlayerCar>(player);

        //create racingcars
        std::shared_ptr<Entity> enemy1=m_Factory->createRacingCar(0.5,-1,1,0.02,0.2);
        m_Transporter->addEntity(enemy1);

        std::shared_ptr<Entity> enemy2=m_Factory->createRacingCar(-0.5,-2,1,0.02,0.2);
        m_Transporter->addEntity(enemy2);

        std::shared_ptr<Entity> enemy3=m_Factory->createRacingCar(0.5,-3,1,0.02,0.2);
        m_Transporter->addEntity(enemy3);

        std::shared_ptr<Entity> enemy4=m_Factory->createRacingCar(-0.5,-4,1,0.02,0.2);
        m_Transporter->addEntity(enemy4);

        std::shared_ptr<Entity> enemy5=m_Factory->createRacingCar(0.5,1,1,0.02,0.2);
        m_Transporter->addEntity(enemy5);

        std::shared_ptr<Entity> enemy6=m_Factory->createRacingCar(-0.5,2,1,0.02,0.2);
        m_Transporter->addEntity(enemy6);

        std::shared_ptr<Entity> enemy7=m_Factory->createRacingCar(0.5,3,1,0.02,0.2);
        m_Transporter->addEntity(enemy7);

        std::shared_ptr<Entity> enemy8=m_Factory->createRacingCar(-0.5,4,1,0.02,0.2);
        m_Transporter->addEntity(enemy8);

        std::shared_ptr<Entity> end=m_Factory->createEnd(-100);
        m_Transporter->addEntity(end);
    }

    void RoadFighterGame::addRandomCars() {
        int newCarProb=Random::getInstance().getRandom(5);
        if(newCarProb==0){
            int bonusorpassing=Random::getInstance().getRandom(5);
            if(bonusorpassing==0){
                int loc=Random::getInstance().getRandom(6)-3;
                auto bonus=m_Factory->createBonusCar(loc,-5,-0.5);
                m_Transporter->addEntity(bonus);
            }else{
                int loc=Random::getInstance().getRandom(6)-3;
                auto passing=m_Factory->creatPassingCar(loc,-5,-0.5);
                m_Transporter->addEntity(passing);
            }
        }

    }


    void RoadFighterGame::stopHorizontalMove() {
        m_MoveController->setHorMove(h_none);
    }

    void RoadFighterGame::stopVerticalMove() {
        m_MoveController->setVertMove(v_none);
    }

    double RoadFighterGame::getsSpeed() const {
        return m_Player->getVerticalSpeed();
    }

    double RoadFighterGame::getYvariance() const {
        return m_Player->getLoc2().getY()-m_Player->getheight()/2;
    }

    void RoadFighterGame::normalizeWorld(double ySetback) {
        m_world->setBackY(ySetback);
    }

}