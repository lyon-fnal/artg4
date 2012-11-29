// Utility functions

#ifndef UTILITY_HH
#define UTILITY_HH

#include <vector>
#include <functional>
#include <string>

class G4LogicalVolume;
class G4VisAttributes;

namespace artg4 {


  // Set visual attributes
  void setVisAtts(G4LogicalVolume* lv, bool display, const std::vector<double> & rgba);
  void setVisAtts(G4LogicalVolume* lv, bool display, const std::vector<double> & rgba, std::function<void (G4VisAttributes*)> func );
    
  // Put a number in a name
  std::string addNumberToName(const std::string& name, int number);
  
}

#endif