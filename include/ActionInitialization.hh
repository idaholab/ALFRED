// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class DetectorConstruction;
class G4VSteppingVerbose;


class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(DetectorConstruction*);
   ~ActionInitialization() override = default;

   void BuildForMaster() const override;
   void Build() const override;
   
  private:
    DetectorConstruction* fDetector = nullptr; 
};

#endif

    
