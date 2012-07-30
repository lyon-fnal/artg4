// Provides the implementation for the @ActionHolder@ service.
// For more comprehensive documentation, see the header file ActionHolder.hh

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Includes
#include "gm2g4/art/ActionHolder.hh"

#include "art/Framework/Services/Registry/ServiceMacros.h"

// Don't type 'std::' all the time...
using std::string;
using std::map;
using std::pair;

// Constructor doesn't do much with the passed arguments, but does initialize
// the logger for the service
gm2::ActionHolder::ActionHolder(fhicl::ParameterSet const&,
				art::ActivityRegistry&) :
  _logInfo("ACTIONHOLDER")
{}

// Register an action object with the service.
void gm2::ActionHolder::registerAction(ActionBase * const action)
{
  // Note that we're registering the action
  _logInfo << "Registering action named " << action -> myName() << ".\n";
  
  // Check whether we have an action with the same name already
  if (0 == _actionMap.count( action -> myName() )) {
    // This action isn't already in the map - let's add it!
    pair<string, ActionBase *> itemToAdd(action -> myName(), action);
    
    _actionMap.insert(itemToAdd);
  }
  else {
    // We already have one of these detectors - something serious is wrong.
    throw cet::exception("ACTIONHOLDER") 
      << "Duplicate action found. "
      << "There are at least two actions found named "
      << action -> myName() << ".\n";
  }
}

// Return the map of registered actions. Key: name (string). Value: pointer to
// action object (ActionBase *)
inline map<string, ActionBase *> const & gm2::ActionHolder::getActions() const
{
  return _actionMap;
}

// Return a pointer to the action object described by the given name, or throw
// an exception if there isn't one.
gm2::ActionBase * gm2::ActionHolder::getActionByName(string name)
{
  // Check if we have an action with the given name
  map<string, ActionBase*>::iterator actionIter = _actionMap.find(name);
  if (actionIter != _actionMap.end()) {
    // We have a detector with that name
    return actionIter -> second;
  }
  else {
    // We don't have a detector with that name - problem!
    throw cet::exception("ACTIONHOLDER") << "No action found with name "
					 << name << ".\n";
  }
}
