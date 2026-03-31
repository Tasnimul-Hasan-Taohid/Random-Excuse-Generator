/*
  Random Excuse Generator
  An Arduino-based device that generates random "I can't, because..." excuses
  to help you avoid meetings!
  
  Features:
  - 50 unique excuses
  - Button press to cycle through excuses
  - Hold for 2 seconds to mark/unmark favorite
  - Persistent storage of favorites in EEPROM
  
  Hardware:
  - Arduino Uno/Nano/Mega
  - Push button (pin 2)
  - LED (optional, pin 13)
*/

#include <EEPROM.h>

// Pin definitions
const int BUTTON_PIN = 2;
const int LED_PIN = 13;

// Configuration
const int TOTAL_EXCUSES = 50;
const int HOLD_TIME = 2000; // 2 seconds
const int DEBOUNCE_DELAY = 50; // 50ms debounce

// State variables
int currentExcuse = 0;
bool isFavorite[TOTAL_EXCUSES];
unsigned long buttonPressTime = 0;
bool buttonPressed = false;
int lastButtonState = HIGH;

// The 50 excuses
const char* excuses[TOTAL_EXCUSES] = {
  "My cat just knocked over my coffee",
  "I need to reorganize my file cabinet",
  "My WiFi is acting up",
  "I have a dentist appointment",
  "I need to walk my dog",
  "My internet just went down",
  "I have to pick up groceries",
  "My phone battery is at 1%",
  "I need to charge my laptop",
  "My car won't start",
  "I'm dealing with a family emergency",
  "I have a migraine",
  "My internet is frozen",
  "I need to take an important call",
  "My delivery is arriving soon",
  "I have to pay my bills",
  "My computer crashed",
  "I need to go to the bank",
  "I have a flat tire",
  "I'm having technical difficulties",
  "My printer is jammed",
  "I need to reset my password",
  "My hard drive is corrupting files",
  "I have to help a friend move",
  "My meeting invite didn't come through",
  "I'm experiencing severe lag",
  "I need to reboot my system",
  "My monitor just died",
  "I have a surprise visitor",
  "I need to handle an urgent email",
  "My keyboard is broken",
  "I'm stuck in traffic",
  "I need to attend to my garden",
  "My software license expired",
  "I have to renew my insurance",
  "I'm experiencing a power outage",
  "I need to back up my files",
  "My mouse just broke",
  "I have to visit the mechanic",
  "I'm updating my system software",
  "I have a Zoom call conflict",
  "My headphones aren't working",
  "I need to download important files",
  "I'm dealing with a virus scan",
  "I have to organize my workspace",
  "My notifications are overwhelming",
  "I need to check on something urgent",
  "I'm experiencing audio problems",
  "My schedule got double-booked",
  "I have to attend to a family matter"
};

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize random seed
  randomSeed(analogRead(0));
  
  // Load favorites from EEPROM
  loadFavorites();
  
  // Display initial excuse
  showCurrentExcuse();
}

void loop() {
  handleButton();
}

void handleButton() {
  int buttonState = digitalRead(BUTTON_PIN);
  
  // Debounce
  if (buttonState != lastButtonState) {
    delay(DEBOUNCE_DELAY);
    buttonState = digitalRead(BUTTON_PIN);
  }
  
  lastButtonState = buttonState;
  
  // Button pressed (LOW because of pullup)
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    buttonPressTime = millis();
    digitalWrite(LED_PIN, HIGH); // Visual feedback
  }
  
  // Button released
  if (buttonState == HIGH && buttonPressed) {
    unsigned long holdDuration = millis() - buttonPressTime;
    
    if (holdDuration >= HOLD_TIME) {
      // Long hold - toggle favorite
      toggleFavorite();
    } else {
      // Short press - next excuse
      nextExcuse();
    }
    
    buttonPressed = false;
    digitalWrite(LED_PIN, LOW);
  }
}

void nextExcuse() {
  currentExcuse = random(TOTAL_EXCUSES);
  showCurrentExcuse();
}

void showCurrentExcuse() {
  Serial.println("\n========================================");
  Serial.print("EXCUSE #");
  Serial.print(currentExcuse + 1);
  Serial.print(" - ");
  if (isFavorite[currentExcuse]) {
    Serial.println("(FAVORITE)");
  } else {
    Serial.println("");
  }
  Serial.println("========================================");
  Serial.println(excuses[currentExcuse]);
  Serial.println("========================================\n");
}

void toggleFavorite() {
  isFavorite[currentExcuse] = !isFavorite[currentExcuse];
  saveFavorites();
  
  Serial.println("");
  if (isFavorite[currentExcuse]) {
    Serial.println("⭐ ADDED TO FAVORITES!");
  } else {
    Serial.println("❌ REMOVED FROM FAVORITES!");
  }
  Serial.println("");
  
  // Blink LED to indicate toggle
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void saveFavorites() {
  for (int i = 0; i < TOTAL_EXCUSES; i++) {
    EEPROM.write(i, isFavorite[i] ? 1 : 0);
  }
}

void loadFavorites() {
  for (int i = 0; i < TOTAL_EXCUSES; i++) {
    isFavorite[i] = EEPROM.read(i) == 1;
  }
}
