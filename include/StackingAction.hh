// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

class PrimaryGeneratorAction;

class StackingAction : public G4UserStackingAction
{
  public:
    StackingAction();
   ~StackingAction() override = default;
     
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;

};

#endif

