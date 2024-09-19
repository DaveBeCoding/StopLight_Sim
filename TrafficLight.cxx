#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

enum class LightState { RED, GREEN, YELLOW };

class TrafficLight {
public:
    TrafficLight() : state(LightState::RED) {}

    void changeState(LightState newState) {
        std::lock_guard<std::mutex> lock(mutex);
        state = newState;
        std::cout << "Light changed to: " << stateToString() << std::endl;
    }

    std::string stateToString() const {
        switch (state) {
            case LightState::RED: return "Red";
            case LightState::GREEN: return "Green";
            case LightState::YELLOW: return "Yellow";
        }
        return "Unknown";
    }

    void run() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate time for lights
            changeState(LightState::GREEN);

            std::this_thread::sleep_for(std::chrono::seconds(4));
            changeState(LightState::YELLOW);

            std::this_thread::sleep_for(std::chrono::seconds(2));
            changeState(LightState::RED);
        }
    }

private:
    LightState state;
    mutable std::mutex mutex;
};

// Simulate a pedestrian request system
void pedestrianRequest(TrafficLight& light) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    light.changeState(LightState::RED);  // Force light to change for pedestrians
    std::cout << "Pedestrian crossing...\n";
}

int main() {
    TrafficLight light;

    // Run traffic light system in a separate thread
    std::thread trafficThread(&TrafficLight::run, &light);

    // Simulate pedestrian requests in the main thread
    pedestrianRequest(light);

    trafficThread.join();  // Wait for traffic light thread to finish (it won't, but for simulation)
    return 0;
}
