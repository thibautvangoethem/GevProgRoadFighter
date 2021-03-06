/**
 *@file
 * implementation of the SFMLPassingCar class
 * @author Thibaut Van Goethem
 */

#include "../../Include/Entities/SFMLPassingCar.h"
namespace roadfighterSFML {

    /**
     * constructor for the sfmlPassingCar
     * @param window the renderwindow that is used to draw on
     * @param m_loc1 the first location of the car
     * @param m_loc2 the second location of the car
     * @param vertSpeed the vertical speed of the car
     */
    SFMLPassingCar::SFMLPassingCar(const std::shared_ptr<sf::RenderWindow> &window,
                                   const roadfighter::Location &m_loc1, const roadfighter::Location &m_loc2,
                                   double vertSpeed) : SFMLEntitySprite(
            "./resources/sprites/passing_car.png", window),
                                                       PassingCar(m_loc1, m_loc2, vertSpeed) {
        std::tuple<double, double> sfmlpos1 = Transformation::getInstance().locationTransformation(getLoc1());
        std::tuple<double, double> sfmlpos2 = Transformation::getInstance().locationTransformation(getLoc2());
        setOrigin(SFMLEntitySprite::getGlobalBounds().width / 2, SFMLEntitySprite::getGlobalBounds().height / 2);
        SFMLEntitySprite::scale(sf::Vector2f(
                static_cast<float>((std::get<0>(sfmlpos2) - std::get<0>(sfmlpos1)) / SFMLEntitySprite::getGlobalBounds().width),
                static_cast<float>((std::get<1>(sfmlpos2) - std::get<1>(sfmlpos1)) / SFMLEntitySprite::getGlobalBounds().height)));
    }

    /**
      * draw function that is overriden from roadfighter::entity
      * @return none
      * @exception none
      */
    void SFMLPassingCar::draw() {
        std::tuple<double, double> newloc = Transformation::getInstance().locationTransformation(this->getLoc1());
        setSpriteLocation(std::get<0>(newloc) + SFMLEntitySprite::getGlobalBounds().width / 2,
                          std::get<1>(newloc) + SFMLEntitySprite::getGlobalBounds().height / 2);
        if (getVerticalSpeed() < 0) {
            SFMLEntitySprite::setRotation(180);
        } else {
            SFMLEntitySprite::setRotation(0);
        }
        getWindow()->draw(*this);
    }
}
