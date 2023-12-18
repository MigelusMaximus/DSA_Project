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



//cely kod pre main, je len pre trasy


struct Station {
    std::string name;
    Station* next;
    Station* prev;
};

Station* createStation(const std::string& stationName) {
    Station* station = new Station;
    station->name = stationName;
    station->next = nullptr;
    station->prev = nullptr;
    return station;
}
// classa pre double linkd listy - trasy
struct TrainRoute {
    Station* head;
    Station* tail;

    // Constructor to initialize the route
    TrainRoute() : head(nullptr), tail(nullptr) {}


};
void addStationToRoute(TrainRoute& route, const std::string& stationName) {
    Station* newStation = createStation(stationName);
    if (!route.head) {
        route.head = newStation;
        route.tail = newStation;
    }
    else {
        route.tail->next = newStation;
        newStation->prev = route.tail;
        route.tail = newStation;
    }
}
void displayTrainRoute(const TrainRoute& route) {
    Station* station = route.head;

    std::cout << "Train Route: ";
    while (station) {
        std::cout << station->name;
        station = station->next;
        if (station) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

void displayReverseTrainRoute(const TrainRoute& route) {
    Station* station = route.tail;

    std::cout << "Train Route: ";
    while (station) {
        std::cout << station->name;
        station = station->prev;
        if (station) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

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

    std::cout << "Vitajte v spravcovy Jizdneho Radu \n";
    std::cout << "Mate na vyber nasledujuce prikazy:\n";
    std::cout << "pridaj - prida novy spoj do zoznamu spojov\n";
    std::cout << "odstran - odstrani vybrani spoj zo zoznamu\n";
    std::cout << "____________________________________________ \n";
    std::cout << "hladaj - najde spoj/e podla formatu\n";
    std::cout << "hladaj mozne formaty:\n";
    std::cout << "hladaj ID - otvori moznost na vlozenie ID spoja\n";
    std::cout << "hladaj oddo - otvori moznost na vlozenie stanic\n";
    std::cout << "hladaj zostanice - otvori moznost na vlozenie vychodzej stanice\n";
    std::cout << "hladaj dostanice - otvori moznost na vlozenie prichodzej stanice\n";
    std::cout << "____________________________________________ \n";
    std::cout << "edit - otvori nam moznost editovat\n";
    std::cout << "edit ID - jediny povoleny format, otvori moznost vlozit ID\n";
    std::cout << "____________________________________________ \n";
    std::cout << "zobraz - zobrazi nam zoznam vsetkych spojov\n";
    std::cout << "zobraz - bez argumentov zobrazi vsetky spoje\n";
    std::cout << "zobraz je mozne aj filtrovat\n";
    std::cout << "zobraz kategoria ma este moznych 5 dalsich argumentov v akejkolvek kombinacii\n";
    std::cout << "zobraz kategoria ID departureStation arrivalStation departureTime arrivalTime\n";
    std::cout << "____________________________________________ \n";
    std::cout << "trasa - umozny nam nasledne zadat vychodziu a prichodziu stanicu vlaku a zobrazi celu trasu\n";
    std::cout << "trasy mame aktualne 3 \n";
    std::cout << "Praha-Brno \n";
    std::cout << "Brno-Bratislava \n";
    std::cout << "Bratislava-Kosice \n";
    std::cout << "zobrazit si trasy mozete v oboch smeroch\n";
    std::cout << "____________________________________________ \n";
    std::cout << "exit - ukonci aplikaciu a ulozi spoje do suboru\n";
    while (true) {
        
        std::cout << "\nZadajte Prikaz: ";
        std::getline(std::cin, command);
        std::string flag = "empty";

        std::istringstream entry_command(command);
        std::vector<std::string> splitCommand;
        std::string substring;
        while (entry_command >> substring) {
            splitCommand.push_back(substring);
        }
        if (splitCommand.size() >= 2) {
            command = splitCommand[0];
            flag = splitCommand[1];
        }
        else {
            command = splitCommand[0];
        }


        //Remove chcem nechat cez ID, add zasa by bol vhodnejsie, aby asi automaticky priradovalo ID, I guess
        if (command == "pridaj") {
            std::string trainID, departureStation, arrivalStation, departureTime, arrivalTime;


            std::cout << "Vloz vlak ktory chces pridat. \n";
            std::cout << "Vloz ID vlaku, ktory si zelas pridat: ";
            std::getline(std::cin, trainID);
            std::cout << "Zadaj vychodziu stanicu: ";
            std::getline(std::cin, departureStation);
            std::cout << "Zadaj prichodziu stanicu: ";
            std::getline(std::cin, arrivalStation);
            std::cout << "Zadaj cas odchodu vlaku: ";
            std::getline(std::cin, departureTime);
            std::cout << "Zadaj cas prichodu vlaku: ";
            std::getline(std::cin, arrivalTime);


            TrainSchedule newSchedule(trainID, departureStation, arrivalStation, departureTime, arrivalTime);
            trainScheduleList.addTrainSchedule(newSchedule);
            trainScheduleList.writeSchedulesToFile("train_schedule.txt");

            
        }
        else if (command == "odstran") {
            std::cout << "Zadaj ID vlaku na odstranenie: ";
            std::getline(std::cin, trainID);

            // Odstranenie spoja s danym ID
            trainScheduleList.removeTrainSchedule(trainID);
            std::cout << "Vlak s ID " << trainID << " bol odstraneny." << std::endl;

            //Ulozenie zmazanie spoja do suboru
            trainScheduleList.writeSchedulesToFile("train_schedule.txt");

        }
        else if (command == "hladaj") {
           /*
            std::cout << "Enter 'ID' to find by Train ID or 'route' to find by Departure and Arrival stations: ";
            std::string findType;
            std::getline(std::cin, findType);
            */
            if (flag == "ID") {
                std::string trainID;
                std::cout << "Vloz ID vlaku ktore chces hladat: ";
                std::getline(std::cin, trainID);

                TrainSchedule* schedule = trainScheduleList.findTrainSchedule(trainID);
                if (schedule) {
                    std::cout << "\n" << "Vlak Najdeny:\n"
                        << "Vlak ID: " << schedule->trainID << "\n"
                        << "Vychodzia Stanica: " << schedule->departureStation << "\n"
                        << "Prichodzia Stanica: " << schedule->arrivalStation << "\n"
                        << "Cas odjazdu: " << schedule->departureTime << "\n"
                        << "Cas prijazdu: " << schedule->arrivalTime << "\n" << std::endl;

                }
                else {
                    std::cout << "Train Schedule with ID " << trainID << " not found." << std::endl;
                }
            }
            
            else if (flag == "oddo" || flag=="dostanice" || flag== "zostanice") {
                std::string departureStation, arrivalStation;
                std::vector<TrainSchedule*> foundSchedules;



                if (flag == "oddo") {
                    std::cout << "Zadaj vychodziu stanicu: ";
                    std::getline(std::cin, departureStation);
                    std::cout << "Zadaj prichodziu stanicu: ";
                    std::getline(std::cin, arrivalStation);
                    foundSchedules = trainScheduleList.find(departureStation, arrivalStation);
                }
                else if (flag == "dostanice") {
                    std::cout << "Zadaj prichodziu stanicu: ";
                    std::getline(std::cin, arrivalStation);
                    foundSchedules = trainScheduleList.find(arrivalStation,false);
                }
                else if (flag == "zostanice") {
                    std::cout << "Zadaj vychodziu stanicu: ";
                    std::getline(std::cin, departureStation);
                    foundSchedules = trainScheduleList.find(departureStation,true);
                }
                

                
                for (const auto& schedule : foundSchedules) {
                    std::cout 
                        << "\n" 
                        << "Vlak ID: " << schedule->trainID << "\n"
                        << "Vychodzia Stanica: " << schedule->departureStation << "\n"
                        << "Prichodzia Stanica: " << schedule->arrivalStation << "\n"
                        << "Cas odjazdu: " << schedule->departureTime << "\n"
                        << "Cas prijazdu: " << schedule->arrivalTime << "\n" << std::endl;
                }
            }
            else {
                std::cout << "Invalid flag. Please enter 'ID' or 'route' or 'station'." << std::endl;
            }
        }

        else if (command == "edit") {
           // std::cout << "Enter Train ID to edit: ";
           // std::getline(std::cin, trainID);

            if (flag == "ID")


            {
                std::string inputLine;
                TrainSchedule* schedule = trainScheduleList.findTrainSchedule(flag);
                if (schedule) {




                    //Vypis aktualnych dat
                    std::cout << schedule->trainID << ","
                        << schedule->departureStation << ","
                        << schedule->arrivalStation << ","
                        << schedule->departureTime << ","
                        << schedule->arrivalTime << std::endl;


                    std::cout << "Enter new data in the same format: ";
                    std::getline(std::cin, inputLine);

                    std::istringstream newData(inputLine);
                    std::string newID, newDepartureStation, newArrivalStation, newDepartureTime, newArrivalTime;

                    //Nacitanie editovanych dat
                    char delimiter;
                    if (std::getline(newData, newID, ',') &&
                        std::getline(newData, newDepartureStation, ',') &&
                        std::getline(newData, newArrivalStation, ',') &&
                        std::getline(newData, newDepartureTime, ',') &&
                        std::getline(newData, newArrivalTime)) {
                        // Update dat na nove
                        schedule->trainID = newID;
                        schedule->departureStation = newDepartureStation;
                        schedule->arrivalStation = newArrivalStation;
                        schedule->departureTime = newDepartureTime;
                        schedule->arrivalTime = newArrivalTime;

                        //Ulozenie editovaneho spoja do filu
                        trainScheduleList.writeSchedulesToFile("train_schedule.txt");
                        std::cout << "Train Schedule updated." << std::endl;
                    }


                }
            }

            else if (flag == "fstation") {

                        
                        std::string departureStation;
                        std::vector<TrainSchedule*> foundSchedules;
                        std::cout << "Zadaj vychodziu stanicu: ";
                        std::getline(std::cin, departureStation);
                        foundSchedules = trainScheduleList.find(departureStation, true);


                        for (const auto& schedule : foundSchedules) {
                            std::cout
                                << "\n"
                                << "Train ID: " << schedule->trainID << "\n"
                                << "Vychodzia Stanica: " << schedule->departureStation << "\n"
                                << "Prichodzia Stanica: " << schedule->arrivalStation << "\n"
                                << "Cas odjazdu: " << schedule->departureTime << "\n"
                                << "Cas prijazdu: " << schedule->arrivalTime << "\n" << std::endl;
                        }





                    }
                
            else if (flag == "tstation") {
                    std::string arrivalStation;
                    std::vector<TrainSchedule*> foundSchedules;
                    std::cout << "Zadaj prichodziu stanicu: ";
                    std::getline(std::cin, arrivalStation);
                    foundSchedules = trainScheduleList.find(arrivalStation, true);
                    for (const auto& schedule : foundSchedules) {
                        std::cout
                            << "\n"
                            << "Train ID: " << schedule->trainID << "\n"
                            << "Vychodzia Stanica: " << schedule->departureStation << "\n"
                            << "Prichodzia Stanica: " << schedule->arrivalStation << "\n"
                            << "Cas odjazdu: " << schedule->departureTime << "\n"
                            << "Cas prijazdu: " << schedule->arrivalTime << "\n" << std::endl;
                    }
                }
                    
                
            

            
                
                else {
                    std::cerr << "Invalid input format." << std::endl;
                }

            }

            
        

        //Teraz uz display funguje tak, ze si moze uzivatel zvolit, ktore stlpce chce vidiet, popripade nechat prazdne
        else if (command == "zobraz") {
            if (flag == "empty")

            {
                trainScheduleList.print();

            }
            else if (flag == "kategoria") {
                std::vector<std::string> columns;
                for (int i = 1; i <= 6 && i < splitCommand.size(); i++) {

                    columns.push_back(splitCommand[i]);
                }
                trainScheduleList.displayAllSchedules(columns);
            }
            else{
               std::cout << "Unknown command. Please try again." << std::endl; 
            }

            
        }
        else if (command == "exit") {
            //Ulozi mi data do suboru, v pripade ze chcem odist, nech nepridem o zmeny
            trainScheduleList.writeSchedulesToFile("train_schedule.txt");
            break;
        }
        else if (command == "trasa") {
            //Pre pracu s novym textovym suborom-trasa
            std::vector<TrainRoute> routes;

            // Read train routes from a file and add them to the 'routes' vector
            std::ifstream file("train_routes.txt");
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string stationName;
                TrainRoute route;
                while (std::getline(iss, stationName, ',')) {
                    addStationToRoute(route, stationName);
                }
                routes.push_back(route);
            }

            std::string arrivalStation;
            std::string departureStation;
            std::cout << "Zadaj vychodziu stanicu: ";
            std::getline(std::cin, departureStation);
            std::cout << "Zadaj prichodziu stanicu: ";
            std::getline(std::cin, arrivalStation);

            if (departureStation == "Praha") {
                displayTrainRoute(routes[0]);
            }
            else if (departureStation == "Brno" && arrivalStation == "Praha")
            {
                displayReverseTrainRoute(routes[0]);
            }
            else if (departureStation == "Brno" && arrivalStation == "Bratislava")
            {
                displayTrainRoute(routes[1]);
            }
            else if (departureStation == "Bratislava" && arrivalStation == "Brno")
            {
                displayReverseTrainRoute(routes[1]);
            }
            else if (departureStation == "Bratislava" && arrivalStation == "Kosice")
            {
                displayTrainRoute(routes[2]);
            }
            else if (departureStation == "Kosice" && arrivalStation == "Bratislava")
            {
                displayReverseTrainRoute(routes[2]);
            }
            else {
                std::cout << "Dana trasa neexistuje !";
            }
            
            /*
            displayTrainRoute(routes[1]);
            displayReverseTrainRoute(routes[1]);
            displayTrainRoute(routes[2]);
            */
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
