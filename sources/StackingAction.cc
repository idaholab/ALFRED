// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include "StackingAction.hh"

#include "Run.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"

StackingAction::StackingAction()
{}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* track)
{
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  if (track->GetParentID() == 0) // keep primary particle
  {
    run->ScoreAbsorbtion(track);
    return fUrgent;
  }
  else // count secondary particles
  {
    G4String name    = track->GetDefinition()->GetParticleName();
    G4String process = track->GetCreatorProcess()->GetProcessName();

    if (name == "neutron" && process == "nFission") // fissions neutrons
    {
      G4ThreeVector position = track->GetPosition();
      G4ThreeVector direction = track->GetMomentumDirection();
      G4double energy = track->GetKineticEnergy();
      G4double weight = track->GetWeight();

      run->BankSource(position, direction, energy, weight);
      run->ScoreProduction(track);
      return fKill;
    }
    else if (name == "neutron" && process == "neutronInelastic")
    {
      return fUrgent;
    }
    else if (name == "neutron") // other neutrons
    {
      return fUrgent;
    }
    else if (name == "gamma") // other neutrons
    {
      return fUrgent;
    }
    else // all other particles
    {
      return fUrgent;
    }
    
  }
}

