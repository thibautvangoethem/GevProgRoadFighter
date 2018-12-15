#include <utility>

//
// Created by thibaut on 01.12.18.
//
#include <RoadFighterGame.h>

namespace roadfighter{
    RoadFighterGame::RoadFighterGame():m_status(gameRunning) {
        m_Factory=std::make_shared<GLL_Entity_Factory>(GLL_Entity_Factory());
        initialize();
    }

    RoadFighterGame::RoadFighterGame(std::shared_ptr<Entity_Factory_base> factory):m_status(gameRunning) {
        m_Factory= std::move(factory);
        initialize();
    }


    void RoadFighterGame::tick(double dt) {
        if(m_status!=gamePaused) {
            movementTick(dt);
            m_logicTick += dt;
            while (m_logicTick > 1) {
                m_logicTick -= 1;
                logicTick();
            }
        }
    }

    void RoadFighterGame::movementTick(double dt) {
        //first all cars move forward then the playercar gets moved back to the center
        // the amount the playercar had to move is the same all the other object will move back
        m_world->updateMovement(dt);
        normalizeWorld(getYvariance());
    }

    void RoadFighterGame::logicTick() {
        if(m_status==gameRunning) {
            addRandomCars();
            if(testEnd()){
                endGame();
            }
        }
        m_world->updateLogic();
        m_Transporter->clear();
    }

    bool RoadFighterGame::hasEnded() const {

    }

    bool RoadFighterGame::testEnd() const {
        return m_Player->getStatus()==Won;
    }

    void RoadFighterGame::endGame() {
        m_status=gameEnd;
        m_world->dettachAllObservers();
    }

    void RoadFighterGame::drawWorld() const{
        m_world->draw();
    }

    void RoadFighterGame::moveLeft() {
        if(m_status==gameRunning)m_MoveController->setHorMove(h_left);
    }

    void RoadFighterGame::moveRight() {
        if(m_status==gameRunning) m_MoveController->setHorMove(h_right);
    }

    void RoadFighterGame::accelerate() {
        if(m_status==gameRunning)m_MoveController->setVertMove(v_accel);
    }

    void RoadFighterGame::decelerate() {
        if(m_status==gameRunning)m_MoveController->setVertMove(v_decel);
    }

    void RoadFighterGame::initialize() {
        //creat transporter/movectonroller and set these into the factory so they can be given to the cars
        m_Transporter=m_Factory->getTransporter();
        m_MoveController=m_Factory->getController();
        m_ScoreObserver=std::dynamic_pointer_cast<ScoreObserver>(m_Factory->getScoreObserver());
        m_world=std::dynamic_pointer_cast<World>(m_Factory->createWorld());

        //create player
        std::shared_ptr<Entity> player=m_Factory->createPlayerCar(-0.5,0,0.4,0.005,0.15,100);
        m_Transporter->addEntity(player);
        m_Player=std::dynamic_pointer_cast<PlayerCar>(player);

        //create 8 racingcars
        std::shared_ptr<Entity> enemy1=m_Factory->createRacingCar(0.5,-1,0.3333,0.005,0.15);
        m_Transporter->addEntity(enemy1);

        std::shared_ptr<Entity> enemy2=m_Factory->createRacingCar(-0.5,-2,0.3333,0.005,0.15);
        m_Transporter->addEntity(enemy2);

        std::shared_ptr<Entity> enemy3=m_Factory->createRacingCar(0.5,-3,0.3333,0.005,0.15);
        m_Transporter->addEntity(enemy3);

        std::shared_ptr<Entity> enemy4=m_Factory->createRacingCar(-0.5,-4,0.3333,0.005,0.15);
        m_Transporter->addEntity(enemy4);

        std::shared_ptr<Entity> enemy5=m_Factory->createRacingCar(0.5,1,0.3333,0.005,0.15);
        m_Transporter->addEntity(enemy5);

        std::shared_ptr<Entity> enemy6=m_Factory->createRacingCar(-0.5,2,0.3333,0.005,0.15);
        m_Transporter->addEntity(enemy6);

        std::shared_ptr<Entity> enemy7=m_Factory->createRacingCar(0.5,3,0.3333,0.005,0.15);
        m_Transporter->addEntity(enemy7);

        std::shared_ptr<Entity> enemy8=m_Factory->createRacingCar(-0.5,4,0.3333,0.005,0.15);
        m_Transporter->addEntity(enemy8);

        std::shared_ptr<Entity> end=m_Factory->createEnd(-200);
        m_Transporter->addEntity(end);
    }

    void RoadFighterGame::addRandomCars() {
        int newCarProb=Random::getInstance().getRandom(15);
        if(newCarProb==0){
            int bonusorpassing=Random::getInstance().getRandom(5);
            if(bonusorpassing==0){
                int loc=Random::getInstance().getRandom(6)-3;
                auto bonus=m_Factory->createBonusCar(loc,-5,-0.15);
                m_Transporter->addEntity(bonus);
            }else{
                int loc=Random::getInstance().getRandom(6)-3;
                auto passing=m_Factory->creatPassingCar(loc,-5,-0.15);
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


    double RoadFighterGame::getFuel() const {
        return m_Player->getFuel();
    }

    void RoadFighterGame::shoot() {
        if(m_status==gameRunning)m_MoveController->shoot();

    }

    void RoadFighterGame::stopShooting() {
        m_MoveController->noShoot();
    }

    unsigned int RoadFighterGame::getScore() const {
        return m_ScoreObserver->getScore();
    }

    void RoadFighterGame::pauseGame() {
        if(m_status!=gameEnd){
            m_status=gamePaused;
        }
    }

    void RoadFighterGame::continueGame() {
        if(m_status!=gameEnd){
            m_status=gameRunning;
        }
    }

    EGameStatus RoadFighterGame::getStatus() const {
        return m_status;
    }
}