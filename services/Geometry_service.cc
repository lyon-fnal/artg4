// Geometry_service.cc
// This service is intended to give the user an interface between the
// fhicl input file and their detector_service
// 
// Developed by Brendan Kiburg, Adam Lyon Nov, 2012

#include "Geometry_service.hh"
#include "art/Framework/Services/Registry/ServiceMacros.h"

artg4::GeometryService::GeometryService(fhicl::ParameterSet const &,
					art::ActivityRegistry &)
{
}

artg4::GeometryService::~GeometryService(){

}

fhicl::ParameterSet const & artg4::GeometryService::getDetector(std::string){

}

using artg4::GeometryService;
DEFINE_ART_SERVICE(GeometryService)
