# partGen

A simple GEANT4 program scattering incident electrons from a target and 
determining their emerging energies and positions in the transverse plane.

The default geometry is set in the Geant4 macro file `~/sources/df.mac`.  The world volume is set to vacuum. 

## Downloading the Source 

Create a clone of the repository in your location of choice via: 

```
git clone https://github.com/dflay/partGen.git 
```

## Building 

cd into the `partGen` directory.  Make a `build` directory in parallel to the `sources` directory and 
copy the `config.sh` script to the `build` directory. Be sure that the path to your Geant4 installation 
is correct in the `config.sh` file (see the `-DGEANT4_DIR` variable).  Run the following: 

```
cd build 
./config.sh 
make -jN (N = number of cores of your machine) 
```

## Running 

To run the program, run it from the build directory.  In interactive mode: 

```
./partGenMain 
```

This will bring up a Qt window showing the geometry setup.  To manually run events, 
use `/run/beamOn N`, with N = number of events. 

To run from batch mode: 

```
./partGenMain macro-name.mac
```

Where `macro-name.mac` is a Geant4 macro.  The df.mac gives an example.  
From that file, the target material and size may be changed. 
Additionally, the detector material, size, and location may be changed.

## Output 

The program will generate a ROOT file called `outData.root` with the tree structure as shown below:  

```
Edep = energy deposited in target material (GeV)
Etot = total energy of the track (GeV) = T + m
xPos = x position (mm)
yPos = y position (mm)
zPos = z position (mm)
px = x component of momentum (GeV)
py = y component of momentum (GeV)
pz = z component of momentum (GeV)
P = quadrature sum of px, py, pz (GeV)
hit = hit index (integer)
pid = particle ID 
```
The full particle ID code is here: https://root.cern.ch/doc/master/TPDGCode_8h.html
