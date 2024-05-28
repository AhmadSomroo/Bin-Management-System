#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct BinData {
    std::string sector;
    std::string binNumber;
    std::string binAddress;
    int travelTime;
};

std::vector<BinData> readCSV(const std::string& filename) {
    std::vector<BinData> binDataList;
    
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Skip the header line
        
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string sector, binNumber, binAddress, travelTimeStr;
            
            std::getline(iss, sector, ',');
            std::getline(iss, binNumber, ',');
            std::getline(iss, binAddress, ',');
            std::getline(iss, travelTimeStr, ',');
            
            int travelTime = std::stoi(travelTimeStr);
            
            binDataList.push_back({sector, binNumber, binAddress, travelTime});
        }
        
        file.close();
    } else {
        std::cerr << "Error opening the file." << std::endl;
    }
    
    return binDataList;
}
int binNumberArray[50] = {-1};
int i = 0;
void outputSectorAddressAndTravelTime(const std::vector<BinData>& binDataList, const std::string& binNumber) {
    for (const BinData& binData : binDataList) {
        if (binData.binNumber == binNumber) {
            binNumberArray[i] = std::stoi(binData.binNumber);
            i++;
            std::cout << "Sector: " << binData.sector << std::endl;
            std::cout << "Address: " << binData.binAddress << std::endl;
            //std::cout << "Travel Time: " << binData.travelTime << " minutes" << std::endl;
            
            return;
        }
    }

    
    std::cout << "Bin number not found." << std::endl;
}
void outputSectorAddressAndTravelTime(const std::vector<BinData>& binDataList, const std::string& binNumber, const std::string& sector) {
    for (const BinData& binData : binDataList) {
        if (binData.binNumber == binNumber && binData.sector == sector) {
            binNumberArray[i] = std::stoi(binData.binNumber);
            i++;
            std::cout << "Sector: " << binData.sector << std::endl;
            std::cout << "Address: " << binData.binAddress << std::endl;
            std::cout << "Travel Time: " << binData.travelTime << " minutes" << std::endl;
            return;
        }
    }
    
    std::cout << "Bin number not found." << std::endl;
}

/*int main() {
    
    
    std::string binNumber;
    std::cout << "Enter bin number: ";
    std::cin >> binNumber;
    
    
    
    return 0;
}*/