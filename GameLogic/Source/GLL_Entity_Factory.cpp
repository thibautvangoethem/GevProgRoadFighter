//
// Created by thibaut on 05.12.18.
//

#include "GLL_Entity_Factory.h"
namespace roadfighter{
    std::shared_ptr<Entity>  GLL_Entity_Factory::createBullet() {
        return std::shared_ptr<Entity>(nullptr);
    }

    std::shared_ptr<Entity>  GLL_Entity_Factory::creatPassingCar() {
        return nullptr;
    }

    std::shared_ptr<Entity>  GLL_Entity_Factory::createPlayerCar(double x,double y,double max,double vAccel,double hAccel,double fuel) {
        return nullptr;
    }

    std::shared_ptr<Entity>  GLL_Entity_Factory::createRacingCar(double x,double y,double max,double vAccel,double hAccel) {
        return nullptr;
    }

    std::shared_ptr<Entity>  GLL_Entity_Factory::createWorld() {
        return nullptr;
    }
}