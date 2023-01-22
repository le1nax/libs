#pragma once
#include <stdint.h>
enum class CoordType {eUTM, eUTMREF, eLOCAL, eLLH};
constexpr uint8_t numberOfCoordTypes = 4;
constexpr uint8_t numberOfUTMinputs = 4;
constexpr uint8_t numberOfUTMREFinputs = 5;
constexpr uint8_t numberOfUTMzoneinputs = 1;
constexpr uint8_t numberOfUTMREFzoneinputs = 2;
constexpr uint8_t numberOfLocalCoordinateinputs = 6;
constexpr uint8_t numberOfLocalRefinputs = 3;
constexpr uint8_t numberOfLLHinputs = 3;
constexpr uint8_t doublePrecision = 14;
