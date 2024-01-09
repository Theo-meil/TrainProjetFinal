#include "train.hpp"
#include "station.hpp"
#include "urgenceControl.hpp"



// On crée une fonction afficher le texte des infos des trains
void drawText(sf::RenderWindow& window, sf::Text& text) {
    window.draw(text);
}

// Cette classe est assez longue et va regrouper pas mal de chose tel que l'affichage des stations, des métros, des informations sur les métros, etc...

void afficherTrain(sf::RenderWindow& window, const Train& Train1, const Train& Train2, const std::vector<Station>& stations, bool afficherTrain2, Controleur& superviseur) {

    // On initaialise le fond d'écran
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(std::string(_PATH_IMG_) + "FondFinal.jpeg")) {
        std::cerr << "Une Erreur est survenue , l'image de fond n'as pas charger verifier bien que vous l'avez telechargé" << std::endl;
    }


    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        float(windowSize.x) / textureSize.x,
        float(windowSize.y) / textureSize.y
    );
    window.draw(backgroundSprite);

    // On affiche les rails
    sf::RectangleShape outerTrackRect;
    outerTrackRect.setSize(sf::Vector2f(static_cast<float>(stations.back().position + 20), 200));//taille
    outerTrackRect.setFillColor(sf::Color::Transparent);
    outerTrackRect.setOutlineColor(sf::Color(0, 0, 0));//couleur
    outerTrackRect.setOutlineThickness(10);//largeur
    outerTrackRect.setPosition(0.0f, static_cast<float>(window.getSize().y) / 4.0f - 20.0f);//position
    window.draw(outerTrackRect);



    // On recupere la texture de la station
    sf::Texture stationTexture;
    if (!stationTexture.loadFromFile(std::string(_PATH_IMG_) + "StationFinal.png")) {
        std::cerr << "Une Erreur est survenue , l'image de la station n'as pas charger verifier bien que vous l'avez telechargé" << std::endl;
        return;
    }

    // On affiche chaques stations avec leur noms
    for (const auto& station : stations) {

        sf::Sprite stationSprite;
        stationSprite.setTexture(stationTexture);

        stationSprite.setScale(0.25f, 0.25f);//taille

        sf::Vector2u textureSize = stationTexture.getSize();
        stationSprite.setPosition(static_cast<float>(station.position-50), static_cast<float>(window.getSize().y) / 3.7f);//position
        window.draw(stationSprite);

        //police nom stations
        sf::Font fontStation;
        if (!fontStation.loadFromFile("C:/Windows/Fonts/arial.TTF")) {
            std::cerr << "Une Erreur est survenue , le chargement de la police n'as pas charger verifier bien que vous l'avez dans vos fichier source" << std::endl;
            return;
        }

        // texte station
        sf::Text stationText;
        stationText.setFont(fontStation);
        stationText.setString(station.nom);
        stationText.setCharacterSize(20);
        stationText.setFillColor(sf::Color::White);

        // On affiche le texte
        sf::FloatRect textRect = stationText.getLocalBounds();
        stationText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 4.0f); // origine
        stationText.setPosition(static_cast<float>(station.position), static_cast<float>(window.getSize().y) / 4.0f - 60.0f); //position
        window.draw(stationText);
    }



    
    const float ligneHaut = static_cast<float>(window.getSize().y) / 4.0f - 40.0f;//position rail du haut
    const float ligneBas = static_cast<float>(window.getSize().y) / 4 + 180; // position rail du bas





    // On recupere la texture du train
    sf::Texture train;
    if (!train.loadFromFile(std::string(_PATH_IMG_) + "TrainFinal.png")) {
        std::cerr << "Une Erreur est survenue , l'image du Train n'as pas charger verifier bien que vous l'avez telechargé" << std::endl;
        return;
    }
    sf::Sprite trainSprite;
    trainSprite.setTexture(train);

    trainSprite.setScale(0.1f, 0.1f);// taille

    float trainPosY = Train1.sensAller ? ligneHaut : ligneBas;//on aligne sur le rail
    trainSprite.setPosition(static_cast<float>(Train1.getPosition() - 20), trainPosY);//et on le met à sa position
    window.draw(trainSprite);// on affiche le train



    // Pareil pour le train 2
    sf::Sprite train2Sprite;
    train2Sprite.setTexture(train);
    train2Sprite.setScale(0.1f, 0.1f);
    float train2PosY = Train2.sensAller ? ligneHaut : ligneBas;
    train2Sprite.setPosition(static_cast<float>(Train2.getPosition() - 20), train2PosY);

    window.draw(train2Sprite);




    // Autre police d'écriture
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/calibrib.ttf")) {
        std::cerr << "Une Erreur est survenue , le chargement de la police n'as pas charger verifier bien que vous l'avez dans vos fichier source" << std::endl;
        return;
    }


    // Affichage infos train 1
    sf::Text train1Text;
    train1Text.setFont(font); // police
    train1Text.setCharacterSize(20); // taille
    train1Text.setFillColor(sf::Color::White); // couleur

    // affichage de toutes les infos
    train1Text.setString(std::string("Train 1 (") + (Train1.estALaStation() ? stations[getProchaineStationIndex(Train1, stations)].nom : "En déplacement") + (") :") +
        "\n Passagers Entrés : " + std::to_string(Train1.getPassagersEntrants()) +
        "\n Passagers Sorties : " + std::to_string(Train1.getPassagersSortants()) +
        "\n Passagers à bord : " + std::to_string(Train1.getNombrePassagers())) ;

    // Si le train n'a plus de place on affiche le nb de personnes sur le quai
    if (Train1.getNombrePassagers() < 200) {
        train1Text.setString(train1Text.getString() +
            "\n Passagers sur le quai suivant: " + std::to_string(stations[getProchaineStationIndex(Train1, stations)].gestionPassagers()));
    }

    train1Text.setPosition(350, 500);//position


    // pareil pour le train 2
    sf::Text train2Text;
    train2Text.setFont(font);
    train2Text.setCharacterSize(20);
    train2Text.setFillColor(sf::Color::White);
    train2Text.setString(std::string(" Train 2 (") + (Train2.estALaStation() ? stations[getProchaineStationIndex(Train2, stations)].nom : "En déplacement") + (") :") +
        "\n Passagers Entrés : " + std::to_string(Train2.getPassagersEntrants()) +
        "\n Passagers Sortis : " + std::to_string(Train2.getPassagersSortants()) +
        "\n Passagers à bord : " + std::to_string(Train2.getNombrePassagers()));

    if (Train2.getNombrePassagers() < 200) {
        train2Text.setString(train2Text.getString() +
            "\n Passagers sur le quai suivant: " + std::to_string(stations[getProchaineStationIndex(Train2, stations)].gestionPassagers()));
    }

    train2Text.setPosition(1050, 500);


    sf::FloatRect train1Bounds = train1Text.getLocalBounds();
    sf::FloatRect train2Bounds = train2Text.getLocalBounds();

    // On affiche les textes avec la fonction
    drawText(window, train1Text);
    drawText(window, train2Text);



    // Affichage bouton d'urgence
    superviseur.boutonArret.setSize(sf::Vector2f(500, 50));
    superviseur.boutonArret.setPosition(650, 100);
     superviseur.boutonArret.setFillColor(sf::Color::Red);
    //police du texte
    sf::Font font_stop;
    if (!font_stop.loadFromFile("C:/Windows/Fonts/ARIAL.ttf")) {
        std::cerr << "Une Erreur est survenue , le chargement de la police n'as pas charger verifier bien que vous l'avez dans vos fichier source" << std::endl;
        return;
    }
    superviseur.texteBouton.setFont(font);
    superviseur.texteBouton.setString("ARRET MANUEL D'URGENCE");//texte a afficher
    superviseur.texteBouton.setCharacterSize(24);//taille
    superviseur.texteBouton.setFillColor(sf::Color::White);//couleur

    sf::FloatRect textRect = superviseur.texteBouton.getLocalBounds(); // On récupère la limite du texte

    superviseur.texteBouton.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    superviseur.texteBouton.setPosition(850 + 50, 100 + 25); //position du texte au centre 
    //on affiche le bouton et le texte avec la fonction
    window.draw(superviseur.boutonArret);
    window.draw(superviseur.texteBouton);

    window.display();//on affiche tout
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // init des 2 trains
    Train train1aff;
    train1aff.initialiser(1800);

    Train train2aff;
    train2aff.initialiser(1800);

    bool arretUrgence = false;

    // On init notre tableau contenant les stations
    std::vector<Station> stations = {Station("Business Day", 200),Station("Burj Khalifa", 400),Station("Financial Centre", 600),
        Station("Emirate Tower", 800),Station("World Trade Centre", 1000),Station("Al Jafiliya", 1200),Station("Al Karama", 1400),
        Station("Bur Juman", 1600),Station("Union", 1800),
    };



    // horloge et temps d'arret
    sf::Clock clock;
    sf::Time tempsTotalArrete;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Metro Dubai"); //creation de la fenetre
    Controleur superviseur(train1aff, train2aff, window);//on lance le control

    superviseur.demarrageClock.restart();//reset du temps
    //on lance les deux train en parallèle
    std::thread trainThread1(simulerTrain, std::ref(train1aff), std::cref(stations), false, std::ref(superviseur), std::ref(tempsTotalArrete));
    std::thread trainThread2(simulerTrain, std::ref(train2aff), std::cref(stations), true, std::ref(superviseur), std::ref(tempsTotalArrete));

    //start des trains
    train1aff.byeStation();
    train2aff.byeStation();
    bool simulationDebut = true;//depart

    // On ouvre la fenetre SFML
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // On appelle le superviseur pour les boutons et le temps
            superviseur.verifierEtReagir(event, clock, tempsTotalArrete);


        }
        sf::Time elapsedTime = clock.restart(); 
        //interactions avec la station
        for (auto& station : stations) {

            //on recup les prochaine stations
            size_t IndexStationTrain1 = getProchaineStationIndex(train1aff, stations);
            size_t IndexStationTrain2 = getProchaineStationIndex(train2aff, stations);

            // On vérifie si chaque est à une station
            if (train1aff.estALaStation()) {
                stations[IndexStationTrain1].signalerArretTrain();
            }
            else {
                stations[IndexStationTrain1].signalerGoTrain();
            }

            if (train2aff.estALaStation()) {
                stations[IndexStationTrain2].signalerArretTrain();
            }
            else {
                stations[IndexStationTrain2].signalerGoTrain();
            }
        }

        // Et On met à jour les positions des trains
        superviseur.updateLesPositions(train1aff, train2aff, elapsedTime, stations, simulationDebut);

        //affichage des trains
        if (!superviseur.getArretUrgence()) {
            afficherTrain(window, train1aff, train2aff, stations, true, superviseur);
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    trainThread1.join();
    trainThread2.join();

    return 0;
}