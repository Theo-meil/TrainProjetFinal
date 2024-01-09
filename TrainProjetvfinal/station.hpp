
#ifndef STATION_HPP
#define STATION_HPP


#include "train.hpp"
#include "station.hpp"
#include "urgenceControl.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <cstdlib>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <map>
#include <mutex>
#include <ctime>


class Station {
    friend class Train;
    friend class Controleur;
    friend size_t getProchaineStationIndex(const Train& train, const std::vector<Station>& stations);
    friend double getProchaineStationPosition(const Train& train, const std::vector<Station>& stations);
    friend void afficherTrain(sf::RenderWindow& window, const Train& train, const Train& deuxiemeTrain, const std::vector<Station>& stations, bool afficherDeuxiemeTrain, Controleur& superviseur);
    friend void simulerTrain(Train& train, const std::vector<Station>& stations, bool avecDelai, Controleur& superviseur, sf::Time& tempsTotalArrete);
   
	
private:
    std::string nom;
    double position;
    bool TrainPresence;

public:
    Station(const std::string& nom, double position);
    bool trainEstPresent() const;
    void signalerArretTrain();
    void signalerGoTrain();
    int gestionPassagers() const;
};

#endif 
