// ===========================================================================
// DiningPhilosophers.h
// ===========================================================================

#pragma once


constexpr size_t  NumPhilosophers{ 5 };         // number of dining philosophers

constexpr size_t  SimulationDuration{ 10000 };   // total time of simulation (milliseonds)

constexpr size_t  MinSleepingMSecs{ 10 };       // sleeping between 1 and ...
constexpr size_t  MaxSleepingMSecs{ 30 };       // ... 3 seconds

enum class PhilosopherState { None, Thinking, Eating, Hungry };


// ===========================================================================
// End-of-File
// ===========================================================================
