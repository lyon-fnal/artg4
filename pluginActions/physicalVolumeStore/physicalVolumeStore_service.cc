// Physical Volume Store implementation

#include "artg4/pluginActions/physicalVolumeStore/physicalVolumeStore_service.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"

#include <iostream>

artg4::PhysicalVolumeStore::PhysicalVolumeStore(fhicl::ParameterSet const & p,
                                                art::ActivityRegistry&)
  : RunActionBase(p.get<std::string>("name", "PhysicalVolumeStore")),
    pvMap_( new pvMap ),
    logInfo_("PhysicalVolumeStore")
{ }

artg4::PhysicalVolumeStore::~PhysicalVolumeStore()
{ }


void artg4::PhysicalVolumeStore::callArtProduces(art::EDProducer* producer) {
  producer->produces<pvMap, art::InRun>();
}

ULong64_t artg4::PhysicalVolumeStore::uidForPhysicalVolume(const G4VPhysicalVolume* pvptr ) {
  
  // Determine the UID
  ULong64_t uid = reinterpret_cast<ULong64_t>( pvptr );
  
  // Do we already have it?
  auto pvIter = pvMap_->find(uid);
  if ( pvIter == pvMap_->end() ) {
    // Don't have it already -- add it
    pvMap_->insert( std::pair< ULong64_t, std::string>( uid, pvptr->GetName() ) );
    std::cout << "Adding " << uid << " : " << pvptr->GetName() << std::endl;
  }
  
  return uid;
}

void artg4::PhysicalVolumeStore::fillRunWithArtStuff(art::Run& r) {
  std::cout << "Before r.put" << std::endl;
  
  // Put our map into the run
  r.put( std::move(pvMap_) );

  std::cout << "After r.put" << std::endl;

}

using artg4::PhysicalVolumeStore;
DEFINE_ART_SERVICE(PhysicalVolumeStore)