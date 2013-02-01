// classes.h

#include <map>
#include <string>
#include "TObject.h"

#include "art/Persistency/Common/Wrapper.h"

// Template the map
template class std::map< ULong64_t, std::string >;

// Template the wrapper for the vector (typedef okay)
template class art::Wrapper< std::map< ULong64_t, std::string > >;
