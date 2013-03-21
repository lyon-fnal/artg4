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
      G4double wavelengths[ nEntries ] =
	 { 200.*nm, 270.*nm, 280.*nm, 700.*nm, 950.*nm };
      G4double transmission[ nEntries ] = { 0., 0., 0.95, 0.95, 0.95 } ;

      G4double photonEnergy[ nEntries ] ;
      G4double refractiveIndex[ nEntries ] ;
      G4double absorptionLength[ nEntries ] ;

      for( int i = 0 ; i < nEntries ; ++i )
      {
	 photonEnergy[ i ] = 0.001240 * MeV * nm / wavelengths[ i ] ;
      	 refractiveIndex[ i ] = 1.465 ; // actual index of Bicron BC630
	 // refractiveIndex[ i ] = 1.665 ; // higher index for testing
	 absorptionLength[ i ] = -0.1*mm / log( transmission[ i ] ) ;
      }

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
      const G4int nEntries = 7 ;

      // Transmission coefficients measured for 186mm long cyrstal
    G4double wavelengths[ nEntries ] =
       { 200.*nm, 250.*nm, 300.*nm, 350.*nm, 400.*nm, 800.*nm, 1240.*nm } ;
    G4double transmission[ nEntries ] = { 0., 0., 0.60, 0.74, 0.76, 0.82, 0.88 } ;

    G4double photonEnergy[ nEntries ] ;
    G4double refractiveIndex[ nEntries ] ;
    G4double absorptionLength[ nEntries ] ;

    for( int i = 0 ; i < nEntries ; ++i )
    {
       photonEnergy[ i ] = 0.001240 * MeV * nm / wavelengths[ i ] ;
       refractiveIndex[ i ] = 1.82 ;
       absorptionLength[ i ] = -186.*mm / log( transmission[ i ] ) ;
    }

    G4MaterialPropertiesTable* table = new G4MaterialPropertiesTable() ;
    table->AddProperty( "RINDEX", photonEnergy, refractiveIndex, nEntries ) ;
    table->AddProperty( "ABSLENGTH", photonEnergy, absorptionLength, nEntries ) ;

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


G4OpticalSurface* artg4Materials::Millipore()
{ // optical surfaces don't work quite the way we thought they did when we wrote this
  //  ---- we haven't been using this "Millipore" wrapping ----
   static bool init = true;
   static G4OpticalSurface *millipore = new G4OpticalSurface("Millipore");

   if( init ){

      // type of optical surface
      millipore->SetType(dielectric_dielectric);
      millipore->SetModel(unified);
      millipore->SetFinish(polishedbackpainted);
      double facetSlopeDistributionSigma = 0; // the geant4 code calls this "sigma_alpha"
      millipore->SetSigmaAlpha(facetSlopeDistributionSigma);

      // Material Properties table

      const G4int nEntries = 12 ;

      // take the reflectance of millipore from the measurement shown in 
      // https://muon.npl.washington.edu/elog/g2/Detectors/357
      // Note: that measurement stops at 1.55 eV (aboutr 800 nm), and I've just extrapolated
      // flat down to 1 eV
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

      G4double reflectivity[nEntries] = 
	 { 0.976,
	   0.976,
	   0.979,
	   0.966,
	   0.94,
	   0.912,
	   0.827,
	   0.438,
	   0.391,
	   0.079,
	   0.0474,
	   0.044
	 };

      // assume the millipore is not optically coupled, since it does not bind
      //  to the surface.  There is then a thin layer of air, and the effective
      //  index is 1.0
      G4double effectiveRefractiveIndex = 1.0;
      G4double refractiveIndex[nEntries];
      std::fill_n(refractiveIndex, nEntries, effectiveRefractiveIndex);

      // I believe that what GEANT4 means by efficiency is the transmission 
      // efficiency
//      G4double transmissionEfficiency = 0;
//      G4double efficiency[nEntries];
//      std::fill_n(efficiency, nEntries, transmissionEfficiency);
      // the above didn't work to make the material opaque.  Instead, set the absorption length to 0
      G4double zeroLength = 0;
      G4double absorptionLength[nEntries];
      std::fill_n(absorptionLength, nEntries, zeroLength);

      // UNIFIED model parameters
      // specular spike: specular reflection (theta_reflect = theta_incident) relative to average surface plane
      // specular lobe:  specular reflection relative to local surfance normal (rough polished surfaces)
      // backscatter: fraction of light that does just that: would result physically from multiple reflections from microfacets
      // diffuse or lambertion: calculated as (1 - sum(other three))
      // initially estimate 
      // -- from tyvek, where 1/2 - 2/3 of reflection is specular
      // -- further assuming that the PbF2 crystal surface is highly polished
      
      G4double specularSpikeValue = 0.5;
      G4double specularLobeValue = 0;
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
      table->AddProperty("ABSLENGTH",             photonEnergy, absorptionLength,nEntries ); 
//      table->AddProperty("EFFICIENCY",            photonEnergy, efficiency,      nEntries ); 

      millipore->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return millipore;
}


G4OpticalSurface* artg4Materials::Specular()
// reflectivity = 1, pure specular reflection, with air gap
{
   static bool init = true;
   static G4OpticalSurface *specular = new G4OpticalSurface("Specular");

   if( init ){

      // type of optical surface
      specular->SetType(dielectric_dielectric);
      specular->SetModel(unified);
      specular->SetFinish(polishedbackpainted); // "polished" means wrapping does specular reflection
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations
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


G4OpticalSurface* artg4Materials::SpecularNoGap()
// reflectivity = 1, pure specular reflection, with no air gap
//    (probably the same as "polished" finish)
{
   static bool init = true;
   static G4OpticalSurface *specularNoGap = new G4OpticalSurface("SpecularNoGap");

   if( init ){

      // type of optical surface
      specularNoGap->SetType(dielectric_dielectric);
      specularNoGap->SetModel(unified);
      specularNoGap->SetFinish(polishedbackpainted); // "polished" means wrapping does specular reflection
      double facetSlopeDistributionSigma = 0; // the geant4 code calls this "sigma_alpha"
      specularNoGap->SetSigmaAlpha(facetSlopeDistributionSigma);

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

      // refractive index = same as PbF (no air gap)
      G4double effectiveRefractiveIndex = 1.82;
      G4double refractiveIndex[nEntries];
      std::fill_n(refractiveIndex, nEntries, effectiveRefractiveIndex);

      // all reflection at xtal surface is specular, perfectly smooth xtal surface
      G4double specularSpikeValue = 1.0;
      G4double specularLobeValue = 0;
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

      specularNoGap->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return specularNoGap;
}


G4OpticalSurface* artg4Materials::Diffuse()
// reflectivity = 1, pure diffuse reflection, with air gap; specular reflection at xtal surface
{
   static bool init = true;
   static G4OpticalSurface *diffuse = new G4OpticalSurface("Diffuse");

   if( init ){

      // type of optical surface
      diffuse->SetType(dielectric_dielectric);
      diffuse->SetModel(unified);
      diffuse->SetFinish(groundbackpainted); // "ground" means wrapping does diffuse reflection
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations
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


G4OpticalSurface* artg4Materials::SuperDiffuse()
// reflectivity = 1, pure diffuse reflection, with air gap; diffuse reflection at xtal surface
{
   static bool init = true;
   static G4OpticalSurface *superDiffuse = new G4OpticalSurface("Super Diffuse");

   if( init ){

      // type of optical surface
      superDiffuse->SetType(dielectric_dielectric);
      superDiffuse->SetModel(unified);
      superDiffuse->SetFinish(groundbackpainted); // "ground" means wrapping does diffuse reflection
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations
      superDiffuse->SetSigmaAlpha(facetAngleDistributionSigma);
   

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

      // all reflection at xtal surface is diffuse
      G4double specularSpikeValue = 0;
      G4double specularLobeValue = 0;
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

      superDiffuse->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return superDiffuse;
}


G4OpticalSurface* artg4Materials::Black()
// reflectivity = 0, with air gap; specualar spike reflections at xtal surface
{
   static bool init = true;
   static G4OpticalSurface *black = new G4OpticalSurface("Black");

   if( init ){

      // type of optical surface
      black->SetType(dielectric_dielectric);
      black->SetModel(unified);
      black->SetFinish(polishedbackpainted);
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations
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


G4OpticalSurface* artg4Materials::RoughBlack()
// reflectivity = 0, with air gap; specular lobe reflections at xtal surface
// ---- This wrapping is now the same as "Black" ----
{
   static bool init = true;
   static G4OpticalSurface *roughblack = new G4OpticalSurface("RoughBlack");

   if( init ){

      // type of optical surface
      roughblack->SetType(dielectric_dielectric);
      roughblack->SetModel(unified);
      roughblack->SetFinish(polishedbackpainted);
      double facetAngleDistributionSigma = 0.07379; // based on slope calculations
      roughblack->SetSigmaAlpha(facetAngleDistributionSigma);

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
      
      // all reflection at xtal surface is specular lobe
      G4double specularSpikeValue = 0;
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


      roughblack->SetMaterialPropertiesTable( table ) ;

      init = false;
   }
  
   return roughblack;
}


G4OpticalSurface* artg4Materials::Open()
// Specular lobe reflections at xtal surface (finish type = ground)
// This is different from surface wrapping "None" because "None" makes  a perfectly smooth crystal surface
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
    MAKE_MAP_T(PbSb),
    MAKE_MAP_T(Vacuum),
    MAKE_MAP_T(Vacuum1),
    MAKE_MAP_T(PbF2),
    MAKE_MAP_T(Quartz),
  };

  opticalmap_t opticalmap_[] = {
    MAKE_MAP_T(PolishedMetal),
    MAKE_MAP_T(Millipore),
    MAKE_MAP_T(Specular),
    MAKE_MAP_T(SpecularNoGap),
    MAKE_MAP_T(Diffuse),
    MAKE_MAP_T(Black),
    MAKE_MAP_T(SuperDiffuse),
    MAKE_MAP_T(RoughBlack),
    MAKE_MAP_T(Open),
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

