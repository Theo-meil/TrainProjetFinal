#ifndef urgenceControl_HPP
#define urgenceControl_HPP


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





// On a choisi de defnir ici le chemin versd les images pour le SFML.
constexpr const char* _PATH_IMG_ = "C:/Program Files/SFML/img/";


class Controleur {

    friend class Train;
    friend class Station;
    friend void afficherTrain(sf::RenderWindow& window, const Train& train, const Train& deuxiemeTrain, const std::vector<Station>& stations, bool afficherDeuxiemeTrain, Controleur& superviseur);
    friend void simulerTrain(Train& train, const std::vector<Station>& stations, bool avecDelai, Controleur& superviseur, sf::Time& tempsTotalArrete);
    friend size_t getProchaineStationIndex(const Train& train, const std::vector<Station>& stations);
	

private:
       
    Train& m_train1;
    Train& m_train2;
    sf::RenderWindow& m_window;
    bool enArret = false;
    bool arretUrgence;
    std::chrono::steady_clock::time_point demarrageTime;
	
	
public:
	
    Controleur(Train& train1, Train& train2, sf::RenderWindow& window);
    void verifierEtReagir(sf::Event event, sf::Clock& clock, sf::Time& tempsTotalArrete);
    void toggleArretUrgence(sf::Clock& clock, sf::Time& tempsTotalArrete);
    bool getArretUrgence() const;
    void arretDurgence();
    void updateLesPositions(Train& train1, Train& train2, sf::Time elapsedTime, const std::vector<Station>& stations, bool simulationDebut);
    sf::Clock demarrageClock;
    sf::RectangleShape boutonArret;
    sf::Text texteBouton;
    sf::Time tempsArrete;
    int getIdTrain1() const;
    int getIdTrain2() const;
    double getPositionTrain1() const;
    double getPositionTrain2() const;

};

#endif /
