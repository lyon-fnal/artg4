# port/src/services CMakeLists

# This directory contains artg4's Art services
# For each service in this directory, you need a line like the below

# We apparently need xerces_c for a geant library
find_library( XERCESC  NAMES xerces-c PATHS $ENV{XERCESCROOT}/lib NO_DEFAULT_PATH )

# For each service, we need to:
#   - Build a list of libraries. (Note: allG4Libs comes from find_ups_geant
#     macro.)
#   - Add the above-declared XERCESC to this list, along with any other 
#     dependencies.
#   - Set up the service

# Note that to use a service in a simulation run, it must be listed in the
# FHiCL configuration file: 'services: { user: { <servicename>:{} }}'

# For the DetectorHolder service, with which geometry components register, and
# which takes care of geometry construction...
set(DetectorHolder_libs ${allG4Libs})
list(APPEND DetectorHolder_libs ${XERCESC} "artg4_core")
simple_plugin(DetectorHolder "service" "${DetectorHolder_libs}")

# And for the Materials service, which provides materials when they're needed.
set(MaterialService_libs ${allG4Libs})
list(APPEND MaterialService_libs ${XERCESC})
simple_plugin(MaterialService "service" "${MaterialService_libs}")

# For the GlobalParameters service, which holds on to a set of parameters 
# needed globally.
set(GlobalParameters_libs ${allG4Libs})
list(APPEND GlobalParameters_libs ${XERCESC})
simple_plugin(GlobalParameters "service" "${GlobalParameters_libs}")