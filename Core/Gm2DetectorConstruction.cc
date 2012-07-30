// Gm2DetectorConstruction.cc
// Author: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// See the header file for documentation


#include "Gm2DetectorConstruction.hh"
#include "art/Framework/Services/Registry/ServiceHandle.h"

gm2::Gm2DetectorConstruction::Gm2DetectorConstruction()
{
  art::ServiceHandle<gm2::DetectorHolder> dh;
  _world = dh -> worldPhysicalVolume();
}

gm2::Gm2DetectorConstruction::Gm2DetectorConstruction(G4VPhysicalVolume * world)
  : _world(world)
{
  // nothing else to do!
}

G4VPhysicalVolume * gm2::Gm2DetectorConstruction::Construct()
{
  return _world;
}
