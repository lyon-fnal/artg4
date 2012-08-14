# Core directory

# Contains the action objects, run manager, physics list, and generic
# detector construction class.

# Create a library called "artg4_core"
art_make(LIBRARIES "artg4_services_DetectorHolder_service" "artg4_services_ActionHolder_service" "artg4_geantInit")

# Install header files into the products area
install_headers() 
