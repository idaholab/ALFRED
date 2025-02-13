// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "DetectorConstruction.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
   ~EventAction() override = default;

  public:
    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;
};


#endif

    
