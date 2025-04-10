#include <HID-Project.h>
#include <Keyboard.h>

// Constantes HID pour les touches multimédia (Consumer Control)
#define MEDIA_MUTE 0xE2
#define MEDIA_VOL_UP 0xE9
#define MEDIA_VOL_DOWN 0xEA
#define MEDIA_PLAY_PAUSE 0xCD
#define MEDIA_NEXT 0xB5
#define MEDIA_PREV 0xB6
#define MEDIA_STOP 0xB7
#define MEDIA_EJECT 0xB8

// Variables de contrôle
unsigned long lastDebounceTimeProfil = 0; // Anti-rebond pour le bouton de active_profile
const unsigned long debounceDelay = 50;   // Délai anti-rebond
unsigned long debounceTimes[8] = {0};     // Anti-rebond pour chaque bouton
unsigned long buttonPressStart[8] = {0};  // Enregistrement du temps d'appui pour chaque bouton

// Déclaration des broches
const int Profile_button = A0;                         // Bouton pour changer de active_profile
const int touche_clavier[] = {2, 3, 4, 5, 6, 7, 8, 9}; // touche_clavier d'actions
const int leds[] = {10, 16, 14, 15};                   // LEDs pour les active_profiles

// Profil actif
int active_profile = 0; // Initialisation au premier active_profile

// Enumération des active_profiles
enum active_profiles
{
    PROFIL1,
    PROFIL2,
    PROFIL3,
    PROFIL4
};

void setup()
{
    pinMode(Profile_button, INPUT_PULLUP); // Activer le pull-up interne

    for (int i = 0; i < 8; i++)
    {
        pinMode(touche_clavier[i], INPUT_PULLUP); // Activer les pull-ups internes pour les touche_clavier
    }

    for (int i = 0; i < 4; i++)
    {
        pinMode(leds[i], OUTPUT);   // Configurer les broches des LEDs en sortie
        digitalWrite(leds[i], LOW); // Éteindre les LEDs par défaut
    }

    Keyboard.begin();   // Initialisation pour les commandes clavier
    Serial.begin(9600); // Debug via le port série
}

void loop()
{
    // Gestion du changement de active_profile
    if (!digitalRead(Profile_button) && millis() - lastDebounceTimeProfil > debounceDelay)
    {
        active_profile = (active_profile + 1) % 4; // Passer au prochain active_profile (cyclique de 0 à 3)
        Serial.print("Profil actif : ");
        Serial.println(active_profile);
        lastDebounceTimeProfil = millis();
    }

    // Mise à jour des LEDs pour indiquer le active_profile actif
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(leds[i], (i == active_profile) ? HIGH : LOW);
    }

    // Gestion des touche_clavier pour chaque active_profile
    for (int i = 0; i < 8; i++)
    {
        if (!digitalRead(touche_clavier[i]))
        {
            if (debounceTimes[i] == 0)
            {
                debounceTimes[i] = millis(); // Enregistre le moment où le bouton a été pressé
            }

            unsigned long pressDuration = millis() - debounceTimes[i];

            if (pressDuration > 1000)
            { // Longue pression (plus de 1 seconde)
                if (buttonPressStart[i] == 0)
                {
                    buttonPressStart[i] = millis(); // Démarre le suivi de la longue pression
                    envoyerCommandeLonguePression(active_profile, i + 1);
                }
            }
            else
            { // Pression courte
                if (buttonPressStart[i] != 0)
                {
                    buttonPressStart[i] = 0; // Réinitialise pour ne pas répéter l'action longue
                }
                envoyerCommande(active_profile, i + 1);
            }
        }
        else
        {
            debounceTimes[i] = 0;    // Réinitialise quand le bouton est relâché
            buttonPressStart[i] = 0; // Réinitialise aussi le suivi de la longue pression
        }
    }
}

void envoyerCommande(int active_profile, int bouton)
{
    switch (active_profile)
    {
    case PROFIL1:
        switch (bouton)
        {
        case 1:
            Keyboard.press(MEDIA_MUTE); // Bouton Mute
            Keyboard.releaseAll();
            break;
        case 2:
            Keyboard.write(MEDIA_PREV); // Musique précédente
            break;
        case 3:
            Keyboard.write(MEDIA_PLAY_PAUSE); // Play/Pause
            break;
        case 4:
            Keyboard.write(MEDIA_NEXT); // Musique suivante
            break;
        case 5:
            Keyboard.write(MEDIA_VOL_UP); // Volume +
            break;
        case 6:
            Keyboard.write(MEDIA_VOL_DOWN); // Volume -
            break;
        case 7:
            Keyboard.press(KEY_LEFT_CTRL); // Explorateur de fichiers (Ctrl + E)
            Keyboard.press('e');
            Keyboard.releaseAll();
            break;
        case 8:
            Keyboard.press(KEY_LEFT_GUI); // Paramètres (Windows + I)
            Keyboard.press('i');
            Keyboard.releaseAll();
            break;
        }
        break;

    case PROFIL2:
        switch (bouton)
        {
        case 1:
            Keyboard.print("Commande active_profile 2 bouton 1");
            break;
        }
        break;

    case PROFIL3:
        switch (bouton)
        {
        case 1:
            Keyboard.print("Commande active_profile 3 bouton 1");
            break;
        }
        break;

    case PROFIL4:
        switch (bouton)
        {
        case 1:
            Keyboard.print("Commande active_profile 4 bouton 1");
            break;
        }
        break;
    }
}

// Fonction pour gérer la longue pression
void envoyerCommandeLonguePression(int active_profile, int bouton)
{
    switch (active_profile)
    {
    case PROFIL1:
        switch (bouton)
        {
        case 1:
            // Ouvrir le Mélangeur Audio (Windows + R puis "mmsys.cpl")
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press('r');
            Keyboard.releaseAll();
            delay(100);
            Keyboard.print("mmsys.cpl");
            Keyboard.press(KEY_RETURN);
            Keyboard.releaseAll();
            break;

        case 3:
            // Ouvrir Spotify (Windows + R puis "spotify")
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press('r');
            Keyboard.releaseAll();
            delay(100);
            Keyboard.print("spotify");
            Keyboard.press(KEY_RETURN);
            Keyboard.releaseAll();
            break;
        }
        break;
    }
}