Modélisation simplifiées du VAL

En quoi consitait ce projet:


Notre projet de programmation en C++ vise à modéliser un système de transport automatisé de type "VAL" (Véhicule Automatique Léger).
Le but est de simuler la gestion des rames de métro, leur circulation sur un circuit fermé, la gestion de leur accélération, décélération, et la maintenance d'une distance de sécurité entre les rames. 
Le système comprend également un superviseur qui reçoit des informations continues de chaque rame et peut initier des arrêts d'urgence. 

Chaque station gère l'afflux de passagers, et le projet requiert la modélisation de ces interactions.
Le projet met l'accent sur l'autonomie des différents acteurs (rame, station, superviseur) et leur synchronisation. 
Nous avions la liberté d'implémenter le projet en utilisant des threads ou des programmes indépendants communiquant via des sockets. Le projet inclut également un aspect graphique, avec la représentation du réseau et la position des rames. 
Les outils et bibliothèques recommandés incluent CMake, git, SFML, et d'autres relatifs au réseau et au threading.
En résumé, le projet consiste à créer un modèle de transport automatisé en C++, en mettant l'accent sur la synchronisation et l'interaction entre les différents composants du système.

Voici la vidéo de notre projet : https://youtu.be/TnQpI-eH3_s

Nous avons fait le choix de beaucoup commenter notre code pour qu'une personne quelconque puisse le comprendre sans trop de problème.

Pour ce qui est des images nous avons glisser dans les dossier un fichier imgNecessaires contenant les images nécessaire pour pouvoir lancer notre programme il suffira juste de les glisser à cette adresse : C:\Program Files\SFML\img

Les problemes rencontrées:

    - le temp : 
    en effet nous avons eu énormément de mal a gérer notre temps a cause des partiels et des vacances d'hiver qui étaient en même temps. Et nous nous en excusons d'avance pour ces 2jours de retards.

    - le manque de connaissance: 
    Nous sommes tout deux des élèves en difficultés avec cette matières et nous avons fait le choix de ne pas utilisés d’outils comme chat GPT par exemple 
    et a cause du manque de connaissances nous avons eu énormément de mal dans la confection de notre projet.

    - Les erreurs:  Tout au long de notre projets nous avons rencontrées énormément d’erreur qui nous on stoppé comme la mise en place d ‘un temp d’attente,
    d’instaurer une vitesse a nos wagons et enfin d’y injecter le SFML .

    -les distances des sécurités entre les wagons:
    En effets vous verez que nous n'avons malheuresement pas réussi a y implémenter les distances d'arret entre les wagons sans que les SFML ne marche pas.

    -mettre plus que 2 Trains : 
    Par conséquent le fait qu'il n'y ai pas de distances de sécurités d'urgences nous n'avaons pas pus mettre plus que 2 wagons.

Bon visionnage et lecture de notre code!


                                            Nous vous remercions de nous avoir laisser vous présenter ce code: Ruet Arthur / Theo Meilliez.



