//
// Created by thibaut on 01.12.18.
//

#include "../../Include/Entities/SFMLPlayerCar.h"
#include <iostream>


void SFMLPlayerCar::draw() {
    std::tuple<int,int> newloc=Transformation::getInstance().locationTransformation(this->getLoc1());
    setSpriteLocation(std::get<0>(newloc),std::get<1>(newloc));
    if(getHorizontalSpeed()<0){
        SFMLEntitySprite::setRotation(-10);
    }else if(getHorizontalSpeed()>0){
        SFMLEntitySprite::setRotation(10);
    }else{
        if(getRotation()>160) {
            SFMLEntitySprite::setRotation(getRotation()+1);
        }else if(getRotation()>0){
            SFMLEntitySprite::setRotation(getRotation()-1);
        }
    }

    getWindow()->draw(*this);
}

SFMLPlayerCar::SFMLPlayerCar(const roadfighter::Location &m_loc1, const roadfighter::Location &m_loc2,
                             double m_maxVertSpeed, double m_vertAccel, double m_horAccel, double m_fuel,
                             const std::shared_ptr<roadfighter::MoveController> &m_moveController,
                              const std::shared_ptr<sf::RenderWindow> &window) : PlayerCar(
        m_loc1, m_loc2, m_maxVertSpeed, m_vertAccel, m_horAccel, m_fuel, m_moveController), SFMLEntitySprite("../../SFMLConversion/resources/sprites/player_car.png",
                                                                                                             window) {
    std::tuple<int,int> sfmlpos1=Transformation::getInstance().locationTransformation(getLoc1());
    std::tuple<int,int> sfmlpos2=Transformation::getInstance().locationTransformation(getLoc2());
    SFMLEntitySprite::scale(sf::Vector2f(
            ((std::get<0>(sfmlpos2)-std::get<0>(sfmlpos1))/SFMLEntitySprite::getGlobalBounds().width),
            ((std::get<1>(sfmlpos2)-std::get<1>(sfmlpos1))/SFMLEntitySprite::getGlobalBounds().height)));
}
