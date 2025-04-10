#include <HID-Project.h>

// Constantes HID pour les touches multimédia (Consumer Control)
#define MEDIA_MUTE 0xE2
#define MEDIA_VOL_UP 0xE9
#define MEDIA_VOL_DOWN 0xEA
//#define MEDIA_PLAY_PAUSE  0xCD
#define MEDIA_NEXT 0xB5
#define MEDIA_PREV 0xB6

// Délais
const unsigned long debounceDelay = 500;
unsigned long lastDebounceTimeProfil = 0;
unsigned long debounceTimes[8] = { 0 };
unsigned long buttonPressStart[8] = { 0 };
unsigned long lastRepeatTime[8] = { 0 };


// Broches
const int Profile_button = A0;
const int touche_clavier[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
const int leds[] = { 10, 16, 14, 15 };

// Profils
int active_profile = 0;
enum active_profiles { PROFIL1,
                       PROFIL2,
                       PROFIL3,
                       PROFIL4 };

void setup() {
  pinMode(Profile_button, INPUT_PULLUP);
  for (int i = 0; i < 8; i++) pinMode(touche_clavier[i], INPUT_PULLUP);
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  Consumer.begin();
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  // Changement de profil
  if (!digitalRead(Profile_button) && millis() - lastDebounceTimeProfil > debounceDelay) {
    active_profile = (active_profile + 1) % 4;
    Serial.print("Profil actif : ");
    Serial.println(active_profile);
    lastDebounceTimeProfil = millis();
  }

  // Mise à jour LEDs
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], (i == active_profile) ? HIGH : LOW);
  }

  // Gestion des boutons
  for (int i = 0; i < 8; i++) {
    if (!digitalRead(touche_clavier[i])) {
      if (debounceTimes[i] == 0) debounceTimes[i] = millis();  // Enregistrer le temps du premier appui

      unsigned long pressDuration = millis() - debounceTimes[i];

      // Détection de pression longue (plus de 1500 ms)
      if (pressDuration > 1500) {  // Longue pression
        if (buttonPressStart[i] == 0) {
          envoyerCommandeLonguePression(active_profile, i + 1);
          buttonPressStart[i] = 1;  // Marquer comme exécuté
        }
      }
      // Détection de pression courte
      else {
        if (buttonPressStart[i] == 0) {
          envoyerCommande(active_profile, i + 1);
          buttonPressStart[i] = 1;
        }
      }
    }

    // Si le bouton est relâché
    if (digitalRead(touche_clavier[i]) == HIGH) {
      if (debounceTimes[i] != 0) {
        debounceTimes[i] = 0;
        buttonPressStart[i] = 0;  // Réinitialisation
      }
      Consumer.write(0);  // Relâcher toutes les touches
    }
  }
}

void envoyerCommande(int profil, int bouton) {
  switch (profil) {
    case PROFIL1:
      switch (bouton) {
        case 1:
          Consumer.write(MEDIA_MUTE);
          delay(100);         // Pause pour simuler l'appui
          Consumer.write(0);  // Relâcher la touche
          break;
        case 2:
          Consumer.write(MEDIA_PREV);
          delay(100);
          Consumer.write(0);
          break;
        case 3:
          Consumer.write(MEDIA_PLAY_PAUSE);
          delay(100);
          Consumer.write(0);
          break;
        case 4:
          Consumer.write(MEDIA_NEXT);
          delay(100);
          Consumer.write(0);
          break;
        case 5:
          Consumer.write(MEDIA_VOL_DOWN);
          delay(100);
          Consumer.write(0);
          break;
        case 6:
          Consumer.write(MEDIA_VOL_UP);
          delay(100);
          Consumer.write(0);
          break;
        case 7:
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_LEFT_ARROW);
          Keyboard.releaseAll();
          delay(100);
          break;
        case 8:
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_RIGHT_ARROW);
          Keyboard.releaseAll();
          break;
      }
      break;

    case PROFIL2:
      if (bouton == 1) Keyboard.print("Commande profil 2 bouton 1");
      break;
    case PROFIL3:
      if (bouton == 1) Keyboard.print("Commande profil 3 bouton 1");
      break;
    case PROFIL4:
      if (bouton == 1) Keyboard.print("Commande profil 4 bouton 1");
      break;
  }
}


void envoyerCommandeLonguePression(int profil, int bouton) {
  switch (profil) {
    case PROFIL1:
      switch (bouton) {
        case 1:  // Ouvrir mélangeur audio en appuyant longtemps sur la touche 1
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press('r');
          Keyboard.releaseAll();
          delay(100);
          Keyboard.print("sndvol");
          Keyboard.press(KEY_RETURN);
          Keyboard.releaseAll();
          break;

        case 3:  // Ouvrir Spotify
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press('r');
          Keyboard.releaseAll();  // Relâcher après la combinaison de touches
          delay(100);             // Laisser le temps de réagir
          Keyboard.print("spotify");
          Keyboard.press(KEY_RETURN);
          Keyboard.releaseAll();  // Relâcher après la commande
          break;
      }
      break;
  }
}
