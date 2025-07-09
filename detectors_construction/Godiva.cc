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
  // -> U
  G4Isotope* U235  = new G4Isotope("U235", 92, 235, 235.043928*g/mole);
  G4Isotope* U238  = new G4Isotope("U238", 92, 238, 238.050787*g/mole);
  G4Isotope* U234  = new G4Isotope("U234", 92, 234, 234.040950*g/mole);
  G4Element* U = new G4Element("uranium", "U", 3);
  U -> AddIsotope(U235, 93.70996755*perCent);
  U -> AddIsotope(U238,  5.27003791*perCent);
  U -> AddIsotope(U234,  1.01999454*perCent);
  // material definition
  G4Material* uranium = new G4Material("uranium", 18.739886*g/cm3, nComponents=1);
  uranium -> AddElement(U  , 100.00000000*perCent);
  return uranium;
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

  G4Sphere* solidWorld = new G4Sphere("World", 0., 8.7407*cm, 0., 360.*degree, 00., 180.*degree);

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