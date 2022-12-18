cd CMake 
cmake ../

cmake --build . --config Release --target IntegerNumbers
cmake --build . --config Release --target NaturalNumbers
cmake --build . --config Release --target LinearAlgebra
move Release\* ../bin

cd ../