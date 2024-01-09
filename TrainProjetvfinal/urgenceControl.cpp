

#include "train.hpp"
#include "station.hpp"
#include "urgenceControl.hpp"




// on initialise notre constructeur
Controleur::Controleur(Train& train1, Train& train2, sf::RenderWindow& window)
    : m_train1(train1), m_train2(train2), m_window(window),
    enArret(false), arretUrgence(false) {
    demarrageTime = std::chrono::steady_clock::now();
}



// On va ensuite créer une fonction pour l'arret d'urgence quand on appuie sur le bouton stop
void Controleur::verifierEtReagir(sf::Event event, sf::Clock& clock, sf::Time& tempTotalArret) {
	
    // On vérifie d'abord si un clic de souris a eu lieu.
    if (event.type == sf::Event::MouseButtonPressed) {
        // On vérifie aussi si le bouton cliqué est le bouton gauche de la souris.
        if (event.mouseButton.button == sf::Mouse::Left) {
			// dans ce cas on obtient la position actuelle de la souris.
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
			
            // On vérifie aussi si la position de la souris est sur le bouton d'arrêt d'urgence.
            if (boutonArret.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                std::cout << "On declenche l'arret d'urgence" << std::endl;

				//On uilise la fonction d'apres pour activer ou désactiver l'arrêt d'urgence en fonction de l'état actuel
                toggleArretUrgence(clock, tempTotalArret);
            }
        }
    }
}

// Voici la méthode pour déclencher l'arret d'urgence (on arrete juste les deux Trains et on passe l'arret a True)
void Controleur::arretDurgence() {
    m_train1.arretTotal();
    m_train2.arretTotal();
    arretUrgence = true;
}

// Methode pour savoir quand l'arret d'urgence est activé
bool Controleur::getArretUrgence() const {
    return arretUrgence;
}

// On crée une methode qui régit les conséquences de l'arret d'urgence
void Controleur::toggleArretUrgence(sf::Clock& clock, sf::Time& tempsTotalArrete) {
    arretUrgence = !arretUrgence;

	// Si il y a arret d'urgence on arrete les deux Trains et prend en compte le temps d'arret
    if (arretUrgence) {
        tempsTotalArrete += clock.getElapsedTime();
        m_train1.arretTotal();
        m_train2.arretTotal();
    }
    // Quand il n'y a plus besoin d'arret d urgence les deux trains repartent faire leurs cycles
    else {
        m_train1.byeStation();
        m_train2.byeStation();
    }
}



// Nous avons maintenant besoin de mettre a jour la position des Trains
void Controleur::updateLesPositions(Train& train1, Train& train2, sf::Time elapsedTime, const std::vector<Station>& stations, bool simulationDebut) {
	//On attrape leurs positions actuelles
    double positionTrain1 = train1.getPosition();
    double positionTrain2 = train2.getPosition();

    // Puis on fait avancer les trains le long des rames
    train1.suivreRame(elapsedTime, stations, positionTrain2, *this); 
    train2.suivreRame(elapsedTime, stations, positionTrain1, *this); 
}


// On garde en mémoire l'Id des Trains
int Controleur::getIdTrain1() const {
    return m_train1.getID();
}
int Controleur::getIdTrain2() const {
    return m_train2.getID();
}

// On garde en mémoire la position des Trains
double Controleur::getPositionTrain1() const {
    return m_train1.getPosition();
}
double Controleur::getPositionTrain2() const {
    return m_train2.getPosition();
}