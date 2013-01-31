// The Universal Object Manager (UOM)

// The univeral object manager basically takes a map with ID as the key and
// string as the value


// The idea here is that hit objects will contain IDs for volumes To get the
// actual name of the volume, you query this object. You can also
// do a regular expression search for ID corresponding to a volume name.
//
// Only volumes that are actually referred to are stored.
//
// Since volumes are set at Runtime, this UOM object is stored in the
// Run record and lives as a Run action so that it gets stored into the event.
//

#ifndef UOM_HH
#define UOM_HH

namespace artg4 {
  class UniqueObjectManager {
    
    
  }
}

#endif  // UOM_HH
