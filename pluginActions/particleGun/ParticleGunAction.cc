// ParticleGunAction.cc provides the implementation for an action object that 
// produces primary particles using a particle gun.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "artg4/pluginActions/particleGun/ParticleGunAction.hh"

// Other includes
// Note: I'm not certain that all of these are necessary.
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"

#include "GeneralParticleSource.hh"

#include <iostream>
#include <cmath>

using std::string;

// Constructor takes a parameter set, calls the base class's constructor, and
// initializes member data
artg4::ParticleGunAction::ParticleGunAction(fhicl::ParameterSet const & p)
  : ActionBase(p.get<string>("name", "particleGun")),
    // Initialize our general particle source using a sub-pset from the passed
    // parameters.
    GPS(new GeneralParticleSource(p.get<fhicl::ParameterSet>("GPS"))),
    // Initialize our message logger
    _logInfo("PARTICLEGUNACTION")
{}

// Destructor cleans up the general particle source
artg4::ParticleGunAction::~ParticleGunAction()
{
  delete GPS;
}

// Create a primary particle for an event!
// (Standard Art G4 simulation)
void artg4::ParticleGunAction::GeneratePrimaries(G4Event * anEvent)
{
  // Everything is taken care of by the general particle source!
  GPS -> GeneratePrimaryVertex(anEvent);
}
