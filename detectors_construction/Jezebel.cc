#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4RunManager.hh"
#include <iomanip>

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4Material* DetectorConstruction::MakeFuel()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> Pu
  G4Isotope* Pu239  = new G4Isotope("Pu239", 94, 239, 239.052162*g/mole);
  G4Isotope* Pu240  = new G4Isotope("Pu240", 94, 240, 240.053812*g/mole);
  G4Isotope* Pu241  = new G4Isotope("Pu241", 94, 241, 241.056850*g/mole);
  G4Element* Pu = new G4Element("plutonium", "Pu", 3);
  Pu -> AddIsotope(Pu239, 95.17960000*perCent);
  Pu -> AddIsotope(Pu240,  4.51796133*perCent);
  Pu -> AddIsotope(Pu241,  0.30243867*perCent);
  // -> Ga
  G4Isotope* Ga69  = new G4Isotope("Ga69", 31, 69, 68.925574*g/mole);
  G4Isotope* Ga71  = new G4Isotope("Ga71", 31, 71, 70.924703*g/mole);
  G4Element* Ga = new G4Element("gallium", "Ga", 2);
  Ga -> AddIsotope(Ga69, 59.42048459*perCent);
  Ga -> AddIsotope(Ga71, 40.57951541*perCent);
  // material definition
  G4Material* Fuel = new G4Material("Fuel", 15.610017*g/cm3, nComponents=2);
  Fuel -> AddElement(Pu , 98.98002842*perCent);
  Fuel -> AddElement(Ga ,  1.01997158*perCent);
  return Fuel;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  //
  // Materials
  //
  G4Material* uranium = DetectorConstruction::MakeFuel();
  
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  G4Sphere* solidWorld = new G4Sphere("World", 0., 6.3849*cm, 0., 360.*degree, 00., 180.*degree);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,              //solid
                        uranium,                 //material
                        "World");                //name

  fPhysiWorld = 
    new G4PVPlacement(0,                        //no rotation
                        G4ThreeVector(),        //at (0,0,0)
                      logicWorld,               //logical volume
                      "World",                  //name
                       0,                       //mother volume
                       false,                   //no boolean operation
                       0);                      //copy number

  return fPhysiWorld;
}