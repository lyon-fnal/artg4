// This file is the header for the @ActionBase@ class.

// There is no implementation file, as it is intended only as a base class.

// All action objects MUST inherit from this class.

// When you create an action object, you have the option to overload the
// following methods:

// @BeginOfRun@ - This method, which takes a pointer to a constant @G4Run@ 
// object, is called once at the beginning of each run. Putting code in this
// method of an action object is equivalent to putting it in the 
// @BeginOfRun@ method of the simulation's run action class.

// @EndOfRun@ - This method, which takes a pointer to a constant @G4Run@ 
// object, is called once at the end of each run. Putting code in this method
// of an action object is equivalent to putting it in the @EndOfRun@ method
// of the simulation's run action class.

// @BeginOfEventAction@ - This method, which takes a pointer to a constant
// @G4Event@ object, is called once at the beginning of each event. Note that
// this occurs after the primaries have been constructed and passed to the 
// event manager, but before anything is simulated. Putting code in this 
// method of an action object is equivalent to putting it in the 
// @BeginOfEventAction@ method of the simulation's event action class.

// @EndOfEventAction@ - This method, which takes a pointer to a constant
// @G4Event@ object, is called once at the end of each event. This is the 
// last time the event object is accessible (right before the state changes
// from EventProc (in which the event is accessible) to GeomClosed). Putting
// code in this method of an action object is equivalent to putting it in the
// @EndOfEventAction@ method of the simulation's event action class.

// @PreUserTrackingAction@ - This method, which takes a pointer to a constant
// @G4Track@ object, is called once after a track has been created but before
// it is simulated. Putting code in this method of an action object is 
// equivalent to putting it in the @PreUserTrackingAction@ method of the 
// simulation's tracking action class.

// @PostUserTrackingAction@ - This method, which takes a pointer to a constant
// @G4Track@ object, is called once after a track has been stopped. Putting 
// code in this method of an action object is equivalent to putting it in the 
// @PostUserTrackingAction@ method of the simulation's tracking action class.

// @UserSteppingAction@ - This method, which takes a pointer to a constant
// @G4Step@ object, is called at the end of each step (I think - the 
// documentation is a little vague). Putting code in this method of an action
// object is equivalent to putting it in the @UserSteppingAction@ method of
// the simulation's stepping action class.

// @GeneratePrimaries@ - This method, which takes a pointer to a @G4Event@
// object, is called to create the primary particle(s) for an event. It is
// called once at the beginning of each event. Putting code in this method of
// and action object is equivalent to putting it in the @GeneratePrimaries@ 
// method of the simulation's primary generator action class.

// You may overload any or all of these methods.
// All of these methods have a second argument, the pointer to the object
// calling them. This is only to be used when completing an action that needs
// to be done from that class (using a member function of the base class, for
// example).

// Include guard
#ifndef ACTION_BASE_HH
#define ACTION_BASE_HH

#include <string>
#include <iostream>

// Declarations of types we use as input parameters
class G4Run;
class G4Step;
class G4Event;
class G4Track;

class G4UserRunAction;
class G4UserEventAction;
class G4UserTrackingAction;
class G4UserSteppingAction;
class G4VUserPrimaryGeneratorAction;


// Everything goes in the Art G4 namespace
namespace artg4 {

  class ActionBase {
  public:
    // Constructor. The derived class must call this constructor. It takes a 
    // single string for the name of the action object.
    ActionBase(std::string myName)
      : _myName( myName )
    {}

    // Destructor
    virtual ~ActionBase(){}

    // Accessor
    std::string myName() const {return _myName;}

    // h3. The interesting methods. 
    // All of these are defined to do nothing by default. Users can override 
    // them if desired, and if they're not overloaded, they do nothing.

    // Called at the beginning of each run.
    virtual void BeginOfRunAction(const G4Run * currentRun, 
				  G4UserRunAction *) {}

    // Called at the end of each run.
    virtual void EndOfRunAction(const G4Run * currentRun,
				G4UserRunAction *) {}

    // Called at the beginning of each event (after creation of primaries)
    virtual void BeginOfEventAction(const G4Event * currentEvent,
				    G4UserEventAction *) {}

    // Called at the end of each event
    virtual void EndOfEventAction(const G4Event * currentEvent,
				  G4UserEventAction *) {}

    // Called before a track is simulated
    virtual void PreUserTrackingAction(const G4Track * currentTrack,
				       G4UserTrackingAction *) {}
    
    // Called when a track is stopped
    virtual void PostUserTrackingAction(const G4Track * currentTrack,
					G4UserTrackingAction *) {}

    // Called at the end of each step
    virtual void UserSteppingAction(const G4Step * currentStep,
				    G4UserSteppingAction *) {}

    // Called for the generation of primaries
    virtual void GeneratePrimaries(G4Event * anEvent,
				   G4VUserPrimaryGeneratorAction *) {
      std::cout << "hi there. I'm generating primaries." << std::endl;}
    

  private:
    // A string containing this action object's name
    std::string _myName;
  };
}


#endif // ACTION_BASE_HH
