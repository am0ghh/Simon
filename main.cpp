#include <Arduino.h>
#include <vector>

std::vector<int> gameSeq;
const int buzz = 6;
const int green = 8, blue = 9, yellow = 10, red = 11;
const int push1 = 3, push2 = 4, push3 = 5, push4 = 2;

// --- Helper: Play a single Note/LED ---
void playNote(int note) {
  int freq = 0;
  int led = 0;

  if (note == 1) { led = green; freq = 880; }
  else if (note == 2) { led = blue; freq = 932; }
  else if (note == 3) { led = yellow; freq = 1046; }
  else if (note == 4) { led = red; freq = 1174; }

  digitalWrite(led, HIGH);
  tone(buzz, freq);
  delay(200); 
  noTone(buzz);
  digitalWrite(led, LOW);
  delay(50);  
}

// --- Helper: Play the whole pattern ---
void playSequence() {
  Serial.println("Watch the pattern...");
  delay(400); 
  for (int note : gameSeq) {
    playNote(note);
  }
}

// --- Helper: Wait for and return a button press ---
int getButtonPressed() {
  while (true) {
    if (digitalRead(push1) == LOW) return 1;
    if (digitalRead(push2) == LOW) return 2;
    if (digitalRead(push3) == LOW) return 3;
    if (digitalRead(push4) == LOW) return 4;
  }
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); 

  pinMode(buzz, OUTPUT);
  pinMode(green, OUTPUT); pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT); pinMode(red, OUTPUT);
  pinMode(push1, INPUT_PULLUP); pinMode(push2, INPUT_PULLUP);
  pinMode(push3, INPUT_PULLUP); pinMode(push4, INPUT_PULLUP);

  Serial.println("Game Start!");
}

void loop() {
  gameSeq.push_back(random(1, 5));
  
  playSequence();

  Serial.println("Your turn!");
  for (int i = 0; i < gameSeq.size(); i++) {
    int expected = gameSeq[i];
    int pressed = getButtonPressed();
    
    if (pressed == 1) { digitalWrite(green, HIGH); tone(buzz, 880); }
    else if (pressed == 2) { digitalWrite(blue, HIGH); tone(buzz, 932); }
    else if (pressed == 3) { digitalWrite(yellow, HIGH); tone(buzz, 1046); }
    else if (pressed == 4) { digitalWrite(red, HIGH); tone(buzz, 1174); }

    if (pressed == 1) while(digitalRead(push1) == LOW);
    if (pressed == 2) while(digitalRead(push2) == LOW);
    if (pressed == 3) while(digitalRead(push3) == LOW);
    if (pressed == 4) while(digitalRead(push4) == LOW);
    
    noTone(buzz);
    digitalWrite(green, LOW); 
    digitalWrite(blue, LOW);
    digitalWrite(yellow, LOW); 
    digitalWrite(red, LOW);
    
    delay(50); 

    if (pressed != expected) {
      Serial.println("GAME OVER!");
      tone(buzz, 150, 1000); 
      digitalWrite(green, HIGH);
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(yellow, HIGH);
      delay(1000);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      gameSeq.clear();       
      delay(2000);
      return;                
    }
  }

  Serial.println("Level Complete!");
  delay(500); 
}