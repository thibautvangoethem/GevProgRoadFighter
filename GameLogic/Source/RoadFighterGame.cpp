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
        m_world->update(dt);
        m_Transporter->clear();
        normalizeWorld(getYvariance());
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
        std::shared_ptr<Entity> player=m_Factory->createPlayerCar(0,0,1.2,0.02,0.1,100);
        m_Transporter->addEntity(player);
        m_Player=std::dynamic_pointer_cast<PlayerCar>(player);

        //create racingcar
        std::shared_ptr<Entity> enemy1=m_Factory->createRacingCar(1,1,1,0.02,0.2);
        m_Transporter->addEntity(enemy1);

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
        return m_Player->getM_loc2().getY()-m_Player->getheight()/2;
    }

    void RoadFighterGame::normalizeWorld(double ySetback) {
        m_world->setBackY(ySetback);
    }

}