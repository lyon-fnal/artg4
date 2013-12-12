# Core directory

# Contains the action objects, run manager, physics list, and generic
# detector construction class.

# Create a library called "artg4_core"
art_make(MODULE_LIBRARIES "artg4_geantInit" "${XERCESCLIB}" "${G4_LIB_LIST}" )

# Install header files into the products area
install_headers() 
