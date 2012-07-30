// This file is the header for the @DetectorBase@ class.

// There is no implementation file since it is an abstract base class.

// All @ArtG4@ detector objects MUST inherit from this @DetectorBase@ class. 

// For your detector to work, you must override the following methods:

// * @build@ - This method, which takes no arguments, constructs the detector logical volume and returns a pointer to it. The system takes over ownership of this pointer. 

// * @place@ - This method takes the mother logical volume as an argument and performs the functions necessary to place this detector within it. This method then returns a pointer to the resulting physical volume. The system takes over ownership of this pointer. 

// * @convertGeantHitsToArtHits@ - This method is optional, but is necessary if your detector produces hits. Its argument is the G4 Hit collection for this event. You then write code (or perhaps use a script that writes the code for you) to convert the Geant hits into corresponding Art hits. Your class must hold on to these generated Art hits for retrieval later on by the system. 

// * @getArtHits@ - This method is optional, but is necessary if your detector produces hits. It is not declared in this header of @DetectorBase@ because it is specific to the Art module corresponding to this detector. It should return the Art hit vector of the appropriate type. 

// See below for information about each method. Note that many of them you never
// call yourself. 

// Header Guard

#ifndef artg4_detectorBase_hh
#define artg4_detectorBase_hh

// STL includes
#include <vector>

// Art includes

#include "fhiclcpp/ParameterSet.h"

// Geant includes

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4HCofThisEvent.hh"

// Declare the @DetectorBase@ class

// All offical Art G4 specific code goes into the @artg4@ namespace
namespace artg4 {
  
  class DetectorBase {
  
  public:
    
    // Constructor. Your derived class must call this 
    // constructor. The base class constructor takes,
    // * The parameter set for the corresponding Art producer module
    // * The name of this detector
    // * The category of this detector
    // * The category of the mother volume (that this detector is placed within)
    DetectorBase(
                 fhicl::ParameterSet const& p,
                 std::string myName, std::string category, 
                 std::string motherCategory ) :
        _myParams(fhicl::ParameterSet(p)),
        _myName( myName ),
        _category( category ),
        _motherCategory( motherCategory)
    {}
  
    // Destructor
    virtual ~DetectorBase(){}
  
    // Build and store the logical volume (calls your @build@ method). You 
    // do not need to call this method yourself. 
    void buildLVs() {
      _myLVs = build();
    }
    
    // Place the detector in the mother volumen and store and return the 
    // physical volume (calls your @place@ method). You do not need to call
    // this method yourself.   
    std::vector<G4VPhysicalVolume*> placeToPVs( 
                                    std::vector<G4LogicalVolume*> motherLVs ) {
      _myPVs = place( motherLVs );
      return _myPVs;
    }
  

    // Convert geant hits into Art hits. You need to override this method
    // if your detector generates hits. You must store the hits in your 
    // derived object.
    virtual void convertGeantToArtHits(G4HCofThisEvent *) {}


    // h3. Accessors

    // Return this detector's Geant Physical Volume
    std::vector<G4VPhysicalVolume*> pvs() const { return _myPVs; }
    
    // Return this detector's Geant Logical Volume
    std::vector<G4LogicalVolume*> lvs() const { return _myLVs; }

    // Return the name of this detector
    std::string myName() const { return _myName; }
    
    // Return the category of this detector
    std::string category() const { return _category; }
    
    // Returh the mother category for this detector
    std::string motherCategory() const {return _motherCategory; }
    
    // Return the parameter set for this detector
    fhicl::ParameterSet parameters() const {return _myParams; }
    
    // h3. Abstract methods you must override (see list above)
    
    // Build the detector logical volume and return it
    virtual std::vector<G4LogicalVolume*> build() = 0;

    // Place the detector within the passed in mother logical volume and return
    // the resulting physical volume
    virtual std::vector<G4VPhysicalVolume*> place( 
                                std::vector<G4LogicalVolume*> motherLV ) = 0;
  

  private:
    
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
