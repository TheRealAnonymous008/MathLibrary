cd CMake 
cmake ../

cmake --build . --config Release --target NumberSystems
cmake --build . --config Release --target LinearAlgebra
move Release\* ../bin

cd ../