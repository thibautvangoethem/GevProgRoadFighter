/**
 *@file
 * implementation of the SFMLEnd class
 * @author Thibaut Van Goethem
 */
#include "../../Include/Entities/SFMLEnd.h"
namespace roadfighterSFML {

    /**
     * constructor for the sfmlend class
     * @param m_loc1 first location of the end
     * @param m_loc2 second location of the object
     * @param window the sfmlrenderwindow that is used to draw on
     * @return none
     * @exception none
     */
    SFMLEnd::SFMLEnd(const roadfighter::Location &m_loc1, const roadfighter::Location &m_loc2,
                     const std::shared_ptr<sf::RenderWindow> &window) : End(m_loc1, m_loc2),
                                                                        SFMLEntitySprite(
                                                                                "./resources/sprites/Finishline.png",
                                                                                window) {
        std::tuple<double, double> sfmlpos1 = Transformation::getInstance().locationTransformation(getLoc1());
        std::tuple<double, double> sfmlpos2 = Transformation::getInstance().locationTransformation(getLoc2());
        SFMLEntitySprite::scale(sf::Vector2f(
                static_cast<float>((std::get<0>(sfmlpos2) - std::get<0>(sfmlpos1)) / SFMLEntitySprite::getGlobalBounds().width),
                static_cast<float>((std::get<1>(sfmlpos2) - std::get<1>(sfmlpos1)) / SFMLEntitySprite::getGlobalBounds().height)));
    }
    /**
      * draw function that is overriden from roadfighter::entity
      * @return none
      * @exception none
      */
    void SFMLEnd::draw() {
        std::tuple<double, double> newloc = Transformation::getInstance().locationTransformation(this->getLoc1());
        setSpriteLocation(std::get<0>(newloc), std::get<1>(newloc));
        getWindow()->draw(*this);
    }
}
