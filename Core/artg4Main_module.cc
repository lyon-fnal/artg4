// artg4Main is the main producer module for Geant.

// artg4Main_module.cc replicates many GEANT programs' @main()@ driver. It
// creates and initializes the run manager, controls the beginning and end of 
// events, and controls visualization.

// Authors: Tasha Arvanitis, Adam Lyon

// Date: July 2012

// Art includes
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Run.h"

// Local includes (like actions)
#include "artg4/geantInit/ArtG4RunManager.hh"
#include "artg4/geantInit/ArtG4DetectorConstruction.hh"

// The actions
#include "artg4/geantInit/ArtG4EventAction.hh"
#include "artg4/geantInit/ArtG4PrimaryGeneratorAction.hh"
#include "artg4/geantInit/ArtG4RunAction.hh"
#include "artg4/geantInit/ArtG4SteppingAction.hh"
#include "artg4/geantInit/ArtG4StackingAction.hh"
#include "artg4/geantInit/ArtG4TrackingAction.hh"

// Services
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "artg4/services/ActionHolder_service.hh"
#include "artg4/services/DetectorHolder_service.hh"
#include "artg4/services/PhysicsListHolder_service.hh"
#include "art/Framework/Services/Optional/RandomNumberGenerator.h"


// G4 includes
#ifdef G4VIS_USE
#include "Geant4/G4VisExecutive.hh"
#endif

#include "Geant4/G4UImanager.hh"
#include "Geant4/G4UIterminal.hh"

using namespace std;

namespace artg4 {

  // Define the producer
  class artg4Main : public art::EDProducer {
  
  public:

    // Constructor
    explicit artg4Main(fhicl::ParameterSet const & p);

    // Destructor
    virtual ~artg4Main();

    // Overriding producer members
    virtual void produce(art::Event & e) override;
    virtual void beginJob() override;
    virtual void beginRun(art::Run &r) override;
    virtual void endRun(art::Run &) override;

  private:
    // Our custom run manager
    unique_ptr<ArtG4RunManager> runManager_;
  
    // G4 session and managers
    G4UIsession* session_;
    G4UImanager* UI_;

    // Visualization manager if necessary
#ifdef G4VIS_USE
    G4VisManager* visManager_;
#endif

    // Determine whether we should use visualization
    // False by default, can be set by config file
    bool enableVisualization_;

    // Directory path(s), in colon-delimited list, in which we should look for
    // macros, or the name of an environment variable containing that path.
    // Contains only the current directory ('.') by default, but can be
    // set by config file
    string macroPath_;

    // And a tool to find files along that path
    // Initialized based on macroPath_.
    cet::search_path pathFinder_;
  
    // Name of a macro file for visualization
    // 'vis.mac' by default, and can be customized by config file.
    string visMacro_;

    // Boolean to determine whether we pause execution after each event
    // If it's true, then we do. Otherwise, we pause only after all events
    // have been produced.
    // False by default, can be changed by afterEvent in FHICL
    bool pauseAfterEvent_;
    
    // Run diagnostic level (verbosity)
    int rmvlevel_;
    
    // When to pop up user interface
    bool uiAtBeginRun_;
    bool uiAtEndEvent_; // set by afterEvent in FHICL
    
    // What to do at the end of the event
    // Choices are
    //     pass -- do nothing
    //     pause -- Let user press return at the end of each event
    //     ui    -- show the UI at the end of the event
    std::string afterEvent_;
    
    // Message logger
    mf::LogInfo logInfo_;
  };
}

// Constructor - set parameters
artg4::artg4Main::artg4Main(fhicl::ParameterSet const & p)
  : runManager_(),
    session_(0),
    UI_(0),
    enableVisualization_( p.get<bool>("enableVisualization",false)),
    macroPath_( p.get<std::string>("macroPath",".")),
    pathFinder_( macroPath_),
    visMacro_( p.get<std::string>("visMacro", "vis.mac")),
    pauseAfterEvent_(false),
    rmvlevel_( p.get<int>("rmvlevel",0)),
    uiAtBeginRun_( p.get<bool>("uiAtBeginRun", false)),
    uiAtEndEvent_(false),
    afterEvent_( p.get<std::string>("afterEvent", "pass")),
    logInfo_("ArtG4Main")
{
  // We need all of the services to run @produces@ on the data they will store. We do this
  // by retrieving the holder services.
  art::ServiceHandle<ActionHolderService> actionHolder;
  art::ServiceHandle<DetectorHolderService> detectorHolder;
  
  // And running @callArtProduces@ on each
  actionHolder -> callArtProduces(this);
  detectorHolder -> callArtProduces(this);
  
  // Set up the random number engine.
  // See the documentation in RandomNumberHeader.h for
  // how this works. Note that @createEngine@ is a member function
  // of our base class (actually, a couple of base classes deep!).
  // Note that the name @G4Engine@ is special. 
  createEngine( 12345, "G4Engine");
  
  // Handle the afterEvent setting
  if ( afterEvent_ == "ui" ) {
    uiAtEndEvent_ = true;
  }
  else if ( afterEvent_ == "pause" ) {
    pauseAfterEvent_ = true;
  }
}

// Destructor
artg4::artg4Main::~artg4Main()
{}

// At begin job
void artg4::artg4Main::beginJob()
{
  // Set up run manager
  mf::LogDebug("Main_Run_Manager") << "In begin job";
  runManager_.reset( new ArtG4RunManager );
}

// At begin run
void artg4::artg4Main::beginRun(art::Run & r)
{  
  // Get the physics list and pass it to Geant and initialize the list if necessary
  art::ServiceHandle<PhysicsListHolderService> physicsListHolder;
  runManager_->SetUserInitialization( physicsListHolder->makePhysicsList() );
  physicsListHolder->initializePhysicsList();
  
  // Get all of the detectors and initialize them
  art::ServiceHandle<DetectorHolderService> detectorHolder;
  detectorHolder->initialize();
  
  // Build the detectors' logical volumes
  detectorHolder -> constructAllLVs();

  // Declare the detector construction to Geant
  runManager_->SetUserInitialization(new ArtG4DetectorConstruction);
  
  // Get all of the actions and initialize them
  art::ServiceHandle<ActionHolderService> actionHolder;
  actionHolder->initialize();
  
  // Store the run in the action holder
  actionHolder->setCurrArtRun(r);
  
  // Declare the primary generator action to Geant
  runManager_->SetUserAction(new ArtG4PrimaryGeneratorAction);

  // Note that these actions (and ArtG4PrimaryGeneratorAction above) are all
  // generic actions that really don't do much on their own. Rather, to 
  // use the power of actions, one must create action objects (derived from
  // @ActionBase@) and register them with the Art @ActionHolder@ service.
  // See @ActionBase@ and/or @ActionHolderService@ for more information.
  runManager_ -> SetUserAction(new ArtG4SteppingAction);
  runManager_ -> SetUserAction(new ArtG4StackingAction);
  runManager_ -> SetUserAction(new ArtG4EventAction);
  runManager_ -> SetUserAction(new ArtG4TrackingAction);
  runManager_ -> SetUserAction(new ArtG4RunAction);

  runManager_->Initialize();

  //get the pointer to the User Interface manager   
  UI_ = G4UImanager::GetUIpointer();  

  // Set up visualization if it's allowed by current values of env. variables
#ifdef G4VIS_USE

  // Turn on visualization if necessary
  if (enableVisualization_) {
    logInfo_ << "Initializing visualization\n" << endl;

    // Create and initialize the visualization manager
    visManager_ = new G4VisExecutive;
    visManager_->Initialize();

    // Find the macro (or try to) along the directory path.
    string macroLocation = "";
    bool macroWasFound = pathFinder_.find_file(visMacro_, macroLocation);
    logInfo_ << "Finding path for " << visMacro_ << "...\nSearch " 
	     << (macroWasFound ? "successful " : "unsuccessful ")
	     << "and path is: \n" << macroLocation << "\n" << endl;

    // Execute the macro if we were able to find it
    if (macroWasFound) {
      // Create the string containing the execution command
      logInfo_ << "Executing macro: " << visMacro_ << "\n" << endl;
      string commandToExecute = "/control/execute ";
      commandToExecute.append(macroLocation);
      UI_->ApplyCommand(commandToExecute); 

    } else {
      // If it wasn't found...
      // Leave a message for the user ... 
      logInfo_ << "Unable to find " << visMacro_ << " in the path(s) "
	       << macroPath_ << endl;
      // ... and disable visualization for the future
      enableVisualization_ = false;
      delete visManager_;

    } // if the macro was found

  } // if visualization was enabled

#endif // G4VIS_USE
  
  // Open a UI if asked
  if ( uiAtBeginRun_ ) {
    session_ = new G4UIterminal;
    session_->SessionStart();
    delete session_;
  }

  // Start the Geant run!
  runManager_ -> BeamOnBeginRun(r.id().run());
}

// Produce the Geant event
void artg4::artg4Main::produce(art::Event & e)
{
  // The holder services need the event
  art::ServiceHandle<ActionHolderService> actionHolder;
  art::ServiceHandle<DetectorHolderService> detectorHolder;
  
  actionHolder -> setCurrArtEvent(e);
  detectorHolder -> setCurrArtEvent(e);

  // Begin event
  runManager_ -> BeamOnDoOneEvent(e.id().event());
  
  logInfo_ << "Producing event " << e.id().event() << "\n" << endl;

  // Done with the event
  runManager_ -> BeamOnEndEvent();

#ifdef G4VIS_USE
  // If visualization is enabled, and we want to pause after each event, do
  // the pausing.
  if (enableVisualization_) {
    
    // Flush the visualization
    //UI_->ApplyCommand("/tracking/storeTrajectory 1");
    UI_->ApplyCommand("/vis/viewer/flush");
    
    if ( uiAtEndEvent_ ) {
      session_ = new G4UIterminal;
      session_->SessionStart();
      delete session_;
    }
    
    if ( pauseAfterEvent_ ) {
      // Use cout so that it is printed to console immediately.
      // logInfo_ prints everything at once, so if we used that, we would
      // find out that we should press ENTER to continue only *after* we'd
      // actually done so!
      cout << "Pausing so you can appreciate visualization. "
      << "Hit ENTER to continue." << std::endl;
      std::cin.ignore();
    }
    
  }
#endif

}

// At end run
void artg4::artg4Main::endRun(art::Run & r)
{
  art::ServiceHandle<ActionHolderService> actionHolder;
  actionHolder->setCurrArtRun(r);

  runManager_ -> BeamOnEndRun();

  //  visualization stuff
#ifdef G4VIS_USE
  // If visualization is enabled and we didn't already pause after each event,
  // pause now, with all the events visible.
//  if ( enableVisualization_ && (! pauseAfterEvent_) ) {
    // Use cout so that it is printed to console immediately. 
    // logInfo_ prints everything at once, so if we used that, we would
    // find out that we should press ENTER to finish only *after* we'd 
    // actually done so!
//    cout << "Pausing so you can appreciate visualization. "
//	 << "Hit ENTER to finish job." << std::endl;
//    std::cin.ignore();
//  }
  if ( enableVisualization_ ) {
    // Delete ui
    delete visManager_;
  }
#endif
}

using artg4::artg4Main;
DEFINE_ART_MODULE(artg4Main)
