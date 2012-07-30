#ifndef SingleParticleSource_hh
#define SingleParticleSource_hh

// SingleParticleSource.hh is a modified and updated version of the
// SPS included with the distribution of GEANT4, details below.  Many
// changes have been made to this file to suit MIGTRACE needs.
// Much of the remaining original code has been reorganized and
// documented more extensively.  Time distribution functions were
// added, as well as the ability to import TURTLE, BTRAF, and
// userDefined particle files into MIGTRACE for particle injection.

// Thanks to the good people at QinetiQ ltd. for their generously
// allowing the use of their code...by which I mean I stole it
// unabashedly...
    
// - MODULE:       G4SingleParticleSource (modified version of G4GPS included
//                                         in GEANT4.6.0 distribution)
// - Version:      2.0
// - Date:         5/02/04
// - Author:       Fan Lei 
// - Organisation: QinetiQ ltd.
// - Customer:     ESA/ESTEC

// Authors:
//   - Zach Hartwig 2005
//   - Tasha Arvanitis, Adam Lyon 2012

// SingleParticleSource has a multitude of parameters that determine its 
// behavior. Unlike in the older version of the Art G4 simulation (MIGTRACE),
// in which all parameters were set by messengers combined with macros, the
// new, artized simulation sets all of these parameters in a configuration
// file. The parameters which can be set are:

// Note on code-doxify - try < pre >?

// - position:

//   - type (string): Describe the type of position distribution desired.
//         Choices are "Point", "Beam", "Plane", "Surface", and "Volume".
//         Default is "Point".

//   - shape (string): Describe the shape of the position distribution (only
//         for types Plane, Surface, or Volume). Choices are "Circle", 
//         "Annulus", "Ellipse", "Square", "Rectangle", "Sphere", "Ellipsoid", 
//         "Cylinder", and "Para". Should be "NULL" for types Point and Beam.
//         Default is "NULL".

//   - position (list of doubles): Give the position of the source (x, y, z) in
//         centimeters.
//         What coordinate system?
//         Default is [0, 0, 0].

//   - rotation:

//     - rotation1 (list of doubles): Give the first vector defining the 
//           rotation matrix. Does not need to be a unit vector. Not all of the
//           components may be zero.
//           Default is the x-axis [1, 0, 0].

//     - rotation2 (list of doubles): Give the second vector defining the 
//           rotation matrix. Doesn't need to be a unit vector. Not all of the 
//           components may be zero.
//           Default is the y-axis [0, 1, 0].

//   - half_x (double): Give half the x-length of the source, in centimeters.
//         Default is 0.

//   - half_y (double): Give half the y-length of the source, in centimeters.
//         Default is 0.

//   - half_z (double): Give half the z-length of the source, in centimeters.
//         Default is 0.

//   - radius (double): Give the radius of the source, in centimeters.
//         Default is 0.

//   - radius0 (double): Give the inner radius of the source, when required,
//         in centimeters.
//         Default is 0.

//   - sigma: (Only used when type is Beam)
//     - r (double): Give the error in r of the position distribution, in cm.
//           Default is provided, and is 0.

//     - x (double): Give the error in x of the position distribution, in cm.
//           Note: NO DEFAULT IS PROVIDED, as r=0 implies x=0. If the given
//           parameter set has both sigma.x and sigma.y, we use those. Otherwise
//           we use r.

//     - y (double): Give the error in y of the position distribution, in cm.
//           Note: like for x, NO DEFAULT IS PROVIDED. See above for details.

//   - confine_to (string): Give the name of a volume to which the source is
//         confined, or "NULL" to avoid confining the innocent source.
//         Default is "NULL".

//   - para: (Only used when type is Para)
//     - alpha (double): Give the angle from the y-axis of y', in degrees.
//           Default is 0.
//     - theta (double): Give the polar angle through the centers of the z
//           faces, in degrees.
//           Default is 0.
//     - phi (double): Give the azimuthal angle through the centers of the z
//           faces, in degrees.
//           Default is 0.

// - angular:
//   - type (string): Give the angular source distribution type. Choices are
//         "iso", "cos", "planar", "beam1d", "beam2d", or "user".
//         Default is "iso".

//   - rotation:

//     - rotation1 (list of doubles): Give the first vector defining the 
//           rotation matrix. Does not need to be a unit vector. Not all of the
//           components may be zero.
//           Default is the x-axis [1, 0, 0].

//     - rotation2 (list of doubles): Give the second vector defining the 
//           rotation matrix. Doesn't need to be a unit vector. Not all of the 
//           components may be zero.
//           Default is the y-axis [0, 1, 0].

//   - min_theta (double): Give the minimum theta, in degrees.
//         Default is 0.

//   - max_theta (double): Give the maximum theta, in degrees.
//         Default is 180 degrees.

//   - min_phi (double): Give the minimum phi, in degrees.
//         Default is 0.

//   - max_phi (double): Give the maximum phi, in degrees.
//         Default is 360 degrees.

//   - sigma: 
//     - r (double): Give the error in r of the angular distribution, in deg.
//           Only used when type is beam1d.
//           Default is 0.

//     - x (double): Give the error in x of the angular distribution, in deg.
//           Only used when type is beam2d.
//           Default is 0.

//     - y (double): Give the error in y of the angular distribution, in deg.
//           Only used when type is beam2d.
//           Default is 0.

//   - focus_point (list of doubles): Give the coordinates (x, y, z) of the 
//         focusing point for the beam, all in centimeters.
//         Default is [0, 0, 0].

//   - use_user_axes (bool): Set to true for using user-defined angular
//         coordinates, false otherwise.
//         Default is false.

//   - use_surf_norm (bool): Set to true to use user-defined distribution with
//         respect to surface normals rather than x/y/z axes.
//         Default is false.

// - energy:
//   - type (string): Give the energy distribution type. Options are "Mono",
//         "Lin", "Pow", "Exp", "Gauss", "Brem", "Bbody", "Cdg", "User", "Arb",
//         and "Epn".
//         Default is "Mono".

//   - min (double): Give the minimum energy for the distribution, in keV.
//         Default is 0.

//   - max (double): Give the maximum energy for the distribution, in keV.
//         Default is 1.e33.

//   - mono_energy (double): Give the monocromatic energy, in keV. Used for
//         type Mono.
//         Default is 1000. keV.

//   - gauss_sigma (double): Give the standard deviation for the Gaussian energy
//         distribution, in keV. Used for type Gauss.
//         Default is 0.

//   - pow_alpha (double): Give Alpha (index) for power-law energy dist. Used
//         for type Pow.
//         Default is 0.

//   - brem_bbody_temp (double): Give temperature (in Kelvin) for Brem and Bbody
//         distributions.
//         Default is 0.

//   - exp_ezero (double): Give E_0 for exponential distributions. Used for type
//         Exp.
//         Default is 0.

//   - lin_gradient (double): Give gradient, in 1/MeV, for type Lin.
//         Default is 0.

//   - lin_intercept (double): Give intercept (in MeV) for distributions of type
//         Lin.
//         Default is 0.

//   - energy_spec (bool): Set to true for energy distribution and false for
//         momentum distribution.
//         Default is true.

//   - diff_spec (bool): Set to true for differential and false for integral
//         spectra.
//         Default is true.

// - time:

//   - type (string): String describing the time distribution. Choices are
//         "Mono", "Gauss", and "Linear".
//          Default is "Mono".

//   - min (double): Give minimum time for distribution, in nanoseconds.
//          Default is 0.

//   - max (double): Give maximum time for distribution, in nanoseconds.
//          Default is 0.

//   - mono_time (double): Give a monochronologic time, in nanoseconds. Used
//          for type Mono.
//          Default is 109. nanoseconds.

//   - gauss_sigma (double): Give the standard deviation for the Gaussian time
//          distribution, in nanoseconds. Only used for type Gauss.
//          Default is 0.

//   - lin_gradient (double): Give the slope for the linear distribution, in 
//          1/nanoseconds. Used for type Lin.
//          Default is 0.

//   - lin_intercept (double): Give the intercept for the linear distribution, 
//          in nanoseconds. Used for type Lin.
//          Default is 0.

// - mu_from_file (bool): Determine whether to use distributions from a file
//        (true) or generate them internally (false).
//        Default is false.

// - file_type (string): Set the type of import file. Choices are "turtle",
//        and "btraf". As "userDefined" was never completely implemented, it is
//        left out here.
//        Default is "turtle"

// - file_name (string): Set the file to be imported. Only used if the file name
//        mu_from_file is set to true.
//        Default is "".

// - direction (list of doubles): Set the momentum direction. This need not be
//        a unit vector.
//        Default is [0, 0, -1]

// - verbose (int): Set verbosity for particle gun. 0 is silent, 1 is limited
//        information, and 2 is detailed information.
//        Default is 0.

// The parameters above are sorted into a hierarchy, with, for instance, 'type'
// as a sub-category of 'position'. To denote this in the configuration file,
// simply nest parameter sets:

// source1: { 
//   position: {
//     type: "Beam"
//     shape: "NULL"
//     position: [1, 2, 3]
//     ...
//   }
//   angular: {
//     ...
//   }
//   ...
// }

#include "G4VPrimaryGenerator.hh"
#include "G4ParticleMomentum.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4SPSPosDistribution.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "SPSTimeDistribution.hh"
#include "G4SPSRandomGenerator.hh"

#include "fhiclcpp/ParameterSet.h"

#include <vector>

namespace artg4 {
  // A modified version of G2SingleParticleSource, to support time
  // distributions 
  class SingleParticleSource : public G4VPrimaryGenerator
  {
  public:
    // Constructor accepts a parameter set to initialize member data
    SingleParticleSource (fhicl::ParameterSet const & p); 
    ~SingleParticleSource ();

    // Some setup methods.
    void setUpPositionDist(ParameterSet const & p);
    void setUpAngularDist(ParameterSet const & p);
    void setUpEnergyDist(ParameterSet const & p);
    void setUpTimeDist(ParameterSet const & p);
    void setUpFileImport(ParameterSet const & p);
    void setUpHistos(ParameterSet const & p);
    void setUpParticleGun(ParameterSet const & p);

    // The three main SPS functions
    void GeneratePrimaryVertex(G4Event *evt);
    void UseImportedParticles(G4Event *evt);
    void UseInternallyGenerateParticles(G4Event *evt);

    // Called from GPS, returns the requested distribution generators
    G4SPSPosDistribution *GetPosDist() {return posGenerator;}
    G4SPSAngDistribution *GetAngDist() {return angGenerator;}
    G4SPSEneDistribution *GetEneDist() {return eneGenerator;}
    SPSTimeDistribution *GetTimeDist() {return timeGenerator;}
    G4SPSRandomGenerator *GetBiasRndm() {return biasRndm;}
  
    // Set the verbosity level.
    void SetVerbosity(G4int);

    // The five functions that implement the importation of particle files
    void SetImportFlag(G4bool newFlag); 
    void SetImportFileType(G4String);
    void SetImportFileStructure(G4String);
    void LoadImportFile(G4String);
    void ClearImportData();

    // Set the particle species
    void SetParticleDefinition (G4ParticleDefinition * aParticleDefinition);
    inline G4ParticleDefinition * GetParticleDefinition () 
    { return particle_definition;}

    // Set the particle charge
    inline void SetParticleCharge(G4double aCharge) 
    { particle_charge = aCharge; }

    // Set polarization
    inline void SetParticlePolarization (G4ThreeVector aVal) 
    {particle_polarization = aVal;}
    inline G4ThreeVector GetParticlePolarization ()  
    {return particle_polarization;}

    // Set Time
    inline void SetParticleTime(G4double aTime)  { particle_time = aTime; }
    inline G4double GetParticleTime()  { return particle_time; }

    inline void SetNumberOfParticles(G4int i)  
    { NumberOfParticlesToBeGenerated = i; }

    inline G4int GetNumberOfParticles() 
    { return NumberOfParticlesToBeGenerated; }
    inline G4ThreeVector GetParticlePosition()  { return particle_position;};
    inline G4ThreeVector GetParticleMomentumDirection()  
    { return particle_momentum_direction;}
    inline G4double GetParticleEnergy()  {return particle_energy;};

  private:
 
    // Create the distribution generators
    G4SPSPosDistribution *posGenerator;
    G4SPSAngDistribution *angGenerator;
    G4SPSEneDistribution *eneGenerator;
    SPSTimeDistribution *timeGenerator;
    G4SPSRandomGenerator *biasRndm;
  
    // Other particle properties used in the primary vertex
    G4int                  NumberOfParticlesToBeGenerated;
    G4ParticleDefinition  *particle_definition;
    G4ParticleMomentum     particle_momentum_direction;
    G4double               particle_energy;
    G4double               particle_charge;
    G4ThreeVector          particle_position;
    G4double               particle_time;
    G4ThreeVector          particle_polarization;
    G4double               particle_weight;

    // Verbosity
    G4int verbosityLevel;

    // particle import variables and parameters
    // parameters set by the GPS messenger for particle importation
    G4bool importFlag;
    G4String importFileType;
    G4String importFileName;
    G4bool fileSuccessfullyOpened;

    // Position of particles in inflector coordinates.  NOTE: z_i = 0 
    // for all particles (they begin at inflector upstream face)
    G4double x_i, y_i;
  
    // Angles made by momentum vector with inflector x and y axes
    G4double xPrime_i, yPrime_i;

    // Momentum components of momentum vector in inflector coordinates
    G4double pX_i, pY_i, pZ_i;

    // Total scalar value of momentum vector
    G4double pTotal;

    // Spin componenets of spin vector in inflector coordinates
    G4double sX_i, sY_i, sZ_i;
  
    // Position of particles in world coordinates
    G4double x_w, y_w, z_w;
  
    // Momentum components of momentum vector in world coordinates
    G4double pX_w, pY_w, pZ_w;
  
    // Spin components of spin vector in world coordinates
    G4double sX_w, sY_w, sZ_w;
  

    // In order to read in the variables from a file, a struct is
    // created containing appropriate data members for each line
    // (representing one particle) of the file.  Then, a vector of these
    // structs is created to hold all the lines (thus, all the
    // particles).  Later, according to the eventID, each particle can
    // be easily and individually accessed
    struct importContainer
    {
      G4double x;
      G4double xPrime;
      G4double y;
      G4double yPrime;
      G4double pTotal;
      G4double null1;
      G4double null2;
      G4double spin1;
      G4double spin2;
      G4double spin3;
    } import;
  
  std::vector<importContainer> importVector;

};
}
#endif




