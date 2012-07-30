// EventArtHit is an art-friendly hit class that records how many times
// the muon in question circled the storage ring, and describes whether it 
// was considered 'stored'

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef EVENT_ART_HIT_HH
#define EVENT_ART_HIT_HH

// An include
#include <vector>

// Everything goes in g-2 namespace
namespace gm2 {
  // Begin class declaration
  class EventArtHit {
  public: 
    // Default constructor
    EventArtHit() :
      _turns(0),
      _muonWasStored(false)
    {}

    // More specific constructor
    EventArtHit(int turns, bool muWasStored) :
      _turns(turns),
      _muonWasStored(muWasStored)
    {}
    
    // Set the number of turns
    void setTurns(int turns)
    {
      _turns = turns;
    }

    // Set muon storage status
    void setMuWasStored(bool muWasStored)
    {
      _muonWasStored = muWasStored;
    }

  private:
    // Class members
    int _turns;
    bool _muonWasStored;
  };

  // Define a collection of EventArtHits
  typedef std::vector<EventArtHit> EventArtHitCollection;
}

#endif
