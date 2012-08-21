// Common materials used throughout the simulation

#include "artg4/services/Dummy_service.hh"

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
  std::cout << "running produces<int>()...";
  prod -> produces<int>();
  std::cout << "done!" << std::endl;
}

using artg4::DummyService;
DEFINE_ART_SERVICE(DummyService)
