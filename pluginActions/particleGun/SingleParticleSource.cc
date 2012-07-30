 /** @file SingleParticleSource.cc

    Provides the modified distribution of the G4SingleParticleSource
    that includes time distribution.

    - Zach Hartwig 2005
*/

#include "G4PrimaryParticle.hh"
#include "G4Event.hh"
#include "Randomize.hh"
#include <math.h>
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
#include "G4Ions.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"

#include "SingleParticleSource.hh"
//#include "inflectorConstruction.hh"
//#include "inflectorGeometry.hh"

#include <vector>

using std::string;
using fhicl::ParameterSet;
using std::vector;

artg4::SingleParticleSource::
  SingleParticleSource(ParameterSet const & p)
{
  // Initialize the variables that will be used for calculating the
  // input particle parameters (just in case they aren't determined later in
  // the constructor)
  x_i = y_i = 0.;
  xPrime_i = yPrime_i = 0.;
  pX_i = pY_i = pZ_i = pTotal = 0.;
  x_w = y_w = z_w =0.;
  pX_w = pY_w = pZ_w = 0.;
  sX_w = sY_w = sZ_w = 0.;

  // Initialize the generators
  biasRndm = new G4SPSRandomGenerator();
  posGenerator = new G4SPSPosDistribution();
  posGenerator->SetBiasRndm(biasRndm);
  angGenerator = new G4SPSAngDistribution();
  angGenerator->SetPosDistribution(posGenerator);
  angGenerator->SetBiasRndm(biasRndm);
  eneGenerator = new G4SPSEneDistribution();
  eneGenerator->SetBiasRndm(biasRndm);
  timeGenerator = new SPSTimeDistribution();
  timeGenerator->SetBiasRndm(biasRndm);

  // There are four easy categories most of these parameters fall into: 
  // position, angular distribution, energy distribution, and time 
  // distribution. Outside of these, there are some parameters relating to:
  // file import, histograms of biases, and the general particle gun. 

  // Sort out the position distribution, using the position-specific params
  setUpPositionDist(p.get<ParameterSet>("position"));

  // Sort out the angular distribution, using the angular distribution
  // parameters
  setUpAngularDist(p.get<ParameterSet>("angular"));
  
  // Sort out the energy distribution, using the energy distribution parameters
  setUpEnergyDist(p.get<ParameterSet>("energy"));
  
  // Sort out the time distribution, using the time distribution parameters
  setUpTimeDist(p.get<ParameterSet>("time"));

  // Figure out the file import stuff.
  setUpFileImport(p);

  // Figure out histogram/bias stuff.
  // I (Tasha) don't understand what's going on here, so I have a tricky time
  // translating it. To be implemented at a future time.
  //setUpHistos(p);

  // Set up the general particle gun.
  setUpParticleGun(p);

  // --------------------------------------------------------------------
  // --------------------------------------------------------------------
  // --------------------------------------------------------------------
  // --------------------------------------------------------------------

  // Initialise all variables with some reasonable defaults

  // Default particle parameters
  NumberOfParticlesToBeGenerated = 1;
  particle_definition = G4Geantino::GeantinoDefinition();
  G4ThreeVector zero;
  particle_momentum_direction = G4ParticleMomentum(1,0,0);
  particle_energy = 1.0*MeV;
  particle_position = zero;
  particle_time = 0.*ns;
  particle_polarization = zero;
  particle_charge = 0.0;
  particle_weight = 1.0;

  // Create all the necessary distribution generators
  biasRndm = new G4SPSRandomGenerator();
  posGenerator = new G4SPSPosDistribution();
  posGenerator->SetBiasRndm(biasRndm);
  angGenerator = new G4SPSAngDistribution();
  angGenerator->SetPosDistribution(posGenerator);
  angGenerator->SetBiasRndm(biasRndm);
  eneGenerator = new G4SPSEneDistribution();
  eneGenerator->SetBiasRndm(biasRndm);
  timeGenerator = new SPSTimeDistribution();
  timeGenerator->SetBiasRndm(biasRndm);

  // Set the verbosity default 
  verbosityLevel = 0;

  // Set the particle import defaults
  importFlag = false;
  importFileType = "turtle";
  fileSuccessfullyOpened = false;
    
  // Initialize the variables that will be used for calculating the
  // input particle parameters
  x_i = y_i = 0.;
  xPrime_i = yPrime_i = 0.;
  pX_i = pY_i = pZ_i = pTotal = 0.;
  x_w = y_w = z_w =0.;
  pX_w = pY_w = pZ_w = 0.;
  sX_w = sY_w = sZ_w = 0.;

  // --------------------------------------------------------------------
  // --------------------------------------------------------------------
  // --------------------------------------------------------------------
  // --------------------------------------------------------------------
  
}

// Boring destructor
artg4::SingleParticleSource::~SingleParticleSource()
{}

// Set up the position distribution (posGenerator). This is all just parameter
// extraction. See the header file for an explanation of what each parameter
// describes.
void artg4::SingleParticleSource::setUpPositionDist(ParameterSet const & p)
{
  posGenerator -> SetPosDisType(p.get<string>("type"));
  posGenerator -> SetPosDisShape(p.get<string>("shape"));
  
  vector<double> position = p.get<vector<double> >("position");
  posGenerator -> SetCentreCoords(G4ThreeVector(position[0]*cm,
						position[1]*cm,
						position[2]*cm));
  
  ParameterSet rotation = p.get<ParameterSet>("rotation");
  vector<double> rot1 = rotation.get<vector<double> >("rotation1");
  vector<double> rot2 = rotation.get<vector<double> >("rotation2");
  posGenerator -> SetPosRot1(G4ThreeVector(rot1[0],
					   rot1[1],
					   rot1[2]));
  posGenerator -> SetPosRot2(G4ThreeVector(rot2[0],
					   rot2[1],
					   rot2[2]));

  posGenerator -> SetHalfX(p.get<double>("half_x")*cm);
  posGenerator -> SetHalfY(p.get<double>("half_y")*cm);
  posGenerator -> SetHalfZ(p.get<double>("half_z")*cm);

  posGenerator -> SetRadius(p.get<double>("radius")*cm);
  posGenerator -> SetRadius0(p.get<double>("radius0")*cm);

  ParameterSet sigma = p.get<ParameterSet>("sigma");
  // This is a tricky bit. We want to either access the r value (which is
  // provided by default and possibly overloaded by the specific configuration
  // file), or both x and y. To do so, we check whether x and y are present
  // in 'sigma'. If so, we use them. Otherwise, we use the r value.
  vector<string> psetKeys = p.get_keys();
  vector<string>::const_iterator begin = psetKeys.begin();
  vector<string>::const_iterator end = psetKeys.end();
  if ((std::find(begin, end, "x") != end) && (std::find(begin, end, "y") != end)) {
    // We have an x and y; use them.
    posGenerator -> SetBeamSigmaInX(sigma.get<double>("x")*cm);
    posGenerator -> SetBeamSigmaInY(sigma.get<double>("y")*cm);    
  } 
  else {
    // We don't have an x and y, so use r.
    posGenerator -> SetBeamSigmaInR(sigma.get<double>("r")*cm);
  }

  posGenerator -> ConfineSourceToVolume(p.get<string>("confine_to"));

  ParameterSet para = p.get<ParameterSet>("para");
  posGenerator -> SetParAlpha(para.get<double>("alpha")*deg);
  posGenerator -> SetParTheta(para.get<double>("theta")*deg);
  posGenerator -> SetParPhi(para.get<double>("phi")*deg);
}

// Set up the angular distribution (angGenerator). This is all just parameter
// extraction. See the header file for an explanation of what each parameter
// describes.
void artg4::SingleParticleSource::setUpAngularDist(ParameterSet const & p)
{
  angGenerator -> SetAngDistType(p.get<string>("type"));

  ParameterSet rotation = p.get<ParameterSet>("rotation");
  vector<double> rot1 = rotation.get<vector<double> >("rotation1");
  vector<double> rot2 = rotation.get<vector<double> >("rotation2");
  angGenerator -> DefineAngRefAxes("angref1", G4ThreeVector(rot1[0],
							    rot1[1],
							    rot1[2]));
  angGenerator -> DefineAngRefAxes("angref2", G4ThreeVector(rot2[0],
							    rot2[1],
							    rot2[2]));

  angGenerator -> SetMinTheta(p.get<double>("min_theta")*deg);
  angGenerator -> SetMaxTheta(p.get<double>("max_theta")*deg);
  angGenerator -> SetMinPhi(p.get<double>("min_phi")*deg);
  angGenerator -> SetMaxPhi(p.get<double>("max_phi")*deg);

  ParameterSet sigma = p.get<ParameterSet>("sigma");
  // Unlike above, all of these sigmas are independent (r is for 1D, x and y for
  // 2D), so we don't have to go through the same thing we did for position.
  angGenerator -> SetBeamSigmaInAngR(sigma.get<double>("r")*deg);
  angGenerator -> SetBeamSigmaInAngX(sigma.get<double>("x")*deg);
  angGenerator -> SetBeamSigmaInAngY(sigma.get<double>("y")*deg);

  vector<double> focus = p.get<vector<double> >("focus_point");
  angGenerator -> SetFocusPoint(G4ThreeVector(focus[0]*cm,
					      focus[1]*cm,
					      focus[2]*cm));
  
  angGenerator -> SetUseUserAngAxis(p.get<bool>("use_user_axes"));
  angGenerator -> SetUserWRTSurface(p.get<bool>("use_surf_norm"));
}

// Set up the energy distribution for the particle gun.
void artg4::SingleParticleSource::setUpEnergyDist(ParameterSet const & p)
{
  // Use parameters to set up energy distribution for gun.
  eneGenerator -> SetEnergyDisType(p.get<string>("type"));
  eneGenerator -> SetEmin(p.get<double>("min")*keV);
  eneGenerator -> SetEmax(p.get<double>("max")*keV);
  eneGenerator -> SetMonoEnergy(p.get<double>("mono_energy")*keV);
  eneGenerator -> SetBeamSigmaInE(p.get<double>("gauss_sigma")*keV);
  eneGenerator -> SetTemp(p.get<double>("brem_bbody_temp"));
  eneGenerator -> SetEzero(p.get<double>("exp_ezero")*MeV);
  eneGenerator -> SetGradient(p.get<double>("lin_gradient")*(1/MeV));
  eneGenerator -> SetInterCept(p.get<double>("lin_intercept")*MeV);
  // Calculate distribution, just in case. Actually used for Cdg and Bbody.
  eneGenerator -> Calculate();
  // Back to reading in parameters
  eneGenerator -> InputEnergySpectra(p.get<bool>("energy_spec"));
  eneGenerator -> InputDifferentialSpectra(p.get<bool>("diff_spec"));
}

// Set up time distribution based on parameters. See the header file for
// descriptions (and units) for all parameters.
void artg4::SingleParticleSource::setUpTimeDist(ParameterSet const & p)
{
  timeGenerator -> SetTimeDisType(p.get<string>("type"));
  timeGenerator -> SetTimeMin(p.get<double>("min")*ns);
  timeGenerator -> SetTimeMax(p.get<double>("max")*ns);
  timeGenerator -> SetTimeMono(p.get<double>("mono_time")*ns);
  timeGenerator -> SetBeamSigmaInT(p.get<double>("gauss_sigma")*ns);
  timeGenerator -> SetTimeGradient(p.get<double>("lin_gradient")*(1/ns));
  timeGenerator -> SetTimeInterCept(p.get<double>("lin_intercept")*ns);
}

// Set up file imports, and, if necessary, import the muon configuration.
void artg4::SingleParticleSource::setUpFileImport(ParameterSet const & p)
{
  SetImportFlag(p.get<bool>("mu_from_file"));
  SetImportFileType(p.get<bool>("file_type"));
  // Check if we want to import from a file.
  if ( p.get<bool>("mu_from_file") ) {
    LoadImportFile(p.get<string>("file_name"));
  }
}

void artg4::SingleParticleSource::setUpHistos(ParameterSet const & p)
{
  G4cout << "setUpHistos not implemented." << G4endl;
}

void artg4::SingleParticleSource::setUpParticleGun(ParameterSet const & p) 
{
  vector<double> pDir = p.get<vector<double> >("direction");
  angGenerator -> SetParticleMomentumDirection(G4ThreeVector(pDir[0],
							     pDir[1],
							     pDir[2]));
  SetVerbosity(p.get<int>("verbose"));
}

// Function called by GPS to create the vertex
void artg4::SingleParticleSource::GeneratePrimaryVertex(G4Event *evt)
{
  if(particle_definition==NULL) return;
  
  if(verbosityLevel > 1)
    G4cout << " NumberOfParticlesToBeGenerated: "
	   << NumberOfParticlesToBeGenerated 
	   << G4endl;

  // Generate the vertex using imported or internally generated particles
  if(importFlag && fileSuccessfullyOpened)
    //    UseImportedParticles(evt);
    G4cout << "Imported particles aren't supported yet, because of a "
	   << "yicky dependence on inflector geometry." << G4endl;
  else
    UseInternallyGenerateParticles(evt);
  
}

/*
void artg4::SingleParticleSource::UseImportedParticles(G4Event *evt)
{
  // When this function is called, importVector has been loaded with
  // all the particles.  First, static member function of
  // "inflectorConstruction.hh" are called to set the inflector
  // position variables needed to calculate the correct position of
  // the particles.  Then, each particle is picked out by the current
  // eventID, which serves as a self-indexing number to cycle through
  // all particles in the vector

  // Below functions ensure that the new parameters of the imported
  // particles are calculated with the most up-to-date geometrical
  // values for the inflector!

  // ** WARNING ** The inflector parameters have changed!  'gamma' now
  // ** describes the total deviation from the tangent to the storage orbit
  // ** at the downstream point of injection, and 'tiltAngle' has been
  // ** replaced by 'zeta'.  This needs to be fixed!!
  // ** ZSH - 08 SEP 08

  inflectorGeometry& ig = inflectorGeometry::getInstance();
  G4double delta = ig.delta();
  G4double gamma = ig.gamma();
  G4double L = ig.half_length();
  G4double apRad = ig.aperture_off();

  G4int eventID = evt -> GetEventID();

  // Make sure that the values exist!
  if( !importVector.empty() )
    {
      x_i = (importVector.at(eventID).x) * cm;
      xPrime_i = importVector.at(eventID).xPrime * milliradian;
      y_i = (importVector.at(eventID).y) * cm;
      yPrime_i = importVector.at(eventID).yPrime * milliradian;
      pTotal = (importVector.at(eventID).pTotal) * GeV;
      sX_i = importVector.at(eventID).spin1;
      sY_i = importVector.at(eventID).spin2;
      sZ_i = importVector.at(eventID).spin3;
    }
  else
    G4cout << "\nWARNING: particle importVector was empty! Nothing injected!\n";
  
  {
    
    // Transform from inflector coordinates (at the upstream end of the
    // inflector) into world coordinates
    G4double point3_x = apRad*cos(delta) - (2*L*sin(delta+gamma));
    G4double point3_z = -apRad*sin(delta) - (2*L*cos(delta+gamma));
    
    x_w = point3_x - (x_i*cos(delta+gamma));
    y_w = y_i;
    z_w = point3_z + (x_i*sin(delta+gamma));
    
    // Using the momentum vectors angles with the x and y inflector
    // axes, calculate the momentum vector components in inflector
    // coordinates
    pY_i = pTotal * sin(xPrime_i);  
    pZ_i = ( pTotal * cos(yPrime_i) ) * cos(xPrime_i);
    pX_i = pZ_i * sin(xPrime_i);

    // Perform a rotation to transform the momentum vector components
    // from inflector coordinates to world coordinates.  
    G4double rAngle = delta + gamma;

    pX_w = ( pX_i * cos(rAngle) ) + ( pZ_i * sin(rAngle) );
    pY_w = pY_i;
    pZ_w = ( pX_i * (-1) * sin(rAngle) ) + ( pZ_i * cos(rAngle) );
    
    
    // Perfom a rotation to transform the imported spin components into
    // world spin coordinates
  }
  
  // Generate the position and time necessary to create the particle vertex
  // particle_position = posGenerator -> GenerateOne();
  particle_position = G4ThreeVector(x_w, y_w, z_w);
  particle_time = timeGenerator->GenerateOne(particle_definition);
  
  G4PrimaryVertex *vertex = new G4PrimaryVertex(particle_position, particle_time);
  
  // Set the remaining particle parameters
  for(G4int i=0; i<NumberOfParticlesToBeGenerated; i++)
    {
      G4double mass =  particle_definition->GetPDGMass();
      
      particle_energy = std::sqrt(pTotal*pTotal + mass*mass);      
      particle_momentum_direction = G4ParticleMomentum(pX_w,pY_w,pZ_w);
      
      if(verbosityLevel > 1)
	{
	  G4cout << "Particle name: "<<particle_definition->GetParticleName() << G4endl; 
	  G4cout << "       Energy: "<<particle_energy << G4endl;
	  G4cout << "     Position: "<<particle_position<< G4endl; 
	  G4cout << "    Direction: "<<particle_momentum_direction << G4endl;
	}
      
      G4PrimaryParticle* particle =
	new G4PrimaryParticle(particle_definition, pX_w, pY_w, pZ_w);
      particle->SetMass( mass );
      particle->SetCharge( particle_charge );
      particle->SetPolarization(0, 0, 0);
      //      particle->SetPolarization(Sx_w, Sy_w, Sz_w);
      
      vertex->SetPrimary( particle );
      
      // Set bweight equal to the multiple of all non-zero weights
      particle_weight = biasRndm->GetBiasWeight();
      // pass it to primary particle
      particle->SetWeight(particle_weight);
    }
  
  // Set the distribution weight and add particle to the primary vertex
  vertex->SetWeight(particle_weight);
  evt->AddPrimaryVertex( vertex );
  if(verbosityLevel > 1)
    G4cout << " Primary Vertex generated !"<< G4endl;   
  
}
*/
 
void artg4::SingleParticleSource::UseInternallyGenerateParticles(G4Event *evt)
{
  // Generate a position
  particle_position = posGenerator->GenerateOne();
  // Generate a time
  particle_time = timeGenerator->GenerateOne(particle_definition);
  
  // Create a new vertex
  G4PrimaryVertex* vertex = new G4PrimaryVertex(particle_position,particle_time);
  
  for( G4int i=0; i<NumberOfParticlesToBeGenerated; i++ ) {
    // Generate an angular distribution value
    particle_momentum_direction = angGenerator->GenerateOne();
    // Generate an energy value
    particle_energy = eneGenerator->GenerateOne(particle_definition);
    
    if(verbosityLevel >= 2)
      G4cout << "Creating primaries and assigning to vertex" << G4endl;

    // Create new primaries and set them to the vertex
    G4double mass =  particle_definition->GetPDGMass();
    G4double energy = particle_energy + mass;
    G4double pmom = std::sqrt(energy*energy-mass*mass);
    G4double px = pmom*particle_momentum_direction.x();
    G4double py = pmom*particle_momentum_direction.y();
    G4double pz = pmom*particle_momentum_direction.z();

    if(verbosityLevel > 1){
      G4cout << "Particle name: "<<particle_definition->GetParticleName() << G4endl; 
      G4cout << "       Energy: "<<particle_energy << G4endl;
      G4cout << "     Position: "<<particle_position<< G4endl; 
      G4cout << "    Direction: "<<particle_momentum_direction << G4endl;
    }

    G4PrimaryParticle* particle =
      new G4PrimaryParticle(particle_definition,px,py,pz);
    particle->SetMass( mass );
    particle->SetCharge( particle_charge );
    particle->SetPolarization(particle_polarization.x(),
			      particle_polarization.y(),
			      particle_polarization.z());
    
    if(verbosityLevel > 1)
      G4cout << " Polarization: " << particle->GetPolarization() << G4endl;

    vertex->SetPrimary( particle );
      
    // Set bweight equal to the multiple of all non-zero weights
    particle_weight = biasRndm->GetBiasWeight();
    // Pass it to primary particle
    particle->SetWeight(particle_weight);
  }
  // Now pass the weight to the primary vertex
  vertex->SetWeight(particle_weight);
  evt->AddPrimaryVertex( vertex );
  if(verbosityLevel > 1)
    G4cout << " Primary Vertex generated !"<< G4endl;   
}



void artg4::SingleParticleSource::SetParticleDefinition
  (G4ParticleDefinition* aParticleDefinition)
{
  particle_definition = aParticleDefinition;
  particle_charge = particle_definition->GetPDGCharge();
}


// UI function to set the verbosity
void artg4::SingleParticleSource::SetVerbosity(int vL)
{
  verbosityLevel = vL;
  posGenerator->SetVerbosity(vL);
  angGenerator->SetVerbosity(vL);
  eneGenerator->SetVerbosity(vL);
  timeGenerator->SetVerbosity(vL);
  G4cout << "Verbosity Set to: " << verbosityLevel << G4endl;
}

// UI function to determine source of to-br-injected particles
void artg4::SingleParticleSource::SetImportFlag(G4bool flag)
{ importFlag = flag; }

// UI function to set the type of particle import file
void artg4::SingleParticleSource::SetImportFileType(G4String type)
{ importFileType = type; }

// UI function to set the structure of the particle import file
void artg4::SingleParticleSource::SetImportFileStructure(G4String /*type*/)
{
  G4cout << "\n" << "**** WARNING ****: THIS FUNCTION HAS NOT YET BEEN IMPLEMENTED!!"
	 << "\n" << "                   YOU, THEREFORE, HAVE ACCOMPLISHED NOTHING BY"
	 << "\n" << "                   ATTEMPTING TO USE THIS COMMAND!!\n\n";   
}

// UI function to load the specified particle file
void artg4::SingleParticleSource::LoadImportFile(G4String fName)
{
  // Create the stream and open the user-specified file
  std::ifstream importParticles;
  importParticles.open(fName);
    
  // Test to make sure that the file successfully opened
  if( !importParticles.fail() )
    { 
      // Determine the appropriate file type.  Then, line by line
      // inside the while loop, set the struct parameters and push a
      // completed struct into the importVector.  When the stream
      // reaches the end-of-file character, loading is terminated

      if(importFileType == "turtle")
	while(importParticles.good())
	  {
	    if( importParticles.eof() ){
	      importParticles.close();
	      break;
	    } 

	    importParticles >> import.x
			    >> import.xPrime 
			    >> import.y 
			    >> import.yPrime 
			    >> import.pTotal 
			    >> import.null1
			    >> import.null2;

	    importVector.push_back(import);
	    
	  }
      
      else if(importFileType == "btraf")
	while(importParticles.good())
	  {
	    if( importParticles.eof() ){
	      importParticles.close();
	      break;
	    } 
	    importParticles  >> import.pTotal
			     >> import.x
			     >> import.xPrime
			     >> import.y 
			     >> import.yPrime
			     >> import.spin1 
			     >> import.spin2 
			     >> import.spin3;
	    
	    importVector.push_back(import);
	    
	  }	
      
      else if(importFileType == "userDefined")
	G4cout << "\nERROR: This function is not yet available!!\n\n";
      
      else
	G4cout << "\nERROR: User specified file type does not exist!!\n\n";
      
      // Get and printout the number of particles that have been
      // successfully loaded
      G4int size = importVector.size();
      if(size>0)
	G4cout << "\n\n...Particle loading successful!\n\n"
	       << "There are "<< size << " particles ready for launch, Cap'n!\n\n";

      // Set the flag for a successfully opened file
      fileSuccessfullyOpened = true;
      importParticles.close();
    }
  
  else
    G4cout << "\n\nERROR: MIGTRACE was unable to open the specified file!!\n\n";
}


void artg4::SingleParticleSource::ClearImportData()
{ 
  // If the vector has data, clear it all out!
  if(importVector.size() != 0){
    importVector.clear();
    G4cout << "\nAll currently particles have been deleted!\n\n";
  }
  else
    G4cout << "\nThere are no particles to clear!\n\n";
}
