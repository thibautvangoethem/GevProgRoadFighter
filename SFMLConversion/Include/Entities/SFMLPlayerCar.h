/**
 * @file
 * header for SFMLPlayerCar class
 * @author Thibaut Van Goethem
 */


#ifndef GEVPROGROADFIGHTER_SFMLPLAYERCAR_H
#define GEVPROGROADFIGHTER_SFMLPLAYERCAR_H

#include <Entities/PlayerCar.h>
#include <EntityTransporter.h>
#include <Entity_Factory_base.h>
#include <SFML/Graphics.hpp>
#include "SFMLEntitySprite.h"

namespace roadfighterSFML {
    class SFMLPlayerCar : public roadfighter::PlayerCar, public SFMLEntitySprite {
    public:
        //constructor with parameters
        SFMLPlayerCar(const roadfighter::Location &m_loc1, const roadfighter::Location &m_loc2, double m_maxVertSpeed,
                      double m_vertAccel, double m_horAccel, double m_fuel,
                      const std::shared_ptr<roadfighter::InputController> &m_moveController,
                      const std::shared_ptr<roadfighter::EntityTransporter> &transporter,
                      const std::shared_ptr<roadfighter::Entity_Factory_base> &factory,
                      const std::shared_ptr<sf::RenderWindow> &window);
        //draw function overriden from roadfighter::entity
        void draw() override;
    };
}


#endif //GEVPROGROADFIGHTER_SFMLPLAYERCAR_H
