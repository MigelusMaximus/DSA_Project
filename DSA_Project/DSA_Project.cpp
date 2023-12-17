// DSA_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>

//Kniznice pre loadovanie filov
#include <string>
#include <iostream>

//Importovanie vytvorenej classy/structure pre Jizdny Rad
#include "TrainSchedule.h"
//Includnutie double linked listu
#include "DoubleLinkedList.h"

//Na editovanie
#include <sstream>


int main() {
    /* Pouzival som pre testovanie nacitavania a citania zo suboru
    * 
    std::ifstream file("train_schedule.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    return 0;

    */


    /*Toto som pouzival ako testovanie vsetkych metod ktore som si nadefinoval predom
    * 
    * 
    //Ako prve potrebujeme spravit instanci triedy, aby sme mohli zacat pouzivat metody
    DoubleLinkedList trainScheduleList;
    trainScheduleList.loadSchedulesFromFile("train_schedule.txt");


    std::cout << "All Train Schedules:" << std::endl;
    trainScheduleList.displayAllSchedules();

    
    TrainSchedule newSchedule("T006", "Liberec", "Ceske Budejovice", "15:30", "18:45");
    trainScheduleList.addTrainSchedule(newSchedule);
    trainScheduleList.writeSchedulesToFile("train_schedule.txt");


    
    std::cout << "\nAll Train Schedules after adding a new one:" << std::endl;
    trainScheduleList.displayAllSchedules();

    
    trainScheduleList.removeTrainSchedule("T003");
    trainScheduleList.writeSchedulesToFile("train_schedule.txt");


    
    std::cout << "\nAll Train Schedules after removing one:" << std::endl;
    trainScheduleList.displayAllSchedules();

    
    const std::string trainIDToFind = "T004";
    TrainSchedule* foundSchedule = trainScheduleList.findTrainSchedule(trainIDToFind);
    if (foundSchedule) {
        std::cout << "\nFound Train Schedule for Train ID " << trainIDToFind << ":" << std::endl;
        std::cout << "Train ID: " << foundSchedule->trainID
            << ", Departure Station: " << foundSchedule->departureStation
            << ", Arrival Station: " << foundSchedule->arrivalStation
            << ", Departure Time: " << foundSchedule->departureTime
            << ", Arrival Time: " << foundSchedule->arrivalTime << std::endl;
    }
    else {
        std::cout << "\nNo Train Schedule found for Train ID " << trainIDToFind << std::endl;
    }

    return 0;
    */

    DoubleLinkedList trainScheduleList;
    trainScheduleList.loadSchedulesFromFile("train_schedule.txt");



    std::string command;
    std::string trainID;


    while (true) {
        std::cout << "Enter command (add, remove, find, display, exit): ";
        std::getline(std::cin, command);

        //Remove chcem nechat cez ID, add zasa by bol vhodnejsie, aby asi automaticky priradovalo ID, I guess
        if (command == "add") {
            std::string trainID, departureStation, arrivalStation, departureTime, arrivalTime;


            std::cout << "Enter the Train you want to add. \n";
            std::cout << "Enter the ID of the Train: ";
            std::getline(std::cin, trainID);
            std::cout << "Enter the Departire Station of the Train: ";
            std::getline(std::cin, departureStation);
            std::cout << "Enter the Arrival Station of the Train: ";
            std::getline(std::cin, arrivalStation);
            std::cout << "Enter the Departure Time of the Train: ";
            std::getline(std::cin, departureTime);
            std::cout << "Enter the Arrival time of the Train: ";
            std::getline(std::cin, arrivalTime);


            TrainSchedule newSchedule(trainID, departureStation, arrivalStation, departureTime, arrivalTime);
            trainScheduleList.addTrainSchedule(newSchedule);
            trainScheduleList.writeSchedulesToFile("train_schedule.txt");


        }
        else if (command == "remove") {
            std::cout << "Enter Train ID to remove: ";
            std::getline(std::cin, trainID);

            // Odstranenie spoja s danym ID
            trainScheduleList.removeTrainSchedule(trainID);
            std::cout << "Train Schedule with ID " << trainID << " has been removed." << std::endl;

            //Ulozenie zmazanie spoja do suboru
            trainScheduleList.writeSchedulesToFile("train_schedule.txt");

        }
        if (command == "find") {
            std::cout << "Enter 'ID' to find by Train ID or 'route' to find by Departure and Arrival stations: ";
            std::string findType;
            std::getline(std::cin, findType);

            if (findType == "ID") {
                std::string trainID;
                std::cout << "Enter Train ID to find: ";
                std::getline(std::cin, trainID);

                TrainSchedule* schedule = trainScheduleList.findTrainSchedule(trainID); // Assuming the method for finding by ID is named 'find'
                if (schedule) {
                    std::cout << "\n" << "Train Schedule found:\n"
                        << "Train ID: " << schedule->trainID << "\n"
                        << "Departure Station: " << schedule->departureStation << "\n"
                        << "Arrival Station: " << schedule->arrivalStation << "\n"
                        << "Departure Time: " << schedule->departureTime << "\n"
                        << "Arrival Time: " << schedule->arrivalTime << "\n" << std::endl;

                }
                else {
                    std::cout << "Train Schedule with ID " << trainID << " not found." << std::endl;
                }
            }
            else if (findType == "route") {
                std::string departureStation, arrivalStation;
                std::cout << "Enter departure station: ";
                std::getline(std::cin, departureStation);
                std::cout << "Enter arrival station: ";
                std::getline(std::cin, arrivalStation);

                std::vector<TrainSchedule*> foundSchedules = trainScheduleList.find(departureStation, arrivalStation); // Overloaded method call
                std::cout << "Train Schedule found:\n" << std::endl;
                for (const auto& schedule : foundSchedules) {
                    std::cout 
                        << "\n" 
                        << "Train ID: " << schedule->trainID << "\n"
                        << "Departure Station: " << schedule->departureStation << "\n"
                        << "Arrival Station: " << schedule->arrivalStation << "\n"
                        << "Departure Time: " << schedule->departureTime << "\n"
                        << "Arrival Time: " << schedule->arrivalTime << "\n" << std::endl;
                }
            }
            else {
                std::cout << "Invalid find type. Please enter 'ID' or 'route'." << std::endl;
            }
        }

        if (command == "edit") {
            std::cout << "Enter Train ID to edit: ";
            std::getline(std::cin, trainID);
            std::string inputLine;
            TrainSchedule* schedule = trainScheduleList.findTrainSchedule(trainID);
            if (schedule) {
                //Vypis aktualnych dat
                std::cout << schedule->trainID << ","
                    << schedule->departureStation << ","
                    << schedule->arrivalStation << ","
                    << schedule->departureTime << ","
                    << schedule->arrivalTime << std::endl;

          
                std::cout << "Enter new data in the same format: ";
                std::getline(std::cin, inputLine);

                std::istringstream iss(inputLine);
                std::string newDepartureStation, newArrivalStation, newDepartureTime, newArrivalTime;

                //Nacitanie editovanych dat
                char delimiter;
                if (std::getline(iss, newDepartureStation, ',') &&
                    std::getline(iss, newArrivalStation, ',') &&
                    std::getline(iss, newDepartureTime, ',') &&
                    std::getline(iss, newArrivalTime)) {
                    // Update dat na nove
                    schedule->departureStation = newDepartureStation;
                    schedule->arrivalStation = newArrivalStation;
                    schedule->departureTime = newDepartureTime;
                    schedule->arrivalTime = newArrivalTime;

                    //Ulozenie editovaneho spoja do filu
                    trainScheduleList.writeSchedulesToFile("train_schedule.txt");
                    std::cout << "Train Schedule updated." << std::endl;
                }
                else {
                    std::cerr << "Invalid input format." << std::endl;
                }
            }
            else {
                std::cout << "Train Schedule with ID " << trainID << " not found." << std::endl;
            }
        }

        //Teraz uz display funguje tak, ze si moze uzivatel zvolit, ktore stlpce chce vidiet
        else if (command == "display") {
            std::cout << "Enter the columns to display separated by commas (e.g., ID,departureStation): ";
            std::string columnsInput;
            std::getline(std::cin, columnsInput);

            std::istringstream colStream(columnsInput);
            std::vector<std::string> columns;
            std::string column;
            while (std::getline(colStream, column, ',')) {
                columns.push_back(column);
            }

            trainScheduleList.displayAllSchedules(columns);
        }
        else if (command == "exit") {
            //Ulozi mi data do suboru, v pripade ze chcem odist, nech nepridem o zmeny
            trainScheduleList.writeSchedulesToFile("train_schedule.txt");
            break;
        }
        else {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
