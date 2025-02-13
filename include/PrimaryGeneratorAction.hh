// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "Run.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4Event;
class DetectorConstruction;
class PrimaryGeneratorMessenger;
class RunAction;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(DetectorConstruction*, RunAction*);    
   ~PrimaryGeneratorAction() override;

  public:
    void GeneratePrimaries(G4Event*) override;
    G4ParticleGun* GetParticleGun() {return fParticleGun;};
    
  private:
    G4int nParticle;

    G4ParticleGun*             fParticleGun = nullptr;
    G4GeneralParticleSource*   fGps = nullptr;
    DetectorConstruction*      fDetector = nullptr;
    RunAction*                 fRunAction = nullptr;

    G4int ix = 9;
    G4int iy = 9;
    G4int iz = 9;

  private:
    G4ParticleDefinition* GetParticleDefinition();

    Run::ParticleData SampleParticle(G4int);
};

#endif

