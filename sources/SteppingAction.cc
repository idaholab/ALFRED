// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include "SteppingAction.hh"

#include "Run.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"

#include "G4RunManager.hh"



SteppingAction::SteppingAction(RunAction* run, EventAction* event, TrackingAction* tracking, DetectorConstruction* det)
{
    fRunAction = run;
    fEventAction = event;
    fTrackingAction = tracking;
    fDetector = det;
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4double eDep = step->GetTotalEnergyDeposit();
    Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    G4Track* track = step->GetTrack();

    run->ScoreEnergyDeposited(track, eDep);
    //if track->GetParticleDefinition()->GetName()

    // G4double edep = step->GetTotalEnergyDeposit()/MeV;
    // G4StepPoint* prePoint = step->GetPreStepPoint(); 
    // G4ThreeVector preposition = prePoint->GetPosition()/cm;
    // G4double pretime = prePoint->GetGlobalTime()/s;
    // G4double epre = prePoint->GetKineticEnergy()*MeV;
    // G4StepPoint* postPoint = step->GetPostStepPoint(); 
    // G4ThreeVector postposition = postPoint->GetPosition()/cm;
    // G4double posttime = postPoint->GetGlobalTime()/s;
    // G4double epost = postPoint->GetKineticEnergy()/MeV;

    // G4ThreeVector delta = postposition-preposition;
    // G4double dist = pow(pow(delta.getX(),2)+pow(delta.getY(),2)+pow(delta.getZ(),2),0.5);

    // G4int trackID = step->GetTrack()->GetTrackID();
    // G4cout << step->GetTrack()->GetParticleDefinition()->GetParticleName() << " [" << pretime << " : " << posttime << "] " << preposition << " -> " << postposition << " - Energy " << epre << " -> " << epost << " - Deposited: " << edep << G4endl;

}
