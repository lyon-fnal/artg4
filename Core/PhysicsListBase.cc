// Implementation of PhysicsListBase

#include "artg4/core/PhysicsListBase.hh"

#include "artg4/services/PhysicsListHolder_service.hh"
#include "art/Framework/Services/Registry/ServiceHandle.h"

artg4::PhysicsListBase::PhysicsListBase() {
  art::ServiceHandle<PhysicsListHolderService> holder;
  holder->registerPhysicsList(this);
}

void artg4::PhysicsListBase::ConstructParticle() {
  // If we reached here, then something is very wrong
  throw cet::exception("PhysicsListBase") << "ConstructParticle was not overridden\n";
}


void artg4::PhysicsListBase::ConstructProcess() {
  // If we reached here, then something is very wrong
  throw cet::exception("PhysicsListBase") << "ConstructProcess was not overridden\n";
}
