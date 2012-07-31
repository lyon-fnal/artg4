// GeneralParticleSource.cc provides the implementations of the modified 
// General Particle Source.

// Authors:
//  - Zach Hartwig 2005
//  - Tasha Arvanitis, Adam Lyon 2012

#include "G4Event.hh"
#include "Randomize.hh"
#include "GeneralParticleSource.hh"

using std::endl;
using std::vector;

// Constructor uses the passed parameter set to set its member data, and 
// creates sources with the given nested parameter sets.
artg4::GeneralParticleSource::
  GeneralParticleSource(fhicl::ParameterSet const & p)
    : _multiple_vertex(p.get<bool>("multiple_vertex")), 
      _logInfo("GENERALPARTICLESOURCE")
{
  // Make sue all our source vectors are empty
  _sourceVector.clear();
  _sourceIntensity.clear();
  _sourceProbability.clear();

  // Get the parameter sets describing all the sources
  vector<fhicl::ParameterSet> sourceParams = 
    p.get<vector<fhicl::ParameterSet> >("sources");
  
  // Loop over our vector and create a single particle source for each
  // parameter set.
  for (size_t i = 0; i != sourceParams.size(); ++i) {
    fhicl::ParameterSet currParams = sourceParams[i];
    
    // Create the source
    _currentSource = new SingleParticleSource(currParams);
    _sourceVector.push_back(_currentSource);

    // Get the source intensity
    _sourceIntensity.push_back(currParams.get<double>("intensity"));

    // Lather, rinse, repeat.
  }

  _currentSourceIdx = int(_sourceVector.size() - 1);
  IntensityNormalization();
}

// Boring destructor.  
artg4::GeneralParticleSource::~GeneralParticleSource()
{}

// Normalize the intensities of our sources to find the probability that each
// source will be the producer of a given primary particle.
void artg4::GeneralParticleSource::IntensityNormalization()
{
  // Sum up the intensities of all sources
  double total  = 0.;
  size_t i = 0 ;
  for (i = 0; i < _sourceIntensity.size(); i++) 
    total += _sourceIntensity[i] ;
  
  // Clear out any old probabilities
  _sourceProbability.clear();

  // Determine the probability that each source will be the one to generate a 
  // given primary particle. These are then put into a specific form, so that 
  // a random number between 0 and 1 will determine exactly one source (the
  // one with the largest probability smaller than the random number), and that
  // the chance of source i being chosen in this manner is proportional to its
  // intensity. 
  _sourceProbability.push_back(_sourceIntensity[0]/total);
  for ( i = 1 ;  i < _sourceIntensity.size(); i++) {
    _sourceProbability.push_back(_sourceIntensity[i]/total + 
				_sourceProbability[i-1]); 
  }
  _normalised = true;
} 

// This is the method called by the action object in order to create a primary
// using the particle gun. 
void artg4::GeneralParticleSource::GeneratePrimaryVertex(G4Event* evt)
{
  if (!_multiple_vertex){
    // We only want to generate one primary vertex
    if (_sourceIntensity.size() > 1) {
      // We have multiple sources, and need to choose just one.

      // Make sure that the probabilities in our source vectors are up-to-date
      if (!_normalised) IntensityNormalization();

      // Pick one of our single-particle sources randomly
      double rndm = G4UniformRand();
      size_t i = 0 ;
      while ( rndm > _sourceProbability[i] ) {
	i++;
      }
      
      // Set '_currentSource' to the random source we ended up with.
      _currentSource = _sourceVector[i];
    }
    
    // Use our current source (either the only one we have or a randomly chosen
    // one of our collection) to generate the vertex.
    _currentSource-> GeneratePrimaryVertex(evt);
  } 

  else {
    // We want to use all of our sources! Note that this doesn't take the
    // source intensities into account.
    for (size_t i = 0; i <  _sourceIntensity.size(); i++) {
      _sourceVector[i]->GeneratePrimaryVertex(evt); 
    }
  }
}

// Below are many setters and getters, most (all?) of which are unused 
// currently, but may conceivably be useful at some point in the future.

/*
// Add a new source with the given intensity, and make it current. 
// Since we don't have a parameter set to pass in, this method isn't used
// and is thus commented out.
void artg4::GeneralParticleSource::AddaSource(double intensity)
{
  _currentSource = new SingleParticleSource();
  _sourceVector.push_back(_currentSource);
  _sourceIntensity.push_back(intensity);
  _currentSourceIdx = int(_sourceVector.size() - 1);
  IntensityNormalization();
}
*/

// Give some information on the sources.
void artg4::GeneralParticleSource::ListSource()
{
  _logInfo << " The number of particle source is " 
	   << _sourceIntensity.size() << endl;
  for (size_t i = 0 ; i < _sourceIntensity.size(); i++) 
    _logInfo << "   source " << i 
	     << " intensity is " << _sourceIntensity[i] << endl;
}

// Choose a new source to call current
void artg4::GeneralParticleSource::SetCurrentSourceto(int aV)
{
  size_t id = size_t (aV) ;
  // Check that the index is valid
  if ( id <= _sourceIntensity.size() ) {
    _currentSourceIdx = aV;
    _currentSource = _sourceVector[id];
  } 
  else {
    _logInfo << " source index is invalid " << endl;
    _logInfo << "    it should be <= " << _sourceIntensity.size() << endl;
  }
}

// Set the intensity of the current source
void artg4::GeneralParticleSource::SetCurrentSourceIntensity(double aV)
{
  _sourceIntensity[_currentSourceIdx] = aV;
  _normalised = false;
}

// Remove all sources
void artg4::GeneralParticleSource::ClearAll()
{
  _currentSourceIdx = -1;
  _currentSource = 0;
  _sourceVector.clear();
  _sourceIntensity.clear();
  _sourceProbability.clear();
}

// Remove a source from our collections.
void artg4::GeneralParticleSource::DeleteaSource(int aV)
{
  size_t id = size_t (aV) ;
  // Check that the passed index is valid
  if ( id <= _sourceIntensity.size() ) {
    // Remove the relevant entries. No need to remove the one from the 
    // probability vector - that whole vector will be remade when we 
    // normalize again.
    _sourceVector.erase(_sourceVector.begin()+aV);
    _sourceIntensity.erase(_sourceIntensity.begin()+aV);
    _normalised = false ;

    // Check if the given index was our current source. If so, find a new
    // source to call current.
    if (_currentSourceIdx == aV ) { 
	if ( _sourceIntensity.size() > 0 ) { 
	  _currentSource = _sourceVector[0];
	  _currentSourceIdx = 1;
	} else {
	  _currentSource = 0;
	  _currentSourceIdx = -1;
	}
    }	  		
  } 
  else {
    _logInfo << " source index is invalid " << endl;
    _logInfo << "    it shall be <= " << _sourceIntensity.size() << endl;
  }
} 


