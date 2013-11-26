// Implemenation for PhysicsListHolder_service

#include "artg4/services/PhysicsListHolder_service.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "artg4/services/PhysicsListServiceBase.hh"

void artg4::PhysicsListHolderService::registerPhysicsListService( PhysicsListServiceBase* pl ) {
  // There can be only one
  if ( physicsListService_ ) {
    throw cet::exception("PhysicsListHolderService") << "A physics list is already registered.\n";
  }
  
  physicsListService_ = pl;
}


G4VUserPhysicsList* artg4::PhysicsListHolderService::makePhysicsList() const {
  // Make sure we have one
  if ( ! physicsListService_ ) {
    throw cet::exception("PhysicsListHolderService") << "No physics list has been registered.\n";
  }
  
  // Return the physics list (Geant is going to delete it)
  return physicsListService_->makePhysicsList();
}


void artg4::PhysicsListHolderService::initializePhysicsList() const {
  // Make sure we have one
  if ( ! physicsListService_ ) {
    throw cet::exception("PhysicsListHolderService") << "No physics list has been registered.\n";
  }
  
  physicsListService_->initializePhysicsList();
}

// Register the service with Art
using artg4::PhysicsListHolderService;

DEFINE_ART_SERVICE(PhysicsListHolderService)
