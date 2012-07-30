//
// Override the G4RunManager class so that the Gm2 framework can drive
// the event loop.
////
// Original author Rob Kutschke
//
//
// Notes:
// 1) In G4RunManager the counter i_event is used as the event number.
//    In this code it is taken from the event number of the art::event.
//
// Implementation file for @Gm2G4RunManager@


// Gm2 includes.
#include "gm2g4/Core/Gm2G4RunManager.h"

// Includes from G4.
#include "G4UImanager.hh"
#include "G4ScoringManager.hh"
#include "G4Timer.hh"
#include "G4Run.hh"

using namespace std;

namespace gm2 {
  
  // If the c'tor is called a second time, the c'tor of base will
  // generate an exception.
  Gm2G4RunManager::Gm2G4RunManager():
  G4RunManager(),
  _macroFile(0),
  _n_select(-1),
  _nProcessed(0),
  _realElapsed(0.),
  _systemElapsed(0.),
  _userElapsed(0.),
  _msg(""){
  }
  
  // Destructor of base is called automatically.  No need to do anything.
  Gm2G4RunManager::~Gm2G4RunManager(){
  }
  
  // Do the "begin run" parts of BeamOn.
  void Gm2G4RunManager::BeamOnBeginRun( unsigned int runNumber, const char* macroFile, G4int n_select){
    
    SetRunIDCounter(runNumber);
    
    bool cond = ConfirmBeamOnCondition();
    if(!cond){
      // throw here
      return;
    }
    
    // Initialize member data for the new run.
    _macroFile     = macroFile;
    _n_select      = n_select;
    _msg           = "";
    _nProcessed    = 0;
    _realElapsed   = 0;
    _systemElapsed = 0;
    _userElapsed   = 0;
    
    // Construct command to execute the macro.
    if(_macroFile!=0){
      _msg = "/control/execute ";
      _msg += _macroFile;
    } else{
      _n_select = -1;
    }
    
    numberOfEventToBeProcessed = 1;
    ConstructScoringWorlds();
    RunInitialization();
  }
  
  // Do the "per event" part of DoEventLoop.
  void Gm2G4RunManager::BeamOnDoOneEvent( int eventNumber){
    
    timer->Start();
    
    // This is the body of the event loop from DoEventLoop().
    currentEvent = GenerateEvent(eventNumber);
    eventManager->ProcessOneEvent(currentEvent);
    AnalyzeEvent(currentEvent);
    UpdateScoring();
    
    if(_nProcessed<_n_select) G4UImanager::GetUIpointer()->ApplyCommand(_msg);
    
    // Should pause, not stop, if I can do that.
    timer->Stop();
    
    // Accumulate time spent in G4 for all events in this run.
    _realElapsed   += timer->GetRealElapsed();
    _systemElapsed += timer->GetSystemElapsed();
    _userElapsed   += timer->GetUserElapsed();
    
    
    if(verboseLevel>0){
      
      G4int oldPrecision = G4cout.precision(3);
      std::ios::fmtflags oldFlags = G4cout.flags();
      G4cout.setf(std::ios::fixed,std::ios::floatfield); 
      
      G4cout << "TimeEvent> "
      << eventNumber << " "
      << G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID() << " "
      << timer->GetRealElapsed() << " "
      << timer->GetUserElapsed() + timer->GetSystemElapsed() << " "
      << _userElapsed+_systemElapsed
      << G4endl;
      
      G4cout.setf(oldFlags);
      G4cout.precision(oldPrecision);
      
    }
    
  }
  
  void Gm2G4RunManager::BeamOnEndEvent(){
    
    StackPreviousEvent(currentEvent);
    currentEvent = 0;
    
    ++_nProcessed;
  }
  
  // Do the "end of run" parts of DoEventLoop and BeamOn.
  void Gm2G4RunManager::BeamOnEndRun(){
    
    // From G4RunManager::DoEventLoop
    if(verboseLevel>0){
      
      G4cout << "G4Run terminated." << G4endl;
      G4cout << "G4Run Summary" << G4endl;
      if(runAborted)
      { G4cout << "  G4Run Aborted after " << _nProcessed << " events processed." << G4endl; }
      else
      { G4cout << "  Number of events processed : " << _nProcessed << G4endl; }
      G4cout << "  User="  << _userElapsed
      << "s Real="  << _realElapsed
      << "s Sys="   << _systemElapsed
      << G4endl;
      
      G4int oldPrecision = G4cout.precision(3);
      std::ios::fmtflags oldFlags = G4cout.flags();
      G4cout.setf(std::ios::fixed,std::ios::floatfield); 
      
      G4cout << "TimeReport> Time report complete in ";
      G4cout << _realElapsed;
      G4cout << " seconds"
      << G4endl;
      
      G4cout.setf(oldFlags);
      G4cout.precision(oldPrecision);
      
    }
    
    // From G4RunManager::BeamOn.
    RunTermination();
  }
  
} // end namespace gm2
