// Provides the implementation for the @ActionHolder@ service.
// For more comprehensive documentation, see the header file ActionHolder.hh

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Includes
#include "artg4/services/ActionHolder.hh"

#include "art/Framework/Services/Registry/ServiceMacros.h"

// Don't type 'std::' all the time...
using std::string;
using std::map;
using std::pair;

// Constructor doesn't do much with the passed arguments, but does initialize
// the logger for the service
artg4::ActionHolder::ActionHolder(fhicl::ParameterSet const&,
				art::ActivityRegistry&) :
  _logInfo("ACTIONHOLDER")
{}

// Register an action object with the service.
void artg4::ActionHolder::registerAction(ActionBase * const action)
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
inline map<string, artg4::ActionBase *> const & artg4::ActionHolder::getActionMap() const
{
  return _actionMap;
}

// Return a pointer to the action object described by the given name, or throw
// an exception if there isn't one.
artg4::ActionBase const * artg4::ActionHolder::getActionByName(string name) const
{
  // Check if we have an action with the given name
  map<string, ActionBase*>::const_iterator actionIter = _actionMap.find(name);
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

// Register the service with Art
using artg4::ActionHolder;
DEFINE_ART_SERVICE(ActionHolder)
