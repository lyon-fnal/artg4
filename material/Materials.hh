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

  G4Material *Al(); // aluminum
  G4Material *C();  // carbon
  G4Material *Cr(); // cromium
  G4Material *Cu(); // copper
  G4Material *F();  // flourine
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
  
  
  // Here be the mixtures 
  G4Material *Air();       // The same stuff as in our President's head 
  G4Material *Al6061();    // Alloy for the inflector mandrel
  G4Material *BC404Scintillator();     // Plastic Scintillator
  G4Material *BC408Scintillator();     // Another lastic Scintillator
  G4Material *BCF10ScintFiber();     // Plastic scintillating fiber
  G4Material *Conductor(); // superconducting material for inflector
  G4Material *MacorCeramic();   // Ceramic for quadrupole supports
  G4Material *Mylar();     // carbon, hydrogen, oxygen
  G4Material *NbTi();      // superconducting Niobium-Titanium
  G4Material *PbSb();      // lead-antimony alloy
  G4Material *Vacuum();
  G4Material *Vacuum1();
  G4Material *H2O();
  G4Material *PbF2();
  G4Material *Quartz() ;
  G4Material *BicronBC630();    // optical grease
  G4Material *Borosilicate();   // using the pyrex borosilicate formulation from the NIST database in G4
  G4Material *Epoxy();


  // optical surfaces
  G4OpticalSurface *PolishedMetal();
  G4OpticalSurface *Millipore();
  G4OpticalSurface *Specular();
  G4OpticalSurface *SpecularNoGap();
  G4OpticalSurface *Diffuse();
  G4OpticalSurface *SuperDiffuse();
  G4OpticalSurface *Black();
  G4OpticalSurface *RoughBlack();
  G4OpticalSurface *Open();

  // a lookup by name!
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
