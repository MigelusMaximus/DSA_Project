
//Toto je implementacia hlavickoveho suboru Double Linked List



#include "DoubleLinkedList.h"
#include <iostream>

//Potrebujem citat data zo suboru, preto pouzijem tieto libraries
#include <fstream>
#include <sstream>



/*
* Metoda na pridanie spoja
* Dolezite spravne nastavit pointre, kedze pridavame spoj
*/
void DoubleLinkedList::addTrainSchedule(const TrainSchedule& newSchedule) {
    TrainSchedule* newNode = new TrainSchedule(newSchedule);
    if (!head) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

/*
Metoda na odstranenie spoja
-doelzite sa spravne zbavit aj vsetkych ukazatelov, kedze ide o double linked list
- pre pracu s pointrami pouzivam ->
*/

void DoubleLinkedList::removeTrainSchedule(const std::string& trainID) {
    TrainSchedule* current = head;
    while (current) {
        if (current->trainID == trainID) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            delete current;
            return;
        }
        current = current->next;
    }
}


//Metoda na najdenie spoja
TrainSchedule* DoubleLinkedList::findTrainSchedule(const std::string& trainID) const {
    TrainSchedule* current = head;
    while (current) {
        if (current->trainID == trainID) return current;
        current = current->next;
    }
    return nullptr;
}




//Zobrazenie vsetkych spojov
void DoubleLinkedList::displayAllSchedules(const std::vector<std::string>& columns) const {
    TrainSchedule* current = head;
    while (current) {
        for (const std::string& col : columns) {
            if (col == "ID") {
                std::cout << current->trainID << " ";
            }
            else if (col == "departureStation") {
                std::cout << current->departureStation << " ";
            }
            else if (col == "arrivalStation") {
                std::cout << current->arrivalStation << " ";
            }
            else if (col == "departureTime") {
                std::cout << current->departureTime << " ";
            }
            else if (col == "arrivalTime") {
                std::cout << current->arrivalTime << " ";
            }
            // Add else if blocks for other columns as necessary
        }
        std::cout << std::endl; // Finish line after all columns
        current = current->next; // Move to the next node
    }
}


//Metoda ktora je na displaynutie/printnutie vsetkych spjov
void DoubleLinkedList::print() {
    TrainSchedule* current = head;

    while (current != nullptr) {

        std::cout
            << "\n"
            << "Train ID: " << current->trainID << "\n"
            << "Departure Station: " << current->departureStation << "\n"
            << "Arrival Station: " << current->arrivalStation << "\n"
            << "Departure Time: " << current->departureTime << "\n"
            << "Arrival Time: " << current->arrivalTime << "\n" << std::endl;

        current = current->next;
    }
}


//Metoda ktora mi najde vsetky spoje, ktore maju danu stanicu od-do
std::vector<TrainSchedule*> DoubleLinkedList::find(const std::string& departureStation, const std::string& arrivalStation) const {
    std::vector<TrainSchedule*> foundSchedules;
    TrainSchedule* current = head;

    while (current != nullptr) {
        if (current->departureStation == departureStation && current->arrivalStation == arrivalStation) {
            foundSchedules.push_back(current);
        }
        current = current->next;
    }

    return foundSchedules;
}

//Metoda ktora vdaka bool hodnote pre man bude riesit bud vsetky spoje odchodzie zo stanice, alebo prichodzie do stanice
std::vector<TrainSchedule*> DoubleLinkedList::find(const std::string& station,bool flag) const {
    std::vector<TrainSchedule*> foundSchedules;
    TrainSchedule* current = head;

    while (current != nullptr) {
        if (flag) {
            if (current->departureStation == station) {
                foundSchedules.push_back(current);
            }
            
        }
        else {
            if (current->arrivalStation == station) {
                foundSchedules.push_back(current);
            }
        }

        current = current->next;
    }

    return foundSchedules;
}


//Metoda na nacitanie dat z textaku
void DoubleLinkedList::loadSchedulesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string trainID, departureStation, arrivalStation, departureTime, arrivalTime;

        // Pouzivam zatial cas ako string, ale dalo by sa to implementovat aj specifickejsie ...
        //Aktualny format suboru je CSV - coma separated values, teda data oddelene ciarkou
        //V suboru pouzijem aj header file pre prehladnost.
        if (getline(iss, trainID, ',') &&
            getline(iss, departureStation, ',') &&
            getline(iss, arrivalStation, ',') &&
            getline(iss, departureTime, ',') &&
            getline(iss, arrivalTime)) {
            
            TrainSchedule schedule(trainID, departureStation, arrivalStation, departureTime, arrivalTime);
            addTrainSchedule(schedule);
        }
    }

    file.close();
}


//Metoda na vypis Linked Listu naspat do suboru
void DoubleLinkedList::writeSchedulesToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    TrainSchedule* current = head;
    while (current != nullptr) {
        file << current->trainID << ","
            << current->departureStation << ","
            << current->arrivalStation << ","
            << current->departureTime << ","
            << current->arrivalTime << std::endl;
        current = current->next;
    }

    file.close();
}


/*
Destruktor pre double linked list
Zacneme od hlavy listu
Postupne si nacitame dalsi "uzol"
Vzdy zmazeme aktualny a skocime dalej

*/
DoubleLinkedList::~DoubleLinkedList() {
    TrainSchedule* current = head;
    while (current) {
        TrainSchedule* next = current->next;
        delete current;
        current = next;
    }
}
