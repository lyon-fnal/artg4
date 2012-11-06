// Declarations for the @PhysicsListHolder@ service

// Hang on to a physics list to be given to Geant

// Note that this is a little different than the other holder services.
// Instead of "forwarding" member functons from the Geant class, we need
// to initialize Geant with the *real* physics list class (because it will
// change things internally). 

// Include guard
#ifndef PHYSICSLIST_HOLDER_SERVICE_HH
#define PHYSICSLIST_HOLDER_SERVICE_HH

// Includes
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"

class G4VUserPhysicsList;


// Everything for the Art G4 simulation goes in the @artg4@ namespace
namespace artg4 {
  
  class PhysicsListHolderService {
  public:
    
    // Constructor for Physics List holder
    PhysicsListHolderService(fhicl::ParameterSet const&, art::ActivityRegistry&) :
      physicsList_(0)
    {}
    
    // Destructor - don't do anything
    virtual ~PhysicsListHolderService() {}
    
    // This registers the passed detector with the service.
    void registerPhysicsList(G4VUserPhysicsList *);
    
    // Get Physics list
    G4VUserPhysicsList* getPhysicsList();

  private:
    
    G4VUserPhysicsList* physicsList_;
  };
  
} // end namespace artg4


#endif // PHYSICSLIST_HOLDER_SERVICE