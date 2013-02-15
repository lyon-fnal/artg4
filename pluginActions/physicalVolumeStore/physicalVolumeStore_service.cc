// Physical Volume Store implementation

#include "artg4/pluginActions/physicalVolumeStore/physicalVolumeStore_service.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"

#include <iostream>

artg4::PhysicalVolumeStoreService::PhysicalVolumeStoreService(fhicl::ParameterSet const & p,
                                                art::ActivityRegistry& iRegistry)
  : RunActionBase(p.get<std::string>("name", "")),
    producerLabel_( p.get<std::string>("producerLabel", "artg4")),
    instanceLabel_( p.get<std::string>("instanceLabel", "")),
    pvs_( new artg4::PhysicalVolumeStoreData ),
    logInfo_("PhysicalVolumeStore")
{
  // Register our postBeginRun method
  iRegistry.watchPostBeginRun(this, &artg4::PhysicalVolumeStoreService::postBeginRun);
}

artg4::PhysicalVolumeStoreService::~PhysicalVolumeStoreService()
{ }


void artg4::PhysicalVolumeStoreService::callArtProduces(art::EDProducer* producer) {
  producer->produces< artg4::PhysicalVolumeStoreData, art::InRun>( myName() );
}

unsigned int artg4::PhysicalVolumeStoreService::idGivenPhysicalVolume(const G4VPhysicalVolume* pvptr ) {
  
  // Determine the id
  return pvs_->idGivenString( pvptr->GetName() );
}

void artg4::PhysicalVolumeStoreService::fillRunWithArtStuff(art::Run& r) {
  
  // Debug
  mf::LogDebug("PhysicalVolumeStore") << "Storing " << pvs_->size() << " items in the physical volume store";
  
  // Put our map into the run
  r.put( std::move(pvs_), myName() );

}

void artg4::PhysicalVolumeStoreService::postBeginRun(const art::Run& r) {

  // Let's see if the run record has the PhysicalVolumeStoreData (e.g. we're reading from a file)
  std::vector< art::Handle<artg4::PhysicalVolumeStoreData> > pvsHV;
  r.getManyByType(pvsHV);
  
  if ( ! pvsHV.empty() ) {
    // We found something in the run record. Let's see what it is.
    for ( auto aHandle : pvsHV ) {
      // Check the provenance for the handle
      art::Provenance const * prov = aHandle.provenance();
      
      // Check the module label
      if ( producerLabel_.empty() || producerLabel_ == prov->moduleLabel() ) {
        // Check the instance label
        if ( instanceLabel_.empty() || instanceLabel_ == prov->productInstanceName() ) {
          // This is it!
          mf::LogDebug("ParticleTrackAnalyzer") << "Getting PVS from Run record";
          
          // We now want to replace our PhysicalVolumeStoreData with this one.
          // We can't simply do a pvs_.reset(new Ptr) because the pointer we'll
          // get from the Run is const. So reset the contents
          pvs_->reset( *aHandle );
        }
      }
    }
  }
}

using artg4::PhysicalVolumeStoreService;
DEFINE_ART_SERVICE(PhysicalVolumeStoreService)