# partGen

A simple GEANT4 program scattering incident electrons from a target and 
determining their emerging energies and positions in the transverse plane.

The default geometry is set in the Geant4 macro file `~/sources/df.mac`.  The world volume is set to vacuum. 

## Building 

Make a `build` directory in parallel to the `sources` directory and copy the `config.sh` script to the `build` directory.

Run the following: 

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

This will bring up a Qt window showing the geometry setup.  To manually run events, use `/run/beamOn N`, with N = number of events. 

To run from batch mode: 

```
./partGenMain macro-name.mac
```

Where `macro-name.mac` is a Geant4 macro.  The df.mac gives an example.  From that file, the target material and size may be changed. 
Additionally, the detector material, size, and location may be changed.
 
