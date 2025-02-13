// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "Run.hh"

class ParticleData;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
   ~RunAction() override;

  public:
    void   BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*)   override;
    G4Run* GenerateRun() override;

    void WriteSources(const G4Run*);

  public:
    std::vector<Run::ParticleData>* GetPreviousBatchSources() {return &previousBatchSources;};
    
  private:
    std::vector<Run::ParticleData> previousBatchSources;

  private:
    Run* fRun = nullptr;
};

#endif

