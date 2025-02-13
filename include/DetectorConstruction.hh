// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSolid.hh"
#include "G4VisAttributes.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

class G4GlobalMagFieldMessenger;


class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  
  DetectorConstruction();
 ~DetectorConstruction() override;

public:

  G4VPhysicalVolume* Construct() override;
  G4Material* MakeFuel();
  G4Material* MakeZr();
  G4Material* MakeGraphite();
  G4Material* MakeAir();
  G4Material* MakeAlSteel();
  G4Material* MakeAlAir();
  G4Material* MakeReflector();
  G4Material* MakeAluminium();
  G4Material* MakeZirc2();
  G4Material* MakeSteel();
  G4Material* MakeZrSteel();
  G4Material* MakeB4cNew();
  G4Material* MakeAirSteel();

  G4VSolid* BuildOctagon(G4String, G4double, G4double, G4double);
  G4VSolid* BuildOctagonWithTubeHole(G4String, G4double, G4double, G4double, G4double);
  G4VSolid* BuildBoxWithTubeHole(G4String, G4double, G4double, G4double, G4double);
  G4VSolid* BuildOctagonWithOctagonHole(G4String, G4double, G4double, G4double, G4double, G4double);

  void ConstructFuelAssembly(G4int, G4String, G4ThreeVector, G4LogicalVolume*);
  void ConstructAlumAssembly(G4int, G4String, G4ThreeVector, G4LogicalVolume*);
  void ConstructCRAssembly(G4int, G4String, G4ThreeVector, G4LogicalVolume*);
  void ConstructCR(G4int, G4String, G4ThreeVector, G4LogicalVolume*, G4double);
  void ConstructTR(G4int, G4String, G4ThreeVector, G4LogicalVolume*, G4double);
  void ConditionalTube(G4int, G4String, G4double, G4double, G4double, G4double, G4Material*, G4Color, G4LogicalVolume*, G4double);

public:

  G4double GetFuelSizeXY()   {return fuelSizeXY;};
  G4double GetFuelSizeZ()    {return fuelSizeZ;};
  G4VPhysicalVolume* GetWorld() {return fPhysiWorld;};
  G4bool IsInMaterial(G4String, G4ThreeVector);
     
private:
  G4Material* mFuel      = nullptr;
  G4Material* mZr        = nullptr;
  G4Material* mGraphite  = nullptr;
  G4Material* mAir       = nullptr;
  G4Material* mAlSteel   = nullptr;
  G4Material* mAlAir     = nullptr;
  G4Material* mReflector = nullptr;
  G4Material* mAluminium = nullptr;
  G4Material* mZirc2     = nullptr;
  G4Material* mSteel     = nullptr;
  G4Material* mZrSteel   = nullptr;
  G4Material* mB4cNew    = nullptr;
  G4Material* mAirSteel  = nullptr;

private:
  G4double zCR01 = 90.0684*cm;
  G4double zCR02 = 90.0684*cm;
  G4double zCR03 = 90.0684*cm;
  G4double zCR04 = 90.0684*cm;

  G4double zCC01 = 148.59*cm;
  G4double zCC02 = 148.59*cm;
  G4double zCC03 = 148.59*cm;
  G4double zCC04 = 148.59*cm;

  G4double zTR01 = 101.60*cm;
  G4double zTR02 = 101.60*cm;
  G4double zTR03 = 101.60*cm;
  G4double zTR04 = 101.60*cm;

private:

  G4double           fWorldSizeX  = 320.*cm;
  G4double           fWorldSizeY  = 320.*cm;  
  G4double           fWorldSizeZ  = 270.*cm;  
  G4Material*        fDefaultMaterial = nullptr;

  G4double           fuelSizeXY   = 10.1600000*cm;
  G4double           fuelSizeZ    = 120.967500*cm;
  G4double           asseSizeZ    = 255.289250*cm;
  G4double           zFuelinAsse  = 123.310500*cm;

  G4double           reflectorXY = 193.6*cm;
  
  std::array<std::array<G4int, 19>, 19> fuelMap = {
                                        90,90,11,11,11,11,11,11,11,00,11,11,11,11,11,11,11,90,90,
                                        90,11,11,11,11,11,11,11,11,00,11,11,11,11,11,11,11,11,90,
                                        11,11,11,11,11,11,11,34,11,00,11,31,11,11,11,11,11,11,11,
                                        11,11,11,11,11,34,11,11,11,00,11,11,11,31,11,11,11,11,11,
                                        11,11,11,11,11,11,11,11,11,00,11,11,11,11,11,11,11,11,11,
                                        11,11,11,24,11,11,11,11,11,00,11,11,11,11,11,21,11,11,11,
                                        11,11,11,11,11,11,11,11,11,00,11,11,11,11,11,11,11,11,11,
                                        11,11,24,11,11,44,11,11,11,00,11,11,11,41,11,11,21,11,11,
                                        11,11,11,11,11,11,11,11,00,00,00,11,11,11,11,11,11,11,11,
                                        11,11,11,11,11,11,11,11,00,00,00,11,11,11,11,11,11,11,11,
                                        11,11,11,11,11,11,11,11,00,00,00,11,11,11,11,11,11,11,11,
                                        11,11,23,11,11,43,11,11,11,11,11,11,11,42,11,11,22,11,11,
                                        11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
                                        11,11,11,23,11,11,11,11,11,11,11,11,11,11,11,22,11,11,11,
                                        11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
                                        11,11,11,11,11,33,11,11,11,11,11,11,11,32,11,11,11,11,11,
                                        11,11,11,11,11,11,11,33,11,11,11,32,11,11,11,11,11,11,11,
                                        90,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,90,
                                        90,90,11,11,11,11,11,11,11,90,11,11,11,11,11,11,11,90,90};
  G4VPhysicalVolume* fPhysiWorld = nullptr;

private:

  G4VPhysicalVolume* ConstructVolumes();
  void ColorSpecs(G4LogicalVolume*, G4Color, G4bool, G4bool);
};


#endif

