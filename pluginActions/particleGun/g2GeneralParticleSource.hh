#ifndef g2GeneralParticleSource_hh
#define g2GeneralParticleSource_hh

// @file g2GeneralParticleSource.hh

// g2GeneralParticleSource is a modified and updated version of the
// GPS included with the distribution of GEANT4, details below.  I
// will add brief code documentation throughout the g2GPS files, with
// more detailed comments in the sections more relevant to g2MIGTRACE.
  
// Thanks to the good people at QinetiQ ltd. for their generously
// allowing the use of their code...by which I mean I stole it
// unabashedly...
    
// g2GPS uses the following modified modules:
// - g2GeneralParticleSource -> expanded from original G4
// - g2SingleParticleSource -> expanded and completely overhauled
// - g2SPSTimeDistribution -> newly scripted for g2GPS
    
// Original authorship information:
// - MODULE:       G4GeneralParticleSource
// - Version:      2.0
// - Date:         5/02/04
// - Author:       Fan Lei 
// - Organisation: QinetiQ ltd.
// - Customer:     ESA/ESTEC

// - Zach Hartwig 2005

// - Modified by Tasha Arvanitis, Adam Lyon (2012)

// The parameter set passed in must contain the following items:
// - multiple_vertex (bool): Determines whether we should create more than one
//       primary vertex in an event.
//       Default is false.

// - sources (list of parameter sets): A list of parameter sets describing the
//       source(s) that should be created in this g2GPS instance. Each 
//       parameter set must contain:
//       - intensity (double): The relative intensity of the source, which
//             is used to normalize the sources.
//       - approximatly a gazillion (technical term) parameters, some with
//             nested parameter sets, described in g2SingleParticleSource.hh.

#include "globals.hh"
#include <vector>

#include "G4Event.hh"
#include "g2SingleParticleSource.hh"

#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MesageLogger/MessageLogger.h"

// Put this class in the g-2 namespace
namespace gm2 {

  // Provides a modified General Particle Source to include time
  // distribution
  class g2GeneralParticleSource : public G4VPrimaryGenerator
  {
  public:
    // Constructor accepts a parameter set, rather than using a messenger.
    g2GeneralParticleSource(fhicl::ParameterSet);
    ~g2GeneralParticleSource();
  
    // Generate the much-anticipated primary particle(s)!
    void GeneratePrimaryVertex(G4Event*);
  
    // Some setters and getters
    int GetNumberofSource() { return sourceVector.size(); }
    void ListSource();
    void SetCurrentSourceto(int) ;
    void SetCurrentSourceIntensity(double);
    g2SingleParticleSource* GetCurrentSource() {return _currentSource;}
    int GetCurrentSourceIndex() { return _currentSourceIdx; }
    double GetCurrentSourceIntensity() 
    { return sourceIntensity[_currentSourceIdx]; }
    void ClearAll();
    void AddaSource (double);
    void DeleteaSource(int);

    // Set the verbosity level.
    void SetVerbosity(int i) {_currentSource->SetVerbosity(i);} ;

    // Set if multiple vertex per event.
    void SetMultipleVertex(bool av) {multiple_vertex = av;} ;

    // Set the particle species
    void SetParticleDefinition (G4ParticleDefinition * aParticleDefinition) 
    { _currentSource->SetParticleDefinition(aParticleDefinition); }

    G4ParticleDefinition * GetParticleDefinition () 
    { return _currentSource->GetParticleDefinition(); }

    void SetParticleCharge(double aCharge) 
    { _currentSource->SetParticleCharge(aCharge); }

    // Set polarization
    void SetParticlePolarization (G4ThreeVector aVal) 
    { _currentSource->SetParticlePolarization(aVal); }
    G4ThreeVector GetParticlePolarization ()  
    {return _currentSource->GetParticlePolarization();}

    // Set Time.
    void SetParticleTime(double aTime)  
    { _currentSource->SetParticleTime(aTime); }
    double GetParticleTime()  
    { return _currentSource->GetParticleTime(); }

    void SetNumberOfParticles(int i)  
    { _currentSource->SetNumberOfParticles(i); }
    int GetNumberOfParticles() 
    { return _currentSource->GetNumberOfParticles(); }

    G4ThreeVector GetParticlePosition()  
    { return _currentSource->GetParticlePosition();}
    G4ThreeVector GetParticleMomentumDirection()  
    { return _currentSource->GetParticleMomentumDirection();}
    double GetParticleEnergy()  
    {return _currentSource->GetParticleEnergy();}

  private:

    void IntensityNormalization();

  private:
    // Member data!
    bool _multiple_vertex;
    bool _normalised;
    int _currentSourceIdx;
    g2SingleParticleSource* _currentSource;
    std::vector <g2SingleParticleSource*> _sourceVector;
    std::vector <double> _sourceIntensity;
    std::vector <double> _sourceProbability;
    
    mf::LogInfo _logInfo;
  
  };

}
#endif
