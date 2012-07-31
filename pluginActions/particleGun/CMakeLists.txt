# Particle Gun directory CMakeLists.txt

art_make( LIBRARIES "artg4_Core" )

# create library called artg4_pluginactions_particlegun
#cet_make( LIBRARY_NAME artg4_pluginactions_particlegun )

# install header files into the products area
install_headers()

# Set up our producer module, too!
# set(particleGun_libs ${allG4Libs})
# find_library(XERCESC NAMES xerces-c PATHS $ENV{XERCESCROOT}/lib NO_DEFAULT_PATH )
# list(APPEND particleGun_libs ${XERCESC} "artg4_core")
# simple_plugin(particleGunAction "module" "${particleGun_libs}")