# partGen

A simple GEANT4 program scattering incident electrons from a target and 
determining their emerging energies and positions in the transverse plane.

More details to follow soon.   

# Building 

Make a `build` directory in parallel to the `sources` directory and copy the `config.sh` script to the `build` directory.

Run the following: 

```
cd build 
./config.sh 
make -jN (N = number of cores of your machine) 
```
