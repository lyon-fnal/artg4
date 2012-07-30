// Gm2PrimaryGeneratorAction.hh provides declarations for the built-in
// primary generator action for the g-2 simulation. In its main method, 
// GeneratePrimaries, it gets the collection of all action objects registered
// for the run and calls their GeneratePrimaries method.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef GM2_PGA_HH
#define GM2_PGA_HH

// G4 includes
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"

// Everything goes in the g-2 namespace
namespace gm2 {

  class Gm2PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public: 
    // Compiler-generated c'tor, d'tor, copy c'tor and equality operator are
    // fine - not much to this class!

    // Create the primary particles for the event. Called after a G4Event has
    // been created but not fully initialized.
    void GeneratePrimaries(G4Event *anEvent);

  };

}
#endif GM2_PGA_HH
