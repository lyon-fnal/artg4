// This file provides the implementation for an action object that produces
// the primary particles for the simulation.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: August 2012

#include "artg4/pluginActions/particleGun/ParticleGunAction_service.hh"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "artg4/services/ActionHolder_service.hh"

#include <iostream>

using std::string;

artg4::ParticleGunActionService::
ParticleGunActionService(fhicl::ParameterSet const & p, 
			 art::ActivityRegistry &)
  : PrimaryGeneratorActionBase(p.get<string>("name","particleGun")),
    // Initialize our general particle source using a sub-pset from the passed
    // parameters.
    GPS_(new GeneralParticleSource(p.get<fhicl::ParameterSet>("GPS"))),
    // Initialize our message logger
    logInfo_("ParticleGunAction")
{
  // Register ourselves with the ActionHolder
  art::ServiceHandle<ActionHolderService> actionHolder;

  actionHolder -> registerAction(this);
}

// Destructor
artg4::ParticleGunActionService::~ParticleGunActionService()
{
  delete GPS_;
}

// Create a primary particle for an event!
// (Standard Art G4 simulation)
void artg4::ParticleGunActionService::generatePrimaries(G4Event * anEvent)
{
  // Everything is taken care of by the general particle source!
  GPS_ -> GeneratePrimaryVertex(anEvent);
}

using artg4::ParticleGunActionService;
DEFINE_ART_SERVICE(ParticleGunActionService)
