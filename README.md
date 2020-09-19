# MPI Examples

This is a collection of c++ code examples for MPI. You can build examples by using CMake.

## Installation of MPI

### Windows

You can use either MS-MPI or MPICH. MS-MPI can be downloaded from [here](https://docs.microsoft.com/ja-jp/message-passing-interface/microsoft-mpi), and MPICH can be downloaded from [here](https://www.mpich.org/downloads/).

### Linux or Mac

You can use either OpenMPI or MPICH. I recommend to install OpenMPI or MPICH by using the software package manager. For example, you can install OpenMP in Ubuntu as

```terminal
$> sudo apt install openmp
```

Or, for MPICH,

```terminal
$> sudo apt install mpich
```

## Build

### Windows

If you have installed Visual Studio, you can build examples by just opening the project folder. Visual Studio will automatically recognize the CMake scripts and configure the scripts. Then, you can build examples by pressing `F7` button or clicking [Build]>[Build All] in the menue bar.

### Linux or Mac

You need CMake to build the project. Under the project root directory, type the follwing command to build examples:

```terminal
$> mkdir build
$> cd build
$> cmake ..
$> make
```

## Run

### Windows

You can run executables by

```
$> mpiexec -np <number of processes> <executable name>
```

where `<number of processes>` can be an integer, and `<executable name>` can be `hello_world.exe`, for example.

### Linux or Mac

You can run executables by

```
$> mpirun -np <number of processes> <executable name>
```