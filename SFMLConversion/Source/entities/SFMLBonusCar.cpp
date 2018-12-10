//
// Created by thibaut on 08.12.18.
//

#include "../../Include/Entities/SFMLBonusCar.h"

SFMLBonusCar::SFMLBonusCar( const std::shared_ptr<sf::RenderWindow> &window,
                           const roadfighter::Location &m_loc1, const roadfighter::Location &m_loc2, double vertSpeed)
        : SFMLEntitySprite("../../SFMLConversion/resources/sprites/special_car.png", window), BonusCar(m_loc1, m_loc2, vertSpeed) {
    std::tuple<int,int> sfmlpos1=Transformation::getInstance().locationTransformation(getLoc1());
    std::tuple<int,int> sfmlpos2=Transformation::getInstance().locationTransformation(getLoc2());
    SFMLEntitySprite::scale(sf::Vector2f(
            ((std::get<0>(sfmlpos2)-std::get<0>(sfmlpos1))/SFMLEntitySprite::getGlobalBounds().width),
            ((std::get<1>(sfmlpos2)-std::get<1>(sfmlpos1))/SFMLEntitySprite::getGlobalBounds().height)));
}

void SFMLBonusCar::draw() {
    std::tuple<int,int> newloc=Transformation::getInstance().locationTransformation(this->getLoc1());
    setSpriteLocation(std::get<0>(newloc),std::get<1>(newloc));
    if(getVerticalSpeed()<0){
        SFMLEntitySprite::setRotation(180);
    }else{
        SFMLEntitySprite::setRotation(0);
    }
    getWindow()->draw(*this);
}
