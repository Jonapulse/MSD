#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // We use a loop that never ends to test background persistence
    while (true) {
        std::cout << "hello" << std::endl;

        // Sleep for 5 seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}