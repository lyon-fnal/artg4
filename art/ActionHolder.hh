// Declarations for the @ActionHolder@ Art service.

// @ActionHolder@ is a globally-accessible service that manages the action
// objects for a simulation. An action object has a multitude of hooks into
// various points during event creation and processing. All action objects
// must be registered with this service in order to function. 

// Any class can @#include@ and access the @ActionHolder@ service to get either
// a collection of registered action objects or a specific action object given
// a name.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef ACTION_HOLDER_HH
#define ACTION_HOLDER_HH

// Includes
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "gm2g4/Core/ActionBase.hh"

#include <map>

// Everything for the g-2 simulation goes in the @gm2@ namespace
namespace gm2 {
  
  class ActionHolder {
  public:
    // Constructor for ActionHolder
    ActionHolder(fhicl::ParameterSet const &, art::ActivityRegistry&);

    // This method registers the passed action object with the service,
    // which solely entails adding it to the map of action objects (and throwing
    // and exception if there's already an action object registered with the
    // same name.
    void registerAction(ActionBase * const action);

    // This returns the map of registered actions, with a string as a key and 
    // an action object as the corresponding value.
    std::map<std::string, ActionBase *> const & getActions() const;

    // This returns a pointer to the ActionBase with the given name. If the 
    // specified action was never registered, it throws an exception.
    ActionBase * getActionByName(std::string name) const;

  private:
    // A collection of all our actions, arranged by name
    std::map<std::string, ActionBase*> _actionMap;

    // A message logger
    mf::LogInfo _logInfo;
  };
}

#endif // ACTION_HOLDER_HH
