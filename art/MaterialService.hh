#ifndef MATERIAL_SERVICE_HH
#define MATERIAL_SERVICE_HH

// Art
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"

// GEANT
#include "globals.hh"
#include "G4Material.hh"
#include "G4Element.hh"

namespace gm2 {

  class MaterialService {
  public: 
    MaterialService(fhicl::ParameterSet const&, art::ActivityRegistry&);
    ~MaterialService();

    G4Material* newAir();
    G4Material* newAr();
    G4Material* newSi();
    G4Material* newScint();
    G4Material* newLead();
    
  private:
    G4Element *H, *C, *N, *O;
    double a, z, density; // For clarity in material definitions
    int nel; // Something to do with the phase it's in?

  };
}

#endif
