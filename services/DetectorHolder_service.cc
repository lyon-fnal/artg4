// For more comprehensive documentation, see DetectorHolderService.hh.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

//Includes
#include <iostream>

#include "artg4/services/DetectorHolder_service.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "messagefacility/MessageLogger/MessageLogger.h" 

#include "G4HCofThisEvent.hh"

// Save ourselves the trouble of typing 'std::' all the time
using std::string;
using std::map;
using std::pair;
using std::endl;

// Category for this file
static std::string msgctg = "DetectorHolderService";

// PUBLIC METHODS

// Constructor doesn't do anything with either of its passed components.
artg4::DetectorHolderService::DetectorHolderService(fhicl::ParameterSet const&,
				    art::ActivityRegistry&) :
  categoryMap_(),
  worldPV_(0)
{}

// Register a detector object with this service
void artg4::DetectorHolderService::registerDetector(DetectorBase *const db)
{
  LOG_DEBUG(msgctg) << "Registering detector named " << db->myName() << ".\n";
  addDBtoCategoryMap(db);
}

// Get the physical volume for the world/lab in the simulation
G4VPhysicalVolume * artg4::DetectorHolderService::worldPhysicalVolume()
{
  // Check if we have a world yet.
  if (0 == worldPV_) {
    // We don't - let's construct all the physical volumes.
    constructAllPVs();

    // Check whether we have a world at this point. If not, we have a problem.
    if (0 == worldPV_) {
      throw cet::exception("DetectorHolderService") << "No world volume "
						    << "constructed!\n";
    }
  }
  // If we reach this point, the world volume exists, so let's return it!
  return worldPV_;
  
}

// Set up all the detectors' LVs
void artg4::DetectorHolderService::constructAllLVs()
{
  // Let's loop over the detectors in the map
  for (std::map<std::string, DetectorBase*>::iterator itr = 
	 categoryMap_.begin();
       itr != categoryMap_.end(); 
       ++itr ) {
    LOG_DEBUG(msgctg) << "Constructing logical volumes for detector of "
		      << "category " << itr->second->category();

    itr -> second -> buildLVs();
  }
}

// Set up all the detectors' PVs
void artg4::DetectorHolderService::constructAllPVs()
{
  // Let's loop over the detectors in the map
  for (std::map<std::string, DetectorBase*>::iterator itr = 
	 categoryMap_.begin();
       itr != categoryMap_.end(); 
       ++itr ) {
    LOG_DEBUG(msgctg) << "Constructing physical volumes for detector of "
		      << "category " << itr->second->category();

    placeDetector(itr -> second);
  } 
}

// Get a specific detector, given a category string.
artg4::DetectorBase * artg4::DetectorHolderService::
getDetectorForCategory(std::string category) const
{
  map<string,DetectorBase*>::const_iterator categoryDB = 
    categoryMap_.find(category);
  if (categoryDB != categoryMap_.end()) {
    // We have a detector of that category
    return categoryDB -> second;
  }
  else {
    // We don't have a detector of that category - problem!
    throw cet::exception("DetectorHolderService") 
      << "No detector found for category "
      << category << ".\n";
  }
}

// Get the parameter set for a detector given its category string
fhicl::ParameterSet const 
artg4::DetectorHolderService::getParametersForCategory(std::string category)
{
  return getDetectorForCategory(category) -> parameters();
}

// Tell the detectors to tell Art what they produce
void artg4::DetectorHolderService::callArtProduces(art::EDProducer * prod)
{
  // Let's loop over the detectors in the map
  for (std::map<std::string, DetectorBase*>::iterator itr = 
	 categoryMap_.begin();
       itr != categoryMap_.end(); 
       ++itr ) {
    LOG_DEBUG(msgctg) << "Calling art produces for category " 
		      << itr->second->category();
    itr -> second -> callArtProduces(prod);
  }
}

// Convert geant hits to art hits for all detectors
void artg4::DetectorHolderService::fillEventWithArtHits(G4HCofThisEvent* hc) 
{
  // Let's loop over the detectors in the map
  for (std::map<std::string, DetectorBase*>::iterator itr = 
	 categoryMap_.begin();
       itr != categoryMap_.end(); 
       ++itr ) {
    LOG_DEBUG(msgctg) << "Converting hits for category " 
		      << itr->second->category();
    itr -> second -> fillEventWithArtHits(hc);
  }
}

// PRIVATE METHODS

// Add a detector base object to our collection of registered detectors
void artg4::DetectorHolderService::addDBtoCategoryMap(DetectorBase * const db)
{
  if (0 == categoryMap_.count( db -> category() )) {
    // This DB isn't already in the map - let's add it!
    pair<string, DetectorBase *> itemToAdd(db -> category(), db);
    categoryMap_.insert(itemToAdd);
    LOG_DEBUG(msgctg) << "Registered detectory with category: " << db->category() << ".\n";
  }
  else {
    // We already have one of these detectors - something serious is wrong.
    throw cet::exception("DetectorHolderService") 
      << "Duplicate detector found. "
      << "There are at least two detectors found with category "
      << db -> category() << ".\n";
  }
}

// Find a detector's mother logical volume and pass it to the detector to 
// allow it to create its own physical volume.
void artg4::DetectorHolderService::placeDetector(DetectorBase * const db)
{
  // Check if we're dealing with the world volume first.
  if ( 0 == (db -> category()).compare("world") ) {
    // The world's mother 'logical volume' is an empty vector.
    worldPV_ = (db -> placeToPVs( std::vector<G4LogicalVolume*>() ))[0];
    LOG_DEBUG(msgctg) << "Just placed detector with category: " 
		      << db->category() 
		      << ".\n";
    return;
  }

  // Deal with non-world detectors
  map<string, DetectorBase *>::iterator motherCategoryDB = 
    categoryMap_.find(db -> motherCategory());

  if (motherCategoryDB != categoryMap_.end()) {
    // We have a parent volume - pass the DB its mother volume and call place.
    db->placeToPVs(motherCategoryDB -> second -> lvs());
    // Success!
    LOG_DEBUG(msgctg) << "Just placed detector with category: " 
		      << db->category() 
		      << ".\n";
    return;

  }
  // If we reach this point, we're missing a detector - throw an exception.
  throw cet::exception("DetectorHolderService") 
    << "No mother volume found for detector with category " 
    << db -> category() << ", which wanted a mother of category "
    << db -> motherCategory() << ". This probably means you are missing a "
    << "detector class (derived from DetectorBase).\n";

  // Finding the mother volume failed.
  return;
}

// Register the service with Art
using artg4::DetectorHolderService;
DEFINE_ART_SERVICE(DetectorHolderService)
