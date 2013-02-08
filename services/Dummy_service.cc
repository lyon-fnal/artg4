// Common materials used throughout the simulation

#include "artg4/services/Dummy_service.hh"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include <iostream>

artg4::DummyService::DummyService(fhicl::ParameterSet const &, 
				  art::ActivityRegistry &)
{
  std::cout << "DummyService has been constructed!" << std::endl;
}

// Destructor
artg4::DummyService::~DummyService()
{
}

void artg4::DummyService::notifyArtOfProduction(art::EDProducer * prod)
{
  mf::LogDebug("DummyService") << "running produces<int>()...";
  prod -> produces<int>();
  mf::LogDebug("DummyService") << "done!";
}

using artg4::DummyService;
DEFINE_ART_SERVICE(DummyService)
