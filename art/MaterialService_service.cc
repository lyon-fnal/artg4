//
// MaterialService_service.cc
//
// Created by Tasha Arvanitis on 6 July 2012

#include "MaterialService.hh"

#include "art/Framework/Services/Registry/ServiceMacros.h"

// Constructor
gm2::MaterialService::MaterialService(fhicl::ParameterSet const &, 
				      art::ActivityRegistry &)
{
  // Create the base elements we'll be using later
  
  H = new G4Element("Hydrogen", "H", z=1., a=  1.01*g/mole);
  C = new G4Element("Carbon",   "C", z=6., a= 12.01*g/mole);
  N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
  O = new G4Element("Oxygen",   "O", z=8., a= 16.00*g/mole);

}

// Destructor
gm2::MaterialService::~MaterialService()
{
  delete H;
  delete C;
  delete N;
  delete O;
}

// Create some air
G4Material* gm2::MaterialService::newAir()
{
  G4Material * Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
  Air->AddElement(N, 70.*perCent);
  Air->AddElement(O, 30.*perCent);

  return Air;
}

// Create some argon
G4Material* gm2::MaterialService::newAr()
{
  return new G4Material("ArgonGas",
			z=18., 
			a= 39.95*g/mole, 
			density=1.782*mg/cm3);  
}

// Create some silicon
G4Material* gm2::MaterialService::newSi()
{
  return new G4Material("Silicon", 
			z=14., 
			a= 28.09*g/mole, 
			density= 2.33*g/cm3);
}

// Create some scintillator material.
G4Material* gm2::MaterialService::newScint()
{
  G4Material * Scint = new G4Material("Scintillator", 
				      density= 1.032*g/cm3, 
				      nel=2);
  Scint->AddElement(C, 9);
  Scint->AddElement(H, 10);

  return Scint;
}

// Create a new lead material
G4Material* gm2::MaterialService::newLead()
{
  return new G4Material("Lead", z=82., a= 207.19*g/mole, density= 11.35*g/cm3);
}

// Create a new vacuum material
G4Material* gm2::MaterialService::newVacuum()
{
  new G4Material("Vacuum", 
		 1., 
		 1.01*g/mole,
		 universe_mean_density,
		 kStateGas, 
		 3.e-18*pascal, 
		 2.73*kelvin);
}


using gm2::MaterialService;
DEFINE_ART_SERVICE(MaterialService)
