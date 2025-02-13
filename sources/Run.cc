// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include "Run.hh"

#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include <iomanip>

const G4double Run::GetKCollision()
{
  return GetProduction()/GetAbsorbtion();
}

void Run::BankSource(G4ThreeVector position, G4ThreeVector direction, G4double energy, G4double weight)
{
  ParticleData particle = ParticleData(position, direction, energy, weight);
  fParticlesData.push_back(particle);
}

void Run::ScoreAbsorbtion(const G4Track* track)
{
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  absorbtion += track->GetWeight()/run->GetNumberOfEventToBeProcessed();
}

void Run::ScoreProduction(const G4Track* track)
{
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  production += track->GetWeight()/run->GetNumberOfEventToBeProcessed();
}

void Run::ScoreFission(const G4Track* track)
{ 
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  G4double weight = track->GetWeight();
  G4double nParticle = run->GetNumberOfEventToBeProcessed();

  tFission += weight/nParticle;
  G4String materialName = track->GetMaterial()->GetName();
  if (tFissionMaterial.find(materialName) != tFissionMaterial.end())
  {
    tFissionMaterial[materialName] += weight/nParticle;
  }
}

void Run::ScoreEnergyDeposited(const G4Track* track, G4double eDep)
{ 
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  G4double weight = track->GetWeight();
  G4double nParticle = run->GetNumberOfEventToBeProcessed();

  eDeposited += eDep*weight/nParticle;
  G4String materialName = track->GetMaterial()->GetName();
  G4double trackTime = track->GetGlobalTime();

  G4int i = 0;
  while (timeGrid[i] <= trackTime/second && i < timeGrid.size())
  {
    i++;
  }
  eDepositedInTime[i] += eDep*weight/nParticle;
  if (eDepositedInMaterial.find(materialName) != eDepositedInMaterial.end())
  {
    eDepositedInMaterial[materialName][i] += eDep*weight/nParticle;
  }
}

void Run::Merge(const G4Run* run)
{
  const Run* localRun = static_cast<const Run*>(run);

  absorbtion += localRun->absorbtion;
  production += localRun->production;
  tFission   += localRun->tFission;
  eDeposited += localRun->eDeposited;

  fParticlesData.insert(fParticlesData.end(), localRun->fParticlesData.begin(), localRun->fParticlesData.end());
  G4Run::Merge(run);
} 

void Run::EndOfRun() 
{
  G4cout << "RUN: " << GetRunID() 
         << " keff: " << GetKCollision() 
         << " tFission: " << GetFissionRate();
  std::map<G4String,G4double>::const_iterator itp0;
  for ( itp0 = tFissionMaterial.begin(); itp0 != tFissionMaterial.end(); ++itp0 )
  {
    G4String name = itp0->first;
    G4double energy = itp0->second;
    G4cout << " "+name+": " << energy;
  }
  G4cout << " production: " << GetProduction()
         << " absorbtion: " << GetAbsorbtion() 
         << " energyDeposited: " << GetEnergyDeposited()/MeV;

  std::map<G4String, std::array<G4double, 59>>::const_iterator itp1;
  for ( itp1 = eDepositedInMaterial.begin(); itp1 != eDepositedInMaterial.end(); ++itp1 )
  {
    G4String name = itp1->first;
    std::array<G4double, 59> energyArray = itp1->second;
    for (G4int i =0; i< energyArray.size(); i++)
    {
      G4double energy = energyArray[i];
      G4cout << " "+name+"_"<< i << ": " << energy/MeV;
    }
  }
  for (G4int i = 0; i < eDepositedInTime.size(); ++i)
  {
    if (i==0)
    {
      G4cout << " " << 0. <<": ";
    }
    else
    {
      G4cout << " " << timeGrid[i-1] <<": ";
    }
    G4cout << eDepositedInTime[i]/MeV;
  }
  G4cout << G4endl;
  fParticlesData.clear();
}