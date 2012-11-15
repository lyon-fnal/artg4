// Geometry_service.cc
// This service is intended to give the user an interface between the
// fhicl input file and their detector_service
// 
// Developed by Brendan Kiburg, Adam Lyon Nov, 2012

#include "Geometry_service.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"

artg4::GeometryService::GeometryService(fhicl::ParameterSet const & p,
					art::ActivityRegistry &)
  : p_ ( p ) 
{
}

artg4::GeometryService::~GeometryService(){

}

int artg4::GeometryService::getInt(std::string s){
  return p_.get<int>(s);

}


//The Geometry Service assumes that individual detectors will be inside of the fhicl Parameter Sets within Geometry . This method allows a user to extract the parameter set by name
fhicl::ParameterSet artg4::GeometryService::getDetParSet(std::string s){

  fhicl::ParameterSet p = p_.get<fhicl::ParameterSet>(s);
  return p;

}

using artg4::GeometryService;
DEFINE_ART_SERVICE(GeometryService)
