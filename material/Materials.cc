/** @file artg4Materials.cc

    Contains the implementations of the material property getter functions.

    Actual material parameter values were obtained from the several
    sources:  
    -# g2GEANT3 
    -# The CRC Handbook of Chemistry and Physics 
    -# Web Elements - available at http://www.webelements.com
    -# Engineering Fundamentals - available at
    http://www.efunda.com/materials/materials_home/materials.cfm 

    There's a static initialization issue with trying to get a file
    scope pointer to the NistManager.  The static initialization in
    these implementations works, though.  So don't think about
    changing it, or you'll end up back in the crashing regime.
   
    @author Zach Hartwig
    @author Kevin Lynch
    @author Justin Phillips
    @date 2005-2011
    @Moved over for artg4 Nov 2012, Brendan Kiburg
    @author NSF(3/13): Fixed some materials, added some new ones, cleaned up code
*/

#include "Geant4/G4NistManager.hh"

#include "artg4/material/Materials.hh"

#include <tr1/functional>

#include <boost/algorithm/string.hpp>


//====================================================================//
//===========================   ELEMENTS  ============================//
//====================================================================//

G4Material *artg4Materials::Al()
{
  static G4Material *Al = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
  return Al;
}

G4Material *artg4Materials::Ar()
{
  static G4Material *Ar =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Ar");
  return Ar;
}

G4Material *artg4Materials::Be()
{
  static G4Material *Be =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Be");
  return Be;
}

G4Material *artg4Materials::C()
{
  static G4Material *C = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_C");
  return C;
}

G4Material *artg4Materials::Cr()
{
  static G4Material *Cr = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Cr");
  return Cr;
}

G4Material *artg4Materials::Cu()
{
  static G4Material *Cu = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
  return Cu;
}

G4Material *artg4Materials::F()
{
  static G4Material *F = 
     G4NistManager::Instance()->FindOrBuildMaterial("G4_F");
  return F;
}

G4Material *artg4Materials::Fe()
{
  static G4Material *Fe = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe");
  return Fe;
}

G4Material *artg4Materials::H()
{
  static G4Material *H = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_H");
  return H;
}

G4Material *artg4Materials::Mg()
{
  static G4Material *Mg = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Mg");
  return Mg;
}

G4Material *artg4Materials::N()
{
  static G4Material *N = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_N");
  return N;
}

G4Material *artg4Materials::Nb()
{
  static G4Material *Nb = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Nb");
  return Nb;
}

G4Material *artg4Materials::O()
{
  static G4Material *O = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_O");
  return O;
}

G4Material *artg4Materials::Pb()
{
  static G4Material *Pb = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
  return Pb;
}

G4Material *artg4Materials::Sb()
{
  static G4Material *Sb = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Sb");
  return Sb;
}

G4Material *artg4Materials::Si()
{
  static G4Material *Si = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
  return Si;
}

G4Material *artg4Materials::Ti()
{
  static G4Material* Ti = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Ti");
  return Ti;
}

G4Material *artg4Materials::W()
{
  static G4Material *W = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_W");
  return W;
}

G4Material *artg4Materials::Zn()
{
  static G4Material *Zn = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Zn");
  return Zn;
}


//====================================================================//
//===========================   COMPOUNDS   ==========================//
//====================================================================//

G4Material *artg4Materials::CO2()
{
  static G4Material *CO2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
  return CO2;
}

G4Material *artg4Materials::Air()
{
  static G4Material *Air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
  return Air;
}


G4Material *artg4Materials::Al5052() // quad inner/outer electordes
{
  static G4Material *Al5052 = new G4Material( "AluminumAlloy5052-H34", 2.68*g/cm3, 3 );
  static bool init = true;
  if( init ){
    Al5052->AddMaterial(artg4Materials::Mg(), 2.50*perCent); //z=12
    Al5052->AddMaterial(artg4Materials::Al(),97.25*perCent); //z=13
    Al5052->AddMaterial(artg4Materials::Si(), 0.25*perCent); //z=14
    init = false;
  }
  return Al5052;
}


G4Material *artg4Materials::Al6061() // inflector mandrel, quad upper/lower electrodes, etc.
{
  static G4Material *Al6061 = new G4Material( "AluminumAlloy6061-T6", 2.70*g/cm3, 5 );
  static bool init = true;
  if( init ){
    Al6061->AddMaterial(artg4Materials::Mg(), 1.00*perCent); // z=12
    Al6061->AddMaterial(artg4Materials::Al(),97.92*perCent); // z=13
    Al6061->AddMaterial(artg4Materials::Si(), 0.60*perCent); // z=14
    Al6061->AddMaterial(artg4Materials::Cr(), 0.20*perCent); // z=24
    Al6061->AddMaterial(artg4Materials::Cu(), 0.28*perCent); // z=29
    init = false;
  }    
  return Al6061;
}

G4Material *artg4Materials::ArCO2(){
  static G4Material *ArCO2 = new G4Material("ArgonCO2", 0.0018*g/cm3 ,2);
  
  static bool init = true;
  if (init){
    ArCO2->AddMaterial(artg4Materials::Ar(), 80*perCent);
    ArCO2->AddMaterial(artg4Materials::CO2(), 20*perCent);
    init = false;
  }
  
  return ArCO2;
}

namespace{ 
  G4Material *Scintillator(G4String name, 
			   G4double density, G4double HCratio){
    G4Material *scint = new G4Material(name, density, 2);
    
    G4double const aH = artg4Materials::H()->GetA();
    G4double const aC = artg4Materials::C()->GetA();
    G4double const Hweight = HCratio*aH/(HCratio*aH + aC);
    scint->AddMaterial(artg4Materials::H(), Hweight);
    scint->AddMaterial(artg4Materials::C(), 1.-Hweight);

    return scint;
  }
}
 
G4Material *artg4Materials::BC404Scintillator(){
  static bool init = true;
  static G4Material *BC404 = 0;

  if( init )
    BC404 = Scintillator("BC404Scintillator", 1.032*g/cm3, 1.1);

  return BC404;
}
 
G4Material *artg4Materials::BC408Scintillator(){
  static bool init = true;
  static G4Material *BC408 = 0;

  if( init )
    BC408 = Scintillator("BC408Scintillator", 1.032*g/cm3, 1.104);

  return BC408;
}

G4Material *artg4Materials::BCF10ScintFiber(){
  static bool init = true;
  static G4Material *BCF10 = 0;

  if( init )
    BCF10 = Scintillator("BCF10ScintFiber", 1.05*g/cm3, 4.82/4.85);

  return BCF10;
}


G4Material* artg4Materials::BicronBC630()
{
   static bool init = true;
   static G4Material *bicronBC630;

   if( init ){

      G4NistManager* nistMan = G4NistManager::Instance();
      std::vector<G4int> natoms;
      std::vector<G4double> fractionMass;
      std::vector<G4String> elements;

       //--------------------------------------------------
       // Silicone (Template for Optical Grease)
       //--------------------------------------------------
       
       elements.push_back("C");     natoms.push_back(2);
       elements.push_back("H");     natoms.push_back(6);
       double density = 1.060*g/cm3;
       
       bicronBC630 = nistMan->
       ConstructNewMaterial("BicronBC630", elements, natoms, density);
       
       // Material Properties table
       const G4int nEntries = 5 ;
       
       // Transmission coefficients from bicron datasheet: assume 100 micron thickness
       
       // Order from low energy to high energy (required for Geant 4.9.5)
       G4double wavelengths[ nEntries ] = { 950.*nm, 700.*nm, 280.*nm, 270.*nm, 200.*nm };
       G4double transmission[ nEntries ] = { 0.95, 0.95, 0.95, 0., 0. } ;
       
       G4double photonEnergy[ nEntries ] ;
       G4double refractiveIndex[ nEntries ] ;
       G4double absorptionLength[ nEntries ] ;
       
       for( int i = 0 ; i < nEntries ; ++i )
       {
           photonEnergy[ i ] = 0.001240 * MeV * nm / wavelengths[ i ] ;
           refractiveIndex[ i ] = 1.465 ; // actual index of Bicron BC630
           absorptionLength[ i ] = -0.1*mm / log( transmission[ i ] ) ;
       }
       
       // Geant 4.9.5 Material properties table: photonEnergy must be in order
       G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
       table->AddProperty( "RINDEX", photonEnergy, refractiveIndex, nEntries ) ;
       table->AddProperty( "ABSLENGTH", photonEnergy, absorptionLength, nEntries ) ;
       
       bicronBC630->SetMaterialPropertiesTable( table ) ;
       
       init = false;
   }
    
    return bicronBC630;
}


G4Material* artg4Materials::Borosilicate() // aka, pyrex
{
  static G4Material *pyrex = 
     G4NistManager::Instance()->FindOrBuildMaterial("G4_Pyrex_Glass");

  // http://hypernews.slac.stanford.edu/HyperNews/geant4/get/opticalphotons/299.html
  const G4int num = 2 ;
  G4MaterialPropertiesTable* myPyrexWindow = new G4MaterialPropertiesTable();
  G4double pyrexPhotonAbsorptionLengthNRG[num] = { 1.0*eV, 5.0*eV } ;
  G4double pyrexPhotonAbsorptionLength[num] = {5000.*mm , 5000.*mm};
  myPyrexWindow->AddProperty("ABSLENGTH",pyrexPhotonAbsorptionLengthNRG,
			      pyrexPhotonAbsorptionLength,num);
  G4double pyrexPhotonRefractiveIndexNRG[num] = { 1.0*eV, 5.0*eV } ;
  G4double pyrexPhotonRefractiveIndex[num] = {1.51 , 1.51};
  myPyrexWindow->AddProperty("RINDEX",pyrexPhotonRefractiveIndexNRG,
			      pyrexPhotonRefractiveIndex,num);
  pyrex->SetMaterialPropertiesTable(myPyrexWindow);

  return pyrex;
}


G4Material *artg4Materials::Brass() // E821 quad support bolts
{
  //  http://webmineral.com/data/Brass.shtml, http://www.engineeringtoolbox.com/metal-alloys-densities-d_50.html
  static G4Material *Brass = new G4Material( "Brass", 8.52*g/cm3, 2 );
  static bool init = true;
  if( init ){
    Brass->AddMaterial( artg4Materials::Cu(), 59.31*perCent ); //z=29
    Brass->AddMaterial( artg4Materials::Zn(), 40.69*perCent ); //z=30
    init = false;
  }
  return Brass;
}


G4Material *artg4Materials::Conductor()
{
  //  NSF(3/13), Source: E821 inflector NIM paper, plus some simple calculations involving MASS fractions
  static G4Material *Conductor = new G4Material( "Conductor", 4.394*g/cm3, 3 );
  static bool init = true;
  if( init ){
    Conductor->AddMaterial(artg4Materials::NbTi(),30.95*perCent);
    Conductor->AddMaterial(artg4Materials::Cu(),  25.15*perCent);
    Conductor->AddMaterial(artg4Materials::Al(),  43.90*perCent);
    init = false;
  }
  return Conductor;
}


G4Material* artg4Materials::Epoxy() // same as quartz, with different R and density
{
  //  http://www.mt-berlin.com/frames_cryst/descriptions/quartz%20.htm
  static G4Material *epoxy = new G4Material( "Epoxy", 1.02*g/cm3, 2 );
  static bool init = true;
  if( init ){
    //  http://www.convertunits.com/molarmass/SiO2
    epoxy->AddMaterial(artg4Materials::Si(),46.743*perCent);
    epoxy->AddMaterial(artg4Materials::O(), 53.257*perCent);

    //  Material properties table
    const G4int nEntries = 2;
    G4double epoxyR = 1.5; //refractive index
    G4double photonEnergy[ nEntries ]     = { 1.0*eV,  5.0*eV  };
    G4double refractiveIndex[ nEntries ]  = { epoxyR,  epoxyR  };
    G4double absorptionLength[ nEntries ] = { 500.*cm, 500.*cm };

    G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable();
    table->AddProperty( "RINDEX",    photonEnergy, refractiveIndex,  nEntries );
    table->AddProperty( "ABSLENGTH", photonEnergy, absorptionLength, nEntries );

    epoxy->SetMaterialPropertiesTable( table ) ;
    init = false;
  }
  return epoxy;
}


G4Material *artg4Materials::H2O()
{
  static G4Material *H2O = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
  return H2O;
}


G4Material *artg4Materials::Kapton()
{
  static G4Material *Kapton = G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON");
  return Kapton;
}


G4Material *artg4Materials::MacorCeramic()
{
  //  http://www.azom.com/details.asp?ArticleID=1459
  static G4Material *MacorCeramic = new G4Material( "MacorCeramic", 2.52*g/cm3, 6 );
  static bool init = true;
  if( init ){
    MacorCeramic->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_SILICON_DIOXIDE"),46.*perCent);
    MacorCeramic->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_ALUMINUM_OXIDE"), 16.*perCent);
    MacorCeramic->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_POTASSIUM_OXIDE"),10.*perCent);
    MacorCeramic->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_MAGNESIUM_OXIDE"),17.*perCent);
    MacorCeramic->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_B"),4.4*perCent);
    MacorCeramic->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_O"),6.6*perCent);
    init = false;
  }
  return MacorCeramic;
}


G4Material *artg4Materials::Mylar()
{
  static G4Material *Mylar = G4NistManager::Instance()->FindOrBuildMaterial("G4_MYLAR");
  return Mylar;
}


G4Material *artg4Materials::NbTi()
{
  //  NSF(3/13): E821 inflector NIM paper, plus some simple calculations involving MASS fractions
  static G4Material *NbTi = new G4Material( "NbTi", 6.555*g/cm3, 2 );
  static bool init = true;
  if( init ){
    NbTi->AddMaterial(artg4Materials::Nb(),66.00*perCent);
    NbTi->AddMaterial(artg4Materials::Ti(),34.00*perCent); 
    init = false;
  }
  return NbTi;
}


G4Material* artg4Materials::NusilLS5257()
{
    static bool init = true;
    static G4Material *nusilLS5257;
    
    if( init ){
        
        G4NistManager* nistMan = G4NistManager::Instance();
        std::vector<G4int> natoms;
        std::vector<G4double> fractionMass;
        std::vector<G4String> elements;
        
        // use same elemental composition and density as Bicron BC-630 optical grease
        elements.push_back("C");     natoms.push_back(2);
        elements.push_back("H");     natoms.push_back(6);
        double density = 1.060*g/cm3;
        
        nusilLS5257 = nistMan->
        ConstructNewMaterial("NusilLS5257", elements, natoms, density);
        
        // Material Properties table
        const G4int nEntries = 6 ;
        
        // Order from low energy to high energy (required for Geant 4.9.5)
        G4double wavelengths[ nEntries ] = { 950.*nm, 833.*nm, 589.*nm, 411.*nm, 300.*nm, 250.*nm };
        G4double photonEnergy[ nEntries ] ;
        for( int i = 0 ; i < nEntries ; ++i )
        {
            photonEnergy[ i ] = 0.001240 * MeV * nm / wavelengths[ i ] ;
        }
        
        // Refractive index from Nusil LS 5257 data sheet
        G4double refractiveIndex[ nEntries ] = { 1.552, 1.5550, 1.5677, 1.6015, 1.755, 2.126 };

        // Not including any absorption for now; much more transparent than Bicron grease
        
        // Geant 4.9.5 Material properties table: photonEnergy must be in order
        G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
        table->AddProperty( "RINDEX", photonEnergy, refractiveIndex, nEntries ) ;
        
        nusilLS5257->SetMaterialPropertiesTable( table ) ;
        
        init = false;
    }
    
    return nusilLS5257;
}


G4Material* artg4Materials::PbSb()
{
  static G4Material *PbSb = new G4Material( "PbSb", 11.19*g/cm3, 2 ); // NSF(3/13): density calculated from mass fractions below
  static bool init = true;
  if( init ){
    PbSb->AddMaterial(artg4Materials::Pb(),94.*perCent); //assume correct
    PbSb->AddMaterial(artg4Materials::Sb(), 6.*perCent); //assume correct
    init = false;
  }
  return PbSb;
}

G4Material *artg4Materials::Vacuum()
{
  static G4Material *Vacuum = new G4Material("Vacuum", 
					     1., 
					     1.01*g/mole,
					     universe_mean_density,
					     kStateGas, 
					     3.e-18*pascal, 
					     2.73*kelvin);
  
  return Vacuum;
}  


G4Material *artg4Materials::Vacuum1()
// vacuum with index of refraction = 1; needed for optical processes
{
  static bool init = true;
  static G4Material *Vacuum1 = new G4Material("Vacuum1", 
					     1., 
					     1.01*g/mole,
					     universe_mean_density,
					     kStateGas, 
					     3.e-18*pascal, 
					     2.73*kelvin);

   if( init ){
      // Material Properties table
      const G4int nEntries = 2 ;
      G4double photonEnergy[ nEntries ] = { 1.0*eV, 5.0*eV } ;
      G4double refractiveIndex[ nEntries ] = { 1.0, 1.0 } ;
      G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
      table->AddProperty( "RINDEX", photonEnergy, refractiveIndex, nEntries ) ;

      Vacuum1->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
  return Vacuum1;
}  


G4Material* artg4Materials::PbF2()
{
   static bool init = true;
   // http://www.crystran.co.uk/lead-fluoride-pbf2.htm
   static G4Material *PbF2 = new G4Material("PbF2",
					    7.77*g/cm3,
					    2);
   if( init ){
      // http://www.convertunits.com/molarmass/PbF2
      PbF2 -> AddMaterial(artg4Materials::Pb(), 84.504*perCent);
      PbF2 -> AddMaterial(artg4Materials::F(), 15.496*perCent);

      // Material Properties table
      const G4int nEntries = 8 ;

       // Order from low energy to high energy (required for Geant 4.9.5)
       G4double wavelengths[ nEntries ] =
         { 950.*nm,
             800.*nm,
             600.*nm,
             400.*nm,
             350.*nm,
             300.*nm,
             275.*nm,
             250.*nm } ;
       
       // Transmission coefficients measured for 186mm long crystal
       G4double transmission[ nEntries ] =
         { 0.84, // 950 nm
             0.83, // 800 nm
             0.81, // 600 nm
             0.75, // 400 nm
             0.71, // 350 nm
             0.48, // 300 nm
             0.18,   // 275 nm
             0. } ; // 250 nm
       
       // refractive index data from http://refractiveindex.info/?group=CRYSTALS&material=PbF2
       G4double refractiveIndex[ nEntries ] =
         { 1.74, // 950 nm
             1.75, // 800 nm
             1.76, // 600 nm
             1.82, // 400 nm
             1.85, // 350 nm
             1.94, // 300 nm
             1.98, // 275 nm
             2.02 } ; // 250 nm

       
    G4double photonEnergy[ nEntries ] ;
    // G4double rayleighLength[ nEntries ];
    G4double transCorrectionFactor[ nEntries ] ;
    G4double absorptionLength[ nEntries ] ;

    for( int i = 0 ; i < nEntries ; ++i )
    {
       photonEnergy[ i ] = 0.001240 * MeV * nm / wavelengths[ i ] ;
        // rayleighLength[ i ] = 1.*cm ;
        
        // correction for surface reflections:
        // Transmission_internal = Transmission_total * (1+n)^4 / (4n)^2
        // See simulation elog 217 https://muon.npl.washington.edu/elog/g2/Simulation/217
        G4double n = refractiveIndex[ i ];
        G4double sqrtCorrection = (1+n)*(1+n)/(4*n);
        transCorrectionFactor[ i ] = sqrtCorrection*sqrtCorrection;
        
        absorptionLength[ i ] = -186.*mm / log( transmission[ i ]*transCorrectionFactor[ i ] ) ;
    }

    // Geant 4.9.5 Material properties table: photonEnergy must be in order
    G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
    table->AddProperty( "RINDEX", photonEnergy, refractiveIndex, nEntries ) ;
    table->AddProperty( "ABSLENGTH", photonEnergy, absorptionLength, nEntries ) ;
    // table->AddProperty( "RAYLEIGH", photonEnergy, rayleighLength, nEntries ) ;

    PbF2->SetMaterialPropertiesTable( table ) ;

    init = false;
   }
  
   return PbF2;
}


G4Material* artg4Materials::Quartz() // SiO2
{
  static G4Material *quartz = 
     G4NistManager::Instance()->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

  // http://hypernews.slac.stanford.edu/HyperNews/geant4/get/opticalphotons/299.html
  const G4int num = 2 ;
  G4MaterialPropertiesTable* myQuartzWindow = new G4MaterialPropertiesTable();
  G4double quartzPhotonAbsorptionLengthNRG[num] = { 1.0*eV, 5.0*eV } ;
  G4double quartzPhotonAbsorptionLength[num] = {5000.*mm , 5000.*mm};
  myQuartzWindow->AddProperty("ABSLENGTH",quartzPhotonAbsorptionLengthNRG,
			      quartzPhotonAbsorptionLength,num);
  G4double quartzPhotonRefractiveIndexNRG[num] = { 1.0*eV, 5.0*eV } ;
  G4double quartzPhotonRefractiveIndex[num] = {1.458 , 1.458};
  myQuartzWindow->AddProperty("RINDEX",quartzPhotonRefractiveIndexNRG,
			      quartzPhotonRefractiveIndex,num);
  quartz->SetMaterialPropertiesTable(myQuartzWindow);

  return quartz;
}

G4Material* artg4Materials::SiPMSurfaceResin()
/* With the correct index of refraction (n = 1.55). Other bulk properties don't matter for the simulation, because particle tracks are killed when they enter the photodetector volume.
 */
{
    static bool init = true;
    static G4Material *sipmresin = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
    
    if( init ){
    const G4int nEntries = 2 ;
    G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable();
    G4double photonEnergy[nEntries] = { 1.0*eV, 5.0*eV } ;
    G4double refractiveIndex[nEntries] = {1.55 , 1.55};
    table->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);
    sipmresin->SetMaterialPropertiesTable(table);
    }
    return sipmresin;
}



//====================================================================//
//=======================   OPTICAL SURFACES   =======================//
//====================================================================//

G4OpticalSurface* artg4Materials::PolishedMetal()
{
   static bool init = true;
   static G4OpticalSurface *polishedMetal = new G4OpticalSurface("PolishedMetal");

   if( init ){
      polishedMetal->SetType( dielectric_metal ) ;
      polishedMetal->SetFinish( polished ) ;
      polishedMetal->SetModel( unified ) ;

      init = false;
   }

   return polishedMetal;
}

G4OpticalSurface* artg4Materials::PolishedMetalReverse()
// same as PolishedMetal (back side same as front)
{
    static bool init = true;
    static G4OpticalSurface *polishedMetalReverse = new G4OpticalSurface("PolishedMetalReverse");
    
    if( init ){
        polishedMetalReverse->SetType( dielectric_metal ) ;
        polishedMetalReverse->SetFinish( polished ) ;
        polishedMetalReverse->SetModel( unified ) ;
        
        init = false;
    }
    
    return polishedMetalReverse;
}

G4OpticalSurface* artg4Materials::Specular()
// PbF2 crystal surface with specular wrapping material
// reflectivity = 1, pure specular reflection, with air gap
{
   static bool init = true;
   static G4OpticalSurface *specular = new G4OpticalSurface("Specular");

   if( init ){

      // type of optical surface
      specular->SetType(dielectric_dielectric);
      specular->SetModel(unified);
      specular->SetFinish(polishedbackpainted); // "polished" means wrapping does specular reflection
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations for PbF2 surface
      specular->SetSigmaAlpha(facetAngleDistributionSigma);

      // Material Properties table

      const G4int nEntries = 12 ;

      G4double photonEnergy[ nEntries ] = 
	 { 1.0*eV,
	   1.55*eV,
	   2.7*eV,
	   2.97*eV,
	   3.31*eV,
	   3.55*eV,
	   3.82*eV,
	   4.46*eV,
	   4.92*eV,
	   5.5*eV,
	   5.82*eV,
	   6.21*eV
	 };

      G4double reflectivityValue = 1.0;
      G4double reflectivity[nEntries];
      std::fill_n(reflectivity, nEntries, reflectivityValue);

      // refractive index for air gap
      G4double effectiveRefractiveIndex = 1.0;
      G4double refractiveIndex[nEntries];
      std::fill_n(refractiveIndex, nEntries, effectiveRefractiveIndex);

      // xtal surface is faceted; all reflections are specular using surface normal from distribution
      G4double specularSpikeValue = 0.0;
      G4double specularLobeValue = 1.0;
      G4double backscatterValue = 0;
      G4double specularSpike[nEntries];
      G4double specularLobe[nEntries];
      G4double backscatter[nEntries];

      std::fill_n(specularSpike, nEntries, specularSpikeValue);
      std::fill_n(specularLobe, nEntries, specularLobeValue);
      std::fill_n(backscatter, nEntries, backscatterValue);
      

      G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
      table->AddProperty("RINDEX",                photonEnergy, refractiveIndex, nEntries ) ;
      table->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, specularSpike,   nEntries );
      table->AddProperty("SPECULARLOBECONSTANT",  photonEnergy, specularLobe,    nEntries );
      table->AddProperty("BACKSCATTERCONSTANT",   photonEnergy, backscatter,     nEntries );
      table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );

      specular->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return specular;
}

G4OpticalSurface* artg4Materials::SpecularReverse()
// Optical surface for photons hitting the other side of the specular wrapping
//     (i.e., the photons would enter the PbF2 crystal if the wrapping weren't there to stop them)
// reflectivity = 1, pure specular reflection
{
    static bool init = true;
    static G4OpticalSurface *specularReverse = new G4OpticalSurface("SpecularReverse");
    
    if( init ){
        
        // type of optical surface
        specularReverse->SetType(dielectric_dielectric);
        specularReverse->SetModel(unified);
        specularReverse->SetFinish(polishedfrontpainted); // "polished" means wrapping does specular reflection
        
        // Material Properties table
        
        const G4int nEntries = 12 ;
        
        G4double photonEnergy[ nEntries ] =
        { 1.0*eV,
            1.55*eV,
            2.7*eV,
            2.97*eV,
            3.31*eV,
            3.55*eV,
            3.82*eV,
            4.46*eV,
            4.92*eV,
            5.5*eV,
            5.82*eV,
            6.21*eV
        };
        
        G4double reflectivityValue = 1.0;
        G4double reflectivity[nEntries];
        std::fill_n(reflectivity, nEntries, reflectivityValue);
        
        G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
        table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );
        
        specularReverse->SetMaterialPropertiesTable( table ) ;
        
        init = false;
    }
    
    return specularReverse;
}

G4OpticalSurface* artg4Materials::Diffuse()
// PbF2 crystal surface with diffuse white wrapping material
// reflectivity = 1, pure diffuse reflection, with air gap; specular reflection at xtal surface
{
   static bool init = true;
   static G4OpticalSurface *diffuse = new G4OpticalSurface("Diffuse");

   if( init ){

      // type of optical surface
      diffuse->SetType(dielectric_dielectric);
      diffuse->SetModel(unified);
      diffuse->SetFinish(groundbackpainted); // "ground" means wrapping does diffuse reflection
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations for PbF2 surface
      diffuse->SetSigmaAlpha(facetAngleDistributionSigma);

      // Material Properties table

      const G4int nEntries = 12 ;

      G4double photonEnergy[ nEntries ] = 
	 { 1.0*eV,
	   1.55*eV,
	   2.7*eV,
	   2.97*eV,
	   3.31*eV,
	   3.55*eV,
	   3.82*eV,
	   4.46*eV,
	   4.92*eV,
	   5.5*eV,
	   5.82*eV,
	   6.21*eV
	 };

      G4double reflectivityValue = 1.0;
      G4double reflectivity[nEntries];
      std::fill_n(reflectivity, nEntries, reflectivityValue);

      // refractive index for air gap
      G4double effectiveRefractiveIndex = 1.0;
      G4double refractiveIndex[nEntries];
      std::fill_n(refractiveIndex, nEntries, effectiveRefractiveIndex);

      // xtal surface is faceted; all reflections are specular using surface normal from distribution
      G4double specularSpikeValue = 0.0;
      G4double specularLobeValue = 1.0;
      G4double backscatterValue = 0;
      G4double specularSpike[nEntries];
      G4double specularLobe[nEntries];
      G4double backscatter[nEntries];

      std::fill_n(specularSpike, nEntries, specularSpikeValue);
      std::fill_n(specularLobe, nEntries, specularLobeValue);
      std::fill_n(backscatter, nEntries, backscatterValue);
      

      G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
      table->AddProperty("RINDEX",                photonEnergy, refractiveIndex, nEntries ) ;
      table->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, specularSpike,   nEntries );
      table->AddProperty("SPECULARLOBECONSTANT",  photonEnergy, specularLobe,    nEntries );
      table->AddProperty("BACKSCATTERCONSTANT",   photonEnergy, backscatter,     nEntries );
      table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );

      diffuse->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return diffuse;
}


G4OpticalSurface* artg4Materials::DiffuseReverse()
// Optical surface for photons hitting the other side of the diffuse wrapping
//     (i.e., the photons would enter the PbF2 crystal if the wrapping weren't there to stop them)
// reflectivity = 1, pure diffuse reflection
{
    static bool init = true;
    static G4OpticalSurface *diffuseReverse = new G4OpticalSurface("DiffuseReverse");
    
    if( init ){
        
        // type of optical surface
        diffuseReverse->SetType(dielectric_dielectric);
        diffuseReverse->SetModel(unified);
        diffuseReverse->SetFinish(groundfrontpainted); // "ground" means wrapping does diffuse reflection
        
        // Material Properties table
        
        const G4int nEntries = 12 ;
        
        G4double photonEnergy[ nEntries ] =
        { 1.0*eV,
            1.55*eV,
            2.7*eV,
            2.97*eV,
            3.31*eV,
            3.55*eV,
            3.82*eV,
            4.46*eV,
            4.92*eV,
            5.5*eV,
            5.82*eV,
            6.21*eV
        };
        
        G4double reflectivityValue = 1.0;
        G4double reflectivity[nEntries];
        std::fill_n(reflectivity, nEntries, reflectivityValue);
        
        G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
        table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );
        
        diffuseReverse->SetMaterialPropertiesTable( table ) ;
        
        init = false;
    }
    
    return diffuseReverse;
}


G4OpticalSurface* artg4Materials::Black()
// PbF2 crystal surface with black wrapping material
// reflectivity = 0, with air gap; specualar spike reflections at xtal surface
{
   static bool init = true;
   static G4OpticalSurface *black = new G4OpticalSurface("Black");

   if( init ){

      // type of optical surface
      black->SetType(dielectric_dielectric);
      black->SetModel(unified);
      black->SetFinish(polishedbackpainted);
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations for PbF2 surface
      black->SetSigmaAlpha(facetAngleDistributionSigma);

      // Material Properties table

      const G4int nEntries = 12 ;

      G4double photonEnergy[ nEntries ] = 
	 { 1.0*eV,
	   1.55*eV,
	   2.7*eV,
	   2.97*eV,
	   3.31*eV,
	   3.55*eV,
	   3.82*eV,
	   4.46*eV,
	   4.92*eV,
	   5.5*eV,
	   5.82*eV,
	   6.21*eV
	 };

      G4double reflectivityValue = 0.0;
      G4double reflectivity[nEntries];
      std::fill_n(reflectivity, nEntries, reflectivityValue);

      // refractive index for air gap
      G4double effectiveRefractiveIndex = 1.0;
      G4double refractiveIndex[nEntries];
      std::fill_n(refractiveIndex, nEntries, effectiveRefractiveIndex);

      // xtal surface is faceted; all reflections are specular using surface normal from distribution      
      G4double specularSpikeValue = 0.0;
      G4double specularLobeValue = 1.0;
      G4double backscatterValue = 0;
      G4double specularSpike[nEntries];
      G4double specularLobe[nEntries];
      G4double backscatter[nEntries];

      std::fill_n(specularSpike, nEntries, specularSpikeValue);
      std::fill_n(specularLobe, nEntries, specularLobeValue);
      std::fill_n(backscatter, nEntries, backscatterValue);

      G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
      table->AddProperty("RINDEX",                photonEnergy, refractiveIndex, nEntries ) ;
      table->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, specularSpike,   nEntries );
      table->AddProperty("SPECULARLOBECONSTANT",  photonEnergy, specularLobe,    nEntries );
      table->AddProperty("BACKSCATTERCONSTANT",   photonEnergy, backscatter,     nEntries );
      table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );


      black->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return black;
}


G4OpticalSurface* artg4Materials::BlackReverse()
// Optical surface for photons hitting the other side of the black wrapping
//     (i.e., the photons would enter the PbF2 crystal if the wrapping weren't there to stop them)
// reflectivity = 0
{
    static bool init = true;
    static G4OpticalSurface *blackReverse = new G4OpticalSurface("BlackReverse");
    
    if( init ){
        
        // type of optical surface
        blackReverse->SetType(dielectric_dielectric);
        blackReverse->SetModel(unified);
        blackReverse->SetFinish(polishedfrontpainted);
        
        // Material Properties table
        
        const G4int nEntries = 12 ;
        
        G4double photonEnergy[ nEntries ] =
        { 1.0*eV,
            1.55*eV,
            2.7*eV,
            2.97*eV,
            3.31*eV,
            3.55*eV,
            3.82*eV,
            4.46*eV,
            4.92*eV,
            5.5*eV,
            5.82*eV,
            6.21*eV
        };
        
        G4double reflectivityValue = 0.0;
        G4double reflectivity[nEntries];
        std::fill_n(reflectivity, nEntries, reflectivityValue);
        
        G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
        table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );
        
        blackReverse->SetMaterialPropertiesTable( table ) ;
        
        init = false;
    }
    
    return blackReverse;
}

G4OpticalSurface* artg4Materials::Tedlar()
// Diffuse reflection based on reflectivity measurements made on Tedlar paper
{
   static bool init = true;
   static G4OpticalSurface *tedlar = new G4OpticalSurface("Tedlar");

   if( init ){

      // type of optical surface
      tedlar->SetType(dielectric_dielectric);
      tedlar->SetModel(unified);
      tedlar->SetFinish(groundbackpainted);
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations for PbF2 surface
      tedlar->SetSigmaAlpha(facetAngleDistributionSigma);

      // Material Properties table

      const G4int nEntries = 24 ;

      G4double photonEnergy[ nEntries ] = 
	{ 1.38*eV,
	  1.55*eV,
	  1.77*eV,
	  1.82*eV,
	  1.88*eV,
	  1.94*eV,
	  2.0*eV,
	  2.07*eV,
	  2.14*eV,
	  2.21*eV,
	  2.3*eV,
	  2.38*eV,
	  2.48*eV,
	  2.58*eV,
	  2.7*eV,
	  2.82*eV,
	  2.95*eV,
	  3.1*eV,
	  3.31*eV,
	  3.54*eV,
	  3.81*eV,
	  4.13*eV,
	  4.51*eV,
	  4.96*eV
	 };

      // From Detector Elog 584
      G4double reflectivity[nEntries] = 
	{
	  0.0669,
	  0.0741,
	  0.0708,
	  0.0708,
	  0.0708,
	  0.0713,
	  0.0718,
	  0.0728,
	  0.0735,
	  0.0741,
	  0.0749,
	  0.0760,
	  0.0776,
	  0.0788,
	  0.0805,
	  0.0821,
	  0.0835,
	  0.0831,
	  0.0679,
	  0.0601,
	  0.0605,
	  0.0631,
	  0.0635,
	  0.0637
	};
      
      // refractive index for air gap
      G4double effectiveRefractiveIndex = 1.0;
      G4double refractiveIndex[nEntries];
      std::fill_n(refractiveIndex, nEntries, effectiveRefractiveIndex);

      // xtal surface is faceted; all reflections are specular using surface normal from distribution      
      G4double specularSpikeValue = 0.0;
      G4double specularLobeValue = 1.0;
      G4double backscatterValue = 0;
      G4double specularSpike[nEntries];
      G4double specularLobe[nEntries];
      G4double backscatter[nEntries];

      std::fill_n(specularSpike, nEntries, specularSpikeValue);
      std::fill_n(specularLobe, nEntries, specularLobeValue);
      std::fill_n(backscatter, nEntries, backscatterValue);

      G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
      table->AddProperty("RINDEX",                photonEnergy, refractiveIndex, nEntries ) ;
      table->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, specularSpike,   nEntries );
      table->AddProperty("SPECULARLOBECONSTANT",  photonEnergy, specularLobe,    nEntries );
      table->AddProperty("BACKSCATTERCONSTANT",   photonEnergy, backscatter,     nEntries );
      table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );


      tedlar->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return tedlar;
}

G4OpticalSurface* artg4Materials::TedlarReverse()
// Optical surface for photons that would be entering the xtal
{
    static bool init = true;
    static G4OpticalSurface *tedlarReverse = new G4OpticalSurface("TedlarReverse");
    
    if( init ){
        
        // type of optical surface
        tedlarReverse->SetType(dielectric_dielectric);
        tedlarReverse->SetModel(unified);
        tedlarReverse->SetFinish(groundfrontpainted);
        
        // Material Properties table
        
        const G4int nEntries = 24 ;
        
       G4double photonEnergy[ nEntries ] = 
	{ 1.38*eV,
	  1.55*eV,
	  1.77*eV,
	  1.82*eV,
	  1.88*eV,
	  1.94*eV,
	  2.0*eV,
	  2.07*eV,
	  2.14*eV,
	  2.21*eV,
	  2.3*eV,
	  2.38*eV,
	  2.48*eV,
	  2.58*eV,
	  2.7*eV,
	  2.82*eV,
	  2.95*eV,
	  3.1*eV,
	  3.31*eV,
	  3.54*eV,
	  3.81*eV,
	  4.13*eV,
	  4.51*eV,
	  4.96*eV
	 };

      // From Detector Elog 584
      G4double reflectivity[nEntries] = 
	{
	  0.0669,
	  0.0741,
	  0.0708,
	  0.0708,
	  0.0708,
	  0.0713,
	  0.0718,
	  0.0728,
	  0.0735,
	  0.0741,
	  0.0749,
	  0.0760,
	  0.0776,
	  0.0788,
	  0.0805,
	  0.0821,
	  0.0835,
	  0.0831,
	  0.0679,
	  0.0601,
	  0.0605,
	  0.0631,
	  0.0635,
	  0.0637
	};
	               
        
        G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
        table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );
        
        tedlarReverse->SetMaterialPropertiesTable( table ) ;
        
        init = false;
    }
    
    return tedlarReverse;
}

G4OpticalSurface* artg4Materials::Millipore()
// Diffuse reflection based on reflectivity measurements made on Millipore paper
{
   static bool init = true;
   static G4OpticalSurface *millipore = new G4OpticalSurface("Millipore");

   if( init ){

      // type of optical surface
      millipore->SetType(dielectric_dielectric);
      millipore->SetModel(unified);
      millipore->SetFinish(groundbackpainted);
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations for PbF2 surface
      millipore->SetSigmaAlpha(facetAngleDistributionSigma);

      // Material Properties table

      const G4int nEntries = 24 ;

      G4double photonEnergy[ nEntries ] = 
	{ 1.38*eV,
	  1.55*eV,
	  1.77*eV,
	  1.82*eV,
	  1.88*eV,
	  1.94*eV,
	  2.0*eV,
	  2.07*eV,
	  2.14*eV,
	  2.21*eV,
	  2.3*eV,
	  2.38*eV,
	  2.48*eV,
	  2.58*eV,
	  2.7*eV,
	  2.82*eV,
	  2.95*eV,
	  3.1*eV,
	  3.31*eV,
	  3.54*eV,
	  3.81*eV,
	  4.13*eV,
	  4.51*eV,
	  4.96*eV
	 };

      // From Detector Elog 584
      G4double reflectivity[nEntries] = 
	{
	  0.972,
	  0.982,
	  0.984,
	  0.985,
	  0.987,
	  0.987,
	  0.988,
	  0.989,
	  0.991,
	  0.992,
	  0.993,
	  0.994,
	  0.995,
	  0.999,
	  1,
	  1,
	  1,
	  1,
	  1,
	  1,
	  0.967,
	  0.978,
	  0.951,
	  0.893
	};

      
      // refractive index for air gap
      G4double effectiveRefractiveIndex = 1.0;
      G4double refractiveIndex[nEntries];
      std::fill_n(refractiveIndex, nEntries, effectiveRefractiveIndex);

      // xtal surface is faceted; all reflections are specular using surface normal from distribution      
      G4double specularSpikeValue = 0.0;
      G4double specularLobeValue = 1.0;
      G4double backscatterValue = 0;
      G4double specularSpike[nEntries];
      G4double specularLobe[nEntries];
      G4double backscatter[nEntries];

      std::fill_n(specularSpike, nEntries, specularSpikeValue);
      std::fill_n(specularLobe, nEntries, specularLobeValue);
      std::fill_n(backscatter, nEntries, backscatterValue);

      G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
      table->AddProperty("RINDEX",                photonEnergy, refractiveIndex, nEntries ) ;
      table->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, specularSpike,   nEntries );
      table->AddProperty("SPECULARLOBECONSTANT",  photonEnergy, specularLobe,    nEntries );
      table->AddProperty("BACKSCATTERCONSTANT",   photonEnergy, backscatter,     nEntries );
      table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );


      millipore->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return millipore;
}

G4OpticalSurface* artg4Materials::MilliporeReverse()
// Optical surface for photons that would be entering the xtal
{
    static bool init = true;
    static G4OpticalSurface *milliporeReverse = new G4OpticalSurface("MilliporeReverse");
    
    if( init ){
        
        // type of optical surface
        milliporeReverse->SetType(dielectric_dielectric);
        milliporeReverse->SetModel(unified);
        milliporeReverse->SetFinish(groundfrontpainted);
        
        // Material Properties table
        
        const G4int nEntries = 24 ;
        
      G4double photonEnergy[ nEntries ] = 
	{ 1.38*eV,
	  1.55*eV,
	  1.77*eV,
	  1.82*eV,
	  1.88*eV,
	  1.94*eV,
	  2.0*eV,
	  2.07*eV,
	  2.14*eV,
	  2.21*eV,
	  2.3*eV,
	  2.38*eV,
	  2.48*eV,
	  2.58*eV,
	  2.7*eV,
	  2.82*eV,
	  2.95*eV,
	  3.1*eV,
	  3.31*eV,
	  3.54*eV,
	  3.81*eV,
	  4.13*eV,
	  4.51*eV,
	  4.96*eV
	 };

      // From Detector Elog 584
      G4double reflectivity[nEntries] = 
	{
	  0.972,
	  0.982,
	  0.984,
	  0.985,
	  0.987,
	  0.987,
	  0.988,
	  0.989,
	  0.991,
	  0.992,
	  0.993,
	  0.994,
	  0.995,
	  0.999,
	  1,
	  1,
	  1,
	  1,
	  1,
	  1,
	  0.967,
	  0.978,
	  0.951,
	  0.893
	};	               
        
        G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
        table->AddProperty("REFLECTIVITY",          photonEnergy, reflectivity,    nEntries );
        
        milliporeReverse->SetMaterialPropertiesTable( table ) ;
        
        init = false;
    }
    
    return milliporeReverse;
}

G4OpticalSurface* artg4Materials::Open()
// Optical surface for unwrapped PbF2 surface
// Specular lobe reflections at xtal surface (finish type = ground)
{
  static bool init = true;
  static G4OpticalSurface *open = new G4OpticalSurface("Open");

  if( init ){
    //type of optical surface
    open->SetType(dielectric_dielectric);
    open->SetModel(unified);
    open->SetFinish(ground);
    double facetAngleDistributionSigma = 0.07379; // based on slope calculations
    open->SetSigmaAlpha(facetAngleDistributionSigma);

    init = false;
  }

  return open;
}

G4OpticalSurface* artg4Materials::OpenReverse()
// Same as "Open" -- surface is the same no matter which way the photons pass through
{
    static bool init = true;
    static G4OpticalSurface *openReverse = new G4OpticalSurface("OpenReverse");
    
    if( init ){
        //type of optical surface
        openReverse->SetType(dielectric_dielectric);
        openReverse->SetModel(unified);
        openReverse->SetFinish(ground);
        double facetAngleDistributionSigma = 0.07379; // based on slope calculations
        openReverse->SetSigmaAlpha(facetAngleDistributionSigma);
        
        init = false;
    }
    
    return openReverse;
}

G4OpticalSurface* artg4Materials::GroundGlass()
// Rough surface for diffuser
{
    static bool init = true;
    static G4OpticalSurface *groundGlass = new G4OpticalSurface("GroundGlass");
    
    if( init ){
        //type of optical surface
        groundGlass->SetType(dielectric_dielectric);
        groundGlass->SetModel(unified);
        groundGlass->SetFinish(ground);
        double facetAngleDistributionSigma = 12 * deg;
           // sigma_alpha value for ground glass from Janecek and Williams,
           // IEEE Transactions on Nuclear Science 57, 964 (2010)
        groundGlass->SetSigmaAlpha(facetAngleDistributionSigma);
        
        
        // Material Properties table
        
        const G4int nEntries = 2 ;
        G4double photonEnergy[ nEntries ] = { 1.0*eV, 6.0*eV };

        // diffuse reflection probability is implicit:
        //         diffuse = 1 - specularSpike - specularLobe - backscatter
        G4double specularSpikeValue = 0.0;
        G4double specularLobeValue = 1.0;
        G4double backscatterValue = 0;
        G4double specularSpike[nEntries];
        G4double specularLobe[nEntries];
        G4double backscatter[nEntries];
        
        std::fill_n(specularSpike, nEntries, specularSpikeValue);
        std::fill_n(specularLobe, nEntries, specularLobeValue);
        std::fill_n(backscatter, nEntries, backscatterValue);
        
        G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
        table->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, specularSpike,   nEntries );
        table->AddProperty("SPECULARLOBECONSTANT",  photonEnergy, specularLobe,    nEntries );
        table->AddProperty("BACKSCATTERCONSTANT",   photonEnergy, backscatter,     nEntries );
        
        groundGlass->SetMaterialPropertiesTable( table ) ;

        init = false;
    }    
    return groundGlass;
}

G4OpticalSurface* artg4Materials::EtchedGlass()
// smooth surface for back of diffuser
{
    static bool init = true;
    static G4OpticalSurface *etchedGlass = new G4OpticalSurface("EtchedGlass");
    
    if( init ){
        //type of optical surface
        etchedGlass->SetType(dielectric_dielectric);
        etchedGlass->SetModel(unified);
        etchedGlass->SetFinish(ground);
        double facetAngleDistributionSigma = 4 * deg;
          // sigma_alpha value for etched glass from Janecek and Williams,
          // IEEE Transactions on Nuclear Science 57, 964 (2010)
          // chose etched glass because similar to our measured PbF2 sigma_alpha
        etchedGlass->SetSigmaAlpha(facetAngleDistributionSigma);
        
        
        // Material Properties table
        
        const G4int nEntries = 2 ;
        G4double photonEnergy[ nEntries ] = { 1.0*eV, 6.0*eV };
        
        // diffuse reflection probability is implicit:
        //         diffuse = 1 - specularSpike - specularLobe - backscatter
        G4double specularSpikeValue = 0.0;
        G4double specularLobeValue = 1.0;
        G4double backscatterValue = 0;
        G4double specularSpike[nEntries];
        G4double specularLobe[nEntries];
        G4double backscatter[nEntries];
        
        std::fill_n(specularSpike, nEntries, specularSpikeValue);
        std::fill_n(specularLobe, nEntries, specularLobeValue);
        std::fill_n(backscatter, nEntries, backscatterValue);
        
        G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
        table->AddProperty("SPECULARSPIKECONSTANT", photonEnergy, specularSpike,   nEntries );
        table->AddProperty("SPECULARLOBECONSTANT",  photonEnergy, specularLobe,    nEntries );
        table->AddProperty("BACKSCATTERCONSTANT",   photonEnergy, backscatter,     nEntries );
        
        etchedGlass->SetMaterialPropertiesTable( table ) ;
        
        init = false;
    }
    return etchedGlass;
}


namespace{

  struct map_t { G4String name; std::tr1::function<G4Material*()> func;};
  struct opticalmap_t { G4String name; std::tr1::function<G4OpticalSurface*()> func;};

#define MAKE_MAP_T(NAME) {""#NAME, artg4Materials::NAME}

  map_t namemap_[] = {
    //  Elements
    MAKE_MAP_T(Al),
    MAKE_MAP_T(Ar),
    MAKE_MAP_T(Be),
    MAKE_MAP_T(C),
    MAKE_MAP_T(Cr),
    MAKE_MAP_T(Cu),
    MAKE_MAP_T(F),
    MAKE_MAP_T(Fe),
    MAKE_MAP_T(H),
    MAKE_MAP_T(Mg),
    MAKE_MAP_T(N),
    MAKE_MAP_T(Nb),
    MAKE_MAP_T(O),
    MAKE_MAP_T(Pb),
    MAKE_MAP_T(Sb),
    MAKE_MAP_T(Si),
    MAKE_MAP_T(Ti),
    MAKE_MAP_T(W),
    MAKE_MAP_T(Zn),
    //  Compounds
    MAKE_MAP_T(Air),
    MAKE_MAP_T(Al5052),
    MAKE_MAP_T(Al6061),
    MAKE_MAP_T(BC404Scintillator),
    MAKE_MAP_T(BC408Scintillator),
    MAKE_MAP_T(BCF10ScintFiber),
    MAKE_MAP_T(BicronBC630),
    MAKE_MAP_T(Borosilicate),
    MAKE_MAP_T(Brass),
    MAKE_MAP_T(Conductor),
    MAKE_MAP_T(Epoxy),
    MAKE_MAP_T(H2O),
    MAKE_MAP_T(Kapton),
    MAKE_MAP_T(MacorCeramic),
    MAKE_MAP_T(Mylar),
    MAKE_MAP_T(NbTi),
    MAKE_MAP_T(NusilLS5257),
    MAKE_MAP_T(PbSb),
    MAKE_MAP_T(Vacuum),
    MAKE_MAP_T(Vacuum1),
    MAKE_MAP_T(PbF2),
    MAKE_MAP_T(Quartz),
    MAKE_MAP_T(SiPMSurfaceResin),
  };

  opticalmap_t opticalmap_[] = {
    MAKE_MAP_T(PolishedMetal),
    MAKE_MAP_T(PolishedMetalReverse),
    MAKE_MAP_T(Specular),
    MAKE_MAP_T(SpecularReverse),
    MAKE_MAP_T(Diffuse),
    MAKE_MAP_T(DiffuseReverse),
    MAKE_MAP_T(Black),
    MAKE_MAP_T(BlackReverse),
    MAKE_MAP_T(Tedlar),
    MAKE_MAP_T(TedlarReverse),
    MAKE_MAP_T(Millipore),
    MAKE_MAP_T(MilliporeReverse),
    MAKE_MAP_T(Open),
    MAKE_MAP_T(OpenReverse),
    MAKE_MAP_T(GroundGlass),
    MAKE_MAP_T(EtchedGlass),
  };
}


G4Material *artg4Materials::findByName(G4String name){
  std::string sname(name);
  for(int i=0; i!=sizeof(namemap_)/sizeof(namemap_[0]); ++i){
    std::string mname(namemap_[i].name);
    if( boost::algorithm::to_lower_copy(sname) ==
	boost::algorithm::to_lower_copy(mname) ){
      return (namemap_[i].func)();
    }
  }
  throw artg4Materials::material_not_found(name);
  return 0;
}


G4OpticalSurface *artg4Materials::findOpticalByName(G4String name){
  std::string sname(name);
  for(int i=0; i!=sizeof(opticalmap_)/sizeof(opticalmap_[0]); ++i){
    std::string mname(opticalmap_[i].name);
    if( boost::algorithm::to_lower_copy(sname) ==
	boost::algorithm::to_lower_copy(mname) ){
      return (opticalmap_[i].func)();
    }
  }
  throw artg4Materials::material_not_found(name);
  return 0;
}

#include <sstream>

const char* artg4Materials::material_not_found::what() const throw() {
  std::ostringstream o;
  o << "Material not found in database: " << payload_;
  message_ = o.str();
  return message_.c_str();
}

