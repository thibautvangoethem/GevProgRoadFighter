//
// Created by thibaut on 01.12.18.
//

#include "../../Include/Entities/SFMLEntity.h"

SFMLEntity::SFMLEntity() {}

SFMLEntity::SFMLEntity(const std::string& path){
    m_texture=new sf::Texture();
    m_texture->loadFromFile(path);
    setTexture(*m_texture);
}



void SFMLEntity::setSpriteLocation(double x, double y) {
   this->setPosition(x,y);
}

void SFMLEntity::setSpriteSize(double width, double height) {

}

void SFMLEntity::loadSprite(const std::string &path) {
//    if(m_texture->loadFromFile(path)) this->setTexture(*m_texture);
}