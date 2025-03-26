//
// Created by Felipe Notebook on 25/03/2025.
//

#include "RandomId.hpp"

#include <chrono>  // For time-based seed if needed
#include <random>

std::string RandomId::generateRandomId() {
    // Use a random device for seeding
    static std::random_device rd;  // Non-deterministic random seed
    static std::mt19937 generator(rd());  // Mersenne Twister PRNG

    std::uniform_int_distribution dist(0, 999);  // Random number in [0, 999]
    const int randomValue = dist(generator);

    // Retrieve a timestamp (e.g., seconds since epoch)
    const auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();

    return std::to_string(randomValue) + std::to_string(timestamp);
}
