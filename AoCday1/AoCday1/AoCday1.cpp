// AoCday1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include <algorithm>

using json = nlohmann::json;

int main()
{
    std::ifstream numbersFile("numbers.json");

    if (!numbersFile) {
        std::cout << "Could not open file";
    }


    // Parse the JSON data
    json jsonData;
    
    try {
        numbersFile >> jsonData; // Read file into json object
    }
    catch (const json::parse_error& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return 1;
    }

    json numbersArray = jsonData;

    
    int difference = 0;
    int index = 0;

    // makes a dynamic array the same size as numbers.json
    int size = numbersArray.size();
    std::vector<int> array1(size);
    std::vector<int> array2(size);

    // fill each array with correct elements
    while (size != 0) {
        array1[index] = jsonData[index][0];
        array2[index] = jsonData[index][1];
        
        index++;
        size--;
    }

    // Sort them
    size = numbersArray.size();
    std::sort(array1.begin(), array1.end());
    std::sort(array2.begin(), array2.end());

    // Iterate through all elements in the array, subtracting each, and adding it all as absolute values
    for (int i = 0; i < size; i++) {
        difference += std::abs(array1[i] - array2[i]);
    }

    // Done
    std::cout << "Difference: " << difference << std::endl;

    // PART 2 ====

    int count = 0;
    int similarity = 0;

    // Loop through all of array 1
    for (int i = 0; i < array1.size(); i++) {
        // Loop through all of array 2 for every array 1 element
        for (int j = 0; j < array2.size(); j++) {
            // if the element of array2 matches that of array1, count up once
            if (array1[i] == array2[j]) {
                count++;
            }
        }

        similarity += array1[i] * count;
        count = 0;
    }

    std::cout << "Similarity score: " << similarity << std::endl;

    numbersFile.close();
}