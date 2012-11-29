// Common materials used throughout the simulation

#include "artg4/services/RunSettings_service.hh"

#include <iostream>

artg4::RunSettingsService::RunSettingsService(fhicl::ParameterSet const & p, 
					      art::ActivityRegistry &) :
  p_ (p) 
{
  std::cout << "\nRunSettingsService has been constructed!" << std::endl;
}

// Destructor
artg4::RunSettingsService::~RunSettingsService()
{
}

fhicl::ParameterSet artg4::RunSettingsService::getSettings(std::string const & s){

  fhicl::ParameterSet p = p_.get<fhicl::ParameterSet>(s,fhicl::ParameterSet());
  return p;
}


using artg4::RunSettingsService;
DEFINE_ART_SERVICE(RunSettingsService)
