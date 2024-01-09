#include "train.hpp"
#include "station.hpp"
#include "urgenceControl.hpp"

//On initialise notre constructeur
Station::Station(const std::string& nom, double position)
    : nom(nom), position(position), TrainPresence(false) {
}

//On implemente la présence du Train dans la station
bool Station::trainEstPresent() const {
    return TrainPresence; //On retourne l'état de l'indicateur de présence de métro
}

//On implemente l'arrivée a la station du Train
void Station::signalerArretTrain() {
    TrainPresence = true; //On met à jour l'indicateur de présence de métro à vrai
}

//On implemente le depart de la station du Train
void Station::signalerGoTrain() {
    TrainPresence = false;
}

//On simule l'arivée de potentiel passager sur le quai de la station
int Station::gestionPassagers() const {
    //On génère un nombre aléatoire de maximun 200 passagers
    return rand() % 100; 
}

// On cherche la positiion de la prochaine station 

double getProchaineStationPosition(const Train& train, const std::vector<Station>& stations) {

    size_t stationIndex = getProchaineStationIndex(train, stations);

    return stations[stationIndex].position;
}


// On cherche la prochaine station ou le train va devoir déposer des passagers
size_t getProchaineStationIndex(const Train& train, const std::vector<Station>& stations) {
    size_t stationIndex = 0;

    if (train.sensAller) {

        // Quand on part de la premiere station il cherche la station la plus proche a droite .
        for (size_t i = 0; i < stations.size() - 1; ++i) {
            if (train.getPosition() >= stations[i].position && train.getPosition() < stations[i + 1].position) {
                stationIndex = i;
                break;
            }
        }
    }
    else {

        // Et quand on part du terminus il cherche la stattion la plus proiche de lui a gauche.
        for (size_t i = stations.size() - 1; i > 0; --i) {
            if (train.getPosition() <= stations[i].position && train.getPosition() > stations[i - 1].position) {
                stationIndex = i;
                break;
            }
        }
    }

    // Maintenant quand le train est soit au terminus soit au depart alors il tourne pour repartir dans sa course
    if (train.sensAller && train.getPosition() >= stations.back().position) {
        stationIndex = stations.size() - 1;
    }
    if (!train.sensAller && train.getPosition() <= stations.front().position) {
        stationIndex = 0;
    }

    return stationIndex;// on retourne a chaque fois l' Index de la station la plus proche
}