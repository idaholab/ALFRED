// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include "PrimaryGeneratorAction.hh"

#include "Run.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4Navigator.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Material.hh"
#include "G4RunManager.hh"
#include "G4PrimaryVertex.hh"

class ParticleData;

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* det, RunAction* runAction)
{
  fDetector = det;
  fRunAction = runAction;
  fParticleGun  = new G4ParticleGun(1);
  G4ParticleDefinition *particle = GetParticleDefinition();
  fParticleGun -> SetParticleDefinition(particle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  nParticle = run->GetNumberOfEventToBeProcessed();
  G4int nEvent = run->GetNumberOfEvent();

  Run::ParticleData particleData = PrimaryGeneratorAction::SampleParticle(nEvent);

  G4ThreeVector position = particleData.position;
  G4ThreeVector direction = particleData.direction;
  G4double energy = particleData.energy;
  G4double weight = particleData.weight;


  fParticleGun -> SetParticleEnergy(energy);
  fParticleGun -> SetParticleMomentumDirection(direction);
  fParticleGun -> SetParticlePosition(position);
  fParticleGun -> SetParticleWeight(weight);
  fParticleGun -> SetParticleTime(0.);

  fParticleGun -> GeneratePrimaryVertex(anEvent);
}

G4ParticleDefinition* PrimaryGeneratorAction::GetParticleDefinition()
{
  G4String particleName = "neutron";
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
  return particle;
}

Run::ParticleData PrimaryGeneratorAction::SampleParticle(G4int i)
{
  std::vector<Run::ParticleData>* sources = fRunAction->GetPreviousBatchSources();
  if (sources->size() == 0)
  {
    G4ThreeVector position = G4ThreeVector(0.,0.,0.);
    G4ThreeVector direction = G4ThreeVector(1.,0.,0.);
    G4double energy = 1.0*MeV;
    G4double weight = 1.;
    Run::ParticleData particleData = Run::ParticleData(position, direction, energy, weight);
    return particleData;
  }
  else
  {
    G4int index = floor(sources->size()*i/nParticle);
    Run::ParticleData particleData = sources->operator[](index);
    return particleData;
  }
}