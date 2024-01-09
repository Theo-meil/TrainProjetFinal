#include "train.hpp"
#include "station.hpp"
#include "urgenceControl.hpp"


//On intialise le constrcuteur 
Train::Train()
    : position(0.0), distanceEntreStations(0.0), vitesse(0.0),vitesseMax(10.0), vitesseArret(0.0), dureeArret(1.0),capaciteMax(200), nbPassagers(0), enArret(false),sensAller(true), positionRamePrecedente(0.0), id(rand()) {
}

//Le train accelere jusqu'a Sa vitesse maximun autorisée
void Train::byeStation() {
    accelerer(vitesseMax);
    enArret = false;
}


//On vérifie si le Train est station
bool Train::estALaStation() const {
    return enArret;
}

//On chgerche la distance exacte qui separe le Train en station a la prochaine station
void Train::initialiser(double distanceEntreStations) {
    this->distanceEntreStations = distanceEntreStations;
}

//On garde en mémoire l'id du Train
int Train::getID() const {
    return id;
}



//Voici une methode qui sert au Train a suivre les lignes de rames
void Train::suivreRame(sf::Time elapsedTime, const std::vector<Station>& stations, double positionPrecedente, Controleur& superviseur)
{
    this->positionRamePrecedente = positionPrecedente; //la position de la rame traversée est l'ancienne position du Train
    double distanceAvecPrecedente = std::abs(position - positionRamePrecedente); //On calcule la distance entre la position actuelle du métro et sa position précédente.

    // on s'occupe du comportement du Train quand il est en marche
    if (!enArret) { 
        double deplacement = (vitesse * elapsedTime.asSeconds()) / 4.0; //la distance parcourue par rapport au temps écoulé
        bool doitSArreter = false; //On initialise l'obligation d'arret du Train la prochaine station        

        //Tant que le Train ne s'apporche pas assez de la station alors il se déplace normalement
        if (sensAller) { //Si le Train est dans le sens aller 
            position += deplacement;
            if (position >= distanceEntreStations) {
                position = distanceEntreStations;
                doitSArreter = true;
            }
        }
        else { // si il se deplace dans le sens retour
            position -= deplacement;
            if (position <= 0.0) {
                position = 0.0;
                doitSArreter = true;
            }
        }

        double prochaineStationPos = getProchaineStationPosition(*this, stations); //On prend la position de la station suivante en compte
        double distanceProchaineStation = std::abs(prochaineStationPos - position); //Et on calcule la distance qui separe le Train de cette station

        //On créer une suite de if qui permet au Train de freiner a l'apporche de la prochaine station (les données on été trouvée à l'oeil)
        if (distanceProchaineStation > 100 && !freinageProgressif) {
            vitesse = 1.5;
            freinageProgressif = true;
            if (distanceProchaineStation > 125) {
                vitesse = 1.25;
                if (distanceProchaineStation > 150) {
                    vitesse = 1;
                }
            }
        }
        freinageProgressif = false;// si le Train ne s'approche pas encore assez de la station alors il n'a pas besoin de freiner        

        //Si il y a une erreur et que le train devait s'arreter et qu'il ne sait pas arreter alors on l'arrete a la main (nous avons cette erreurs pour la premiere station.
        if (doitSArreter && !enArret) {
            arretEnStation();
        }
    }
}

//On gere l'acceleration progressive du Train jusqu'a ce qu'il atteigne ca vitesse max
void Train::accelerer(double acceleration) {
    vitesse += acceleration;
    if (vitesse > vitesseMax) {
        vitesse = vitesseMax;
    }
}




//Voici une méthode qui va gerer ce qui se passe quand le Train sera en station
void Train::arretEnStation() {
    if (!enArret) { 
        vitesse = 0; //On arrete le Train
        enArret = true; //Le Train est compris comme arreté
        stationClock.restart();    //On mesure le temp de l'arret du Train en Station

        //On cherche la duree d'arretfinal qui prend en compte le temp d'arret du temp , le temps de monté d'un passager et de descente.
        double DureeMonterPassagers = 0.02;
        double dureeTotalArret = dureeArret + (passagersEntrants + passagersSortants) * DureeMonterPassagers;

        //Et le Train attend la durée finale calculé et on l'affiche
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dureeTotalArret * 500)));
        std::cout << "Temps passe a la station : " << dureeTotalArret << " secondes" << std::endl;
    }
}





//On gere la monter et la descente des passagers
void Train::gestionPassagers(int passagersQuai) {

    //On fait varié aléatoirement le nombre de passagers entrant et sortant
    int variabilite = (rand() % 20 + 1) * (id % 15);
    passagersSortants = std::min(nbPassagers, rand() % (nbPassagers + 1) + variabilite / 20);
    passagersEntrants = std::min(capaciteMax - nbPassagers, passagersQuai) + variabilite / 25;
    nbPassagers += passagersEntrants - passagersSortants;
    //Sans oublier qu'il y a une capacité max de personne
    if (nbPassagers > capaciteMax) nbPassagers = capaciteMax;
    if (nbPassagers < 0) nbPassagers = 0;
}



//On permet au train de s'arreter a n'impore quel moment
void Train::arretTotal() {
    enArret = true;
    vitesse = vitesseArret;
    arretUrgence = true;
}

//On lui permet par conséquent de redémarrer apres un arret quelconque
void Train::reprisePostArretUrgence() {
    if (arretUrgence) {
        //on relance l'acceleration progressive du métro
        enArret = false;
        accelerer(vitesseMax);
        arretUrgence = false;
    }
}


//On garde mémoire pour la suite toute les informations nécessaires.
int Train::getPassagersEntrants() const {
    return passagersEntrants;
}

int Train::getPassagersSortants() const {
    return passagersSortants;
}

double Train::getVitesse() const {
    return vitesse;
}

double Train::getPosition() const {
    return position;
}

int Train::getCapaciteMaximale() const {
    return capaciteMax;
}

int Train::getNombrePassagers() const {
    return nbPassagers;
}

double Train::getDureeArret() const {
    return dureeArret;
}


//On créer le déplacement linéaire du Train sur les rails
double Train::fonctionDeplacement(double t) const {
    return 2 * t * t * t - 3 * t * t + 1;
}


 // On simule maintenant le déplacement du Train Final
void simulerTrain(Train& train, const std::vector<Station>& stations, bool avecDelai, Controleur& superviseur, sf::Time& tempsTotalArrete) {

    // On fait attendre le dexuième train 30 secondes
    if (avecDelai) {
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
    bool simulationDebut = true; // pour savoir si la simulation a commencé ou non pour la gestion d'erreur
    size_t stationIndex = 0;
    bool estArrete = false; // Pour savoir si le train est a l arret ou non
    bool aller = true; // POur savoir le sens du train
    sf::Clock clock;
    sf::Time tempsArrete; // On aura besoin du calculde temp d'arret

    while (true) {

        // Quand nous ne sommes pas en arret manuel
        if (!superviseur.getArretUrgence()) {

            // on melange le temp ecoulé avec le temp d'arret pour ne pas qu'il trouble les données de l'horloge
            sf::Time tempsTotalEcoulé = clock.getElapsedTime() - tempsTotalArrete;

            // On update les temps d'arret a chaque fois en les renitialisants
            if (estArrete) {
                tempsArrete += clock.restart();
                estArrete = false;
            }

            // Tant qu'il n'est pas arreter alors pas besoin de modifier les temps
            if (!train.enArret) {
                sf::Time tempsEcoulé = clock.getElapsedTime(); 

                // il parcours donc la ligne en suivant le temps écouler 
                train.suivreRame(tempsEcoulé, stations, static_cast<double>(stationIndex), superviseur);
                
                //On cherche a savori quand il atteindra la prochaine station pour l'arreter au bon moment
                double nextStationPos = stations[stationIndex].position;
                if ((aller && train.getPosition() >= nextStationPos) ||
                    (!aller && train.getPosition() <= nextStationPos)) {

                    train.arretEnStation();

                    // Quand nous arriverons au terminus alors on fera descendre tout le monde puis on teleportera le train dans le sens retour et on redemarre tout .
                    if ((stationIndex == stations.size() - 1 && aller) ||
                        (stationIndex == 0 && !aller)) {
                        train.passagersSortants = train.nbPassagers;
                        train.nbPassagers = 0;
                        train.passagersEntrants = 0;
                        std::cout << "Bienvenue au Terminus le la Ligne ,nous esperons que votre trajet etait convenable, Au revoir !!\n";
                        aller = !aller; 
                        stationIndex = aller ? 0 : stations.size() - 1; 
                        clock.restart(); 
                        tempsArrete = sf::Time::Zero; 
                    }
                    else {
                        //Sinon on gere normalement le flux de passagers
                        train.gestionPassagers(stations[stationIndex].gestionPassagers());
                        stationIndex += (aller) ? 1 : -1;
                    }
                    train.sensAller = aller; // Pour que quand le Train au sens retour sera au teminus qu'il se re teleporte 
                }
            }

            // On redemarre tout quand le Train est à l'arret
            if (train.enArret && tempsTotalEcoulé.asSeconds() - tempsArrete.asSeconds() >= train.getDureeArret()) {
                train.byeStation(); // Si il est en station alors qu il la quitte jusqu'a la prochaine
                clock.restart();
                tempsArrete = sf::Time::Zero;
            }
        }
        else {
            // Mais si nous somme en arret manuel d'urgence alors on prendra en compte le temp d'arret
            if (!estArrete) {
                tempsArrete = clock.getElapsedTime();
                estArrete = true; 
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // le temps de l'arret d'urgence.
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // On temporise pour pas que la boucle tourne tout le temps.
    }
}