// This file is the header for the @DetectorBase@ class.

// h2. Introduction

// @DetectorBase@ enforces an interface for the construction and handling of Geant4 detectors. 

// All _ArtG4_ detector objects MUST inherit from this @DetectorBase@ class. 

// For your detector to work, you must override the following methods:

// * @doBuildLVs@ - This private method, which takes no arguments, constructs the detector logical volume and returns a pointer to it. The system takes over ownership of this pointer. 

// * @doPlaceToPVs@ - This private method takes the mother logical volumes as an argument and performs the functions necessary to place this detector within it. This method then returns a pointer to the resulting physical volume. The system takes over ownership of this pointer. 

// * @doConvertGeantHitsToArtHits@ - This private method is optional, but is necessary if your detector produces hits. Its argument is the G4 Hit collection for this event. You then write code (or perhaps use a script that writes the code for you) to convert the Geant hits into corresponding Art hits. Your class must hold on to these generated Art hits for retrieval later on by the system. 

// * @doPutArtHitsInEvent@ - This private method is optional, but is necessary if your detector produces hits. It is not declared in this header of @DetectorBase@ because it is specific to the Art module corresponding to this detector. It should return the Art hit vector of the appropriate type. 

// See below for information about each method. Note that many of them you never
// call yourself. 

// h2. Code

// Header Guard

#ifndef ARTG4_DETECTORBASE_HH
#define ARTG4_DETECTORBASE_HH

// STL includes
#include <vector>

// Art includes
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Principal/Event.h"

// Forward referencing
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4HCofThisEvent;

// h3. Declare the @DetectorBase@ class

// All offical Art G4 specific code goes into the @artg4@ namespace
namespace artg4 {
  
  class DetectorBase {
    
  // h3. Public members
  
  public:
    
    // Constructor. Your derived class must call this 
    // constructor. This base class constructor takes,
    // * The parameter set for the corresponding Art producer module
    // * The name of this detector
    // * The category of this detector
    // * The category of the mother volume that this detector is placed within ("world" if world)
    DetectorBase(
                 fhicl::ParameterSet const& p,
                 std::string myName, std::string category, 
                 std::string motherCategory ) :
        _myParams(fhicl::ParameterSet(p)),
        _myName( myName ),
        _category( category ),
        _motherCategory( motherCategory),
        _myLVs(0),
        _myPVs(0)
    {}
  
    // Destructor
    virtual ~DetectorBase(){}
  
    // Build and store the logical volume (calls your @doBuild@ method). You 
    // do not need to call this method yourself. 
    void buildLVs() {
      _myLVs = doBuildLVs();
    }
    
    // Place the detector in the mother volumen and store and return the 
    // physical volume (calls your @doPlaceToPVs@ method). You do not need to call
    // this method yourself.   
    std::vector<G4VPhysicalVolume*> placeToPVs( 
                                    std::vector<G4LogicalVolume*> motherLVs ) {
      _myPVs = doPlaceToPVs( motherLVs );
      return _myPVs;
    }
  

    // Convert geant hits into Art hits. Calls your @doConvertGeantToArtHits@
    void convertGeantToArtHits(G4HCofThisEvent * hc) {
      doConvertGeantToArtHits(hc);
    }
    
    // Put the Art hits into the event. Calls your @doPutArtHitsInEvent@
    void putArtHitsIntoEvent( art::Event& e) {
      doPutArtHitsIntoEvent( e );
    }


    // h3. Accessors

    // Return this detector's Geant Physical Volume
    std::vector<G4VPhysicalVolume*> pvs() const { return _myPVs; }
    
    // Return this detector's Geant Logical Volume
    std::vector<G4LogicalVolume*> lvs() const { return _myLVs; }

    // Return the name of this detector
    std::string myName() const { return _myName; }
    
    // Return the category of this detector
    std::string category() const { return _category; }
    
    // Returnh the mother category for this detector
    std::string motherCategory() const {return _motherCategory; }
    
    // Return the parameter set for this detector
    fhicl::ParameterSet parameters() const {return _myParams; }
        
  private:
    
    // h3. Private abstract methods you must override (see list above)

    // Build the detector logical volume and return it
    virtual std::vector<G4LogicalVolume*> doBuildLVs() = 0;

    // Place the detector within the passed in mother logical volume and return
    // the resulting physical volume
    virtual std::vector<G4VPhysicalVolume*> doPlaceToPVs( 
                                std::vector<G4LogicalVolume*> motherLV ) = 0;
    
    // h3. Optional private methods you can override (see list above)
    
    // Convert the Geant4 hits into Art hits. You store the Art hits in your class
    virtual void doConvertGeantToArtHits(G4HCofThisEvent* hc) {}
    
    // Put the Art hits into the Event
    virtual void doPutArtHitsIntoEvent( art::Event& e ) {}
  
    
    // h3. Private data
    
    // The parameters from the corresponding producer module
    fhicl::ParameterSet _myParams;
    
    // The detector name
    std::string _myName;
    
    // The detector category
    std::string _category;
    
    // The detector mother category
    std::string _motherCategory;
    
    // The detector's Geant logical volumes
    std::vector<G4LogicalVolume*> _myLVs;
    
    // The detectors's Geant physical volumes
    std::vector<G4VPhysicalVolume*> _myPVs;

  };
}

#endif
