#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include "binread.cpp"
#include "graph.h"
//#include "calculateTime.cpp"
std::string redColor = "\033[38;5;196m";
std::string yellowColor = "\033[38;5;226m";
std::string greenColor = "\033[38;5;46m";
std::string orangeColor = "\033[38;5;202m";
std::string resetColor = "\033[0m";


Graph tempGraph;

struct BinFillLevel {
    int day;
    int hour;
    int binNumber;
    int fillLevel;
};

std::vector<BinFillLevel> binFillLevelData;

void readBinFillLevelData() {
    std::ifstream file("bin_fill_levels.csv");

    if (!file) {
        std::cerr << "Failed to open the file for reading.\n";
        return;
    }

    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string dayStr, hourStr, binNumberStr, fillLevelStr;
        if (std::getline(iss, dayStr, ',') && std::getline(iss, hourStr, ',') &&
            std::getline(iss, binNumberStr, ',') && std::getline(iss, fillLevelStr, ',')) {
            int day = std::stoi(dayStr);
            int hour = std::stoi(hourStr);
            int binNumber = std::stoi(binNumberStr);
            int fillLevel = std::stoi(fillLevelStr);
            binFillLevelData.push_back({ day, hour, binNumber, fillLevel });
        }
    }

    file.close();
}



void displayBinFillLevels(int fillThreshold, int selectedDay, int selectedHour,std::string sector = "") {
    std::cout << "\033c";
    std::vector<BinData> binDataList = readCSV("bin_data.csv");
    std::cout << "Bin Fill Levels (Above " << fillThreshold << "%) for Day " << selectedDay << ", Hour " << selectedHour << ":\n\n";

    bool foundData = false;
    for (const auto& binFillLevel : binFillLevelData) {
        if (binFillLevel.day == selectedDay && binFillLevel.hour == selectedHour && binFillLevel.fillLevel > fillThreshold) {
            foundData = true;
              
           
            if(sector == "")
            {
                outputSectorAddressAndTravelTime(binDataList, std::to_string(binFillLevel.binNumber));
            }
            else
            {
                outputSectorAddressAndTravelTime(binDataList, std::to_string(binFillLevel.binNumber), sector);
            }
            std::cout << "Fill Level: " << binFillLevel.fillLevel << "%\n\n";
        }
    }

    if (!foundData) {
        std::cout << "No bin fill level data available for the selected day and hour.\n";
    }
}

struct Controller {
    std::string username;
    std::string password;

    Controller(const std::string& username, const std::string& password)
        : username(username), password(password) {}
};


std::vector<Controller> controllers;


void readControllersFromFile() {
    std::ifstream file("controllers.txt");

    if (!file) {
        std::cerr << "Failed to open the file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string username, password;
        if (std::getline(iss, username, ',') && std::getline(iss, password, ',')) {
            controllers.push_back(Controller(username, password));
        }
    }

    file.close();
}

void writeControllersToFile() {
    std::ofstream file("controllers.txt");

    if (!file) {
        std::cerr << "Failed to open the file for writing.\n";
        return;
    }

    for (const auto& controller : controllers) {
        file << controller.username << "," << controller.password << "\n";
    }

    file.close();
}

bool controllerLogin() {
    std::string username, password;
    std::cout << "Controller Login\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    for (const auto& controller : controllers) {
        if (controller.username == username && controller.password == password) {
            std::cout << "====================================================================================================\n";
            std::cout << "                             "<<greenColor<<"Login Successful.\n"<<resetColor;
            std::cout << "====================================================================================================\n";
            return true;
        }
    }

    std::cout << redColor<<"Invalid username or password.\n"<<resetColor;
    return false;
}

void controllerSignup() {
    std::string username, password;
    std::cout << "Controller Signup\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    controllers.push_back(Controller(username, password));
    writeControllersToFile();
    std::cout << greenColor<<"Controller account created successfully.\n"<<resetColor;
}



//                                                             DRIVER STARTS HERE

struct TruckDriver {
    int ID;
    std::string password;

    TruckDriver(int ID, const std::string& password)
        : ID(ID), password(password) {}
};

std::vector<TruckDriver> truckDrivers;

void readTruckDriversFromFile() {
    std::ifstream file("truck_drivers.txt");

    if (!file) {
        std::cerr << "File does not exist. Creating a new file.\n";
        file.close();
        std::ofstream newFile("truck_drivers.txt");
        newFile.close();
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int ID;
        std::string password;
        if (iss >> ID && std::getline(iss, password)) {
            truckDrivers.push_back(TruckDriver(ID, password));
        }
    }

    file.close();
}

void writeTruckDriversToFile() {
    std::ofstream file("truck_drivers.txt");

    if (!file) {
        std::cerr << "Failed to open the file for writing.\n";
        return;
    }

    for (const auto& truckDriver : truckDrivers) {
        file << truckDriver.ID << " " << truckDriver.password << "\n";
    }

    file.close();
}
int tempID;
bool truckDriverLogin() {
    int ID;
    std::string password;
    std::cout << "Truck Driver Login\n";
    std::cout << "ID: ";
    std::cin >> ID;
    std::cout << "Password: ";
    std::cin >> password;

    std::ifstream file("truck_drivers.txt");
    if (!file) {
        std::cerr << "Failed to open the file for reading.\n";
        return false;
    }

    int fileID;
    std::string filePassword;
    while (file >> fileID >> filePassword) {
        if (fileID == ID && filePassword == password) {
            tempID = ID;
            std::cout << "Login Successful.\n";
            file.close();
            return true;
        }
    }

    file.close();
    std::cout << "Invalid ID or password.\n";
    return false;
}


void truckDriverSignup() {
    int ID;
    std::string password;
    std::cout << "Truck Driver Signup\n";
    std::cout << "ID: ";
    std::cin >> ID;
    std::cout << "Password: ";
    std::cin >> password;

    truckDrivers.push_back(TruckDriver(ID, password));
    writeTruckDriversToFile();
    std::cout << greenColor<<"Truck Driver account created successfully.\n"<<resetColor;
}








//                                                             DRIVER MENU STARTS HERE


int CalculateTruckTime()
{
    int totalTruckTime=0;
   // Graph tempGraph;
    for(int j=0;j<i;j++)
    {
        if(j==0)
        {
            totalTruckTime+=tempGraph.dijkstraMiniTime(tempID, binNumberArray[j]);
        }
        else{
            totalTruckTime+=tempGraph.dijkstraMiniTime(binNumberArray[j-1], binNumberArray[j]);
        }
        if(totalTruckTime==0)
        {
            return 0;
        }
        else if(tempID==101){
            totalTruckTime+=tempGraph.dijkstraMiniTime(binNumberArray[j], 1001);
        }
        else if(tempID==102){
            totalTruckTime+=tempGraph.dijkstraMiniTime(binNumberArray[j], 1002);
        }
        else if(tempID==103){
            totalTruckTime+=tempGraph.dijkstraMiniTime(binNumberArray[j], 1003);
        }
        else if(tempID==104){
            totalTruckTime+=tempGraph.dijkstraMiniTime(binNumberArray[j], 1004);
        }
        else if(tempID==105){
            totalTruckTime+=tempGraph.dijkstraMiniTime(binNumberArray[j], 1005);
        }
        
    }
    return totalTruckTime;

}

void DriverMenu(int id=0)
{   std::cout << "====================================================================================================\n";
    std::cout<<"                                    "<<orangeColor<<"Welcome Driver\n"<<resetColor;
    //std::cout<<"                    Please LogIn to See if you have any Notifications\n";
    std::cout << "====================================================================================================\n\n";
    
    if(id==tempID)
    {
        cout<<"                                 "<<yellowColor<<"You have a notification.\n"<<resetColor;
        int totaltime=CalculateTruckTime();
        cout<<"                             Your total time is "<<totaltime<<" minutes.\n";
    }
    else
    {
        cout<<"                           "<<yellowColor<<"There are no notifactions for you.\n"<<resetColor;
    }
}



//                                                             CONTROLLER MENU STARTS HERE
void controllerMenu() {
    int fillThreshold;
    int selectedDay = 0;
    int selectedHour = 0;

    std::cout << "Controller Menu\n";
    std::cout << "1. Retrieve Bin Fill Levels\n";
    std::cout << "2. Set Fill Threshold\n";
    std::cout << "3. Set Day and Hour\n";
    std::cout << "4. LogOut\n";

    int choice;
    while (true) {
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            if (binFillLevelData.empty()) {
                std::cout << "No bin fill level data available.\n";
            } else {
                if (fillThreshold == 0) {
                    std::cout << "Please set the fill threshold before retrieving bin fill levels.\n";
                } else if (selectedDay == 0 || selectedHour == 0) {
                    std::cout << "Please set the day and hour before retrieving bin fill levels.\n";
                } else {
                    displayBinFillLevels(fillThreshold, selectedDay, selectedHour);
                }
            }
        } else if (choice == 2) {
            std::cout << "Enter the fill threshold (0-100): ";
            std::cin >> fillThreshold;
            std::cout << "Controller Menu\n";
            std::cout << "1. Retrieve Bin Fill Levels\n";
            std::cout << "2. Set Fill Threshold\n";
            std::cout << "3. Set Day and Hour\n";
            std::cout << "4. LogOut\n";
        } else if (choice == 3) {
           
            std::cout << "Enter the day: ";
            std::cin >> selectedDay;
            std::cout << "Enter the hour: ";
            std::cin >> selectedHour;
            std::cout<<"Do you want to filter by sector? (y/n)";
            char ch;
            std::cin>>ch;
            if(ch == 'y')
            {
                std::cout << "Enter the sector: ";
                std::string sector;
                std::cin >> sector;
                displayBinFillLevels(fillThreshold, selectedDay, selectedHour, sector);
            }
            else
            {
                displayBinFillLevels(fillThreshold, selectedDay, selectedHour);
            }

            int choice;
            int ID;
            std::cout << "Do you want to notify the drivers? (y/n)";
            std::cin >> ch;
            if (ch == 'y' || ch == 'Y') {
                std::cout << "1. Notify all drivers\n";
                std::cout << "2. Notify a particular Driver\n";
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                if (choice == 1) {
                    std::cout << "All drivers notified.\n";
                } else if (choice == 2) {
                    std::cout << "Enter the Driver ID: ";
                    int Id;
                    std::cin >> Id;
                    std::cout << "Drivers with ID " << Id << "  is notified.\n";
                    std::cout<<"                             Logging Out\n";
                    while(!truckDriverLogin())
                    {
                        std::cout<<redColor<<"Invalid Credentials\n"<<resetColor;
                        //DriverMenu(Id);
                    }
                    
                    DriverMenu(Id);
                }else {
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }

        } else if (choice == 4) {
            std::cout << "Exiting the program.\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}



//                                                             MAIN STARTS HERE & CONTROLLER MENU ENDS HERE
int main() {
    tempGraph=graphmaker();
    readControllersFromFile();
    readTruckDriversFromFile();
    int loginChoice;
    std::cout << "====================================================================================================\n";
    std::cout << "                             "<<orangeColor<<"Welcome to the Waste Management System!\n"<<resetColor;
    std::cout << "====================================================================================================\n";
    std::cout << "                               "<<yellowColor<<"LogIn as Controller or Truck-Driver\n"<<resetColor
    ;
    do{
        
        std::cout << "\n1. Login\n";
        std::cout << "2. Signup\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> loginChoice;
        
        if (loginChoice == 1) {
            std::cout<<"DO you Wish to Login as a Controller or a Driver?(C/D)";
            char ch;
            std::cin>>ch;
            if(ch == 'C' || ch == 'c')
            {
                if (controllerLogin()) {
                    readBinFillLevelData();
                    controllerMenu();
                }
            }
            else if(ch == 'D' || ch == 'd')
            {
                if(truckDriverLogin())
                {
                    DriverMenu();
                }
                else
                {
                    std::cout<<redColor<<"Invalid Credentials\n"<<resetColor;
                }
                
            }
            else
            {
                std::cout<<redColor<<"Invalid Choice\n"<<resetColor;
            }

        } else if (loginChoice == 2) {
            std::cout<<"DO you Wish to Signup as a Controller or a Driver?(C/D)";
            char ch;
            std::cin>>ch;
            if(ch == 'C' || ch == 'c')
            {
                controllerSignup();
            }
            else if(ch == 'D' || ch == 'd')
            {
                truckDriverSignup();
            }
            else
            {
                std::cout<<redColor<<"Invalid Choice\n"<<resetColor;
            }
        } else if (loginChoice == 3) {
            std::cout << "Exiting the program.\n";
            break;
        } else {
            std::cout <<redColor<< "Invalid choice. Please try again.\n"<<resetColor;
        }
    }while (loginChoice != 3);

    return 0;
}