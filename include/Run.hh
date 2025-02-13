// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include <vector>

class Run : public G4Run
{
  public:
    Run() = default;
   ~Run() override = default;

  public:
    const G4double GetKCollision();
    const G4double GetProduction() {return production;};
    const G4double GetAbsorbtion() {return absorbtion;};
    const G4double GetFissionRate() {return tFission;};
    const G4double GetEnergyDeposited() {return eDeposited;};
    
    void BankSource(G4ThreeVector, G4ThreeVector, G4double, G4double);
    
    void ScoreAbsorbtion(const G4Track*);
    void ScoreProduction(const G4Track*);
    void ScoreFission(const G4Track*);
    void ScoreEnergyDeposited(const G4Track*, G4double);

    void Merge(const G4Run*) override;
    void EndOfRun();

  public:
    struct ParticleData {
      ParticleData() : position(G4ThreeVector()), direction(G4ThreeVector()), energy(0.), weight(0.) {}
      ParticleData(G4ThreeVector pos, G4ThreeVector dir, G4double E, G4double w) : position(pos), direction(dir), energy(E), weight(w) {}
      G4ThreeVector position;
      G4ThreeVector direction;
      G4double energy;
      G4double weight;
    };

  public:
    std::vector<ParticleData>* GetParticlesData() {return &fParticlesData;};

  private:
    std::vector<ParticleData> fParticlesData;
    G4double absorbtion;
    G4double production;
    G4double tFission;
    G4double eDeposited;

    std::map<G4String, G4double> tFissionMaterial = {{"fuel", 0.}};
    std::map<G4String, std::array<G4double, 59>> eDepositedInMaterial = {{"fuel", {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.}}};
    std::array<G4double, 59> eDepositedInTime;
    std::array<G4double, 58> timeGrid = {0.0001, 0.0002, 0.0003, 0.0004, 0.0005, 0.0006, 0.0007, 0.0008, 0.0009, 0.001, 0.0011, 0.0012, 0.0013, 0.0014, 0.0015, 0.0016, 0.0017, 0.0018, 0.0019, 0.002, 0.0021, 0.0022, 0.0023, 0.0024, 0.0025, 0.00398107171, 0.00630957344, 0.01, 0.0158489319, 0.0251188643, 0.0398107171, 0.0630957344, 0.1, 0.158489319, 0.251188643, 0.398107171, 0.630957344, 1.0, 1.58489319, 2.51188643, 3.98107171, 6.30957344, 10.0, 15.8489319, 25.1188643, 39.8107171, 63.0957344, 100.0, 158.489319, 251.188643, 398.107171, 630.957344, 1000.0, 1584.89319, 2511.88643, 3981.07171, 6309.57344, 10000.0};
    
};

#endif

