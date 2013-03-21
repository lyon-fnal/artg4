#ifndef ARTG4MATERIALS_HH
#define ARTG4MATERIALS_HH

/** @file constructionMaterials.hh 2005-2011
    @file artg4Materials.hh  Nov 2012
    Contains declarations of material property getter functions. 

    @author Zach Hartwig
    @author Kevin Lynch
    @author Justin Phillips
    @date 2005-2011
    @moved over to artg4 Nov 2012, Brendan Kiburg
    @author NSF(3/13): Fixed some materials, added some new ones, cleaned up code
*/

#include "Geant4/G4Material.hh"
#include "Geant4/G4OpticalSurface.hh"

/** The namespace constructionMaterials contains getter functions
    provide material properties. 

    These functions build and stores all the necessary materials for
    the simulation. In essence, this class creates a "library" of
    materials that the construction files can easily access during the
    creation of logical volumes.

    If you add materials here, be sure to update the name->function
    map at the bottom of constructionMaterials.cc
*/

namespace artg4Materials
{
  //  ELEMENTS
  G4Material *Al(); // aluminum
  G4Material *Ar(); // argon
  G4Material *Be(); // beryllium 
  G4Material *C();  // carbon
  G4Material *Cr(); // chromium
  G4Material *Cu(); // copper
  G4Material *F();  // fluorine
  G4Material *Fe(); // iron
  G4Material *H();  // hydrogen
  G4Material *Mg(); // magnesium
  G4Material *N();  // nitrogen
  G4Material *Nb(); // niobium
  G4Material *O();  // oxygen
  G4Material *Pb(); // lead
  G4Material *Sb(); // antimony
  G4Material *Si(); // silicon
  G4Material *Ti(); // titanium
  G4Material *W();  // tungsten
  G4Material *Zn(); // zinc
  
  //  COMPOUNDS
  G4Material *Air();
  G4Material *Al5052();            // inner/outer quad electrodes 
  G4Material *Al6061();            // inflector mandrel, upper/lower quad electrodes, etc.
  G4Material *BC404Scintillator(); // plastic scintillator
  G4Material *BC408Scintillator(); // another plastic scintillator
  G4Material *BCF10ScintFiber();   // plastic scintillating fiber
  G4Material *BicronBC630();       // optical grease
  G4Material *Borosilicate();      // using the pyrex borosilicate formulation from the NIST database in G4
  G4Material *Brass();             // quad support bolts, etc.
  G4Material *Conductor();         // NSF(3/13): Fixed this @bug for the aluminum stabilized NbTi/Cu inflector superconductor (NbTi:Cu:Al = 1.0:0.9:3.7)
  G4Material *Epoxy();
  G4Material *H2O();               // where is this used, exactly?
  G4Material *Kapton();            // insulator (e.g. inflector superconducting wires)
  G4Material *MacorCeramic();      // quad standoffs/supports
  G4Material *Mylar();             // carbon, hydrogen, oxygen
  G4Material *NbTi();              // NSF(3/13): Fixed this @bug for the inflector superconductor (Nb:Ti = 1:1)
  G4Material *PbSb();              // lead-antimony alloy
  G4Material *Vacuum();
  G4Material *Vacuum1();           // index of refraction = 1; needed for optical processes
  G4Material *PbF2();              // calo xtals
  G4Material *Quartz();

  //  OPTICAL SURFACES
  G4OpticalSurface *PolishedMetal();
  G4OpticalSurface *Specular();
  G4OpticalSurface *Diffuse();
  G4OpticalSurface *Black();
  G4OpticalSurface *Open();

  //  A lookup by name!
  G4Material *findByName(G4String);
  G4OpticalSurface *findOpticalByName(G4String);

}

#include <exception>
#include <string>

namespace artg4Materials {
  class material_not_found : public std::exception {
  public:
    material_not_found(std::string requested) : payload_(requested) {}
    const char* what() const throw();
    ~material_not_found() throw() {}
  private:
    material_not_found(); // = deleted // don't implement
    std::string const payload_;
    mutable std::string message_;
  };
}

#endif
