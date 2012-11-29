#ifndef GEOMETRY_BASE_HH
#define GEOMETRY_BASE_HH

#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "artg4/services/Geometry_service.hh"


#include "fhiclcpp/ParameterSet.h"

#include <string>
namespace artg4 {

  struct GeometryBase { 
    
    GeometryBase(std::string const & detName) : 
      name(detName),
      p() 
    {
      art::ServiceHandle <artg4::GeometryService> g;
      p = g->getDetParSet(detName);
      
    }
    
    virtual ~GeometryBase() {}
    
    
    std::string name;
    fhicl::ParameterSet p;
    
  };
}


#endif // GEOMETRY_BASE_HH

