/** @file VisManager.cc

    Implementation of a convenience class that sets up the
    visualization subsystem.

    This is the visualization manager that handles seaching for,
    opening and loading drivers.  This file is fairly standard and can
    merely be copied and linked into any program.  Incidentally, I
    blatantly ripped this from our dear friends at CERN!
    
   @author Zach Hartwig 2005
   Converted to artg4 as part of g-2 gm2ringsim port
   @author Brendan Kiburg
   @date Dec 2012
 */


#ifdef G4VIS_USE

#include "artg4/vis/VisManager.hh"

// Supported drivers...

// Not needing external packages or libraries...
#include "Geant4/G4ASCIITree.hh"
#include "Geant4/G4DAWNFILE.hh"
#include "Geant4/G4HepRepFile.hh"
#include "Geant4/G4HepRep.hh"
#include "Geant4/G4RayTracer.hh"
//FIXME: #include "Geant4/G4RayTracerX.hh"
#include "Geant4/G4VRML1File.hh"
#include "Geant4/G4VRML2File.hh"

// Needing external packages or libraries...

#ifdef G4VIS_USE_DAWN
#include "Geant4/G4FukuiRenderer.hh"
#endif

#ifdef G4VIS_USE_OPENGLX
#include "Geant4/G4OpenGLImmediateX.hh"
#include "Geant4/G4OpenGLStoredX.hh"
#endif

#ifdef G4VIS_USE_OPENGLWIN32
#include "Geant4/G4OpenGLImmediateWin32.hh"
#include "Geant4/G4OpenGLStoredWin32.hh"
#endif

#ifdef G4VIS_USE_OPENGLXM
#include "Geant4/G4OpenGLImmediateXm.hh"
#include "Geant4/G4OpenGLStoredXm.hh"
#endif

#ifdef G4VIS_USE_OIX
#include "Geant4/G4OpenInventorX.hh"
#endif

#ifdef G4VIS_USE_OIWIN32
#include "Geant4/G4OpenInventorWin32.hh"
#endif

#ifdef G4VIS_USE_VRML
#include "Geant4/G4VRML1.hh"
#include "Geant4/G4VRML2.hh"
#endif

// include filters and models
#include "Geant4/G4HitFilterFactories.hh"
#include "Geant4/G4TrajectoryFilterFactories.hh"
#include "Geant4/G4TrajectoryModelFactories.hh"

artg4::VisManager::VisManager() 
{}

artg4::VisManager::~VisManager()
{}

void artg4::VisManager::registerGraphicsSystems () 
{
  
  // Graphics Systems not needing external packages or libraries...
  RegisterGraphicsSystem (new G4ASCIITree);
  RegisterGraphicsSystem (new G4DAWNFILE);
  RegisterGraphicsSystem (new G4HepRepFile);
  RegisterGraphicsSystem (new G4HepRep);
  RegisterGraphicsSystem (new G4RayTracer);
  //FIXME:  RegisterGraphicsSystem (new G4RayTracerX);
  RegisterGraphicsSystem (new G4VRML1File);
  RegisterGraphicsSystem (new G4VRML2File);

  // Graphics systems needing external packages or libraries...

#ifdef G4VIS_USE_DAWN
  RegisterGraphicsSystem (new G4FukuiRenderer);
#endif

#ifdef G4VIS_USE_OPENGLX
  RegisterGraphicsSystem (new G4OpenGLImmediateX);
  RegisterGraphicsSystem (new G4OpenGLStoredX);
#endif

#ifdef G4VIS_USE_OPENGLWIN32
  RegisterGraphicsSystem (new G4OpenGLImmediateWin32);
  RegisterGraphicsSystem (new G4OpenGLStoredWin32);
#endif

#ifdef G4VIS_USE_OPENGLXM
  RegisterGraphicsSystem (new G4OpenGLImmediateXm);
  RegisterGraphicsSystem (new G4OpenGLStoredXm);
#endif

#ifdef G4VIS_USE_OIX
  RegisterGraphicsSystem (new G4OpenInventorX);
#endif

#ifdef G4VIS_USE_OIWIN32
  RegisterGraphicsSystem (new G4OpenInventorWin32);
#endif

#ifdef G4VIS_USE_VRML
  RegisterGraphicsSystem (new G4VRML1);
  RegisterGraphicsSystem (new G4VRML2);
#endif

  if (fVerbose > 0) {
    G4cout <<
      "\nYou have successfully chosen to use the following graphics systems."
	 << G4endl;
    PrintAvailableGraphicsSystems ();
  }
}

void artg4::VisManager::registerModelFactories()
{

   // Trajectory draw models
   RegisterModelFactory(new G4TrajectoryGenericDrawerFactory());       
   RegisterModelFactory(new G4TrajectoryDrawByChargeFactory());
   RegisterModelFactory(new G4TrajectoryDrawByParticleIDFactory());
   RegisterModelFactory(new G4TrajectoryDrawByOriginVolumeFactory());  
   RegisterModelFactory(new G4TrajectoryDrawByAttributeFactory());  

   // Trajectory filter models
   RegisterModelFactory(new G4TrajectoryChargeFilterFactory());
   RegisterModelFactory(new G4TrajectoryParticleFilterFactory());
   RegisterModelFactory(new G4TrajectoryOriginVolumeFilterFactory());
   RegisterModelFactory(new G4TrajectoryAttributeFilterFactory());

   // Hit filter models
//   RegisterModelFactory(new G4HitAttributeFilterFactory());

}


#endif


