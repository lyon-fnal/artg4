// Physical Volume Store implementation

#include "artg4/pluginActions/physicalVolumeStore/physicalVolumeStore_service.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"

#include <iostream>

artg4::PhysicalVolumeStoreService::PhysicalVolumeStoreService(fhicl::ParameterSet const & p,
                                                art::ActivityRegistry& )
  : RunActionBase(p.get<std::string>("name", "physicalVolumeStore")),
    pvs_( new artg4::PhysicalVolumeStoreData ),
    logInfo_("PhysicalVolumeStore")
{}

artg4::PhysicalVolumeStoreService::~PhysicalVolumeStoreService()
{ }


void artg4::PhysicalVolumeStoreService::callArtProduces(art::EDProducer* producer) {
  producer->produces< artg4::PhysicalVolumeStoreData, art::InRun>( myName() );
}

unsigned int artg4::PhysicalVolumeStoreService::idGivenPhysicalVolume(const G4VPhysicalVolume* pvptr ) {
  
  // Determine the id
  return pvs_->idGivenString( pvptr->GetName() );
}

void artg4::PhysicalVolumeStoreService::fillRunEndWithArtStuff(art::Run& r) {
  
  // Debug
  mf::LogDebug("PhysicalVolumeStore") << "Storing " << pvs_->size() << " items in the physical volume store";
  
  // Put our map into the run
  r.put( std::move(pvs_), myName() );

}

using artg4::PhysicalVolumeStoreService;
DEFINE_ART_SERVICE(PhysicalVolumeStoreService)