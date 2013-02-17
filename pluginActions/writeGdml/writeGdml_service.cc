// Implementation of writeGdml_service.cc
//
//

#include "artg4/pluginActions/writeGdml/writeGdml_service.hh"
#include "artg4/pluginActions/writeGdml/gdmlText.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "Geant4/G4GDMLParser.hh"
#include "Geant4/G4TransportationManager.hh"

#include <fstream>
#include <memory>

artg4::WriteGdmlService::WriteGdmlService(fhicl::ParameterSet const& p, art::ActivityRegistry&) :
  RunActionBase( p.get<std::string>("name", "writeGdml") ),
  gdmlFileName_( p.get<std::string>("gdmlFileName") )
 {}

artg4::WriteGdmlService::~WriteGdmlService() {}

// Prepare Art for the data
void artg4::WriteGdmlService::callArtProduces(art::EDProducer * producer) {
  producer->produces< artg4::GdmlText, art::InRun>( myName() );
}

// Write out the data in the Run record
void artg4::WriteGdmlService::fillRunBeginWithArtStuff(art::Run& r) {
  
  // Write out with GDML
  G4GDMLParser parser;
  
  // See genant4/examples/extended/persistency/gdml/G01
  parser.Write(gdmlFileName_, G4TransportationManager::GetTransportationManager()->
                                 GetNavigatorForTracking()->GetWorldVolume()->GetLogicalVolume());
  
  // Now read in the file to a string
  // See http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
  std::ifstream in( gdmlFileName_, std::ios::in );
  std::string contents;
  // Figure out how big we need to make contents
  in.seekg(0, std::ios::end);
  contents.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&contents[0], contents.size());
  in.close();
  
  // Now put this into the run
  std::unique_ptr< artg4::GdmlText > gdmlText( new GdmlText(contents) );
  r.put( std::move(gdmlText), myName() );
  
  mf::LogInfo("WriteGdmlService") << "Wrote GDML";
}

using artg4::WriteGdmlService;
DEFINE_ART_SERVICE(WriteGdmlService)
