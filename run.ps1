param(
    [Int32]$np = 1,
    [String]$builddir = "build"
)

Write-Host "----- Running hello_world.exe -----"
mpiexec.exe -np $np ".\${builddir}\hello_world.exe"
Write-Host "----- Running send_recieve.exe -----"
mpiexec.exe -np $np ".\${builddir}\send_recieve.exe"
Write-Host "----- Running trapezoid.exe -----"
mpiexec.exe -np $np ".\${builddir}\trapezoid.exe"
