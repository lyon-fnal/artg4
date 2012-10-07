// PrimaryGeneratorActionService is the service that injects particles into
// the simulation.
// To use this action, all you need to do is put it in the services section
// of the configuration file, like this:
// 
// services: { 
//   ...
//   user: {
//     PrimaryGeneratorActionService: {}
//     ...
//   }
// }

// Authors: Tasha Arvanitis, Adam Lyon
// Date: August 2012

// Include guard
#ifndef PRIMARYGENERATORACTION_SERVICE_HH
#define PRIMARYGENERATORACTION_SERVICE_HH

// Includes
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"

#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "art/Framework/Core/EDProducer.h"

#include "messagefacility/MessageLogger/MessageLogger.h"

#include "Geant4/G4Event.hh"
#include "Geant4/G4ParticleGun.hh"
#include "artg4/pluginActions/particleGun/GeneralParticleSource.hh"

// Get the base class
#include "artg4/actionBase/PrimaryGeneratorActionBase.hh"

namespace artg4 {

  class ParticleGunActionService : public PrimaryGeneratorActionBase {
  public: 
    ParticleGunActionService(fhicl::ParameterSet const&, 
				  art::ActivityRegistry&);
    virtual ~ParticleGunActionService();

    // To generate primaries, we need to overload the GeneratePrimaries
    // method. 
    virtual void generatePrimaries(G4Event * anEvent);    

    // We don't add anything to the event, so we don't need callArtProduces
    // or FillEventWithArtStuff.

  private:
    // Our particle source
    GeneralParticleSource * GPS_;

    // A message logger for this action
    mf::LogInfo logInfo_;
  };
}

#endif
