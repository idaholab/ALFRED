// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class TrackingMessenger;
class EventAction;

class TrackingAction : public G4UserTrackingAction {

  public:  
    TrackingAction();
   ~TrackingAction() override;
   
    void PreUserTrackingAction(const G4Track*) override;  
    void PostUserTrackingAction(const G4Track*) override;

  private:
    G4String EndTrackProcess(const G4Track*);
    
};


#endif
