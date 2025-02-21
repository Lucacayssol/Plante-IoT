// Définition des broches : ces premières lignes de code permettent de dire à l'arduino où on a branché quoi.
sonst int ledRouge = 3;            //Broche de la led de sous alimentation
const int pinCapteurHumidite = A0; // Broche du capteur d'humidité
const int pinRelais = 4;           // Broche contrôlant le relais de la pompe
const int pinPowerSensor = 2;      // Broche pour contrôler l'alimentation du capteur
// Paramètres à ajuster lors de vos tests
const int seuilHumidite = 800;     // Ajustez cette valeur en fonction de votre tests et des besoins de vos plantes. 
//Conseil : plantez le capteur dans la terre sèche, et lisez la valeur sur le moniteur série. 
//Puis arrosez comme vous voudriez que la plante le soit et mesurez la valeur à l'issue de l'opération
const int Tempspompe = 3000;       // Temps de fonctionnement de la pompe (en millisecondes). Ici elle fonctionne pendant 3 secondes
int NombreArrosage = 0;     // nombre d'arrosage effectuée dans la journée
int Temps = 0;             // temps écoulés dans les dernières 24 heures en heures
int Temps72 = 0;
int NombreArrosage72 = 0;

void setup() {
  // On va saisir ici le code qui ne va être répété qu'une fois
  pinMode(pinRelais, OUTPUT);      // Définit la broche du relais comme sortie
  pinMode(pinPowerSensor, OUTPUT); // Définit la broche de puissance du capteur comme sortie
  digitalWrite(pinRelais, LOW);    // S'assure qu'on commence avec le relais désactivé au démarrage
  digitalWrite(pinPowerSensor, LOW); // S'assurer qu'on commence avec le capteur d'humidité désactivé au démarrage
  Serial.begin(9600);   // Cette commande initialise le port série qui permet à l'Arduino d'envoyer et de recevoir des informations à l'ordinateur
}
void loop() {
  // On met ici le code qui va tourner en boucle pour assurer le suivi de l'humidité au pied de la plante
 if (NombreArrosage < 3) { //Vérifie que l'on a pas trop arrosée pour prévenir une inondation
     digitalWrite(pinPowerSensor, HIGH); // Active l'alimentation du capteur
    delay(1000); // Laisse le temps au capteur de s'initialiser et stabiliser
 
  int valeurHumidite = analogRead(pinCapteurHumidite); // Lit la valeur du capteur d'humidité
  Serial.print("Humidité du sol: ");// Affiche sur le moniteur série la phrase "humidité du sol"
  Serial.println(valeurHumidite);// Inscrit cette valeur d'humidité du sol sur le moniteur série
  digitalWrite(pinPowerSensor, LOW); // Désactive l'alimentation du capteur pour prévenir son oxydation au fil du temps
        if (valeurHumidite > seuilHumidite ) { // Si l'humidité lue par le capteur est inférieure à celle du seuil que nous avons déterminé alors...
          digitalWrite(pinRelais, HIGH); // Active le module relai de la pompe
          Serial.println("Pompe activée"); //Affiche le texte "Pompe activée" sur le moniteur série
          delay(Tempspompe); // Laisse fonctionner la pompe pendant le temps qu'on a déterminé plus haut
          digitalWrite(pinRelais, LOW); //Eteint la pompe
          NombreArrosage = NombreArrosage + 1; //on rajoute 1 a notre compteur d'arrosage
          NombreArrosage72 = NombreArrosage72 + 1;
          Temps = Temps + 3;
          delay(10800000); // Laisse passer 3 heures pour laisser a la terre le temps de sécher
          digitalWrite(ledRouge,LOW) //On éteint une potentielle led rouge

        } else { //Si l'humidité lue par le capteur n'est pas inférieure à notre sol (et donc qu'il est bien humide)
          digitalWrite(pinRelais, LOW); // Eteint le relais de la pompe
          Serial.println("Pompe désactivée"); // Affiche "Pompe désactivée" sur le moniteur série
          Temps = Temps + 1;
          delay(3600000);
        }
 }
 if (Temps = 24)               
   Temps = 0;                 //On remet à zéro la avriable de temps
   Temps72 = Temps72 + 1;               //On rajoute 1 jours à notre compteur de jour
   NombreArrosage = 0;        //On remet à zéro le nombre d'arrosage quotidien

if (Temps72 = 3){        
  if (NombreArrosage72 = 0){
    digitalWrite(ledRouge,HIGH);             //On allume une led rouge si jamais on a pas arrosé depuis 3 jours
  }
  Temps72 = 0;                               //On remet à zéro la variable de temps sur trois jours
  NombreArrosge = 0;                         //On remet à zéro le compteur du nombre d'arrosage dans les trois jours
} 

   
 if  (NombreArrosage > 3){
  Serial.println("Anti-Inondation : Système désactivé pour prévenir tout incident ");
  Temps = Temps + 1;
  delay (3600000);
  
 }

  
}