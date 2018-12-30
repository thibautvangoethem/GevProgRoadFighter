#include <utility>

//
// Created by thibaut on 01.12.18.
//
#include <RoadFighterGame.h>

namespace roadfighter{
    /**
    * default constructor for RoadFighterGameµ
    * @return none
    * @exception none
    */
    RoadFighterGame::RoadFighterGame():m_status(gameRunning) {
        m_Factory=std::make_shared<GLL_Entity_Factory>(GLL_Entity_Factory());
        initialize();
    }

    /**
     * a constructor were the factory that is used to initalise all the objects is given
     * @param factory the factory that will be used to make everything
     * @return none
     * @exception none
     */
    RoadFighterGame::RoadFighterGame(std::shared_ptr<Entity_Factory_base> factory):m_status(gameRunning) {
        m_Factory= std::move(factory);
        initialize();
    }

    /**
    * a function that will tick the whole game with dt ticks
    * @param dt the amount of ticks the game should move (should be 1 or lower otherwise it's possible more gameticks occur in 1 tick)
    *
    * in this function the position of the objects will always be updated by dt ticks
    * but the gamelogic will only be done if 1 tick has passed
    * so if you call this function with dt being 0.5 twice it will update only the positions the first time,
    * but the second time it will update both the positions and the gamelogic
     *
     * @return none
     * @exception none
    */
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

    /**
     * a function that updates the movement of all entities by dt ticks
     * @param dt amount of a tick the postions must be updated with
     * @return none
     * @exception none
     */
    void RoadFighterGame::movementTick(double dt) {
        //first all cars move forward then the playercar gets moved back to the center
        // the amount the playercar had to move is the same all the other object will move back
        m_world->updateMovement(dt);
        normalizeWorld(getYvariance());
    }

    /**
     * a function that does a logic tick which will update the logic of all entities and possibly add new cars to the world
     * @return none
     * @exception none
     */
    void RoadFighterGame::logicTick() {
        if(m_status==gameRunning) {
            addRandomCars();
            if(testEnd()){
                endGame();
            }
        }
        if(m_status!=gameEnded) {
            m_world->updateLogic();
            m_Transporter->clear();
            if (m_status == gameEnding) {
                if (m_Player->getVerticalSpeed() == 0) {
                    m_status = gameEnded;
                }
            }
        }
        if(m_status==gameEnded&&!m_MoveController->getText().empty()){
            HighScoreManager::addHighScore(m_MoveController->getText(),m_ScoreObserver->getScore());
            m_MoveController->setNone();
        }
    }

    /**
     * functiont that checks if the game has ended
     * @return bool
     * @exception none
     */
    bool RoadFighterGame::hasEnded() const {
        return m_status==gameEnded;
    }

    /**
     * function that checks if the game is won
     * @return bool
     * @exception none
     */
    bool RoadFighterGame::testEnd() const {
        return m_Player->getStatus()==Won;
    }

    /**
     * function that ends the game and detaches the scoreobserver
     * @return none
     * @exception none
     */
    void RoadFighterGame::endGame() {
        m_status=gameEnding;
        m_world->dettachAllObservers();
    }

    /**
    * a function that calls the draw function on the world which will then call the draw function on all its entities
     * @return none
     * @exception none
    */
    void RoadFighterGame::drawWorld() const{
        m_world->draw();
    }

    /**
     * a function that will set the movementcontroller to go left next tick
     * @return none
     * @exception none
     */
    void RoadFighterGame::moveLeft() {
        if(m_status==gameRunning)m_MoveController->setHorMove(h_left);
    }

    /**
     * a function that will set the movementcontroller to go right next tick
     * @return none
     * @exception none
     */
    void RoadFighterGame::moveRight() {
        if(m_status==gameRunning) m_MoveController->setHorMove(h_right);
    }

    /**
     * a function that will set the movementcontroller to accelerate in the vertical direction next tick
     * @return none
     * @exception none
     */
    void RoadFighterGame::accelerate() {
        if(m_status==gameRunning)m_MoveController->setVertMove(v_accel);
    }

    /**
    * a function that will set the movementcontroller to decelerate in the vertical direction next tick
     * @return none
     * @exception none
    */
    void RoadFighterGame::decelerate() {
        if(m_status==gameRunning)m_MoveController->setVertMove(v_decel);
    }

    //private function used in constructor
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

        std::shared_ptr<Entity> end=m_Factory->createEnd(-10);
        m_Transporter->addEntity(end);
    }

    //private function used to add random cars to the gamefield
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


    /**
    * a function that sets the movementcontroller to none for the horizontal move
     * @return none
     * @exception none
    */
    void RoadFighterGame::stopHorizontalMove() {
        m_MoveController->setHorMove(h_none);
    }

    /**
     * a function that sets the movementcontroller to none for the vertical move
     * @return none
     * @exception none
     */
    void RoadFighterGame::stopVerticalMove() {
        m_MoveController->setVertMove(v_none);
    }
    /**
    * gets the current speed of the playercar
    * @return a double represeting the speed of the playercar
     * @exception none
    */
    double RoadFighterGame::getsSpeed() const {
        return m_Player->getVerticalSpeed();
    }

    //private funtion used to calculate the middle of a vehicle
    double RoadFighterGame::getYvariance() const {
        return m_Player->getLoc2().getY()-m_Player->getheight()/2;
    }

    //private function used to set the player back to the middle of the screen
    void RoadFighterGame::normalizeWorld(double ySetback) {
        m_world->setBackY(ySetback);
    }


    /**
    * getter for the current amount of fuel in the playercar
     * @return none
     * @exception none
    */
    double RoadFighterGame::getFuel() const {
        return m_Player->getFuel();
    }

    /**
    * a function that handles the movecontroller to make it shoot
     * @return none
     * @exception none
    */
    void RoadFighterGame::shoot() {
        if(m_status==gameRunning)m_MoveController->shoot();

    }

    /**
     * a function that handles the movementcontrolle rto make it stop shooting
     * @return none
     * @exception none
     */
    void RoadFighterGame::stopShooting() {
        m_MoveController->noShoot();
    }

    /**
     * function that gets the score of the player
     * @return an unsigned int denoting the score
     * @exception none
     */
    unsigned int RoadFighterGame::getScore() const {
        return m_ScoreObserver->getScore();
    }

    /**
     * function that pauses the game
     * @return none
     * @exception none
     */
    void RoadFighterGame::pauseGame() {
        if(m_status!=gameEnding){
            m_status=gamePaused;
        }
    }

    /**
     * function that unpauses the game
     * @return none
     * @exception none
     */
    void RoadFighterGame::continueGame() {
        if(m_status!=gameEnding){
            m_status=gameRunning;
        }
    }

    /**
     * getter for the current status of the game
     * @return the status of the game
     * @exception none
     */
    EGameStatus RoadFighterGame::getStatus() const {
        return m_status;
    }

    /**
     * function that checks if the game is paused
     * @return bool
     * @exception none
     */
    bool RoadFighterGame::ispaused() const {
        return m_status==gamePaused;
    }

    /**
     * setter for the text of the inputcontroller
     * @param text the text that will be given to the controller
     * @exception none
     */
    void RoadFighterGame::setText(const std::string &text) {
        m_MoveController->setText(text);
    }
}