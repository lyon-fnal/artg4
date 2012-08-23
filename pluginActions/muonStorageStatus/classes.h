// classes.h    
// This file is required by Art in order to store an EventArtHit or
// EventArtHitCollection in ROOT. 

// Authors: Tasha Arvanitis, Adam Lyon  
// Date: July 2012

// Includes
#include <vector>

#include "art/Persistency/Common/Wrapper.h"

#include "artg4/pluginActions/muonStorageStatus/EventArtHit.hh"

// Template the vector (don't use typedef)
template class std::vector< artg4::EventArtHit >;

// Template the wrapper for the vector (typedef okay)
template class art::Wrapper< artg4::EventArtHitCollection >;
