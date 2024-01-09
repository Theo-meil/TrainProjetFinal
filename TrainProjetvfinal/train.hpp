#ifndef TRAIN_HPP
#define TRAIN_HPP
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


class Train {
    friend class Controleur;
	friend class Station;
	
    friend void simulerTrain(Train& train, const std::vector<Station>& stations, bool avecDelai, Controleur& superviseur, sf::Time& tempsTotalArrete);
    friend size_t getProchaineStationIndex(const Train& train, const std::vector<Station>& stations);
    friend void afficherTrain(sf::RenderWindow& window, const Train& train, const Train& deuxiemeTrain, const std::vector<Station>& stations, bool afficherDeuxiemeTrain, Controleur& superviseur);
    friend double getProchaineStationPosition(const Train& train, const std::vector<Station>& stations);
private:
    double position;
    double distanceEntreStations;
    double vitesse = 0;
    const double vitesseMax = 10.0;
    const double vitesseArret = 0.0;
    const double dureeArret = 1.0;
    const int capaciteMax = 200;
    int nbPassagers;
    sf::Clock stationClock;
    bool enArret;
    int passagersEntrants = 0;
    int passagersSortants = 0;
    bool sensAller; 
    bool arretUrgence = false;
    bool freinageProgressif = false;
    double positionRamePrecedente;
    int id = rand(); 

public:
    Train();
    int getID() const;
    bool estALaStation() const;
    void initialiser(double distanceEntreStations);
    void byeStation();
    void suivreRame(sf::Time elapsedTime, const std::vector<Station>& stations, double positionPrecedente, Controleur& superviseur);
    void arretEnStation();
    void gestionPassagers(int passagersQuai);
    void arretTotal();
    void reprisePostArretUrgence();
    int getPassagersEntrants() const;
    int getPassagersSortants() const;
    double getVitesse() const;
    double getPosition() const;
    int getCapaciteMaximale() const;
    int getNombrePassagers() const;
    double getDureeArret() const;
    void accelerer(double acceleration);
    double fonctionDeplacement(double t) const;
};
#endif 
