// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
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
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.013*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 18.431252*perCent);
  B -> AddIsotope(B11, 81.568748*perCent);
  // -> U
  G4Isotope* U235  = new G4Isotope("U235", 92, 235, 235.044*g/mole);
  G4Isotope* U238  = new G4Isotope("U238", 92, 238, 238.051*g/mole);
  G4Element* U = new G4Element("uranium", "U", 2);
  U -> AddIsotope(U235, 93.159382*perCent);
  U -> AddIsotope(U238,  6.840618*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.650554*perCent);
  Fe -> AddIsotope(Fe56, 91.897534*perCent);
  Fe -> AddIsotope(Fe57,  2.161433*perCent);
  Fe -> AddIsotope(Fe58,  0.290478*perCent);
  // -> O
  G4Isotope* O16  = new G4Isotope("O16", 8, 16, 15.995*g/mole);
  G4Element* O = new G4Element("oxygen", "O", 1);
  O -> AddIsotope(O16, 100.000000*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("TS_C_of_Graphite", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* fuel = new G4Material("fuel", 1.725*g/cm3, nComponents=5);
  fuel -> AddElement(B  ,  0.000758*perCent);
  fuel -> AddElement(U  ,  0.210946*perCent);
  fuel -> AddElement(Fe ,  0.059996*perCent);
  fuel -> AddElement(O  ,  0.028676*perCent);
  fuel -> AddElement(C  , 99.699624*perCent);
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
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.013*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 17.488553*perCent);
  B -> AddIsotope(B11, 82.511447*perCent);
  // -> Cr
  G4Isotope* Cr50  = new G4Isotope("Cr50", 24, 50, 49.946*g/mole);
  G4Isotope* Cr52  = new G4Isotope("Cr52", 24, 52, 51.941*g/mole);
  G4Isotope* Cr53  = new G4Isotope("Cr53", 24, 53, 52.941*g/mole);
  G4Isotope* Cr54  = new G4Isotope("Cr54", 24, 54, 53.939*g/mole);
  G4Element* Cr = new G4Element("chromium", "Cr", 4);
  Cr -> AddIsotope(Cr50,  4.178482*perCent);
  Cr -> AddIsotope(Cr52, 83.701005*perCent);
  Cr -> AddIsotope(Cr53,  9.672334*perCent);
  Cr -> AddIsotope(Cr54,  2.448180*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.650597*perCent);
  Fe -> AddIsotope(Fe56, 91.897424*perCent);
  Fe -> AddIsotope(Fe57,  2.161498*perCent);
  Fe -> AddIsotope(Fe58,  0.290482*perCent);
  // -> Ni
  G4Isotope* Ni58  = new G4Isotope("Ni58", 28, 58, 57.935*g/mole);
  G4Isotope* Ni60  = new G4Isotope("Ni60", 28, 60, 59.931*g/mole);
  G4Isotope* Ni61  = new G4Isotope("Ni61", 28, 61, 60.931*g/mole);
  G4Isotope* Ni62  = new G4Isotope("Ni62", 28, 62, 61.928*g/mole);
  G4Isotope* Ni64  = new G4Isotope("Ni64", 28, 64, 63.928*g/mole);
  G4Element* Ni = new G4Element("nickel", "Ni", 5);
  Ni -> AddIsotope(Ni58, 65.139116*perCent);
  Ni -> AddIsotope(Ni60, 25.951033*perCent);
  Ni -> AddIsotope(Ni61,  1.147136*perCent);
  Ni -> AddIsotope(Ni62,  6.780874*perCent);
  Ni -> AddIsotope(Ni64,  0.981841*perCent);
  // -> Zr
  G4Isotope* Zr90  = new G4Isotope("Zr90", 40, 90, 89.905*g/mole);
  G4Isotope* Zr91  = new G4Isotope("Zr91", 40, 91, 90.906*g/mole);
  G4Isotope* Zr92  = new G4Isotope("Zr92", 40, 92, 91.905*g/mole);
  G4Isotope* Zr94  = new G4Isotope("Zr94", 40, 94, 93.906*g/mole);
  G4Isotope* Zr96  = new G4Isotope("Zr96", 40, 96, 95.908*g/mole);
  G4Element* Zr = new G4Element("zirconium", "Zr", 5);
  Zr -> AddIsotope(Zr90, 50.706140*perCent);
  Zr -> AddIsotope(Zr91, 11.181023*perCent);
  Zr -> AddIsotope(Zr92, 17.278031*perCent);
  Zr -> AddIsotope(Zr94, 17.891058*perCent);
  Zr -> AddIsotope(Zr96,  2.943747*perCent);
  // -> Cd
  G4Isotope* Cd106  = new G4Isotope("Cd106", 48, 106, 105.906*g/mole);
  G4Isotope* Cd108  = new G4Isotope("Cd108", 48, 108, 107.904*g/mole);
  G4Isotope* Cd110  = new G4Isotope("Cd110", 48, 110, 109.903*g/mole);
  G4Isotope* Cd111  = new G4Isotope("Cd111", 48, 111, 110.904*g/mole);
  G4Isotope* Cd112  = new G4Isotope("Cd112", 48, 112, 111.903*g/mole);
  G4Isotope* Cd113  = new G4Isotope("Cd113", 48, 113, 112.904*g/mole);
  G4Isotope* Cd114  = new G4Isotope("Cd114", 48, 114, 113.903*g/mole);
  G4Isotope* Cd116  = new G4Isotope("Cd116", 48, 116, 115.905*g/mole);
  G4Element* Cd = new G4Element("cadmium", "Cd", 8);
  Cd -> AddIsotope(Cd106,  1.177657*perCent);
  Cd -> AddIsotope(Cd108,  0.854305*perCent);
  Cd -> AddIsotope(Cd110, 12.211193*perCent);
  Cd -> AddIsotope(Cd111, 12.628245*perCent);
  Cd -> AddIsotope(Cd112, 24.020880*perCent);
  Cd -> AddIsotope(Cd113, 12.273394*perCent);
  Cd -> AddIsotope(Cd114, 29.111599*perCent);
  Cd -> AddIsotope(Cd116,  7.722728*perCent);
  // -> Sn
  G4Isotope* Sn112  = new G4Isotope("Sn112", 50, 112, 111.905*g/mole);
  G4Isotope* Sn114  = new G4Isotope("Sn114", 50, 114, 113.903*g/mole);
  G4Isotope* Sn115  = new G4Isotope("Sn115", 50, 115, 114.903*g/mole);
  G4Isotope* Sn116  = new G4Isotope("Sn116", 50, 116, 115.902*g/mole);
  G4Isotope* Sn117  = new G4Isotope("Sn117", 50, 117, 116.903*g/mole);
  G4Isotope* Sn118  = new G4Isotope("Sn118", 50, 118, 117.902*g/mole);
  G4Isotope* Sn119  = new G4Isotope("Sn119", 50, 119, 118.903*g/mole);
  G4Isotope* Sn120  = new G4Isotope("Sn120", 50, 120, 119.902*g/mole);
  G4Isotope* Sn122  = new G4Isotope("Sn122", 50, 122, 121.903*g/mole);
  G4Isotope* Sn124  = new G4Isotope("Sn124", 50, 124, 123.905*g/mole);
  G4Element* Sn = new G4Element("tin", "Sn", 10);
  Sn -> AddIsotope(Sn112,  0.914399*perCent);
  Sn -> AddIsotope(Sn114,  0.633276*perCent);
  Sn -> AddIsotope(Sn115,  0.329096*perCent);
  Sn -> AddIsotope(Sn116, 14.195832*perCent);
  Sn -> AddIsotope(Sn117,  7.563099*perCent);
  Sn -> AddIsotope(Sn118, 24.054762*perCent);
  Sn -> AddIsotope(Sn119,  8.603998*perCent);
  Sn -> AddIsotope(Sn120, 32.907547*perCent);
  Sn -> AddIsotope(Sn122,  4.754544*perCent);
  Sn -> AddIsotope(Sn124,  6.043448*perCent);
  // -> Hf
  G4Isotope* Hf174  = new G4Isotope("Hf174", 72, 174, 173.940*g/mole);
  G4Isotope* Hf176  = new G4Isotope("Hf176", 72, 176, 175.941*g/mole);
  G4Isotope* Hf177  = new G4Isotope("Hf177", 72, 177, 176.943*g/mole);
  G4Isotope* Hf178  = new G4Isotope("Hf178", 72, 178, 177.944*g/mole);
  G4Isotope* Hf179  = new G4Isotope("Hf179", 72, 179, 178.946*g/mole);
  G4Isotope* Hf180  = new G4Isotope("Hf180", 72, 180, 179.947*g/mole);
  G4Element* Hf = new G4Element("hafnium", "Hf", 6);
  Hf -> AddIsotope(Hf174,  0.157874*perCent);
  Hf -> AddIsotope(Hf176,  5.131838*perCent);
  Hf -> AddIsotope(Hf177, 18.445014*perCent);
  Hf -> AddIsotope(Hf178, 27.214036*perCent);
  Hf -> AddIsotope(Hf179, 13.664082*perCent);
  Hf -> AddIsotope(Hf180, 35.387156*perCent);
  // material definition
  G4Material* zr = new G4Material("zr", 6.531*g/cm3, nComponents=8);
  zr -> AddElement(B  ,  0.000200*perCent);
  zr -> AddElement(Cr ,  0.003000*perCent);
  zr -> AddElement(Fe ,  0.282979*perCent);
  zr -> AddElement(Ni ,  0.000516*perCent);
  zr -> AddElement(Zr , 99.423246*perCent);
  zr -> AddElement(Cd ,  0.000020*perCent);
  zr -> AddElement(Sn ,  0.280040*perCent);
  zr -> AddElement(Hf ,  0.009999*perCent);
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
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.013*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 17.490049*perCent);
  B -> AddIsotope(B11, 82.509951*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.653817*perCent);
  Fe -> AddIsotope(Fe56, 91.893860*perCent);
  Fe -> AddIsotope(Fe57,  2.161780*perCent);
  Fe -> AddIsotope(Fe58,  0.290543*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("TS_C_of_Graphite", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* graphite = new G4Material("graphite", 1.670*g/cm3, nComponents=3);
  graphite -> AddElement(B  ,  0.000200*perCent);
  graphite -> AddElement(Fe ,  0.099974*perCent);
  graphite -> AddElement(C  , 99.899826*perCent);
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
  G4Isotope* N14  = new G4Isotope("N14", 7, 14, 14.003*g/mole);
  G4Element* N = new G4Element("nitrogen", "N", 1);
  N -> AddIsotope(N14, 100.000000*perCent);
  // -> O
  G4Isotope* O16  = new G4Isotope("O16", 8, 16, 15.995*g/mole);
  G4Element* O = new G4Element("oxygen", "O", 1);
  O -> AddIsotope(O16, 100.000000*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* air = new G4Material("air", 0.001*g/cm3, nComponents=3);
  air -> AddElement(N  , 76.508382*perCent);
  air -> AddElement(O  , 23.479018*perCent);
  air -> AddElement(C  ,  0.012600*perCent);
  return air;
}

G4Material* DetectorConstruction::MakeAlSteel()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> Al
  G4Isotope* Al27  = new G4Isotope("Al27", 13, 27, 26.982*g/mole);
  G4Element* Al = new G4Element("aluminium", "Al", 1);
  Al -> AddIsotope(Al27, 100.000000*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.849237*perCent);
  Fe -> AddIsotope(Fe56, 91.750608*perCent);
  Fe -> AddIsotope(Fe57,  2.120112*perCent);
  Fe -> AddIsotope(Fe58,  0.280043*perCent);
  // -> Mo
  G4Isotope* Mo92  = new G4Isotope("Mo92", 42, 92, 91.907*g/mole);
  G4Isotope* Mo94  = new G4Isotope("Mo94", 42, 94, 93.905*g/mole);
  G4Isotope* Mo95  = new G4Isotope("Mo95", 42, 95, 94.906*g/mole);
  G4Isotope* Mo96  = new G4Isotope("Mo96", 42, 96, 95.905*g/mole);
  G4Isotope* Mo97  = new G4Isotope("Mo97", 42, 97, 96.906*g/mole);
  G4Isotope* Mo98  = new G4Isotope("Mo98", 42, 98, 97.905*g/mole);
  G4Isotope* Mo100  = new G4Isotope("Mo100", 42, 100, 99.907*g/mole);
  G4Element* Mo = new G4Element("molybdenum", "Mo", 7);
  Mo -> AddIsotope(Mo92, 14.217439*perCent);
  Mo -> AddIsotope(Mo94,  9.054629*perCent);
  Mo -> AddIsotope(Mo95, 15.749826*perCent);
  Mo -> AddIsotope(Mo96, 16.675374*perCent);
  Mo -> AddIsotope(Mo97,  9.647038*perCent);
  Mo -> AddIsotope(Mo98, 24.626545*perCent);
  Mo -> AddIsotope(Mo100, 10.029149*perCent);
  // -> N
  G4Isotope* N14  = new G4Isotope("N14", 7, 14, 14.003*g/mole);
  G4Element* N = new G4Element("nitrogen", "N", 1);
  N -> AddIsotope(N14, 100.000000*perCent);
  // -> O
  G4Isotope* O16  = new G4Isotope("O16", 8, 16, 15.995*g/mole);
  G4Element* O = new G4Element("oxygen", "O", 1);
  O -> AddIsotope(O16, 100.000000*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* Al_steel = new G4Material("Al_steel", 4.928*g/cm3, nComponents=6);
  Al_steel -> AddElement(Al , 20.082963*perCent);
  Al_steel -> AddElement(Fe , 78.753795*perCent);
  Al_steel -> AddElement(Mo ,  0.878522*perCent);
  Al_steel -> AddElement(N  ,  0.002454*perCent);
  Al_steel -> AddElement(O  ,  0.000753*perCent);
  Al_steel -> AddElement(C  ,  0.281514*perCent);
  return Al_steel;
}

G4Material* DetectorConstruction::MakeAlAir()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> Al
  G4Isotope* Al27  = new G4Isotope("Al27", 13, 27, 26.982*g/mole);
  G4Element* Al = new G4Element("aluminium", "Al", 1);
  Al -> AddIsotope(Al27, 100.000000*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.650441*perCent);
  Fe -> AddIsotope(Fe56, 91.897695*perCent);
  Fe -> AddIsotope(Fe57,  2.161384*perCent);
  Fe -> AddIsotope(Fe58,  0.290480*perCent);
  // -> N
  G4Isotope* N14  = new G4Isotope("N14", 7, 14, 14.003*g/mole);
  G4Element* N = new G4Element("nitrogen", "N", 1);
  N -> AddIsotope(N14, 100.000000*perCent);
  // -> O
  G4Isotope* O16  = new G4Isotope("O16", 8, 16, 15.995*g/mole);
  G4Element* O = new G4Element("oxygen", "O", 1);
  O -> AddIsotope(O16, 100.000000*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* Al_air = new G4Material("Al_air", 1.249*g/cm3, nComponents=5);
  Al_air -> AddElement(Al , 98.449572*perCent);
  Al_air -> AddElement(Fe ,  1.498687*perCent);
  Al_air -> AddElement(N  ,  0.039587*perCent);
  Al_air -> AddElement(O  ,  0.012148*perCent);
  Al_air -> AddElement(C  ,  0.000007*perCent);
  return Al_air;
}

G4Material* DetectorConstruction::MakeReflector()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> B
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.013*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 17.490049*perCent);
  B -> AddIsotope(B11, 82.509951*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.653817*perCent);
  Fe -> AddIsotope(Fe56, 91.893860*perCent);
  Fe -> AddIsotope(Fe57,  2.161780*perCent);
  Fe -> AddIsotope(Fe58,  0.290543*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("TS_C_of_Graphite", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* reflector = new G4Material("reflector", 1.670*g/cm3, nComponents=3);
  reflector -> AddElement(B  ,  0.000200*perCent);
  reflector -> AddElement(Fe ,  0.099974*perCent);
  reflector -> AddElement(C  , 99.899826*perCent);
  return reflector;
}

G4Material* DetectorConstruction::MakeAluminium()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> Al
  G4Isotope* Al27  = new G4Isotope("Al27", 13, 27, 26.982*g/mole);
  G4Element* Al = new G4Element("aluminium", "Al", 1);
  Al -> AddIsotope(Al27, 100.000000*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.650442*perCent);
  Fe -> AddIsotope(Fe56, 91.897693*perCent);
  Fe -> AddIsotope(Fe57,  2.161385*perCent);
  Fe -> AddIsotope(Fe58,  0.290480*perCent);
  // material definition
  G4Material* aluminium = new G4Material("aluminium", 2.705*g/cm3, nComponents=2);
  aluminium -> AddElement(Al , 98.500538*perCent);
  aluminium -> AddElement(Fe ,  1.499462*perCent);
  return aluminium;
}

G4Material* DetectorConstruction::MakeZirc2()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.650463*perCent);
  Fe -> AddIsotope(Fe56, 91.897668*perCent);
  Fe -> AddIsotope(Fe57,  2.161398*perCent);
  Fe -> AddIsotope(Fe58,  0.290471*perCent);
  // -> Cr
  G4Isotope* Cr50  = new G4Isotope("Cr50", 24, 50, 49.946*g/mole);
  G4Isotope* Cr52  = new G4Isotope("Cr52", 24, 52, 51.941*g/mole);
  G4Isotope* Cr53  = new G4Isotope("Cr53", 24, 53, 52.941*g/mole);
  G4Isotope* Cr54  = new G4Isotope("Cr54", 24, 54, 53.939*g/mole);
  G4Element* Cr = new G4Element("chromium", "Cr", 4);
  Cr -> AddIsotope(Cr50,  4.178512*perCent);
  Cr -> AddIsotope(Cr52, 83.700639*perCent);
  Cr -> AddIsotope(Cr53,  9.672600*perCent);
  Cr -> AddIsotope(Cr54,  2.448249*perCent);
  // -> Ni
  G4Isotope* Ni58  = new G4Isotope("Ni58", 28, 58, 57.935*g/mole);
  G4Isotope* Ni60  = new G4Isotope("Ni60", 28, 60, 59.931*g/mole);
  G4Isotope* Ni61  = new G4Isotope("Ni61", 28, 61, 60.931*g/mole);
  G4Isotope* Ni62  = new G4Isotope("Ni62", 28, 62, 61.928*g/mole);
  G4Isotope* Ni64  = new G4Isotope("Ni64", 28, 64, 63.928*g/mole);
  G4Element* Ni = new G4Element("nickel", "Ni", 5);
  Ni -> AddIsotope(Ni58, 67.200891*perCent);
  Ni -> AddIsotope(Ni60, 26.772680*perCent);
  Ni -> AddIsotope(Ni61,  1.183453*perCent);
  Ni -> AddIsotope(Ni62,  3.830040*perCent);
  Ni -> AddIsotope(Ni64,  1.012936*perCent);
  // -> Zr
  G4Isotope* Zr90  = new G4Isotope("Zr90", 40, 90, 89.905*g/mole);
  G4Isotope* Zr91  = new G4Isotope("Zr91", 40, 91, 90.906*g/mole);
  G4Isotope* Zr92  = new G4Isotope("Zr92", 40, 92, 91.905*g/mole);
  G4Isotope* Zr94  = new G4Isotope("Zr94", 40, 94, 93.906*g/mole);
  G4Isotope* Zr96  = new G4Isotope("Zr96", 40, 96, 95.908*g/mole);
  G4Element* Zr = new G4Element("zirconium", "Zr", 5);
  Zr -> AddIsotope(Zr90, 50.706130*perCent);
  Zr -> AddIsotope(Zr91, 11.180877*perCent);
  Zr -> AddIsotope(Zr92, 17.278090*perCent);
  Zr -> AddIsotope(Zr94, 17.891116*perCent);
  Zr -> AddIsotope(Zr96,  2.943786*perCent);
  // -> Sn
  G4Isotope* Sn112  = new G4Isotope("Sn112", 50, 112, 111.905*g/mole);
  G4Isotope* Sn114  = new G4Isotope("Sn114", 50, 114, 113.903*g/mole);
  G4Isotope* Sn115  = new G4Isotope("Sn115", 50, 115, 114.903*g/mole);
  G4Isotope* Sn116  = new G4Isotope("Sn116", 50, 116, 115.902*g/mole);
  G4Isotope* Sn117  = new G4Isotope("Sn117", 50, 117, 116.903*g/mole);
  G4Isotope* Sn118  = new G4Isotope("Sn118", 50, 118, 117.902*g/mole);
  G4Isotope* Sn119  = new G4Isotope("Sn119", 50, 119, 118.903*g/mole);
  G4Isotope* Sn120  = new G4Isotope("Sn120", 50, 120, 119.902*g/mole);
  G4Isotope* Sn122  = new G4Isotope("Sn122", 50, 122, 121.903*g/mole);
  G4Isotope* Sn124  = new G4Isotope("Sn124", 50, 124, 123.905*g/mole);
  G4Element* Sn = new G4Element("tin", "Sn", 10);
  Sn -> AddIsotope(Sn112,  0.914393*perCent);
  Sn -> AddIsotope(Sn114,  0.633273*perCent);
  Sn -> AddIsotope(Sn115,  0.329096*perCent);
  Sn -> AddIsotope(Sn116, 14.196015*perCent);
  Sn -> AddIsotope(Sn117,  7.563077*perCent);
  Sn -> AddIsotope(Sn118, 24.055102*perCent);
  Sn -> AddIsotope(Sn119,  8.603986*perCent);
  Sn -> AddIsotope(Sn120, 32.907119*perCent);
  Sn -> AddIsotope(Sn122,  4.754548*perCent);
  Sn -> AddIsotope(Sn124,  6.043392*perCent);
  // -> Hf
  G4Isotope* Hf174  = new G4Isotope("Hf174", 72, 174, 173.940*g/mole);
  G4Isotope* Hf176  = new G4Isotope("Hf176", 72, 176, 175.941*g/mole);
  G4Isotope* Hf177  = new G4Isotope("Hf177", 72, 177, 176.943*g/mole);
  G4Isotope* Hf178  = new G4Isotope("Hf178", 72, 178, 177.944*g/mole);
  G4Isotope* Hf179  = new G4Isotope("Hf179", 72, 179, 178.946*g/mole);
  G4Isotope* Hf180  = new G4Isotope("Hf180", 72, 180, 179.947*g/mole);
  G4Element* Hf = new G4Element("hafnium", "Hf", 6);
  Hf -> AddIsotope(Hf174,  0.157874*perCent);
  Hf -> AddIsotope(Hf176,  5.131750*perCent);
  Hf -> AddIsotope(Hf177, 18.445147*perCent);
  Hf -> AddIsotope(Hf178, 27.214017*perCent);
  Hf -> AddIsotope(Hf179, 13.664092*perCent);
  Hf -> AddIsotope(Hf180, 35.387121*perCent);
  // material definition
  G4Material* zirc2 = new G4Material("zirc2", 6.560*g/cm3, nComponents=6);
  zirc2 -> AddElement(Fe ,  0.135000*perCent);
  zirc2 -> AddElement(Cr ,  0.100000*perCent);
  zirc2 -> AddElement(Ni ,  0.055001*perCent);
  zirc2 -> AddElement(Zr , 98.249993*perCent);
  zirc2 -> AddElement(Sn ,  1.450007*perCent);
  zirc2 -> AddElement(Hf ,  0.010000*perCent);
  return zirc2;
}

G4Material* DetectorConstruction::MakeSteel()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.850010*perCent);
  Fe -> AddIsotope(Fe56, 91.750037*perCent);
  Fe -> AddIsotope(Fe57,  2.119951*perCent);
  Fe -> AddIsotope(Fe58,  0.280002*perCent);
  // -> Mo
  G4Isotope* Mo92  = new G4Isotope("Mo92", 42, 92, 91.907*g/mole);
  G4Isotope* Mo94  = new G4Isotope("Mo94", 42, 94, 93.905*g/mole);
  G4Isotope* Mo95  = new G4Isotope("Mo95", 42, 95, 94.906*g/mole);
  G4Isotope* Mo96  = new G4Isotope("Mo96", 42, 96, 95.905*g/mole);
  G4Isotope* Mo97  = new G4Isotope("Mo97", 42, 97, 96.906*g/mole);
  G4Isotope* Mo98  = new G4Isotope("Mo98", 42, 98, 97.905*g/mole);
  G4Isotope* Mo100  = new G4Isotope("Mo100", 42, 100, 99.907*g/mole);
  G4Element* Mo = new G4Element("molybdenum", "Mo", 7);
  Mo -> AddIsotope(Mo92, 14.217440*perCent);
  Mo -> AddIsotope(Mo94,  9.054629*perCent);
  Mo -> AddIsotope(Mo95, 15.749827*perCent);
  Mo -> AddIsotope(Mo96, 16.675376*perCent);
  Mo -> AddIsotope(Mo97,  9.647037*perCent);
  Mo -> AddIsotope(Mo98, 24.626544*perCent);
  Mo -> AddIsotope(Mo100, 10.029148*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* steel = new G4Material("steel", 7.896*g/cm3, nComponents=3);
  steel -> AddElement(Fe , 98.542818*perCent);
  steel -> AddElement(Mo ,  1.103558*perCent);
  steel -> AddElement(C  ,  0.353624*perCent);
  return steel;
}

G4Material* DetectorConstruction::MakeZrSteel()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> B
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.013*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 17.488688*perCent);
  B -> AddIsotope(B11, 82.511312*perCent);
  // -> Cr
  G4Isotope* Cr50  = new G4Isotope("Cr50", 24, 50, 49.946*g/mole);
  G4Isotope* Cr52  = new G4Isotope("Cr52", 24, 52, 51.941*g/mole);
  G4Isotope* Cr53  = new G4Isotope("Cr53", 24, 53, 52.941*g/mole);
  G4Isotope* Cr54  = new G4Isotope("Cr54", 24, 54, 53.939*g/mole);
  G4Element* Cr = new G4Element("chromium", "Cr", 4);
  Cr -> AddIsotope(Cr50,  4.178476*perCent);
  Cr -> AddIsotope(Cr52, 83.700752*perCent);
  Cr -> AddIsotope(Cr53,  9.672567*perCent);
  Cr -> AddIsotope(Cr54,  2.448206*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.848854*perCent);
  Fe -> AddIsotope(Fe56, 91.750905*perCent);
  Fe -> AddIsotope(Fe57,  2.120186*perCent);
  Fe -> AddIsotope(Fe58,  0.280055*perCent);
  // -> Ni
  G4Isotope* Ni58  = new G4Isotope("Ni58", 28, 58, 57.935*g/mole);
  G4Isotope* Ni60  = new G4Isotope("Ni60", 28, 60, 59.931*g/mole);
  G4Isotope* Ni61  = new G4Isotope("Ni61", 28, 61, 60.931*g/mole);
  G4Isotope* Ni62  = new G4Isotope("Ni62", 28, 62, 61.928*g/mole);
  G4Isotope* Ni64  = new G4Isotope("Ni64", 28, 64, 63.928*g/mole);
  G4Element* Ni = new G4Element("nickel", "Ni", 5);
  Ni -> AddIsotope(Ni58, 65.139648*perCent);
  Ni -> AddIsotope(Ni60, 25.950715*perCent);
  Ni -> AddIsotope(Ni61,  1.147105*perCent);
  Ni -> AddIsotope(Ni62,  6.780722*perCent);
  Ni -> AddIsotope(Ni64,  0.981811*perCent);
  // -> Zr
  G4Isotope* Zr90  = new G4Isotope("Zr90", 40, 90, 89.905*g/mole);
  G4Isotope* Zr91  = new G4Isotope("Zr91", 40, 91, 90.906*g/mole);
  G4Isotope* Zr92  = new G4Isotope("Zr92", 40, 92, 91.905*g/mole);
  G4Isotope* Zr94  = new G4Isotope("Zr94", 40, 94, 93.906*g/mole);
  G4Isotope* Zr96  = new G4Isotope("Zr96", 40, 96, 95.908*g/mole);
  G4Element* Zr = new G4Element("zirconium", "Zr", 5);
  Zr -> AddIsotope(Zr90, 50.706405*perCent);
  Zr -> AddIsotope(Zr91, 11.180986*perCent);
  Zr -> AddIsotope(Zr92, 17.277972*perCent);
  Zr -> AddIsotope(Zr94, 17.890941*perCent);
  Zr -> AddIsotope(Zr96,  2.943695*perCent);
  // -> Mo
  G4Isotope* Mo92  = new G4Isotope("Mo92", 42, 92, 91.907*g/mole);
  G4Isotope* Mo94  = new G4Isotope("Mo94", 42, 94, 93.905*g/mole);
  G4Isotope* Mo95  = new G4Isotope("Mo95", 42, 95, 94.906*g/mole);
  G4Isotope* Mo96  = new G4Isotope("Mo96", 42, 96, 95.905*g/mole);
  G4Isotope* Mo97  = new G4Isotope("Mo97", 42, 97, 96.906*g/mole);
  G4Isotope* Mo98  = new G4Isotope("Mo98", 42, 98, 97.905*g/mole);
  G4Isotope* Mo100  = new G4Isotope("Mo100", 42, 100, 99.907*g/mole);
  G4Element* Mo = new G4Element("molybdenum", "Mo", 7);
  Mo -> AddIsotope(Mo92, 14.217529*perCent);
  Mo -> AddIsotope(Mo94,  9.054575*perCent);
  Mo -> AddIsotope(Mo95, 15.749651*perCent);
  Mo -> AddIsotope(Mo96, 16.675355*perCent);
  Mo -> AddIsotope(Mo97,  9.647169*perCent);
  Mo -> AddIsotope(Mo98, 24.626548*perCent);
  Mo -> AddIsotope(Mo100, 10.029173*perCent);
  // -> Cd
  G4Isotope* Cd106  = new G4Isotope("Cd106", 48, 106, 105.906*g/mole);
  G4Isotope* Cd108  = new G4Isotope("Cd108", 48, 108, 107.904*g/mole);
  G4Isotope* Cd110  = new G4Isotope("Cd110", 48, 110, 109.903*g/mole);
  G4Isotope* Cd111  = new G4Isotope("Cd111", 48, 111, 110.904*g/mole);
  G4Isotope* Cd112  = new G4Isotope("Cd112", 48, 112, 111.903*g/mole);
  G4Isotope* Cd113  = new G4Isotope("Cd113", 48, 113, 112.904*g/mole);
  G4Isotope* Cd114  = new G4Isotope("Cd114", 48, 114, 113.903*g/mole);
  G4Isotope* Cd116  = new G4Isotope("Cd116", 48, 116, 115.905*g/mole);
  G4Element* Cd = new G4Element("cadmium", "Cd", 8);
  Cd -> AddIsotope(Cd106,  1.177656*perCent);
  Cd -> AddIsotope(Cd108,  0.854296*perCent);
  Cd -> AddIsotope(Cd110, 12.211228*perCent);
  Cd -> AddIsotope(Cd111, 12.628277*perCent);
  Cd -> AddIsotope(Cd112, 24.020043*perCent);
  Cd -> AddIsotope(Cd113, 12.273395*perCent);
  Cd -> AddIsotope(Cd114, 29.112323*perCent);
  Cd -> AddIsotope(Cd116,  7.722782*perCent);
  // -> Sn
  G4Isotope* Sn112  = new G4Isotope("Sn112", 50, 112, 111.905*g/mole);
  G4Isotope* Sn114  = new G4Isotope("Sn114", 50, 114, 113.903*g/mole);
  G4Isotope* Sn115  = new G4Isotope("Sn115", 50, 115, 114.903*g/mole);
  G4Isotope* Sn116  = new G4Isotope("Sn116", 50, 116, 115.902*g/mole);
  G4Isotope* Sn117  = new G4Isotope("Sn117", 50, 117, 116.903*g/mole);
  G4Isotope* Sn118  = new G4Isotope("Sn118", 50, 118, 117.902*g/mole);
  G4Isotope* Sn119  = new G4Isotope("Sn119", 50, 119, 118.903*g/mole);
  G4Isotope* Sn120  = new G4Isotope("Sn120", 50, 120, 119.902*g/mole);
  G4Isotope* Sn122  = new G4Isotope("Sn122", 50, 122, 121.903*g/mole);
  G4Isotope* Sn124  = new G4Isotope("Sn124", 50, 124, 123.905*g/mole);
  G4Element* Sn = new G4Element("tin", "Sn", 10);
  Sn -> AddIsotope(Sn112,  0.914402*perCent);
  Sn -> AddIsotope(Sn114,  0.633282*perCent);
  Sn -> AddIsotope(Sn115,  0.329093*perCent);
  Sn -> AddIsotope(Sn116, 14.195844*perCent);
  Sn -> AddIsotope(Sn117,  7.563046*perCent);
  Sn -> AddIsotope(Sn118, 24.054774*perCent);
  Sn -> AddIsotope(Sn119,  8.604019*perCent);
  Sn -> AddIsotope(Sn120, 32.907544*perCent);
  Sn -> AddIsotope(Sn122,  4.754589*perCent);
  Sn -> AddIsotope(Sn124,  6.043405*perCent);
  // -> Hf
  G4Isotope* Hf174  = new G4Isotope("Hf174", 72, 174, 173.940*g/mole);
  G4Isotope* Hf176  = new G4Isotope("Hf176", 72, 176, 175.941*g/mole);
  G4Isotope* Hf177  = new G4Isotope("Hf177", 72, 177, 176.943*g/mole);
  G4Isotope* Hf178  = new G4Isotope("Hf178", 72, 178, 177.944*g/mole);
  G4Isotope* Hf179  = new G4Isotope("Hf179", 72, 179, 178.946*g/mole);
  G4Isotope* Hf180  = new G4Isotope("Hf180", 72, 180, 179.947*g/mole);
  G4Element* Hf = new G4Element("hafnium", "Hf", 6);
  Hf -> AddIsotope(Hf174,  0.157876*perCent);
  Hf -> AddIsotope(Hf176,  5.131835*perCent);
  Hf -> AddIsotope(Hf177, 18.445033*perCent);
  Hf -> AddIsotope(Hf178, 27.213736*perCent);
  Hf -> AddIsotope(Hf179, 13.664340*perCent);
  Hf -> AddIsotope(Hf180, 35.387180*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* zr_steel = new G4Material("zr_steel", 6.956*g/cm3, nComponents=10);
  zr_steel -> AddElement(B  ,  0.000129*perCent);
  zr_steel -> AddElement(Cr ,  0.001940*perCent);
  zr_steel -> AddElement(Fe , 34.994906*perCent);
  zr_steel -> AddElement(Ni ,  0.000334*perCent);
  zr_steel -> AddElement(Zr , 64.300329*perCent);
  zr_steel -> AddElement(Mo ,  0.389851*perCent);
  zr_steel -> AddElement(Cd ,  0.000013*perCent);
  zr_steel -> AddElement(Sn ,  0.181109*perCent);
  zr_steel -> AddElement(Hf ,  0.006467*perCent);
  zr_steel -> AddElement(C  ,  0.124923*perCent);
  return zr_steel;
}

G4Material* DetectorConstruction::MakeB4cNew()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> B
  G4Isotope* B10  = new G4Isotope("B10", 5, 10, 10.013*g/mole);
  G4Isotope* B11  = new G4Isotope("B11", 5, 11, 11.009*g/mole);
  G4Element* B = new G4Element("boron", "B", 2);
  B -> AddIsotope(B10, 18.430552*perCent);
  B -> AddIsotope(B11, 81.569448*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* b4c_new = new G4Material("b4c_new", 1.800*g/cm3, nComponents=2);
  b4c_new -> AddElement(B  , 78.264468*perCent);
  b4c_new -> AddElement(C  , 21.735532*perCent);
  return b4c_new;
}

G4Material* DetectorConstruction::MakeAirSteel()
{
  //
  // Materials
  //
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;

  // elements definitions
  // -> N
  G4Isotope* N14  = new G4Isotope("N14", 7, 14, 14.003*g/mole);
  G4Element* N = new G4Element("nitrogen", "N", 1);
  N -> AddIsotope(N14, 100.000000*perCent);
  // -> O
  G4Isotope* O16  = new G4Isotope("O16", 8, 16, 15.995*g/mole);
  G4Element* O = new G4Element("oxygen", "O", 1);
  O -> AddIsotope(O16, 100.000000*perCent);
  // -> Fe
  G4Isotope* Fe54  = new G4Isotope("Fe54", 26, 54, 53.940*g/mole);
  G4Isotope* Fe56  = new G4Isotope("Fe56", 26, 56, 55.935*g/mole);
  G4Isotope* Fe57  = new G4Isotope("Fe57", 26, 57, 56.935*g/mole);
  G4Isotope* Fe58  = new G4Isotope("Fe58", 26, 58, 57.933*g/mole);
  G4Element* Fe = new G4Element("iron", "Fe", 4);
  Fe -> AddIsotope(Fe54,  5.850452*perCent);
  Fe -> AddIsotope(Fe56, 91.749209*perCent);
  Fe -> AddIsotope(Fe57,  2.120268*perCent);
  Fe -> AddIsotope(Fe58,  0.280071*perCent);
  // -> Mo
  G4Isotope* Mo92  = new G4Isotope("Mo92", 42, 92, 91.907*g/mole);
  G4Isotope* Mo94  = new G4Isotope("Mo94", 42, 94, 93.905*g/mole);
  G4Isotope* Mo95  = new G4Isotope("Mo95", 42, 95, 94.906*g/mole);
  G4Isotope* Mo96  = new G4Isotope("Mo96", 42, 96, 95.905*g/mole);
  G4Isotope* Mo97  = new G4Isotope("Mo97", 42, 97, 96.906*g/mole);
  G4Isotope* Mo98  = new G4Isotope("Mo98", 42, 98, 97.905*g/mole);
  G4Isotope* Mo100  = new G4Isotope("Mo100", 42, 100, 99.907*g/mole);
  G4Element* Mo = new G4Element("molybdenum", "Mo", 7);
  Mo -> AddIsotope(Mo92, 14.220176*perCent);
  Mo -> AddIsotope(Mo94,  9.053856*perCent);
  Mo -> AddIsotope(Mo95, 15.751998*perCent);
  Mo -> AddIsotope(Mo96, 16.673894*perCent);
  Mo -> AddIsotope(Mo97,  9.645611*perCent);
  Mo -> AddIsotope(Mo98, 24.628052*perCent);
  Mo -> AddIsotope(Mo100, 10.026412*perCent);
  // -> C
  G4Isotope* C12  = new G4Isotope("C12", 6, 12, 12.000*g/mole);
  G4Isotope* C13  = new G4Isotope("C13", 6, 13, 13.003*g/mole);
  G4Element* C = new G4Element("carbon", "C", 2);
  C -> AddIsotope(C12, 98.852387*perCent);
  C -> AddIsotope(C13,  1.147613*perCent);
  // material definition
  G4Material* Air_steel = new G4Material("Air_steel", 1.833*g/cm3, nComponents=5);
  Air_steel -> AddElement(N  ,  0.038470*perCent);
  Air_steel -> AddElement(O  ,  0.011806*perCent);
  Air_steel -> AddElement(Fe , 98.492837*perCent);
  Air_steel -> AddElement(Mo ,  1.103306*perCent);
  Air_steel -> AddElement(C  ,  0.353580*perCent);
  return Air_steel;
}

G4VSolid* DetectorConstruction::BuildOctagon(G4String name, G4double halfside, G4double halfdiag, G4double height)
{
  G4VSolid* thecube = new G4Box("thecube", halfside, halfside, height/2);
  G4VSolid* eraser = new G4Box("eraser", halfside, halfside, height);
  G4RotationMatrix* rot = new G4RotationMatrix();
  rot->rotateZ( 45.*deg);
  G4ThreeVector tr1(+0.5*sqrt(2.)*(halfside+halfdiag),+0.5*sqrt(2.)*(halfside+halfdiag),0.);
  G4ThreeVector tr2(+0.5*sqrt(2.)*(halfside+halfdiag),-0.5*sqrt(2.)*(halfside+halfdiag),0.);
  G4ThreeVector tr3(-0.5*sqrt(2.)*(halfside+halfdiag),-0.5*sqrt(2.)*(halfside+halfdiag),0.);
  G4ThreeVector tr4(-0.5*sqrt(2.)*(halfside+halfdiag),+0.5*sqrt(2.)*(halfside+halfdiag),0.);
  G4VSolid* sub1 = new G4SubtractionSolid("sub1", thecube, eraser, rot, tr1);
  G4VSolid* sub2 = new G4SubtractionSolid("sub2", sub1, eraser, rot, tr2);
  G4VSolid* sub3 = new G4SubtractionSolid("sub3", sub2, eraser, rot, tr3);
  G4VSolid* sub4 = new G4SubtractionSolid(name, sub3, eraser, rot, tr4);
  return sub4;
}

G4VSolid* DetectorConstruction::BuildOctagonWithTubeHole(G4String name, G4double halfside, G4double halfdiag, G4double height, G4double holeRadius)
{
  G4VSolid* thecube = new G4Box("thecube", halfside, halfside, height/2);
  G4VSolid* eraser = new G4Box("eraser", halfside, halfside, height);
  G4VSolid* holeeraser = new G4Tubs("holeeraser", 0., holeRadius, height, 0., 360.*degree);
  G4RotationMatrix* rot = new G4RotationMatrix();
  rot->rotateZ( 45.*deg);
  G4ThreeVector tr1(+0.5*sqrt(2.)*(halfside+halfdiag),+0.5*sqrt(2.)*(halfside+halfdiag),0.);
  G4ThreeVector tr2(+0.5*sqrt(2.)*(halfside+halfdiag),-0.5*sqrt(2.)*(halfside+halfdiag),0.);
  G4ThreeVector tr3(-0.5*sqrt(2.)*(halfside+halfdiag),-0.5*sqrt(2.)*(halfside+halfdiag),0.);
  G4ThreeVector tr4(-0.5*sqrt(2.)*(halfside+halfdiag),+0.5*sqrt(2.)*(halfside+halfdiag),0.);
  G4VSolid* sub1 = new G4SubtractionSolid("sub1", thecube, eraser, rot, tr1);
  G4VSolid* sub2 = new G4SubtractionSolid("sub2", sub1, eraser, rot, tr2);
  G4VSolid* sub3 = new G4SubtractionSolid("sub3", sub2, eraser, rot, tr3);
  G4VSolid* sub4 = new G4SubtractionSolid("sub4", sub3, eraser, rot, tr4);
  G4VSolid* sub5 = new G4SubtractionSolid(name, sub4, holeeraser);
  return sub5;
}

G4VSolid* DetectorConstruction::BuildOctagonWithOctagonHole(G4String name, G4double halfside, G4double halfdiag, G4double height, G4double halfsidehole, G4double halfdiaghole)
{
  G4VSolid* theoctagon = DetectorConstruction::BuildOctagon("theoctagon", halfside, halfdiag, height/2);
  G4VSolid* eraser = DetectorConstruction::BuildOctagon("eraser", halfsidehole, halfdiaghole, height);
  G4VSolid* sub5 = new G4SubtractionSolid(name, theoctagon, eraser);
  return sub5;
}

G4VSolid* DetectorConstruction::BuildBoxWithTubeHole(G4String name, G4double halfX, G4double halfY, G4double halfZ, G4double holeRadius)
{
  G4VSolid* thecube = new G4Box("thecube", halfX, halfY, halfZ);
  G4VSolid* holeeraser = new G4Tubs("holeeraser", 0., holeRadius, 2*halfZ, 0., 360.*degree);
  G4VSolid* sub5 = new G4SubtractionSolid(name, thecube, holeeraser);
  return sub5;
}

void DetectorConstruction::ConstructFuelAssembly(G4int idx, G4String name, G4ThreeVector position, G4LogicalVolume* logicParent)
{
  //main volume
  G4VSolid* solidAirOut  = new G4Box(name+"_airOut", fuelSizeXY/2, fuelSizeXY/2, asseSizeZ/2);
  G4LogicalVolume* logicAirOut = new G4LogicalVolume(solidAirOut, mAir, name+"_airOut");
  DetectorConstruction::ColorSpecs(logicAirOut, G4Color(.8,1.,1.), false, true);
  new G4PVPlacement(0, position, logicAirOut, name+"_airOut", logicParent, false, idx);
  
  //upper & lower cubes
  G4VSolid* solidAlSteel = new G4Box(name+"_alSteel", fuelSizeXY/2, fuelSizeXY/2, 3.48600*cm/2);
  G4VSolid* solidAlAir   = new G4Box(name+"_alAir",   fuelSizeXY/2, fuelSizeXY/2, 8.02675*cm/2);
  G4LogicalVolume* logicAlSteel   = new G4LogicalVolume(solidAlSteel, mAlSteel, name+"_alSteel");
  G4LogicalVolume* logicAlAir     = new G4LogicalVolume(solidAlAir, mAlAir, name+"_alAir");
  DetectorConstruction::ColorSpecs(logicAlSteel, G4Color(0.65,0.65,0.65), false, true);
  DetectorConstruction::ColorSpecs(logicAlAir, G4Color(0.65,0.65,0.65), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+3.48600*cm/2), logicAlSteel, name+"_alSteel", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+asseSizeZ/2-8.02675*cm/2), logicAlAir, name+"_alAir", logicAirOut, false, idx);
  
  // fuel volumes
  G4VSolid* solidZr   = DetectorConstruction::BuildOctagon(name+"_zr",   5.02920*cm, 6.31860*cm, fuelSizeZ);
  G4VSolid* solidAir  = DetectorConstruction::BuildOctagon(name+"_air",  4.96500*cm, 6.25511*cm, fuelSizeZ);
  G4VSolid* solidFuel = DetectorConstruction::BuildOctagon(name+"_fuel", 4.82600*cm, 6.04775*cm, fuelSizeZ); 
  G4LogicalVolume* logicZr   = new G4LogicalVolume(solidZr, mZr, name+"_zr");
  G4LogicalVolume* logicAir  = new G4LogicalVolume(solidAir, mAir, name+"_air");
  G4LogicalVolume* logicFuel = new G4LogicalVolume(solidFuel, mFuel, name+"_fuel");
  DetectorConstruction::ColorSpecs(logicZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicAir, G4Color(.8,1.,1.), false, true);
  DetectorConstruction::ColorSpecs(logicFuel, G4Color(0.93,.23,0.23), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse), logicZr, name+"_zr", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(), logicAir, name+"_air", logicZr, false, idx);
  new G4PVPlacement(0, G4ThreeVector(), logicFuel, name+"_fuel", logicAir, false, idx);

  // upper & lower fuel caps
  G4VSolid* solidUpperZr   = DetectorConstruction::BuildOctagon(name+"_upperZr",    5.02920*cm, 6.31860*cm, 0.6350*cm);
  G4VSolid* solidUpperAir  = DetectorConstruction::BuildOctagon(name+"_upperAir",   4.96500*cm, 6.25511*cm, 0.3175*cm);
  G4VSolid* solidLowerZr   = DetectorConstruction::BuildOctagon(name+"_lowerZr",    5.02920*cm, 6.31860*cm, 0.6350*cm);
  G4VSolid* solidLowerAir  = DetectorConstruction::BuildOctagon(name+"_lowerAir",   4.96500*cm, 6.25511*cm, 0.3175*cm);
  G4LogicalVolume* logicUpperZr   = new G4LogicalVolume(solidUpperZr, mZr, name+"_upperZr");
  G4LogicalVolume* logicUpperAir  = new G4LogicalVolume(solidUpperAir, mAir, name+"_upperAir");
  G4LogicalVolume* logicLowerZr   = new G4LogicalVolume(solidLowerZr, mZr, name+"_lowerZr");
  G4LogicalVolume* logicLowerAir  = new G4LogicalVolume(solidLowerAir, mAir, name+"_lowerAir");
  DetectorConstruction::ColorSpecs(logicUpperZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicUpperAir, G4Color(.8,1.,1.), false, true);
  DetectorConstruction::ColorSpecs(logicLowerZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicLowerAir, G4Color(.8,1.,1.), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-0.6350*cm/2+0.3175*cm/2), logicUpperAir, name+"_upperAir", logicUpperZr, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse+fuelSizeZ/2+0.6350*cm/2), logicUpperZr, name+"_upperZr", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+0.6350*cm/2-0.3175*cm/2), logicLowerAir, name+"_lowerAir", logicLowerZr, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse-fuelSizeZ/2-0.6350*cm/2), logicLowerZr, name+"_lowerZr", logicAirOut, false, idx);

  // lower reflector
  G4VSolid* solidLowerAlum     = DetectorConstruction::BuildOctagon(name+"_lowerAlum",     5.02920*cm, 6.31860*cm, 58.70575*cm);
  G4VSolid* solidLowerReflAir  = DetectorConstruction::BuildOctagon(name+"_lowerReflAir",  4.90220*cm, 6.19161*cm, 58.57875*cm);
  G4VSolid* solidLowerReflOcto = DetectorConstruction::BuildOctagon(name+"_lowerReflOcto", 4.80060*cm, 6.02070*cm, 49.68875*cm);
  G4VSolid* solidLowerReflCube = new G4Box(name+"_lowerReflCube",                          4.16560*cm, 4.16560*cm, 49.68875*cm/2);
  G4VSolid* solidLowerRefl     = new G4UnionSolid(name+"_lowerRefl", solidLowerReflOcto, solidLowerReflCube, new G4RotationMatrix(), G4ThreeVector(0.,0.,+8.89000*cm));
  G4LogicalVolume* logicLowerAlum     = new G4LogicalVolume(solidLowerAlum, mAluminium, name+"_lowerAlum");
  G4LogicalVolume* logicLowerReflAir  = new G4LogicalVolume(solidLowerReflAir, mAir, name+"_lowerReflAir");
  G4LogicalVolume* logicLowerRefl     = new G4LogicalVolume(solidLowerRefl, mReflector, name+"_lowerRefl");
  DetectorConstruction::ColorSpecs(logicLowerAlum, G4Color(0.8,0.,0.8) ,false, true);
  DetectorConstruction::ColorSpecs(logicLowerReflAir, G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicLowerRefl, G4Color(0.22,0.22,0.22) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+58.70575*cm/2+3.48600*cm), logicLowerAlum, name+"_lowerAlum", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-58.70575*cm/2+58.57875*cm/2), logicLowerReflAir, name+"_lowerReflAir", logicLowerAlum, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-58.57875*cm/2+49.68875*cm/2), logicLowerRefl, name+"_lowerRefl", logicLowerReflAir, false, idx);

  // upper reflector
  G4VSolid* solidUpperAlum     = DetectorConstruction::BuildOctagon(name+"_upperAlum",     5.02920*cm, 6.31860*cm, 62.83325*cm);
  G4VSolid* solidUpperReflAir  = DetectorConstruction::BuildOctagon(name+"_upperReflAir",  4.90220*cm, 6.19161*cm, 62.70625*cm);
  G4VSolid* solidUpperReflOcto = DetectorConstruction::BuildOctagon(name+"_upperReflOcto", 4.80060*cm, 6.02070*cm, 53.81625*cm);
  G4VSolid* solidUpperReflCube = new G4Box(name+"_upperReflCube",                          4.16560*cm, 4.16560*cm, 53.81625*cm/2);
  G4VSolid* solidUpperRefl     = new G4UnionSolid(name+"_upperRefl", solidUpperReflOcto, solidUpperReflCube, new G4RotationMatrix(), G4ThreeVector(0.,0.,-8.89000*cm));
  G4LogicalVolume* logicUpperAlum    = new G4LogicalVolume(solidUpperAlum, mAluminium, name+"_upperAlum");
  G4LogicalVolume* logicUpperReflAir = new G4LogicalVolume(solidUpperReflAir, mAir, name+"_upperReflAir");
  G4LogicalVolume* logicUpperRefl    = new G4LogicalVolume(solidUpperRefl, mReflector, name+"_upperRefl");
  DetectorConstruction::ColorSpecs(logicUpperAlum, G4Color(0.8,0.,0.8) ,false, true);
  DetectorConstruction::ColorSpecs(logicUpperReflAir, G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicUpperRefl, G4Color(0.22,0.22,0.22) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+asseSizeZ/2-62.83325*cm/2-8.02675*cm), logicUpperAlum, name+"_upperAlum", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+62.83325*cm/2-62.70625*cm/2), logicUpperReflAir, name+"_upperReflAir", logicUpperAlum, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+62.70625*cm/2-53.81625*cm/2), logicUpperRefl, name+"_upperRefl", logicUpperReflAir, false, idx);

  // upper tubs
  G4VSolid* solidTubeAirgap   = new G4Tubs(name+"_tubeAirGap",   0., 0.95250*cm, 22.06625*cm/2, 0., 360.*degree);
  G4VSolid* solidTubeAlum     = new G4Tubs(name+"_tubeAlum",     0., 0.47625*cm,  5.95630*cm/2, 0., 360.*degree);
  G4VSolid* solidTubeUpperAir = new G4Tubs(name+"_tubeUpperAir", 0., 0.36195*cm,  5.84190*cm/2, 0., 360.*degree);
  G4VSolid* solidTubeLowerAir = new G4Tubs(name+"_tubeLowerAir", 0., 0.36195*cm,  0.12700*cm/2, 0., 360.*degree);
  G4LogicalVolume* logicTubeAirgap   = new G4LogicalVolume(solidTubeAirgap, mAir, name+"_tubeAirgap");
  G4LogicalVolume* logicTubeAlum     = new G4LogicalVolume(solidTubeAlum, mAluminium, name+"_tubeAlum");
  G4LogicalVolume* logicTubeUpperAir = new G4LogicalVolume(solidTubeUpperAir, mAir, name+"_tubeUpperAir");
  G4LogicalVolume* logicTubeLowerAir = new G4LogicalVolume(solidTubeLowerAir, mAir, name+"_tubeLowerAir");
  DetectorConstruction::ColorSpecs(logicTubeAirgap  , G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicTubeAlum    , G4Color(.8,0.,.8) ,false, true);
  DetectorConstruction::ColorSpecs(logicTubeUpperAir, G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicTubeLowerAir, G4Color(.8,1.,1.) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-53.81625*cm/2-8.89000*cm+22.06625*cm/2), logicTubeAirgap, name+"_tubeAirgap", logicUpperRefl, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-22.06625*cm/2+5.95630*cm/2), logicTubeAlum, name+"_tubeAlum", logicTubeAirgap, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0., -5.95630*cm/2+5.84190*cm/2), logicTubeUpperAir, name+"_tubeUpperAir", logicTubeAlum, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-62.83325*cm/2+0.12700*cm/2), logicTubeLowerAir, name+"_tubeLowerAir", logicUpperAlum, false, idx);
}

void DetectorConstruction::ConstructAlumAssembly(G4int idx, G4String name, G4ThreeVector position, G4LogicalVolume* logicParent)
{
  //main volume
  G4VSolid* solidAirOut  = new G4Box(name+"_airOut", fuelSizeXY/2, fuelSizeXY/2, asseSizeZ/2);
  G4LogicalVolume* logicAirOut = new G4LogicalVolume(solidAirOut, mAir, name+"_airOut");
  DetectorConstruction::ColorSpecs(logicAirOut, G4Color(.8,1.,1.), false, true);
  new G4PVPlacement(0, position, logicAirOut, name+"_airOut", logicParent, false, idx);
  
  //upper & lower cubes
  G4VSolid* solidAlSteel = new G4Box(name+"_alSteel", fuelSizeXY/2, fuelSizeXY/2, 3.48600*cm/2);
  G4VSolid* solidAlAir   = new G4Box(name+"_alAir",   fuelSizeXY/2, fuelSizeXY/2, 8.02675*cm/2);
  G4LogicalVolume* logicAlSteel   = new G4LogicalVolume(solidAlSteel, mAlSteel, name+"_alSteel");
  G4LogicalVolume* logicAlAir     = new G4LogicalVolume(solidAlAir, mAlAir, name+"_alAir");
  DetectorConstruction::ColorSpecs(logicAlSteel, G4Color(0.65,0.65,0.65), false, true);
  DetectorConstruction::ColorSpecs(logicAlAir, G4Color(0.65,0.65,0.65), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+3.48600*cm/2), logicAlSteel, name+"_alSteel", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+asseSizeZ/2-8.02675*cm/2), logicAlAir, name+"_alAir", logicAirOut, false, idx);
  
  // fuel volumes
  G4VSolid* solidZr   = DetectorConstruction::BuildOctagon(name+"_zr",   5.02920*cm, 6.31860*cm, fuelSizeZ);
  G4VSolid* solidAir  = DetectorConstruction::BuildOctagon(name+"_air",  4.96500*cm, 6.25511*cm, fuelSizeZ);
  G4VSolid* solidFuel = DetectorConstruction::BuildOctagon(name+"_fuel", 4.82600*cm, 6.04775*cm, fuelSizeZ); 
  G4LogicalVolume* logicZr   = new G4LogicalVolume(solidZr, mZr, name+"_zr");
  G4LogicalVolume* logicAir  = new G4LogicalVolume(solidAir, mAir, name+"_air");
  G4LogicalVolume* logicFuel = new G4LogicalVolume(solidFuel, mAluminium, name+"_fuel");
  DetectorConstruction::ColorSpecs(logicZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicAir, G4Color(.8,1.,1.), false, true);
  DetectorConstruction::ColorSpecs(logicFuel, G4Color(0.8,0.,0.8), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse), logicZr, name+"_zr", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(), logicAir, name+"_air", logicZr, false, idx);
  new G4PVPlacement(0, G4ThreeVector(), logicFuel, name+"_fuel", logicAir, false, idx);

  // upper & lower fuel caps
  G4VSolid* solidUpperZr   = DetectorConstruction::BuildOctagon(name+"_upperZr",    5.02920*cm, 6.31860*cm, 0.6350*cm);
  G4VSolid* solidUpperAir  = DetectorConstruction::BuildOctagon(name+"_upperAir",   4.96500*cm, 6.25511*cm, 0.3175*cm);
  G4VSolid* solidLowerZr   = DetectorConstruction::BuildOctagon(name+"_lowerZr",    5.02920*cm, 6.31860*cm, 0.6350*cm);
  G4VSolid* solidLowerAir  = DetectorConstruction::BuildOctagon(name+"_lowerAir",   4.96500*cm, 6.25511*cm, 0.3175*cm);
  G4LogicalVolume* logicUpperZr   = new G4LogicalVolume(solidUpperZr, mZr, name+"_upperZr");
  G4LogicalVolume* logicUpperAir  = new G4LogicalVolume(solidUpperAir, mAir, name+"_upperAir");
  G4LogicalVolume* logicLowerZr   = new G4LogicalVolume(solidLowerZr, mZr, name+"_lowerZr");
  G4LogicalVolume* logicLowerAir  = new G4LogicalVolume(solidLowerAir, mAir, name+"_lowerAir");
  DetectorConstruction::ColorSpecs(logicUpperZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicUpperAir, G4Color(.8,1.,1.), false, true);
  DetectorConstruction::ColorSpecs(logicLowerZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicLowerAir, G4Color(.8,1.,1.), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse+fuelSizeZ/2+0.6350*cm/2), logicUpperZr, name+"_upperZr", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-0.6350*cm/2+0.3175*cm/2), logicUpperAir, name+"_upperAir", logicUpperZr, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse-fuelSizeZ/2-0.6350*cm/2), logicLowerZr, name+"_lowerZr", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+0.6350*cm/2-0.3175*cm/2), logicLowerAir, name+"_lowerAir", logicLowerZr, false, idx);

  // lower reflector
  G4VSolid* solidLowerAlum     = DetectorConstruction::BuildOctagon(name+"_lowerAlum",     5.02920*cm, 6.31860*cm, 58.70575*cm);
  G4VSolid* solidLowerReflAir  = DetectorConstruction::BuildOctagon(name+"_lowerReflAir",  4.90220*cm, 6.19161*cm, 58.57875*cm);
  G4VSolid* solidLowerReflOcto = DetectorConstruction::BuildOctagon(name+"_lowerReflOcto", 4.80060*cm, 6.02070*cm, 49.68875*cm);
  G4VSolid* solidLowerReflCube = new G4Box(name+"_lowerReflCube",                          4.16560*cm, 4.16560*cm, 49.68875*cm/2);
  G4VSolid* solidLowerRefl     = new G4UnionSolid(name+"_lowerRefl", solidLowerReflOcto, solidLowerReflCube, new G4RotationMatrix(), G4ThreeVector(0.,0.,+8.89000*cm));
  G4LogicalVolume* logicLowerAlum     = new G4LogicalVolume(solidLowerAlum, mAluminium, name+"_lowerAlum");
  G4LogicalVolume* logicLowerReflAir  = new G4LogicalVolume(solidLowerReflAir, mAir, name+"_lowerReflAir");
  G4LogicalVolume* logicLowerRefl     = new G4LogicalVolume(solidLowerRefl, mReflector, name+"_lowerRefl");
  DetectorConstruction::ColorSpecs(logicLowerAlum, G4Color(0.8,0.,0.8) ,false, true);
  DetectorConstruction::ColorSpecs(logicLowerReflAir, G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicLowerRefl, G4Color(0.22,0.22,0.22) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+58.70575*cm/2+3.48600*cm), logicLowerAlum, name+"_lowerAlum", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-58.70575*cm/2+58.57875*cm/2), logicLowerReflAir, name+"_lowerReflAir", logicLowerAlum, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-58.57875*cm/2+49.68875*cm/2), logicLowerRefl, name+"_lowerRefl", logicLowerReflAir, false, idx);

  // upper reflector
  G4VSolid* solidUpperAlum     = DetectorConstruction::BuildOctagon(name+"_upperAlum",     5.02920*cm, 6.31860*cm, 62.83325*cm);
  G4VSolid* solidUpperReflAir  = DetectorConstruction::BuildOctagon(name+"_upperReflAir",  4.90220*cm, 6.19161*cm, 62.70625*cm);
  G4VSolid* solidUpperReflOcto = DetectorConstruction::BuildOctagon(name+"_upperReflOcto", 4.80060*cm, 6.02070*cm, 53.81625*cm);
  G4VSolid* solidUpperReflCube = new G4Box(name+"_upperReflCube",                          4.16560*cm, 4.16560*cm, 53.81625*cm/2);
  G4VSolid* solidUpperRefl     = new G4UnionSolid(name+"_upperRefl", solidUpperReflOcto, solidUpperReflCube, new G4RotationMatrix(), G4ThreeVector(0.,0.,-8.89000*cm));
  G4LogicalVolume* logicUpperAlum    = new G4LogicalVolume(solidUpperAlum, mAluminium, name+"_upperAlum");
  G4LogicalVolume* logicUpperReflAir = new G4LogicalVolume(solidUpperReflAir, mAir, name+"_upperReflAir");
  G4LogicalVolume* logicUpperRefl    = new G4LogicalVolume(solidUpperRefl, mReflector, name+"_upperRefl");
  DetectorConstruction::ColorSpecs(logicUpperAlum, G4Color(0.8,0.,0.8) ,false, true);
  DetectorConstruction::ColorSpecs(logicUpperReflAir, G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicUpperRefl, G4Color(0.22,0.22,0.22) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+asseSizeZ/2-62.83325*cm/2-8.02675*cm), logicUpperAlum, name+"_upperAlum", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+62.83325*cm/2-62.70625*cm/2), logicUpperReflAir, name+"_upperReflAir", logicUpperAlum, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+62.70625*cm/2-53.81625*cm/2), logicUpperRefl, name+"_upperRefl", logicUpperReflAir, false, idx);

  // upper tubs
  G4VSolid* solidTubeAirgap   = new G4Tubs(name+"_tubeAirGap",   0., 0.95250*cm, 22.06625*cm/2, 0., 360.*degree);
  G4VSolid* solidTubeAlum     = new G4Tubs(name+"_tubeAlum",     0., 0.47625*cm,  5.95630*cm/2, 0., 360.*degree);
  G4VSolid* solidTubeUpperAir = new G4Tubs(name+"_tubeUpperAir", 0., 0.36195*cm,  5.84190*cm/2, 0., 360.*degree);
  G4VSolid* solidTubeLowerAir = new G4Tubs(name+"_tubeLowerAir", 0., 0.36195*cm,  0.12700*cm/2, 0., 360.*degree);
  G4LogicalVolume* logicTubeAirgap   = new G4LogicalVolume(solidTubeAirgap, mAir, name+"_tubeAirgap");
  G4LogicalVolume* logicTubeAlum     = new G4LogicalVolume(solidTubeAlum, mAluminium, name+"_tubeAlum");
  G4LogicalVolume* logicTubeUpperAir = new G4LogicalVolume(solidTubeUpperAir, mAir, name+"_tubeUpperAir");
  G4LogicalVolume* logicTubeLowerAir = new G4LogicalVolume(solidTubeLowerAir, mAir, name+"_tubeLowerAir");
  DetectorConstruction::ColorSpecs(logicTubeAirgap  , G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicTubeAlum    , G4Color(.8,0.,.8) ,false, true);
  DetectorConstruction::ColorSpecs(logicTubeUpperAir, G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicTubeLowerAir, G4Color(.8,1.,1.) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-53.81625*cm/2-8.89000*cm+22.06625*cm/2), logicTubeAirgap, name+"_tubeAirgap", logicUpperRefl, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-22.06625*cm/2+5.95630*cm/2), logicTubeAlum, name+"_tubeAlum", logicTubeAirgap, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0., -5.95630*cm/2+5.84190*cm/2), logicTubeUpperAir, name+"_tubeUpperAir", logicTubeAlum, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-62.83325*cm/2+0.12700*cm/2), logicTubeLowerAir, name+"_tubeLowerAir", logicUpperAlum, false, idx);
}

void DetectorConstruction::ConstructCRAssembly(G4int idx, G4String name, G4ThreeVector position, G4LogicalVolume* logicParent)
{
  //main volume
  G4VSolid* solidAirOut  = DetectorConstruction::BuildBoxWithTubeHole(name+"_airOut", fuelSizeXY/2, fuelSizeXY/2, asseSizeZ/2, 2.9591*cm);
  G4LogicalVolume* logicAirOut = new G4LogicalVolume(solidAirOut, mAir, name+"_airOut");
  DetectorConstruction::ColorSpecs(logicAirOut, G4Color(.8,1.,1.), false, true);
  new G4PVPlacement(0, position, logicAirOut, name+"_airOut", logicParent, false, idx);
  
  //upper & lower cubes
  G4VSolid* solidAlSteel = DetectorConstruction::BuildBoxWithTubeHole(name+"_alSteel", fuelSizeXY/2, fuelSizeXY/2, 3.48600*cm/2, 2.9591*cm);
  G4VSolid* solidAlAir   = DetectorConstruction::BuildBoxWithTubeHole(name+"_alAir",   fuelSizeXY/2, fuelSizeXY/2, 8.02675*cm/2, 2.9591*cm);
  G4LogicalVolume* logicAlSteel   = new G4LogicalVolume(solidAlSteel, mAlSteel, name+"_alSteel");
  G4LogicalVolume* logicAlAir     = new G4LogicalVolume(solidAlAir, mAlAir, name+"_alAir");
  DetectorConstruction::ColorSpecs(logicAlSteel, G4Color(0.65,0.65,0.65), false, true);
  DetectorConstruction::ColorSpecs(logicAlAir, G4Color(0.65,0.65,0.65), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+3.48600*cm/2), logicAlSteel, name+"_alSteel", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+asseSizeZ/2-8.02675*cm/2), logicAlAir, name+"_alAir", logicAirOut, false, idx);
  
  // fuel volumes
  G4VSolid* solidZr   = DetectorConstruction::BuildOctagonWithTubeHole(name+"_zr",   5.02920*cm, 6.31860*cm, fuelSizeZ, 2.9591*cm);
  G4VSolid* solidAir  = DetectorConstruction::BuildOctagonWithTubeHole(name+"_air",  4.96500*cm, 6.25511*cm, fuelSizeZ, 2.9591*cm);
  G4VSolid* solidFuel = DetectorConstruction::BuildOctagonWithTubeHole(name+"_fuel", 4.82600*cm, 6.04775*cm, fuelSizeZ, 2.9591*cm); 
  G4LogicalVolume* logicZr   = new G4LogicalVolume(solidZr, mZr, name+"_zr");
  G4LogicalVolume* logicAir  = new G4LogicalVolume(solidAir, mAir, name+"_air");
  G4LogicalVolume* logicFuel = new G4LogicalVolume(solidFuel, mFuel, name+"_fuel");
  DetectorConstruction::ColorSpecs(logicZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicAir, G4Color(.8,1.,1.), false, true);
  DetectorConstruction::ColorSpecs(logicFuel, G4Color(0.93,.23,0.23), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse), logicZr, name+"_zr", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(), logicAir, name+"_air", logicZr, false, idx);
  new G4PVPlacement(0, G4ThreeVector(), logicFuel, name+"_fuel", logicAir, false, idx);

  // upper & lower fuel caps
  G4VSolid* solidUpperZr   = DetectorConstruction::BuildOctagonWithTubeHole(name+"_upperZr",    5.02920*cm, 6.31860*cm, 0.6350*cm, 2.9591*cm);
  G4VSolid* solidUpperAir  = DetectorConstruction::BuildOctagonWithTubeHole(name+"_upperAir",   4.96500*cm, 6.25511*cm, 0.3175*cm, 2.9591*cm);
  G4VSolid* solidLowerZr   = DetectorConstruction::BuildOctagonWithTubeHole(name+"_lowerZr",    5.02920*cm, 6.31860*cm, 0.6350*cm, 2.9591*cm);
  G4VSolid* solidLowerAir  = DetectorConstruction::BuildOctagonWithTubeHole(name+"_lowerAir",   4.96500*cm, 6.25511*cm, 0.3175*cm, 2.9591*cm);
  G4LogicalVolume* logicUpperZr   = new G4LogicalVolume(solidUpperZr, mZr, name+"_upperZr");
  G4LogicalVolume* logicUpperAir  = new G4LogicalVolume(solidUpperAir, mAir, name+"_upperAir");
  G4LogicalVolume* logicLowerZr   = new G4LogicalVolume(solidLowerZr, mZr, name+"_lowerZr");
  G4LogicalVolume* logicLowerAir  = new G4LogicalVolume(solidLowerAir, mAir, name+"_lowerAir");
  DetectorConstruction::ColorSpecs(logicUpperZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicUpperAir, G4Color(.8,1.,1.), false, true);
  DetectorConstruction::ColorSpecs(logicLowerZr, G4Color(0.63,0.63,0.63), false, true);
  DetectorConstruction::ColorSpecs(logicLowerAir, G4Color(.8,1.,1.), false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse+fuelSizeZ/2+0.6350*cm/2), logicUpperZr, name+"_upperZr", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-0.6350*cm/2+0.3175*cm/2), logicUpperAir, name+"_upperAir", logicUpperZr, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+zFuelinAsse-fuelSizeZ/2-0.6350*cm/2), logicLowerZr, name+"_lowerZr", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+0.6350*cm/2-0.3175*cm/2), logicLowerAir, name+"_lowerAir", logicLowerZr, false, idx);

  // lower reflector
  G4VSolid* solidLowerAlum     = DetectorConstruction::BuildOctagonWithTubeHole(name+"_lowerAlum",     5.02920*cm, 6.31860*cm, 58.70575*cm, 2.9591*cm);
  G4VSolid* solidLowerReflAir  = DetectorConstruction::BuildOctagonWithTubeHole(name+"_lowerReflAir",  4.90220*cm, 6.19161*cm, 58.57875*cm, 2.9591*cm);
  G4VSolid* solidLowerReflOcto = DetectorConstruction::BuildOctagonWithTubeHole(name+"_lowerReflOcto", 4.80060*cm, 6.02070*cm, 49.68875*cm, 2.9591*cm);
  G4VSolid* solidLowerReflCube = DetectorConstruction::BuildBoxWithTubeHole(name+"_lowerReflCube",     4.16560*cm, 4.16560*cm, 49.68875*cm/2, 2.9591*cm);
  G4VSolid* solidLowerRefl     = new G4UnionSolid(name+"_lowerRefl", solidLowerReflOcto, solidLowerReflCube, new G4RotationMatrix(), G4ThreeVector(0.,0.,+8.89000*cm));
  G4LogicalVolume* logicLowerAlum     = new G4LogicalVolume(solidLowerAlum, mAluminium, name+"_lowerAlum");
  G4LogicalVolume* logicLowerReflAir  = new G4LogicalVolume(solidLowerReflAir, mAir, name+"_lowerReflAir");
  G4LogicalVolume* logicLowerRefl     = new G4LogicalVolume(solidLowerRefl, mReflector, name+"_lowerRefl");
  DetectorConstruction::ColorSpecs(logicLowerAlum, G4Color(0.8,0.,0.8) ,false, true);
  DetectorConstruction::ColorSpecs(logicLowerReflAir, G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicLowerRefl, G4Color(0.22,0.22,0.22) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+58.70575*cm/2+3.48600*cm), logicLowerAlum, name+"_lowerAlum", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-58.70575*cm/2+58.57875*cm/2), logicLowerReflAir, name+"_lowerReflAir", logicLowerAlum, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-58.57875*cm/2+49.68875*cm/2), logicLowerRefl, name+"_lowerRefl", logicLowerReflAir, false, idx);

  // upper reflector
  G4VSolid* solidUpperAlum     = DetectorConstruction::BuildOctagonWithTubeHole(name+"_upperAlum",     5.02920*cm, 6.31860*cm, 62.83325*cm, 2.9591*cm);
  G4VSolid* solidUpperReflAir  = DetectorConstruction::BuildOctagonWithTubeHole(name+"_upperReflAir",  4.90220*cm, 6.19161*cm, 62.70625*cm, 2.9591*cm);
  G4VSolid* solidUpperReflOcto = DetectorConstruction::BuildOctagonWithTubeHole(name+"_upperReflOcto", 4.80060*cm, 6.02070*cm, 53.81625*cm, 2.9591*cm);
  G4VSolid* solidUpperReflCube = DetectorConstruction::BuildBoxWithTubeHole(name+"_upperReflCube",     4.16560*cm, 4.16560*cm, 53.81625*cm/2, 2.9591*cm);
  G4VSolid* solidUpperRefl     = new G4UnionSolid(name+"_upperRefl", solidUpperReflOcto, solidUpperReflCube, new G4RotationMatrix(), G4ThreeVector(0.,0.,-8.89000*cm));
  G4LogicalVolume* logicUpperAlum    = new G4LogicalVolume(solidUpperAlum, mAluminium, name+"_upperAlum");
  G4LogicalVolume* logicUpperReflAir = new G4LogicalVolume(solidUpperReflAir, mAir, name+"_upperReflAir");
  G4LogicalVolume* logicUpperRefl    = new G4LogicalVolume(solidUpperRefl, mReflector, name+"_upperRefl");
  DetectorConstruction::ColorSpecs(logicUpperAlum, G4Color(0.8,0.,0.8) ,false, true);
  DetectorConstruction::ColorSpecs(logicUpperReflAir, G4Color(.8,1.,1.) ,false, true);
  DetectorConstruction::ColorSpecs(logicUpperRefl, G4Color(0.22,0.22,0.22) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+asseSizeZ/2-62.83325*cm/2-8.02675*cm), logicUpperAlum, name+"_upperAlum", logicAirOut, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+62.83325*cm/2-62.70625*cm/2), logicUpperReflAir, name+"_upperReflAir", logicUpperAlum, false, idx);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,+62.70625*cm/2-53.81625*cm/2), logicUpperRefl, name+"_upperRefl", logicUpperReflAir, false, idx);

  // zirconium tube
  G4VSolid* solidTubeZirc2 = new G4Tubs(name+"_tubeZirc2", 2.54*cm, 2.8575*cm, asseSizeZ/2, 0., 360.*degree);
  G4LogicalVolume* logicTubeZirc2 = new G4LogicalVolume(solidTubeZirc2, mZirc2, name+"_tubeZirc2");
  DetectorConstruction::ColorSpecs(logicTubeZirc2, G4Color(0.63,0.63,0.63) ,false, true);
  new G4PVPlacement(0, G4ThreeVector(), logicTubeZirc2, name+"_tubeZirc2", logicAirOut, false, idx);
}

void DetectorConstruction::ConstructCR(G4int idx, G4String name, G4ThreeVector position, G4LogicalVolume* logicParent, G4double zCRod)
{
  //main volume
  G4double r50 = 1.9050*cm;
  G4double r51 = 2.2225*cm;
  G4VSolid* solidSteel  = new G4Tubs(name+"_steel", 0., r51, asseSizeZ/2, 0., 360.);
  G4LogicalVolume* logicSteel = new G4LogicalVolume(solidSteel, mSteel, name+"_steel");
  DetectorConstruction::ColorSpecs(logicSteel, G4Color(.52,.39,.39), false, true);
  new G4PVPlacement(0, position, logicSteel, name+"_steel", logicParent, false, idx);

  DetectorConstruction::ConditionalTube(idx, name+"_graphite00", 0.,  r50, -306.64673*cm, -167.74175*cm, mGraphite, G4Color(.2,.2,.2), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_graphite01", 0.,  r50, -157.89925*cm, -120.75175*cm, mGraphite, G4Color(.2,.2,.2), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_zrSteel01",  0.,  r50, -102.97175*cm, -96.939250*cm, mZrSteel, G4Color(.63,.63,.63), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_graphite02", 0.,  r50, -96.939250*cm, +43.395750*cm, mGraphite, G4Color(.2,.2,.2), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_zrSteel02",  0.,  r50, +43.395750*cm, +49.428250*cm, mZrSteel, G4Color(.63,.63,.63),logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_zr",         r50, r51, -102.97175*cm, +49.428250*cm, mZr, G4Color(.63,.63,.63),logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_absorbant",  0.,  r50, +53.238250*cm, +195.79575*cm, mB4cNew, G4Color(1.,.51,.67), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_airSteel",   r50, r51, +201.82825*cm, +210.08325*cm, mAirSteel, G4Color(.65,.64,.65),logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_air",        0.,  r51, +210.08325*cm, +500.00000*cm, mAir, G4Color(.8,1.,1.),logicSteel, zCRod);
}

void DetectorConstruction::ConstructTR(G4int idx, G4String name, G4ThreeVector position, G4LogicalVolume* logicParent, G4double zCRod)
{
  //main volume
  G4double r50 = 1.9050*cm;
  G4double r51 = 2.2225*cm;
  G4VSolid* solidSteel  = new G4Tubs(name+"_steel", 0., r51, asseSizeZ/2, 0., 360.);
  G4LogicalVolume* logicSteel = new G4LogicalVolume(solidSteel, mSteel, name+"_steel");
  DetectorConstruction::ColorSpecs(logicSteel, G4Color(.52,.39,.39), false, true);
  new G4PVPlacement(0, position, logicSteel, name+"_steel", logicParent, false, idx);

  DetectorConstruction::ConditionalTube(idx, name+"_graphite00", 0.,  r50, -258.38673*cm, -119.48175*cm, mGraphite, G4Color(.2,.2,.2), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_graphite01", 0.,  r50, -109.63925*cm,  -86.77925*cm, mGraphite, G4Color(.2,.2,.2), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_zrSteel01",  0.,  r50,  -68.99925*cm,  -62.96675*cm, mZrSteel, G4Color(.63,.63,.63), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_graphite02", 0.,  r50,  -62.96675*cm,  +77.36825*cm, mGraphite, G4Color(.2,.2,.2), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_zrSteel02",  0.,  r50,  +77.36825*cm,  +83.40075*cm, mZrSteel, G4Color(.63,.63,.63),logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_zr",         r50, r51,  -68.99925*cm,  +83.40075*cm, mZr, G4Color(.63,.63,.63),logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_absorbant",  0.,  r50,  +87.21075*cm, +229.76825*cm, mB4cNew, G4Color(1.,.51,.67), logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_airSteel",   r50, r51, +235.80075*cm, +244.05575*cm, mAirSteel, G4Color(.65,.64,.65),logicSteel, zCRod);
  DetectorConstruction::ConditionalTube(idx, name+"_air",        0.,  r51, +244.05575*cm, +500.00000*cm, mAir, G4Color(.8,1.,1.),logicSteel, zCRod);
}

void DetectorConstruction::ConditionalTube(G4int idx, G4String name, G4double rint, G4double rext, G4double z0, G4double z1, G4Material* material, G4Color color, G4LogicalVolume* logicParent, G4double zCRod)
{
  if (asseSizeZ <= z0 + zCRod)
  {}
  else if ( asseSizeZ < z1 + zCRod && z0 + zCRod < asseSizeZ)
  {
    G4VSolid* mySolid  = new G4Tubs(name, rint, rext, (asseSizeZ -(z0 + zCRod))/2, 0., 360.);
    G4LogicalVolume* myLogic = new G4LogicalVolume(mySolid, material, name);
    DetectorConstruction::ColorSpecs(myLogic, color, false, true);
    new G4PVPlacement(0, G4ThreeVector(0.,0.,+asseSizeZ/2-(asseSizeZ -(z0 + zCRod))/2), myLogic, name, logicParent, false, idx);
  }
  else if (0. <= z0 + zCRod && z1 + zCRod <= asseSizeZ)
  {
    G4VSolid* mySolid  = new G4Tubs(name, rint, rext, (z1-z0)/2, 0., 360.);
    G4LogicalVolume* myLogic = new G4LogicalVolume(mySolid, material, name);
    DetectorConstruction::ColorSpecs(myLogic, color, false, true);
    new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+(z1-z0)/2 + z0 + zCRod), myLogic, name, logicParent, false, idx);
  }
  else if (0. < z1 + zCRod && z0 + zCRod < 0. )
  {
    G4VSolid* mySolid  = new G4Tubs(name, rint, rext, (z1 + zCRod)/2, 0., 360.);
    G4LogicalVolume* myLogic = new G4LogicalVolume(mySolid, material, name);
    DetectorConstruction::ColorSpecs(myLogic, color, false, true);
    new G4PVPlacement(0, G4ThreeVector(0.,0.,-asseSizeZ/2+(z1 + zCRod)/2), myLogic, name, logicParent, false, idx);
  }
  else
  {}
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
  G4NistManager* man = G4NistManager::Instance();
  G4int nComponents;
  
  // isotopes
  mFuel      = DetectorConstruction::MakeFuel();
  mZr        = DetectorConstruction::MakeZr();
  mGraphite  = DetectorConstruction::MakeGraphite();
  mAir       = DetectorConstruction::MakeAir();
  mAlSteel   = DetectorConstruction::MakeAlSteel();
  mAlAir     = DetectorConstruction::MakeAlAir();
  mReflector = DetectorConstruction::MakeReflector();
  mAluminium = DetectorConstruction::MakeAluminium();
  mZirc2     = DetectorConstruction::MakeZirc2();
  mSteel     = DetectorConstruction::MakeSteel();
  mZrSteel   = DetectorConstruction::MakeZrSteel();
  mB4cNew    = DetectorConstruction::MakeB4cNew();
  mAirSteel  = DetectorConstruction::MakeAirSteel();

  fDefaultMaterial = mAir;

  // G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //
  // Cleanup old geometry
  //
  
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
  DetectorConstruction::ColorSpecs(logicWorld, G4Color(), false, false);

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
      G4String name = "Assembly_"+std::to_string(19*i+j);
      G4ThreeVector position = G4ThreeVector((j-9)*fuelSizeXY,(9-i)*fuelSizeXY,-fWorldSizeZ/2+asseSizeZ/2);
      if (fuelMap[i][j]==11)
      {
        DetectorConstruction::ConstructFuelAssembly(19*i+j, name, position, logicWorld);
      }
      else if (fuelMap[i][j]==90)
      {
        DetectorConstruction::ConstructAlumAssembly(19*i+j, name, position, logicWorld);
      }
      else if (fuelMap[i][j]==21)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructTR(19*i+j, name+"_TR", position, logicWorld, zTR01);
      }
      else if (fuelMap[i][j]==22)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructTR(19*i+j, name+"_TR", position, logicWorld, zTR02);
      }
      else if (fuelMap[i][j]==23)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructTR(19*i+j, name+"_TR", position, logicWorld, zTR03);
      }
      else if (fuelMap[i][j]==24)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructTR(19*i+j, name+"_TR", position, logicWorld, zTR04);
      }
      else if (fuelMap[i][j]==31)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructCR(19*i+j, name+"_CR", position, logicWorld, zCR01);
      }
      else if (fuelMap[i][j]==32)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructCR(19*i+j, name+"_CR", position, logicWorld, zCR02);
      }
      else if (fuelMap[i][j]==33)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructCR(19*i+j, name+"_CR", position, logicWorld, zCR03);
      }
      else if (fuelMap[i][j]==34)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructCR(19*i+j, name+"_CR", position, logicWorld, zCR04);
      }
      else if (fuelMap[i][j]==41)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructCR(19*i+j, name+"_CC", position, logicWorld, zCC01);
      }
      else if (fuelMap[i][j]==42)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructCR(19*i+j, name+"_CC", position, logicWorld, zCC02);
      }
      else if (fuelMap[i][j]==43)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructCR(19*i+j, name+"_CC", position, logicWorld, zCC03);
      }
      else if (fuelMap[i][j]==44)
      {
        DetectorConstruction::ConstructCRAssembly(19*i+j, name, position, logicWorld);
        DetectorConstruction::ConstructCR(19*i+j, name+"_CC", position, logicWorld, zCC04);
      }
    }
  }

  G4String matname = mGraphite->GetName();
  G4Box* subsolid1 = new G4Box("subsolid1", fWorldSizeX/2, fWorldSizeY/2, fWorldSizeZ/2);
  G4Box* subsolid2 = new G4Box("subsolid2", reflectorXY/2, reflectorXY/2, fWorldSizeZ);
  G4VSolid* solidReflector = new G4SubtractionSolid(matname, subsolid1, subsolid2);
  
  G4LogicalVolume* logicReflector = new G4LogicalVolume(solidReflector,       // solid
                                                        mGraphite,            // material
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

G4bool DetectorConstruction::IsInMaterial(G4String name, G4ThreeVector position)
{
  G4bool isInMaterial = false;

  G4Navigator* g4Navigator = new G4Navigator();
  g4Navigator->SetWorldVolume(fPhysiWorld);

  G4VPhysicalVolume* volume = g4Navigator->LocateGlobalPointAndSetup(position);
  G4Material* material = volume->GetLogicalVolume()->GetMaterial();
  if (material->GetName() == name)
  {
    isInMaterial = true;
  }
  return isInMaterial;
}

void DetectorConstruction::ColorSpecs(G4LogicalVolume* logic, G4Color color = G4Color(0.5,0.5,0.5), G4bool showSurface = true, G4bool visibility = true)
{
  G4VisAttributes* attr = new G4VisAttributes();
  attr->SetColour(color);
  attr->SetVisibility(visibility);
  logic->SetVisAttributes(attr);
}