// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include "TrackingAction.hh"

#include "Run.hh"

#include "G4Track.hh"
#include "G4StepStatus.hh"
#include "G4RunManager.hh"

TrackingAction::TrackingAction()
{}

TrackingAction::~TrackingAction()
{}

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{}

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{
  G4String endProcess = EndTrackProcess(track);
  if (endProcess == "nFission")
  {
    Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    run -> ScoreFission(track);
  }
}

G4String TrackingAction::EndTrackProcess(const G4Track* track)
{
  G4String endProcess = "None";
  
  const G4Step* step = track->GetStep();
  const std::vector<const G4Track*>* trackVector = step->GetSecondaryInCurrentStep();
  for (G4int i = 0; i < trackVector->size(); i++)
  {
    const G4Track* secondTrack = trackVector->operator[](i);
    G4String newProcess = secondTrack->GetCreatorProcess()->GetProcessName();
    if (endProcess == "None")
    {
      endProcess = newProcess;
    }
    else if (endProcess != newProcess)
    {
      G4cout << "WARNING: track with several processes : " << endProcess << " but also " << newProcess << G4endl; 
    }
  }
  return endProcess;
}
