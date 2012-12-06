// Utility functions

#ifndef UTILITY_HH
#define UTILITY_HH

#include <vector>
#include <functional>
#include <string>

#include "Geant4/G4SDManager.hh"

class G4LogicalVolume;
class G4VisAttributes;

namespace artg4 {

  // class T should be a class that inherits from G4VSensitiveDetector
  // but in principle this could should *do something* for any class that 
  // has a constructor which takes a string
  template <class T>
  void getSensitiveDetector(G4String name, T* SDptr){
    G4SDManager* fSDM = G4SDManager::GetSDMpointer();
    if ((SDptr = (T*)(fSDM->FindSensitiveDetector(name))) == NULL)
      SDptr = new T(name);
  }

  // Set visual attributes
  void setVisAtts(G4LogicalVolume* lv, bool display, const std::vector<double> & rgba);
  void setVisAtts(G4LogicalVolume* lv, bool display, const std::vector<double> & rgba, std::function<void (G4VisAttributes*)> func );
    
  // Put a number in a name
  std::string addNumberToName(const std::string& name, int number);
  
}

#endif
