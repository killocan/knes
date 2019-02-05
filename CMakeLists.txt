cmake_minimum_required(VERSION 2.8)

project(knes)

include_directories(./include)


# Coloque os arquivos .ccp aqui
set(SRC src/main.cpp
  src/main.cpp
  src/NesFile.cpp
  src/RomBank.cpp
  src/Trainer.cpp
  src/VRomBank.cpp)

# Coloque os arquivos .hpp aqui
set(HRD include/commonvalues.hpp
  include/Exceptions.hpp
  include/NesFile.hpp
  include/RomBank.hpp
  include/Trainer.hpp
  include/VRomBank.hpp)

add_executable(knes ${SRC} ${HRD})