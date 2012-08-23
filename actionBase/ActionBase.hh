// This file is the header for the @ActionBase@ class.

// It is the lowest level base class for Geant user actions. Do not
// inherit from this class directly. Instead, use a next level up class, like
// @TrackingActionBase@.

// Include guard
#ifndef ACTION_BASE_HH
#define ACTION_BASE_HH

#include <string>
#include <iostream>
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"

// Declarations of types we use as input parameters

// Everything goes in the Art G4 namespace
namespace artg4 {

  class ActionBase {
  public:
    // Constructor. The derived class must call this constructor. It takes a 
    // single string for the name of the action object.
    ActionBase(std::string myName)
      : myName_( myName )
    {}

    // Destructor
    virtual ~ActionBase(){}

    // Accessor
    std::string myName() const {return myName_;}

    // h3. Optional methods
    
    // Call produces<T> to notify Art what you'll be adding to the Art event.
    void callArtProduces(art::EDProducer * producer){}

    // Fill the Art event with whatever you said you would, if you haven't
    // already. This is called by ActionHolder at the very end of the Art
    // event, after all the GEANT stuff is finished.
    // Note that if you need the Art event, you can get it from the 
    // ActionHolder using its @getCurrArtEvent()@ method.
    void fillEventWithArtHits(art::Event & e){}

  private:
    // A string containing this action object's name
    std::string myName_;
  };
}


#endif // ACTION_BASE_HH
