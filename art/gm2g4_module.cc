// gm2g4_module.cc replicates many GEANT programs' @main()@ driver. It
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
#include "gm2g4/Core/Gm2G4RunManager.h"
#include "gm2g4/Core/Gm2DetectorConstruction.hh"
#include "gm2g4/actions/physicsList.hh"
#include "gm2g4/Core/Gm2EventAction.hh"
#include "gm2g4/Core/Gm2PrimaryGeneratorAction.hh"
#include "gm2g4/Core/Gm2RunAction.hh"
#include "gm2g4/Core/Gm2SteppingAction.hh"
#include "gm2g4/Core/Gm2TrackingAction.hh"

// G4 includes
#ifdef G4VIS_USE_OPENGLX
#include "G4VisExecutive.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

using namespace std;

namespace gm2 {
  class gm2g4 : public art::EDProducer {
  public:
    explicit gm2g4(fhicl::ParameterSet const & p);
    virtual ~gm2g4();

    virtual void produce(art::Event & e);
    virtual void beginJob();
    virtual void beginRun(art::Run &r);
    virtual void endRun(art::Run &);

  private:
    // Our custom run manager
    auto_ptr<gm2::Gm2G4RunManager> _runManager;
  
    // G4 stuff
    G4UIsession *_session;
    G4UImanager *_UI;
#ifdef G4VIS_USE_OPENGLX
    G4VisManager *_visManager;
#endif

    // Determine whether we should use visualization
    // False by default, can be set by config file
    bool _enableVisualization;

    // Directory path(s), in colon-delimited list, in which we should look for
    // macros, or the name of an environment variable containing that path.
    // Contains only the current directory ('.') by default, but can be
    // set by config file
    string _macroPath;
    // And a tool to find files along that path
    // Initialized based on _macroPath.
    cet::search_path _pathFinder;
  
    // Name of a macro file for visualization
    // 'vis.mac' by default, and can be customized by config file.
    string _visMacro;

    // Boolean to determine whether we pause execution after each event
    // If it's true, then we do. Otherwise, we pause only after all events
    // have been produced.
    // False by default, can be changed by config file.
    bool _pauseAfterEvent;
  

    // Run diagnostic level (verbosity)
    int _rmvlevel;

    // Message logger
    mf::LogInfo _logInfo;
  };
}

gm2::gm2g4::gm2g4(fhicl::ParameterSet const & p)
  : _runManager(0),
    _session(0),
    _UI(0),
    _enableVisualization( p.get<bool>("enableVisualization",false)),
    _macroPath( p.get<std::string>("macroPath",".")),
    _pathFinder( _macroPath),
    _visMacro( p.get<std::string>("visMacro", "vis.mac")),
    _pauseAfterEvent( p.get<bool>("pauseAfterEvent", false)),
    _rmvlevel( p.get<int>("rmvlevel",0)),
    _logInfo("GEOM")
{
  produces<int>();
}

gm2::gm2g4::~gm2g4()
{
  // Clean up dynamic memory and other resources here.  
}

void gm2::gm2g4::beginJob()
{
  // Set up run manager
  _runManager = auto_ptr<gm2::Gm2G4RunManager>(new gm2::Gm2G4RunManager);
}

void gm2::gm2g4::beginRun(art::Run & r)
{

  // User Initialization classes (mandatory)
  _runManager->SetUserInitialization(new Gm2DetectorConstruction);
  _runManager->SetUserInitialization(new physicsList);
  _runManager->SetUserAction(new Gm2PrimaryGeneratorAction);

  // User actions (optional)
  // Note that these actions (and Gm2PrimaryGeneratorAction above) are all
  // generic actions that really don't do much on their own. Rather, to 
  // use the power of actions, one must create action objects (derived from
  // @ActionBase@) and register them with the Art @ActionHolder@ service.
  // See @ActionBase@ and/or @ActionHolder@ for more information.
  runManager -> SetUserAction(new Gm2SteppingAction);
  runManager -> SetUserAction(new Gm2EventAction);
  runManager -> SetUserAction(new Gm2TrackingAction);
  runManager -> SetUserAction(new Gm2RunAction);

  /*
  // User actions (optional)
    runAction *RunAction = new runAction;
  eventAction *EventAction = new eventAction(RunAction);
  steppingAction *SteppingAction = new steppingAction(EventAction);
  trackingAction *TrackingAction = new trackingAction;
  
  runManager -> SetUserAction(SteppingAction);
  runManager -> SetUserAction(EventAction);
  runManager -> SetUserAction(TrackingAction);
  runManager -> SetUserAction(RunAction);
  */
  _runManager->Initialize();

  //get the pointer to the User Interface manager   
  _UI = G4UImanager::GetUIpointer();  

  // Set up visualization if it's allowed by current values of env. variables
#ifdef G4VIS_USE_OPENGLX

  // Turn on visualization if necessary
  if (_enableVisualization) {
    _logInfo << "Initializing visualization\n" << endl;

    // Create and initialize the visualization manager
    _visManager = new G4VisExecutive;
    _visManager->Initialize();

    // Find the macro (or try to) along the directory path.
    string macroLocation = "";
    bool macroWasFound = _pathFinder.find_file(_visMacro, macroLocation);
    _logInfo << "Finding path for " << _visMacro << "...\nSearch " 
	     << (macroWasFound ? "successful " : "unsuccessful ")
	     << "and path is: \n" << macroLocation << "\n" << endl;

    // Execute the macro if we were able to find it
    if (macroWasFound) {
      // Create the string containing the execution command
      _logInfo << "Executing macro: " << _visMacro << "\n" << endl;
      string commandToExecute = "/control/execute ";
      commandToExecute.append(macroLocation);
      _UI->ApplyCommand(commandToExecute); 

    } else {
      // If it wasn't found...
      // Leave a message for the user ... 
      _logInfo << "Unable to find " << _visMacro << " in the path(s) "
	       << _macroPath << endl;
      // ... and disable visualization for the future
      _enableVisualization = false;

    } // if the macro was found

  } // if visualization was enabled

#endif // G4VIS_USE_OPENGLX

  // run all the macros given on the command line
  if( verbosity ) {
    std::cout << "Are we looking at a macro file or an command?\n";
  }

  std::ostringstream command;

  // Iterate over the macros/commands given on the command line
  std::vector<std::string>::const_iterator  b = macros.begin();
  std::vector<std::string>::const_iterator  e = macros.end();
  for(; b!=e; ++b){
    int ret = stat(b->c_str(), &s);
    
    // Print information about any errors we encounter.
    if( verbosity>0 ){
      std::cout << *b << '\n';
      if( ret!=0){
	std::cerr << "Macro file " << *b << " does not exist. "
		  << "Assume a command.\n";
	continue;
      } else if ( !S_ISREG(s.st_mode) ){
	std::cerr << "Macro file " << *b << " is not a regular file. "
		  << "Assume a command.\n";
	continue;
      }
    }
    
    // Construct the command to run the macro/command we're working on now
    // Is this argument a macro file?
    if( ret==0 && S_ISREG(s.st_mode) ) {
      // If so, we need to prepend the string '/control/execute ' to run it
      // in the UI manager.
      command << "/control/execute ";
    }

    // Whether it's a macro or a command, we need the string passed in as a
    // command-line argument in the command to execute
    command << *b;

    // Apply the command
    UI -> ApplyCommand(command.str());

    // Reset the command stream and do it all again!
    command.str("");
  }

  // Start a run!
  _runManager -> BeamOnBeginRun(r.id().run());
}

// @produce@ is a required method for all producers. This is the module that
// runs the whole event loop, so here (and in no other module), we run one 
// event through GEANT.
void gm2::gm2g4::produce(art::Event & e)
{
   // Begin event
  _runManager -> BeamOnDoOneEvent(e.id().event());
  
  // Write home about it
  _logInfo << "Producing event " << e.id().event() << "\n" << endl;
  
  // Create an auto-ptr to an int
  auto_ptr<int> myVal(new int);
  *(myVal.get()) = 42;
  
  // Add this int to the event!
  e.put(myVal);

  // Done with the event
  _runManager -> BeamOnEndEvent();


#ifdef G4VIS_USE_OPENGLX
  // If visualization is enabled, and we want to pause after each event, do
  // the pausing.
  if (_enableVisualization && _pauseAfterEvent) {
    // Use cout so that it is printed to console immediately. 
    // _logInfo prints everything at once, so if we used that, we would
    // find out that we should press ENTER to continue only *after* we'd 
    // actually done so!
    _UI->ApplyCommand("/tracking/storeTrajectory 1");
    cout << "Pausing so you can appreciate visualization. " 
	 << "Hit ENTER to continue." << std::endl;
    std::cin.ignore();    
  }
#endif
}

void gm2::gm2g4::endRun(art::Run &)
{
  _runManager -> BeamOnEndRun();

  //  visualization stuff
#ifdef G4VIS_USE_OPENGLX
  // If visualization is enabled and we didn't already pause after each event,
  // pause now, with all the events visible.
  if ( _enableVisualization && (! _pauseAfterEvent) ) {
    // Use cout so that it is printed to console immediately. 
    // _logInfo prints everything at once, so if we used that, we would
    // find out that we should press ENTER to finish only *after* we'd 
    // actually done so!
    cout << "Pausing so you can appreciate visualization. " 
	 << "Hit ENTER to finish job." << std::endl;
    std::cin.ignore();
  }

  // Delete ui
  delete _visManager;
#endif
}

using gm2::gm2g4;
DEFINE_ART_MODULE(gm2g4)
