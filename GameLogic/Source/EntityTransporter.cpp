/**
 * @file
 * this file contains the implementation of the EntityTransporter class
 * @author Thibaut Van Goethem
 */

#include "EntityTransporter.h"

/**
* add an entity to the transporter
* @param toAdd a shared pointer to an entity
* @return none
* @exception none
*/
void roadfighter::EntityTransporter::addEntity(std::shared_ptr<roadfighter::Entity> toAdd) {
    m_entities.push_back(toAdd);
}

/**
 * gets all the entities currently in the transporter
 * @return a vector of shard pointers to entities
 * @exception none
 */
std::vector<std::shared_ptr<roadfighter::Entity>> &roadfighter::EntityTransporter::getEntities() {
    return m_entities;
}

/**
 * removes all the entities that are currently in the vector
 * @return none
 * @exception none
 */
void roadfighter::EntityTransporter::clear() {
    m_entities.clear();
}
