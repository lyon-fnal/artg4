
#ifndef GEOMETRY_SERVICE_HH
#define GEOMETRY_SERVICE_HH

// Art                                                                        
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"

namespace artg4 {

  class GeometryService { 
  public: 
    GeometryService(fhicl::ParameterSet const&, art::ActivityRegistry&);
    ~GeometryService();

    fhicl::ParameterSet getDetParSet(std::string);
    int getInt(std::string);

  private:
    fhicl::ParameterSet p_;
  };

} //namespace

#endif //GEOMETRY_SERVICE_HH
