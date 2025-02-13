Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

# ALFRED: ALl particle in Fission Reactor - Energy Deposition

## Description
`ALFRED` is a Geant4 based code designed to compute energy deposition in critical systems such as the TREAT reactor.

## Installation
To install `ALFRED`, follow these steps:

1. Install the Geant4 framework. Follow instructions on website : https://geant4.web.cern.ch/docs/getting-started. For example, the following installation has been tested. It is assumed that `zlib` and `qt` are already installed:
```sh
git clone https://github.com/Geant4/geant4.git
cd geant4
mkdir build
mkdir install 
cd build
cmake -DCMAKE_INSTALL_PREFIX=path/to/install/ -DGEANT4_USE_QT=ON ..
cmake -DGEANT4_INSTALL_DATA=ON .
make -j8
make install
```
The use of `qt` is not mandatory but strongly recommended.

2. Clone `ALFRED` on your system.
```sh
git clone XXX
cd ALFRED
```

3. Create a build directory:
```sh
mkdir build
cd build
cmake ..
make -j 4
```

4. Run `ALFRED`:
```sh
./alfred
```

## Utilisation

1. Create runs folders:
```sh
cd ./ALFRED
mkdir runs
mkdir runs/run00
cd runs/run00
```

2. run `ALFRED` with `eigenvalue.mac` in the run folder:
```sh
../../build/alfred ../../eigenvalue.mac > listing
```
Once the run is completed, a `listing` file and several `.csv` files should appear. 

3. You can process the listing file:
```sh
python ../../scripts/energy_deposition.py listing
```

## Materials and geometry definition

Materials and geometry are defined in `DetectorConstruction.cc`. It is a simple model of the TREAT reactor. The user should define its own geometry:
```cpp
G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
   /**
      geometry defintion
   **/
  return fPhysiWorld
}
```

## Physics List

`ALFRED` use the `Shielding` physics list. It is declared in the `main.cc` file:
```cpp
G4PhysListFactory* factory = new G4PhysListFactory();
G4VModularPhysicsList* physics = factory->GetReferencePhysList("Shielding");
physics->RegisterPhysics( new G4ThermalNeutrons());
```
The user can modify the physics list to its need. `ALFRED` uses the standart G4ENDL nuclear data library. But the user can use any other library: https://www-nds.iaea.org/geant4/.

## Run Action

Each run correspond to a batch of a given number of particle. The source particle is sampled based on the neutron fission sites and energy tallied at the previous batch. The user can recover the sources for each run with csv files created: `Sources_[batch]_nt_FS_0.csv`. Running several batches consist in solving the eigenvalue problem with all particles involved into the fission process being simulated.
The user has to define its own variables and function that tallies the quantity desired.

## Multithread

Multithread runs has no yet been implemented.