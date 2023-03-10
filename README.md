# MPI Examples

This is a collection of c++ code examples for MPI. You can build examples by using CMake.

## Installation of MPI

### Windows

You can use MS-MPI, which can be downloaded from the following webpage:

https://docs.microsoft.com/ja-jp/message-passing-interface/microsoft-mpi

Microsoft also provides an example of how to compile and run a simple MS-MPI program using Visual Studio:

https://learn.microsoft.com/en-us/archive/blogs/windowshpc/how-to-compile-and-run-a-simple-ms-mpi-program

### Linux or Mac

You can use either OpenMPI or MPICH. I recommend to install OpenMPI or MPICH by using any software package manager. For example, you can install OpenMP on Ubuntu as

```terminal
$ sudo apt install openmpi
```

Or, for MPICH,

```terminal
$ sudo apt install mpich
```

## Build

### Windows

#### Visual Studio

If you have installed Visual Studio, you can build examples by just opening the project folder. Visual Studio will automatically recognize CMake scripts in this project folder. Then, you can build examples by pressing `F7` button or clicking [Build]>[Build All] in the menue bar.

#### Visual Studio Code

Open this folder with Visual Studio Code. If you have installed the C/C++ extension pack and CMake tools extension, you can easily build the project.

### Linux or Mac

You need CMake to build this project. Under the project root directory, type the follwing command to build examples:

```terminal
$ cmake -S . -B build
$ cmake --build build
```

## Run

### Windows

You can run executables with the following command on PowerShell:

```powershell
> mpiexec -np [number of processes] [executable name]
```

where `[number of processes]` can be an integer, and `[executable name]` can be `hello_world.exe`, for example.

### Linux or Mac

You can run executables with the following command on Terminal:

```
$ mpirun -np [number of processes] [executable name]
```