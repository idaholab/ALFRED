// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include <iostream>

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UIManager.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"
#include "G4ParticleHPManager.hh"

#include "Shielding.hh"
#include "G4PhysListFactory.hh"
#include "G4ThermalNeutrons.hh"

int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();

    DetectorConstruction* detector = new DetectorConstruction();

    G4PhysListFactory* factory = new G4PhysListFactory();
    G4VModularPhysicsList* physics = factory->GetReferencePhysList("Shielding");
    physics->RegisterPhysics( new G4ThermalNeutrons());

    runManager->SetUserInitialization(detector);
    runManager->SetUserInitialization(physics);
    runManager->SetUserInitialization(new ActionInitialization(detector));
    runManager->Initialize();
    
    // Replaced HP environmental variables with C++ calls
    G4ParticleHPManager::GetInstance()->SetSkipMissingIsotopes( false );
    G4ParticleHPManager::GetInstance()->SetDoNotAdjustFinalState( true );
    G4ParticleHPManager::GetInstance()->SetUseOnlyPhotoEvaporation( true );
    G4ParticleHPManager::GetInstance()->SetNeglectDoppler( false );
    G4ParticleHPManager::GetInstance()->SetProduceFissionFragments( true );
    G4ParticleHPManager::GetInstance()->SetUseWendtFissionModel( false );
    G4ParticleHPManager::GetInstance()->SetUseNRESP71Model( false );

    // ui 
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {ui = new G4UIExecutive(argc,argv);}
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    G4VisExecutive *visManager = new G4VisExecutive;
    if (ui)  { //interactive mode
        visManager->Initialize();

        UImanager->ApplyCommand("/vis/open OGL");
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 0 0 1");
        UImanager->ApplyCommand("/vis/drawVolume");
        UImanager->ApplyCommand("/vis/viewer/set/autoRefresh True");
        UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
        UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set e- blue");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set gamma yellow");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set neutron green");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set proton magenta");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set ion red");

        ui->SessionStart();
        delete ui;
    }
    else  { //batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    //job termination
    delete visManager;
    delete runManager;
}