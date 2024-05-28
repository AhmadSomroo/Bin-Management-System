#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

std::string generate_bin_address(const std::string& sector) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> street_dist(1, 50);
    
    int street = street_dist(gen);
    
    return sector + "_Street " + std::to_string(street);
}

std::string generate_dumpsite_address(const std::string& sector) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> street_dist(1, 50);
    
    int street = street_dist(gen);
    
    return "Dumpsite_" + sector + "_Street " + std::to_string(street);
}

std::vector<int> generate_bin_numbers() {
    std::vector<int> numbers;
    
    for (int i = 0; i < 50; ++i) {
        numbers.push_back(i);
    }
    
    return numbers;
}

int generate_travel_time() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<int> time_dist(1, 5);
    
    return time_dist(gen);
}

int main() {
    std::vector<int> bin_numbers = generate_bin_numbers();
    std::vector<std::string> bin_addresses;
    std::vector<std::string> dumpsite_addresses;
    std::vector<int> travel_times;
    
    std::vector<std::string> sectors = {"F-8", "G-7", "G-8", "F-7", "G-9"};
    
    std::ofstream file("bin_data.csv");
    
    if (file.is_open()) {
        file << "Sector,Bin Number,Bin Address,Travel Time to Next\n";
        
        int bin_index = 0;
        for (const std::string& sector : sectors) {
            for (int i = 0; i < 10; ++i) {
                file << sector << "," << bin_numbers[bin_index] << "," << generate_bin_address(sector) << "," << generate_travel_time() << "\n";
                bin_index++;
            }
            
            file << sector << ",Dumpsite," << generate_dumpsite_address(sector) << "," << generate_travel_time() << "\n";
        }
        
        file.close();
        std::cout << "Data written to bin_data.csv successfully." << std::endl;
    } else {
        std::cerr << "Error opening the file." << std::endl;
    }
    
    return 0;
}