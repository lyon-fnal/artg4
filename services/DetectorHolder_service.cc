// For more comprehensive documentation, see DetectorHolder.hh.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

//Includes
#include <iostream>

#include "artg4/services/DetectorHolder.hh"

#include "art/Framework/Services/Registry/ServiceMacros.h"


// Save ourselves the trouble of typing 'std::' all the time
using std::string;
using std::map;
using std::pair;
using std::endl;

// PUBLIC METHODS

// Constructor doesn't do anything with either of its passed components.
artg4::DetectorHolder::DetectorHolder(fhicl::ParameterSet const&,
				    art::ActivityRegistry&) :
  _worldPV(0),
  _logInfo("DetectorHolder")
{}

// Register a detector object with this service
void artg4::DetectorHolder::registerDetector(DetectorBase *const db)
{
  _logInfo << "Registering detector named " << db->myName() << ".\n";
  addDBtoCategoryMap(db);

  // See if we have the mother volume for this new detector. If so, place db.
  placeDetector(db);
}

// Get the physical volume for the world/lab in the simulation
G4VPhysicalVolume * artg4::DetectorHolder::worldPhysicalVolume() const
{
  // Check if we have a world yet.
  if (0 == _worldPV) {
    // We don't - this is a problem.
    throw cet::exception("DetectorHolder") << "No world volume found!\n";
    return NULL;
  }
  // If we reach this point, the world volume exists, so let's return it!
  return _worldPV;
  
}

// Get a collection of the detectors registered for this run
std::map<std::string, artg4::DetectorBase*> const &
      artg4::DetectorHolder::getDetectorMap() const 
{
  return _categoryMap;
}

// Get a specific detector, given a category string.
artg4::DetectorBase * artg4::DetectorHolder::getDetectorForCategory(std::string 
							   category) const
{
  map<string,DetectorBase*>::const_iterator categoryDB = 
    _categoryMap.find(category);
  if (categoryDB != _categoryMap.end()) {
    // We have a detector of that category
    return categoryDB -> second;
  }
  else {
    // We don't have a detector of that category - problem!
    throw cet::exception("DetectorHolder") << "No detector found for category "
					   << category << ".\n";
  }
}

// Get the parameter set for a detector given its category string
fhicl::ParameterSet const 
      artg4::DetectorHolder::getParametersForCategory(std::string category)
{
  return getDetectorForCategory(category) -> parameters();
}

// PRIVATE METHODS

// Add a detector base object to our collection of registered detectors
void artg4::DetectorHolder::addDBtoCategoryMap(DetectorBase * const db)
{
  if (0 == _categoryMap.count( db -> category() )) {
    // This DB isn't already in the map - let's add it!
    pair<string, DetectorBase *> itemToAdd(db -> category(), db);
    
    _categoryMap.insert(itemToAdd);
  }
  else {
    // We already have one of these detectors - something serious is wrong.
    throw cet::exception("DetectorHolder") 
      << "Duplicate detector found. "
      << "There are at least two detectors found with category "
      << db -> category() << ".\n";
  }
}

// Find a detector's mother logical volume and pass it to the detector to 
// allow it to create its own physical volume.
bool artg4::DetectorHolder::placeDetector(DetectorBase * const db)
{
  // Check if we're dealing with the world volume first.
  if ( 0 == (db -> category()).compare("world") ) {
    // The world's mother 'logical volume' is an empty vector.
    _worldPV = (db -> placeToPVs( std::vector<G4LogicalVolume*>() ))[0];
    _logInfo << "Just placed detector with category: " << db->category() 
	     << ".\n";
    return true;
  }

  // Deal with non-world detectors
  map<string, DetectorBase *>::iterator motherCategoryDB = 
    _categoryMap.find(db -> motherCategory());

  if (motherCategoryDB != _categoryMap.end()) {
    // We have a parent volume - pass the DB its mother volume and call place.
    db->placeToPVs(motherCategoryDB -> second -> lvs());
    // Success!
    _logInfo << "Just placed detector with category: " << db->category() 
	     << ".\n";
    return true;

  }
  // If we reach this point, there's a problem with the ordering of detector
  // registration, and we need to throw an exception.
  throw cet::exception("DetectorHolder") 
    << "No mother volume found for detector with category " 
    << db -> category() << ", which wanted a mother of category "
    << db -> motherCategory() << ". This means you are either missing a "
    << "detector class (derived from DetectorBase) or you've listed the "
    << "detector modules in the wrong order - mother volumes must always "
    << "be registered before their daughters.\n";

  // Finding the mother volume failed.
  return false;
}

// Register the service with Art
using artg4::DetectorHolder;
DEFINE_ART_SERVICE(DetectorHolder)
