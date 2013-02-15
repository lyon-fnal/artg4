// The Physical Volume Store (was the Unique Object Manager)


// The idea here is that hit objects will contain IDs for volumes. To get the
// actual name of the volume, you query this object. You can also
// do a regular expression search for ID corresponding to a volume name.
//
// The ID in this case is the integer value of the pointer. We'd like to use
// @uintptr_t@ (from @csdtint@ header file) which is set in C++11, but Root
// may not have that. Instead, we'll follow the old g2migtrace and use
// Root's @ULong64_t@ from @TObject.h@
//
//
// Only volumes that are actually referred to are stored.
//
// Since volumes are set at Runtime, this UOM object is stored in the
// Run record and lives as a Run action so that it gets stored into the event.
//
// The UOM is actually a RunAction service so that it can write out data to the
// run record

#ifndef PHYSICALVOLUMESTORE_SERVICE_HH
#define PHYSICALVOLUMESTORE_SERVICE_HH

#include <map>
#include <string>
#include <memory>

#include "artg4/actionBase/RunActionBase.hh"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Core/EDProducer.h"

#include "artg4/pluginActions/physicalVolumeStore/PhysicalVolumeStoreData.hh"

#include "Geant4/G4VPhysicalVolume.hh"


namespace artg4 {
  
  typedef std::map< ULong64_t, std::string> pvMap;
  
  class PhysicalVolumeStoreService : public artg4::RunActionBase {
    
    public:
      PhysicalVolumeStoreService(fhicl::ParameterSet const&, art::ActivityRegistry&);
      virtual ~PhysicalVolumeStoreService();
    
      // PostBeginRun (fill the data if there is some in the run)
      void postBeginRun( art::Run const & r);
    
      // Prepare Art for our data
      virtual void callArtProduces(art::EDProducer * producer);
    
      // Get the UID and add to the map
      unsigned int idGivenPhysicalVolume(const G4VPhysicalVolume* pv);

      // Write out our data to the Run record
      virtual void fillRunWithArtStuff(art::Run& r);
    
      // Return the data itself
      const artg4::PhysicalVolumeStoreData& getData() const { return *pvs_; }
    
    private:
    
      // If we're getting the PhysicalVolumeStoreData from a file, use these
      // for the producer and instance labels
      std::string producerLabel_;
      std::string instanceLabel_;
    
      // The map
      std::unique_ptr<artg4::PhysicalVolumeStoreData> pvs_;
    
      // Message logger
      mf::LogInfo logInfo_;
  };
}

#endif  // UOM_HH
