cd CMake 
cmake ../

cmake --build . --config Release --target NumberSystems
move Release\* ../bin

cd ../