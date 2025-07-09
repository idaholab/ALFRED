#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
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
  // -> B
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.012937*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009305*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 18.43125165*perCent);
  B -> AddIsotope(B11, 81.56874835*perCent);
  // -> U
  G4Isotope* U235  = new G4Isotope("U235", 92, 235, 235.043928*g/mole);
  G4Isotope* U238  = new G4Isotope("U238", 92, 238, 238.050787*g/mole);
  G4Element* U = new G4Element("uranium", "U", 2);
  U -> AddIsotope(U235, 93.15938163*perCent);
  U -> AddIsotope(U238,  6.84061837*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.939608*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.934936*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935392*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933274*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.65055392*perCent);
  Fe -> AddIsotope(Fe56, 91.89753445*perCent);
  Fe -> AddIsotope(Fe57,  2.16143348*perCent);
  Fe -> AddIsotope(Fe58,  0.29047815*perCent);
  // -> O
  G4Isotope* O16  = new G4Isotope("O16", 8, 16, 15.994915*g/mole);
  G4Element* O = new G4Element("oxygen", "O", 1);
  O -> AddIsotope(O16, 100.00000000*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003355*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.85238745*perCent);
  C -> AddIsotope(C13,  1.14761255*perCent);
  // material definition
  G4Material* fuel = new G4Material("fuel", 1.724904*g/cm3, nComponents=5);
  fuel -> AddElement(B  ,  0.00075807*perCent);
  fuel -> AddElement(U  ,  0.21094611*perCent);
  fuel -> AddElement(Fe ,  0.05999583*perCent);
  fuel -> AddElement(O  ,  0.02867582*perCent);
  fuel -> AddElement(C  , 99.69962417*perCent);
  return fuel;
}

G4Material* DetectorConstruction::MakeZr()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> B
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.012937*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009305*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 17.48855302*perCent);
  B -> AddIsotope(B11, 82.51144698*perCent);
  // -> Cr
  G4Isotope* Cr50  = new G4Isotope("Cr50", 24, 50, 49.946042*g/mole);
  G4Isotope* Cr52  = new G4Isotope("Cr52", 24, 52, 51.940505*g/mole);
  G4Isotope* Cr53  = new G4Isotope("Cr53", 24, 53, 52.940646*g/mole);
  G4Isotope* Cr54  = new G4Isotope("Cr54", 24, 54, 53.938877*g/mole);
  G4Element* Cr = new G4Element("chromium", "Cr", 4);
  Cr -> AddIsotope(Cr50, 4.17848156*perCent);
  Cr -> AddIsotope(Cr52, 83.70100474*perCent);
  Cr -> AddIsotope(Cr53, 9.67233370*perCent);
  Cr -> AddIsotope(Cr54, 2.44818000*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.939608*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.934936*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935392*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933274*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54, 5.65059680*perCent);
  Fe -> AddIsotope(Fe56, 91.89742371*perCent);
  Fe -> AddIsotope(Fe57, 2.16149789*perCent);
  Fe -> AddIsotope(Fe58, 0.29048160*perCent);
  // -> Ni
  G4Isotope* Ni58  = new G4Isotope("Ni58", 28, 58, 57.935342*g/mole);
  G4Isotope* Ni60  = new G4Isotope("Ni60", 28, 60, 59.930785*g/mole);
  G4Isotope* Ni61  = new G4Isotope("Ni61", 28, 61, 60.931055*g/mole);
  G4Isotope* Ni62  = new G4Isotope("Ni62", 28, 62, 61.928345*g/mole);
  G4Isotope* Ni64  = new G4Isotope("Ni64", 28, 64, 63.927966*g/mole);
  G4Element* Ni = new G4Element("nickel", "Ni", 5);
  Ni -> AddIsotope(Ni58, 65.13911581*perCent);
  Ni -> AddIsotope(Ni60, 25.95103270*perCent);
  Ni -> AddIsotope(Ni61, 1.14713635*perCent);
  Ni -> AddIsotope(Ni62, 6.78087384*perCent);
  Ni -> AddIsotope(Ni64, 0.98184130*perCent);
  // -> Zr
  G4Isotope* Zr90  = new G4Isotope("Zr90", 40, 90, 89.904699*g/mole);
  G4Isotope* Zr91  = new G4Isotope("Zr91", 40, 91, 90.905640*g/mole);
  G4Isotope* Zr92  = new G4Isotope("Zr92", 40, 92, 91.905035*g/mole);
  G4Isotope* Zr94  = new G4Isotope("Zr94", 40, 94, 93.906313*g/mole);
  G4Isotope* Zr96  = new G4Isotope("Zr96", 40, 96, 95.908278*g/mole);
  G4Element* Zr = new G4Element("zirconium", "Zr", 5);
  Zr -> AddIsotope(Zr90, 50.70614048*perCent);
  Zr -> AddIsotope(Zr91, 11.18102333*perCent);
  Zr -> AddIsotope(Zr92, 17.27803094*perCent);
  Zr -> AddIsotope(Zr94, 17.89105807*perCent);
  Zr -> AddIsotope(Zr96, 2.94374718*perCent);
  // -> Cd
  G4Isotope* Cd106  = new G4Isotope("Cd106", 48, 106, 105.906460*g/mole);
  G4Isotope* Cd108  = new G4Isotope("Cd108", 48, 108, 107.904184*g/mole);
  G4Isotope* Cd110  = new G4Isotope("Cd110", 48, 110, 109.903007*g/mole);
  G4Isotope* Cd111  = new G4Isotope("Cd111", 48, 111, 110.904184*g/mole);
  G4Isotope* Cd112  = new G4Isotope("Cd112", 48, 112, 111.902764*g/mole);
  G4Isotope* Cd113  = new G4Isotope("Cd113", 48, 113, 112.904408*g/mole);
  G4Isotope* Cd114  = new G4Isotope("Cd114", 48, 114, 113.903365*g/mole);
  G4Isotope* Cd116  = new G4Isotope("Cd116", 48, 116, 115.904763*g/mole);
  G4Element* Cd = new G4Element("cadmium", "Cd", 8);
  Cd -> AddIsotope(Cd106, 1.17765661*perCent);
  Cd -> AddIsotope(Cd108, 0.85430509*perCent);
  Cd -> AddIsotope(Cd110, 12.21119309*perCent);
  Cd -> AddIsotope(Cd111, 12.62824460*perCent);
  Cd -> AddIsotope(Cd112, 24.02087955*perCent);
  Cd -> AddIsotope(Cd113, 12.27339394*perCent);
  Cd -> AddIsotope(Cd114, 29.11159879*perCent);
  Cd -> AddIsotope(Cd116, 7.72272833*perCent);
  // -> Sn
  G4Isotope* Sn112  = new G4Isotope("Sn112", 50, 112, 111.904825*g/mole);
  G4Isotope* Sn114  = new G4Isotope("Sn114", 50, 114, 113.902780*g/mole);
  G4Isotope* Sn115  = new G4Isotope("Sn115", 50, 115, 114.903345*g/mole);
  G4Isotope* Sn116  = new G4Isotope("Sn116", 50, 116, 115.901743*g/mole);
  G4Isotope* Sn117  = new G4Isotope("Sn117", 50, 117, 116.902954*g/mole);
  G4Isotope* Sn118  = new G4Isotope("Sn118", 50, 118, 117.901607*g/mole);
  G4Isotope* Sn119  = new G4Isotope("Sn119", 50, 119, 118.903311*g/mole);
  G4Isotope* Sn120  = new G4Isotope("Sn120", 50, 120, 119.902203*g/mole);
  G4Isotope* Sn122  = new G4Isotope("Sn122", 50, 122, 121.903445*g/mole);
  G4Isotope* Sn124  = new G4Isotope("Sn124", 50, 124, 123.905280*g/mole);
  G4Element* Sn = new G4Element("tin", "Sn", 10);
  Sn -> AddIsotope(Sn112, 0.91439908*perCent);
  Sn -> AddIsotope(Sn114, 0.63327593*perCent);
  Sn -> AddIsotope(Sn115, 0.32909565*perCent);
  Sn -> AddIsotope(Sn116, 14.19583209*perCent);
  Sn -> AddIsotope(Sn117, 7.56309869*perCent);
  Sn -> AddIsotope(Sn118, 24.05476180*perCent);
  Sn -> AddIsotope(Sn119, 8.60399818*perCent);
  Sn -> AddIsotope(Sn120, 32.90754715*perCent);
  Sn -> AddIsotope(Sn122, 4.75454391*perCent);
  Sn -> AddIsotope(Sn124, 6.04344750*perCent);
  // -> Hf
  G4Isotope* Hf174  = new G4Isotope("Hf174", 72, 174, 173.940048*g/mole);
  G4Isotope* Hf176  = new G4Isotope("Hf176", 72, 176, 175.941410*g/mole);
  G4Isotope* Hf177  = new G4Isotope("Hf177", 72, 177, 176.943230*g/mole);
  G4Isotope* Hf178  = new G4Isotope("Hf178", 72, 178, 177.943708*g/mole);
  G4Isotope* Hf179  = new G4Isotope("Hf179", 72, 179, 178.945826*g/mole);
  G4Isotope* Hf180  = new G4Isotope("Hf180", 72, 180, 179.946560*g/mole);
  G4Element* Hf = new G4Element("hafnium", "Hf", 6);
  Hf -> AddIsotope(Hf174, 0.15787397*perCent);
  Hf -> AddIsotope(Hf176, 5.13183766*perCent);
  Hf -> AddIsotope(Hf177, 18.44501438*perCent);
  Hf -> AddIsotope(Hf178, 27.21403564*perCent);
  Hf -> AddIsotope(Hf179, 13.66408222*perCent);
  Hf -> AddIsotope(Hf180, 35.38715613*perCent);
  // material definition
  G4Material* zr = new G4Material("zr", 6.530860*g/cm3, nComponents=8);
  zr -> AddElement(B  , 0.00020018*perCent);
  zr -> AddElement(Cr , 0.00299989*perCent);
  zr -> AddElement(Fe , 0.28297854*perCent);
  zr -> AddElement(Ni , 0.00051567*perCent);
  zr -> AddElement(Zr , 99.42324647*perCent);
  zr -> AddElement(Cd , 0.00002000*perCent);
  zr -> AddElement(Sn , 0.28003982*perCent);
  zr -> AddElement(Hf , 0.00999943*perCent);
  return zr;
}

G4Material* DetectorConstruction::MakeGraphite()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> B
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.012937*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009305*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 17.49004897*perCent);
  B -> AddIsotope(B11, 82.50995103*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.939608*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.934936*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935392*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933274*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.65381651*perCent);
  Fe -> AddIsotope(Fe56, 91.89386026*perCent);
  Fe -> AddIsotope(Fe57,  2.16178028*perCent);
  Fe -> AddIsotope(Fe58,  0.29054295*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003355*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.85238745*perCent);
  C -> AddIsotope(C13,  1.14761255*perCent);
  // material definition
  G4Material* graphite = new G4Material("graphite", 1.670199*g/cm3, nComponents=3);
  graphite -> AddElement(B  ,  0.00020018*perCent);
  graphite -> AddElement(Fe ,  0.09997412*perCent);
  graphite -> AddElement(C  , 99.89982570*perCent);
  return graphite;
}

G4Material* DetectorConstruction::MakeAir()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> N
  G4Isotope* N14  = new G4Isotope("N14", 7, 14, 14.003074*g/mole);
  G4Element* N = new G4Element("nitrogen", "N", 1);
  N -> AddIsotope(N14, 100.00000000*perCent);
  // -> O
  G4Isotope* O16  = new G4Isotope("O16", 8, 16, 15.994915*g/mole);
  G4Element* O = new G4Element("oxygen", "O", 1);
  O -> AddIsotope(O16, 100.00000000*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003355*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.85238745*perCent);
  C -> AddIsotope(C13,  1.14761255*perCent);
  // material definition
  G4Material* air = new G4Material("air", 0.001200*g/cm3, nComponents=3);
  air -> AddElement(N  , 76.50838222*perCent);
  air -> AddElement(O  , 23.47901800*perCent);
  air -> AddElement(C  ,  0.01259977*perCent);
  return air;
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
  G4Material* graphite = DetectorConstruction::MakeGraphite();
  G4Material* air = DetectorConstruction::MakeAir();
  
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  fDefaultMaterial = air;

  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  //
  // World
  //
  G4Box* solidWorld = new G4Box("World", fWorldSizeX/2,fWorldSizeY/2,fWorldSizeZ/2);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,              //solid
                        fDefaultMaterial,        //material
                        "World");                //name

  fPhysiWorld = 
    new G4PVPlacement(0,                        //no rotation
                        G4ThreeVector(),        //at (0,0,0)
                      logicWorld,               //logical volume
                      "World",                  //name
                       0,                       //mother volume
                       false,                   //no boolean operation
                       0);                      //copy number
                                 
  //
  // Fuel
  //
  for (G4int i=0; i<19; i++) {
    for (G4int j=0; j<19; j++) {
      G4String matname = uranium->GetName()+"_"+std::to_string(19*i+j);
      G4Box* solidFuel = new G4Box(matname, fuelSizeXY/2, fuelSizeXY/2, fuelSizeZ/2);

      G4LogicalVolume* logicFuel = new G4LogicalVolume(solidFuel,             // solid
                                                        uranium,              // material
                                                        matname);             // name
      
      // G4cout << "Mass: " << logicFuel->GetMass()/kg << G4endl;

      G4ThreeVector position = G4ThreeVector((i-9)*fuelSizeXY,(j-9)*fuelSizeXY,0.);
      new G4PVPlacement(0,                     //no rotation
                        position,              //position
                        logicFuel,             //logical volume        
                        matname,               //name
                        logicWorld,            //mother
                        false,                 //no boulean operat
                        19*i+j);               //copy number
    }
  }

  G4String matname = graphite->GetName();
  G4Box* subsolid1 = new G4Box("subsolid1", fWorldSizeX/2, fWorldSizeY/2, fWorldSizeZ/2);
  G4Box* subsolid2 = new G4Box("subsolid2", reflectorXY/2, reflectorXY/2, fWorldSizeZ/2);
  G4VSolid* solidReflector = new G4SubtractionSolid(matname, subsolid1, subsolid2);
  
  G4LogicalVolume* logicReflector = new G4LogicalVolume(solidReflector,       // solid
                                                        graphite,              // material
                                                        matname);             // name

  // G4cout << "Mass: " << logicReflector->GetMass()/kg << G4endl;

  G4ThreeVector position = G4ThreeVector(0.,0.,0.);
  new G4PVPlacement(0,                     //no rotation
                    position,              //position
                    logicReflector,        //logical volume        
                    matname,               //name
                    logicWorld,            //mother
                    false,                 //no boulean operat
                    0);                    //copy number

  return fPhysiWorld;
}