#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <json/json.h> // JSON library (needs to be installed)
#include <cmath> // For base conversion

// Function to decode a value from a given base
int decodeValue(int base, const std::string& value) {
    int result = 0;
    int power = 1;
    for (int i = value.length() - 1; i >= 0; --i) {
        result += (value[i] - '0') * power;
        power *= base;
    }
    return result;
}

// Function to calculate Lagrange interpolation for constant term 'c'
double findConstantTerm(const std::vector<int>& x, const std::vector<int>& y, int k) {
    double constantTerm = 0;

    for (int i = 0; i < k; i++) {
        double term = y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - x[j]) / (x[i] - x[j]);
            }
        }
        constantTerm += term;
    }

    return constantTerm;
}

int main() {
    // Load the JSON input file
    std::ifstream file("input.json");
    Json::Value root;
    file >> root;

    // Parse the number of roots and k (minimum number of roots required)
    int n = root["keys"]["n"].asInt();
    int k = root["keys"]["k"].asInt();

    // Store the x and decoded y values
    std::vector<int> xValues;
    std::vector<int> yValues;

    // Iterate through the JSON object and decode the values
    for (auto it = root.begin(); it != root.end(); ++it) {
        if (it.key().asString() != "keys") {
            int x = std::stoi(it.key().asString()); // Extract the key as x
            int base = std::stoi((*it)["base"].asString()); // Extract the base
            std::string value = (*it)["value"].asString(); // Extract the encoded value

            // Decode y from the given base
            int y = decodeValue(base, value);

            // Store the x and decoded y values
            xValues.push_back(x);
            yValues.push_back(y);
        }
    }

    // Calculate the constant term using Lagrange interpolation
    double constantTerm = findConstantTerm(xValues, yValues, k);

    // Output the constant term 'c'
    std::cout << "The constant term (c) is: " << constantTerm << std::endl;

    return 0;
}
