//
// Created by Jonathan Pulsipher on 4/1/26.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include "ConcurrentQueue.hpp"
/**
 *
 * Note: pow10Padding used (i * pow10Padding) to give predictable, unique int values across producers
 *
 * @param num_producers
 * @param num_consumers
 * @param num_ints
 * @return
 */
bool testQueue(int num_producers, int num_consumers, int num_ints) {
    static ConcurrentQueue<int>* q = new ConcurrentQueue<int>();
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    for (int i = 0; i < num_producers; i++) {
        producers.emplace_back(std::thread([i, num_ints]() {
            int pow10Padding = std::pow(10, std::to_string(num_ints).length());
            for (int j = 0; j < num_ints; j++) {
                q->enqueue(pow10Padding * i + j);
            }
        }));
    }
    for (int i = 0; i < num_consumers; i++) {
        consumers.emplace_back(std::thread([i, num_ints]() {
            for (int j = 0; j < num_ints; j++) {
                int ret;
                q->dequeue(&ret);
            }
        }));
    }

    // Wait for everyone to finish
    for (auto& t : producers) t.join();
    for (auto& t : consumers) t.join();

    return q->size() == (num_producers - num_consumers) * num_ints;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <num_producers> <num_consumers> <num_ints>";
    }
    int num_producers = atoi(argv[1]);
    int num_consumers = atoi(argv[2]);
    int num_ints = atoi(argv[3]);
    bool passed = testQueue(num_producers, num_consumers, num_ints);
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
}