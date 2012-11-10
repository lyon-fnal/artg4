// PhysicsListBase.hh

// This is a base class for all physics lists.

// The handling of physics lists is a little tricky. To make things simple,
// users inherit their physics lists from this class. Calling the default
// constructor here will register the list with the @PhysicsListHolder@ service.
// That service, when asked, will hand off a copy of this physics list to Geant.
// It has to use a copy, because Geant will delete the list itself. Since
// the service is created by the service manager, if we handed off the real
// thing to Geant, then it would get deleted twice (once by the service manager,
// and also by Geant). 

#ifndef PHYSICS_LIST_BASE_HH
#define PHYSICS_LIST_BASE_HH

#include "Geant4/G4VUserPhysicsList.hh"

namespace artg4 {
  
  class PhysicsListBase : public G4VUserPhysicsList {
    public:
    
    // Constructor, automatically register
    PhysicsListBase();
    
    // Copy constructor
//    PhysicsListBase( PhysicsListBase const & );
    
    // Because we are going to make a copy of this, we need to turn
    // abstract G4VUserPhysicsList into a concrete class
    
    virtual void ConstructParticle() override;
          
    virtual void ConstructProcess() override;
         
    // Destructor
    virtual ~PhysicsListBase() {};
    
  };
}

#endif
