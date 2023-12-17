#pragma once
#include <string>


#define TRAIN_SCHEDULE_H

#include <string>

struct TrainSchedule {
    std::string trainID;
    std::string departureStation;
    std::string arrivalStation;
    // Pouzivam zatial cas ako string, ale dalo by sa to implementovat aj specifickejsie ...
    std::string departureTime;
    std::string arrivalTime;

    //implementace double linked listu
    TrainSchedule* next;
    TrainSchedule* prev;

    //Konstruktor
    TrainSchedule(std::string id, std::string depStation, std::string arrStation,
        std::string depTime, std::string arrTime)
        : trainID(id), departureStation(depStation), arrivalStation(arrStation),
        departureTime(depTime), arrivalTime(arrTime), next(nullptr), prev(nullptr) {}
};

