// ParticleGunAction.cc provides the implementation for an action object that 
// produces primary particles using a particle gun.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "gm2g4/pluginActions/particleGun/ParticleGunAction.hh"

// Other includes
// Note: I'm not certain that all of these are necessary.
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"

#include "g2GeneralParticleSource.hh"
#include "g2PreciseValues.hh"

#include <iostream>
#include <cmath>

using std::string;

// Constructor takes a parameter set, calls the base class's constructor, and
// initializes member data
gm2::ParticleGunAction::ParticleGunAction(fhicl::ParameterSet const & p)
  : ActionBase(p.get<string>("name", "particleGun")),
    // Initialize our general particle source using a sub-pset from the passed
    // parameters.
    g2GPS(new g2GeneralParticleSource(p.get<fhicl::ParameterSet>("g2GPS"))),
    // Initialize our message logger
    _logInfo("PARTICLEGUNACTION")
{}

// Destructor cleans up the general particle source
gm2::ParticleGunAction::~ParticleGunAction()
{
  delete g2GPS;
}

// Create a primary particle for an event!
// (Standard g-2 simulation)
void gm2::ParticleGunAction::GeneratePrimaries(cons G4Event * anEvent)
{
  // Everything is taken care of by the general particle source!
  g2GPS -> GeneratePrimaryVertex(anEvent);
}
