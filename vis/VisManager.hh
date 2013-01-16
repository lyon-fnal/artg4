#ifndef VISMANAGER_HH
#define VISMANAGER_HH

/** @file VisManager.hh

    Provides a convenience class that sets up the visualization
    subsystem. 

    @author Zach Hartwig
    @date 2005
    @Adapted to artg4 as part of gm2ringsim port
    @author Brendan Kiburg
    @date Dec 2012
    
 */

#ifdef G4VIS_USE

#include "Geant4/G4VisManager.hh"

namespace artg4 {
  /** A convenience class to set up the visualization subsystems. */
  class VisManager : public G4VisManager
  {
    
  public:
    VisManager();
    ~VisManager();
    
  private:
    void registerGraphicsSystems();
    void registerModelFactories();
  }; //class VisManager
  
} //namespace artg4

#endif

#endif
