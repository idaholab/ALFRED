// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include "RunAction.hh"

#include "Run.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

G4Run* RunAction::GenerateRun()
{ 
  fRun = new Run(); 
  return fRun;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{}

void RunAction::EndOfRunAction(const G4Run* run)
{ 
  if (isMaster)
  {
    WriteSources(run);
    previousBatchSources.clear();
    previousBatchSources.insert(previousBatchSources.end(), fRun->GetParticlesData()->begin(), fRun->GetParticlesData()->end());
    fRun->EndOfRun();
  }
}

void RunAction::WriteSources(const G4Run* run)
{
  const std::vector<Run::ParticleData>* pData = fRun->GetParticlesData();

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("csv");
  std::stringstream nRunStr;
  nRunStr << fRun->GetRunID();
  analysisManager->SetFileName("Sources_"+nRunStr.str());
  analysisManager->OpenFile();

  analysisManager->CreateNtuple("FS_"+nRunStr.str(), "fission sites");
  analysisManager->CreateNtupleDColumn("x0");
  analysisManager->CreateNtupleDColumn("y0");
  analysisManager->CreateNtupleDColumn("z0");
  analysisManager->CreateNtupleDColumn("ux");
  analysisManager->CreateNtupleDColumn("uy");
  analysisManager->CreateNtupleDColumn("uz");
  analysisManager->CreateNtupleDColumn("E");
  analysisManager->CreateNtupleDColumn("w");
  analysisManager->FinishNtuple();

  for (G4int i = 0; i < pData->size(); ++i) 
  {
    G4ThreeVector position = pData->operator[](i).position;
    G4ThreeVector direction = pData->operator[](i).direction;
    G4double energy = pData->operator[](i).energy;
    G4double weight = pData->operator[](i).weight;

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, position.getX()/cm);
    analysisManager->FillNtupleDColumn(1, position.getY()/cm);
    analysisManager->FillNtupleDColumn(2, position.getZ()/cm);
    analysisManager->FillNtupleDColumn(3, direction.getX());
    analysisManager->FillNtupleDColumn(4, direction.getY());
    analysisManager->FillNtupleDColumn(5, direction.getZ());
    analysisManager->FillNtupleDColumn(6, energy/MeV);
    analysisManager->FillNtupleDColumn(7, weight);
    analysisManager->AddNtupleRow();
  }

  analysisManager->Write();
  analysisManager->CloseFile();
}