#pragma once


//Importovanie classy pre vlaky, aby som mohol vyuzit jej stavbu
#include "TrainSchedule.h"

//Kvoli displayovaniu vybranych stlpcov, neskor aj na find ktory vyhladava podla odchozi a prichozi stanice
#include <vector>

class DoubleLinkedList {
private:
    //hlava - zaciatok , tail - koniec
    TrainSchedule* head;
    TrainSchedule* tail;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}


    //Metody:
    //Na pridanie spoja
    void addTrainSchedule(const TrainSchedule& newSchedule);
    //Odobranie spoja podla ID
    void removeTrainSchedule(const std::string& trainID);
    //Najdenie spoja - overloadovanie funkcie find, nech viem pekne pouzit tu istu funkciu na ine sposoby
    TrainSchedule* findTrainSchedule(const std::string& trainID) const;
    std::vector<TrainSchedule*> find(const std::string& departureStation, bool flag) const;
    std::vector<TrainSchedule*> find(const std::string& departureStation, const std::string& arrivalStation) const;    //Vypisanie vsetky spojov
    void displayAllSchedules(const std::vector<std::string>& columns) const;
    //Nacitanie dat zo suboru do linked listu
    void loadSchedulesFromFile(const std::string& filename);
    //vpisovanie Linked Listu naspat do text suboru
    void writeSchedulesToFile(const std::string& filename) const;

    void print();
    //Nezabudnut destruktor !
    ~DoubleLinkedList();
};
