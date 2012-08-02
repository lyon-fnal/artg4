// This file provides the declarations and definitions of the 
// @GlobalParameters@ service. 

// @GlobalParameters@ is designed to hold a set of parameters that are needed
// by a variety of detectors, geometries, or other classes across the 
// simulation. For instance, spin tracking must be either on or off across
// all the magnetic field

// Header guard
#ifndef GLOBAL_PARAMETERS_CC
#define GLOBAL_PARAMETERS_CC

// Necessary includes
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"

// Everything goes in a namespace: artg4
namespace artg4 {
  // Begin class declaration
  class GlobalParameters {
  public:
    // Constructor just takes the parameter set and holds on to a copy.
    GlobalParameters(fhicl::ParameterSet const& pset, 
		     art::ActivityRegistry &)
    // Use ParameterSet copy constructor to create a new ParameterSet, since
    // the one passed in disappears shortly after the end of the constructor
      : _myParams(fhicl::ParameterSet(pset))
    {}
    
    // Accessor sends the global parameters off to whoever requested them
    fhicl::ParameterSet getGlobals() { return _myParams; }

  // Our member data
  private:
    fhicl::ParameterSet _myParams;

  };
}

#endif // GLOBAL_PARAMETERS_CC
