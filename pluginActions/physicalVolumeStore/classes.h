// classes.h

#include <map>
#include <string>
#include "TObject.h"

#include "art/Persistency/Common/Wrapper.h"

// For StringIDs
#include "artg4/pluginActions/physicalVolumeStore/PhysicalVolumeStoreData.hh"
template class art::Wrapper<artg4::PhysicalVolumeStoreData>;
template class art::Wrapper<artg4::StringIDs>;
