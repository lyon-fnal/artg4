// Implemenation for PhysicsListHolder_service

#include "services/PhysicsListHolder_service.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"


void artg4::PhysicsListHolderService::registerPhysicsList(
                        PhysicsListBase* physicsList) {
  // There can be only one
  if ( physicsList_ ) {
  throw cet::exception("PhysicsListHolderService") << "A physics list is already registered.\n";
  }
  
  physicsList_ = physicsList;
}


G4VUserPhysicsList* artg4::PhysicsListHolderService::getPhysicsList() {
  // Make sure we have one
  if ( ! physicsList_ ) {
    throw cet::exception("PhysicsListHolderService") << "No physics list has been registered.\n";
  }
  
  // Return a copy of the physics list (because Geant is going to delete it)
  return new PhysicsListBase( *physicsList_ );
}



// Register the service with Art
using artg4::PhysicsListHolderService;
DEFINE_ART_SERVICE(PhysicsListHolderService)
