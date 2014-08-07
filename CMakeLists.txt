#  This file is the main CMakeLists.txt file for the @artg4@ package. It is used by the g-2 build system.
# h2. Introduction 

# h2. Main code

# Ensure we are using a moden version of CMake
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# h3. Project definition

# --> Define the name of this project (replace @gm2artexamples@ with your 
# project name - use all lowercase)
PROJECT (artg4)

# h3. Load CMake modules
set( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
if( NOT CETBUILDTOOLS_VERSION )
  message( FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules" )
endif()
set( CMAKE_MODULE_PATH $ENV{CETBUILDTOOLS_DIR}/Modules ${CMAKE_MODULE_PATH} )

# art contains cmake modules that we use
set( ART_VERSION $ENV{ART_VERSION} )
if( NOT ART_VERSION )
  message( FATAL_ERROR "ERROR: setup art to get the cmake modules" )
endif()
set( CMAKE_MODULE_PATH $ENV{ART_DIR}/Modules ${CMAKE_MODULE_PATH} )

# Include the necessary macros
include(CetCMakeEnv)
include(BuildPlugins)
include(ArtMake)
include(FindUpsGeant4)

# h3. Configure this product

# Configure
cet_cmake_env()

#set_install_root()

# Do the same compiler flag stuff as Art
cet_set_compiler_flags(DIAGS VIGILANT WERROR 
   EXTRA_FLAGS -pedantic
   EXTRA_CXX_FLAGS -std=c++11
)

cet_report_compiler_flags()


# Locate some UPS areas (the versions are just minimum required) and setup include paths
# These are needed for Art stuff

find_ups_product(cetbuildtools v3_13_00)
find_ups_geant4( v4_9_6_p03 )
find_ups_product(xerces_c v3_1_1)
find_ups_product(art v1_10_00)
find_ups_product(fhiclcpp v2_19_05)
find_ups_product(messagefacility v1_11_10)

# Enable visualization using OpenGL in x windows
add_definitions(-DG4_STORE_TRAJECTORY -DG4VERBOSE -DG4UI_USE -DG4VIS_USE -DG4UI_USE_TCSH -DG4INTY_USE_XT -DG4VIS_USE_OPENGLX -DG4VIS_USE_OPENGL)

# We need xerces_c for a geant library
#find_library( XERCESCLIB  NAMES xerces-c PATHS $ENV{XERCESCROOT}/lib NO_DEFAULT_PATH )

# Macros for art_make and simple plugins
include(ArtDictionary)


# Build these directories
add_subdirectory( geantInit )
add_subdirectory( actionBase )
add_subdirectory( Core  )
add_subdirectory( services )
add_subdirectory( material )
add_subdirectory( pluginActions )
add_subdirectory( util )
add_subdirectory( fcl )
add_subdirectory( ups )


# Packaging facility
include(UseCPack)
