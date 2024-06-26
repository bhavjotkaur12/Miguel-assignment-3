#include "AVLTree.h"
#include "timer.h"
#include <map>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <limits>


const int NUM_ELEMENTS = 10000; // Adjust this number based on your system's capabilities

// Helper function to generate random EmployeeInfo data
EmployeeInfo generateRandomEmployeeInfo(int id) {
    EmployeeInfo empl;
    empl.age = rand() % 60 + 20; // Random age between 20 and 80
    empl.salary = rand() % 50000 + 50000; // Random salary between 50,000 and 100,000
    empl.emplNumber = id;
    empl.sin = rand();
    return empl;
}

// Function to pause and wait for user input
void pause(const std::string& message) {
    std::cout << message << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Test for correctness of insertion with timing
void testInsertion(AVLTree& avlTree) {
    std::cout << "Testing insertion correctness with hard-coded data..." << std::endl;

    // Hard-coded data for insertion
    std::vector<EmployeeInfo> testData = {
        {50000, 30, 1, 101},
        {55000, 35, 2, 102},
        {60000, 40, 3, 103}
    };

    Timer timer;
    timer.start();

    // Insert hard-coded data into AVL tree
    for (const auto& empl : testData) {
        avlTree.insert(empl);
    }

    timer.stop();
    std::cout << "Time taken for insertion: " << timer.currtime() << " seconds" << std::endl;

    // Display the AVL tree
    avlTree.display();

    // Compare with the expected tree structure 
    std::cout << "Manually compare the displayed tree with the expected structure." << std::endl;
    pause("Press Enter to continue...");
}

// Test for correctness of deletion with timing
void testDeletion(AVLTree& avlTree) {
    std::cout << "Testing deletion correctness with hard-coded data..." << std::endl;

    // Hard-coded data for deletion
    int sinToDelete = 102; // Assuming this SIN exists in the tree

    Timer timer;
    timer.start();

    // Delete the node with the given SIN
    avlTree.remove(sinToDelete);

    timer.stop();
    std::cout << "Time taken for deletion: " << timer.currtime() << " seconds" << std::endl;

    // Display the AVL tree
    avlTree.display();

    // Compare with the expected tree structure after deletion 
    std::cout << "Manually compare the displayed tree with the expected structure after deletion." << std::endl;
    pause("Press Enter to continue...");
}



// Test for load (repeated access)
void testLoad(AVLTree& avlTree, std::map<int, EmployeeInfo>& stdMap) {
    std::cout << "Testing load..." << std::endl;
    Timer timer;

    // Measure time taken for repeated access in AVL tree
    timer.start();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        avlTree.insert(generateRandomEmployeeInfo(i));
        avlTree.remove(avlTree.GetRoot()->empl.sin);
    }
    timer.stop();
    std::cout << "AVL tree load test time: " << timer.currtime() << " seconds" << std::endl;

    // Measure time taken for repeated access in std::map
    timer.reset();
    timer.start();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        EmployeeInfo empl = generateRandomEmployeeInfo(i);
        stdMap[empl.sin] = empl;
        stdMap.erase(empl.sin);
    }
    timer.stop();
    std::cout << "std::map load test time: " << timer.currtime() << " seconds" << std::endl;
    pause("Press Enter to continue...");
}


// Test for speed of search (worst case)
void testSearchSpeed(AVLTree& avlTree, std::map<int, EmployeeInfo>& stdMap) {
    std::cout << "Testing search speed (worst case)..." << std::endl;
    Timer timer;

    // Find the elements with the maximum and minimum SIN
    int maxSin = std::max_element(stdMap.begin(), stdMap.end(),
                                  [](const auto& a, const auto& b) {
                                      return a.second.sin < b.second.sin;
                                  })->second.sin;
    int minSin = std::min_element(stdMap.begin(), stdMap.end(),
                                  [](const auto& a, const auto& b) {
                                      return a.second.sin < b.second.sin;
                                  })->second.sin;

    // Measure time taken to search for the maximum SIN in AVL tree
    timer.start();
    avlTree.Find(avlTree.GetRoot(), maxSin);
    timer.stop();
    std::cout << "AVL tree search time for maximum SIN: " << timer.currtime() << " seconds" << std::endl;

    // Measure time taken to search for the maximum SIN in std::map
    timer.reset();
    timer.start();
    stdMap.find(maxSin);
    timer.stop();
    std::cout << "std::map search time for maximum SIN: " << timer.currtime() << " seconds" << std::endl;

    // Measure time taken to search for the minimum SIN in AVL tree
    timer.reset();
    timer.start();
    avlTree.Find(avlTree.GetRoot(), minSin);
    timer.stop();
    std::cout << "AVL tree search time for minimum SIN: " << timer.currtime() << " seconds" << std::endl;

    // Measure time taken to search for the minimum SIN in std::map
    timer.reset();
    timer.start();
    stdMap.find(minSin);
    timer.stop();
    std::cout << "std::map search time for minimum SIN: " << timer.currtime() << " seconds" << std::endl;

    pause("Press Enter to continue...");
}

void runTests() {
    AVLTree avlTree;
    std::map<int, EmployeeInfo> stdMap;

    // Populate AVL tree and std::map with random data
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        EmployeeInfo empl = generateRandomEmployeeInfo(i);
        avlTree.insert(empl);
        stdMap[empl.sin] = empl;
    }

    // Perform tests
    testInsertion(avlTree);
    testDeletion(avlTree);
    testLoad(avlTree, stdMap);
    testSearchSpeed(avlTree, stdMap);
}

int main() {
    srand(time(nullptr)); // Seed the random number generator

    std::cout << "Starting AVL Tree and std::map tests..." << std::endl;
    runTests();
    std::cout << "Tests completed." << std::endl;

    return 0;
}

