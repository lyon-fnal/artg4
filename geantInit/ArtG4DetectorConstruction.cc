// ArtG4DetectorConstruction.cc
// Author: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// See the header file for documentation


#include "ArtG4DetectorConstruction.hh"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "artg4/services/DetectorHolder_service.hh"

artg4::ArtG4DetectorConstruction::ArtG4DetectorConstruction()
{
  art::ServiceHandle<artg4::DetectorHolderService> dh;
  _world = dh -> worldPhysicalVolume();
}

artg4::ArtG4DetectorConstruction::ArtG4DetectorConstruction(G4VPhysicalVolume * world)
  : _world(world)
{
  // nothing else to do!
}

G4VPhysicalVolume * artg4::ArtG4DetectorConstruction::Construct()
{
  return _world;
}
