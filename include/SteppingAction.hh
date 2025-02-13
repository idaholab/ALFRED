// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class RunAction;
class EventAction;
class TrackingAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(RunAction*, EventAction*, TrackingAction*, DetectorConstruction*);
   ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step*) override;
  
  private:
    RunAction* fRunAction = nullptr;
    EventAction* fEventAction = nullptr;
    TrackingAction* fTrackingAction = nullptr;
    DetectorConstruction* fDetector = nullptr;

};

#endif
