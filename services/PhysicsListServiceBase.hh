// PhysicsListServiceBase
#ifndef PHYSICS_LIST_SERVICE_BASE_HH
#define PHYSICS_LIST_SERVICE_BASE_HH

#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "artg4/services/PhysicsListHolder_service.hh"

#include <memory>
#include "Geant4/G4VUserPhysicsList.hh"

namespace artg4 {

  class PhysicsListServiceBase {
    
    public:
    
    // The constructor does the registration
    PhysicsListServiceBase() {
      art::ServiceHandle<PhysicsListHolderService> ph;
      ph->registerPhysicsListService( this );
    }
    
    
    // Make the physics list
    virtual G4VUserPhysicsList* makePhysicsList() const = 0;
  };
    
}



#endif
