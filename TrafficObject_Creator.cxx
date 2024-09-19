#include <iostream>
#include <vector>
#include <memory>  // For smart pointers
#include <thread>  // For threading
#include <chrono>  // For simulating time delays

// Enum for the light state
enum class LightState { RED, YELLOW, GREEN };

// Class definition for TrafficLight
class TrafficLight {
public:
    // Constructor initializing the light state to RED
    TrafficLight() : state(LightState::RED) {}

    // Method to simulate the traffic light cycle
    void run() {
        while (true) {
            changeState();
            displayState();
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate 1-second delay
        }
    }

    // Method to change the traffic light state (cycle through RED, YELLOW, GREEN)
    void changeState() {
        if (state == LightState::RED) {
            state = LightState::GREEN;
        } else if (state == LightState::GREEN) {
            state = LightState::YELLOW;
        } else {
            state = LightState::RED;
        }
    }

    // Method to display the current state
    void displayState() const {
        if (state == LightState::RED) {
            std::cout << "Traffic Light is RED\n";
        } else if (state == LightState::YELLOW) {
            std::cout << "Traffic Light is YELLOW\n";
        } else if (state == LightState::GREEN) {
            std::cout << "Traffic Light is GREEN\n";
        }
    }

private:
    LightState state;  // Current state of the traffic light
};

// Function to generate `n` traffic light objects and start them in separate threads
void createAndRunTrafficLights(int n) {
    // Vector to store pointers to TrafficLight objects
    std::vector<std::shared_ptr<TrafficLight>> trafficLights;

    // Vector to store threads
    std::vector<std::thread> threads;

    // Create `n` TrafficLight objects and store them
    for (int i = 0; i < n; ++i) {
        // Create a TrafficLight object and store it in the vector using a smart pointer
        auto trafficLight = std::make_shared<TrafficLight>();
        trafficLights.push_back(trafficLight);

        // Create a thread for each traffic light to run its `run()` method
        threads.push_back(std::thread(&TrafficLight::run, trafficLight));
    }

    // Join all threads (so the main program waits for them to finish)
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

int main() {
    // Create and run 3 traffic lights
    createAndRunTrafficLights(3);

    return 0;
}
