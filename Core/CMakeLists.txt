# Core directory

# Contains the action objects, run manager, physics list, and generic
# detector construction class.

# Create a library called "artg4_core"
art_make(LIBRARIES ${ART_SERVICES_LIB} "artg4_geantInit")

# Install header files into the products area
install_headers() 
