#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BTN_B1 2
#define BTN_B2 3
#define BTN_B3 4
#define BTN_B4 5

#define LED_L1 6
#define LED_L2 7
#define LED_L3 8
#define LED_L4 9
#define LED_LS 10

#define ENCODER_CLK 11
#define ENCODER_DT 12

const int BTN_PINS[4] = {BTN_B1, BTN_B2, BTN_B3, BTN_B4};

LiquidCrystal_I2C lcd(0x27, 16, 2);

float T1_BASE = 8.0;
float F_FACTOR[5] = {0, 0.85, 0.80, 0.75, 0.70};
int SEQUENCE[4];

enum GameState { WELCOME, PLAYING, GAME_OVER, SLEEPING };
GameState currentState = WELCOME;

int score = 0;
int difficulty = 1;
int buttonIndex = 0;
unsigned long stateStartTime = 0;
unsigned long roundStartTime = 0;
float currentT1 = T1_BASE;
int round_num = 0;
unsigned long pulseTimer = 0;
int lastCLKState = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(LED_L1, OUTPUT);
  pinMode(LED_L2, OUTPUT);
  pinMode(LED_L3, OUTPUT);
  pinMode(LED_L4, OUTPUT);
  pinMode(LED_LS, OUTPUT);

  pinMode(BTN_B1, INPUT_PULLUP);
  pinMode(BTN_B2, INPUT_PULLUP);
  pinMode(BTN_B3, INPUT_PULLUP);
  pinMode(BTN_B4, INPUT_PULLUP);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);

  lcd.init();
  lcd.backlight();

  turnOffAllLEDs();

  currentState = WELCOME;
  stateStartTime = millis();
  displayWelcome();
}

void loop() {
  readEncoderDifficulty();

  switch (currentState) {
    case WELCOME:
      updateWelcome();
      break;
    case PLAYING:
      updatePlaying();
      break;
    case GAME_OVER:
      updateGameOver();
      break;
    case SLEEPING:
      break;
  }
}

void displayWelcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to TOS!");
  lcd.setCursor(0, 1);
  lcd.print("B1:Start Diff:");
  lcd.print(difficulty);

  pulseTimer = millis();
}

void updateWelcome() {
  pulseLED_LS();

  static int lastDiff = difficulty;
  if (difficulty != lastDiff) {
    lastDiff = difficulty;
    lcd.setCursor(14, 1);
    lcd.print(difficulty);
  }

  if (digitalRead(BTN_B1) == LOW) {
    delay(50);
    if (digitalRead(BTN_B1) == LOW) {
      while (digitalRead(BTN_B1) == LOW) delay(10);
      delay(50);
      startGame();
    }
  }

  if (millis() - stateStartTime > 10000) {
    goToSleep();
  }
}

void startGame() {
  currentState = PLAYING;
  score = 0;
  round_num = 0;
  currentT1 = T1_BASE;
  buttonIndex = 0;
  randomSeed(millis());

  turnOffAllLEDs();
  displayGo();
}

void displayGo() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Go!");
  lcd.setCursor(0, 1);
  lcd.print("Score: 0");

  delay(1000);
  playRound();
}

void playRound() {
  round_num++;
  buttonIndex = 0;
  generateSequence();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sequence:");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 4; i++) {
    lcd.print(SEQUENCE[i]);
  }

  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.setCursor(0, 1);
  lcd.print("Press: ");

  roundStartTime = millis();
}

void updatePlaying() {
  float elapsedTime = (millis() - roundStartTime) / 1000.0;
  float remainingTime = currentT1 - elapsedTime;

  lcd.setCursor(6, 0);
  if (remainingTime >= 0) {
    lcd.print(remainingTime, 1);
    lcd.print("s ");
  } else {
    lcd.print("0.0s ");
  }

  for (int i = 0; i < 4; i++) {
    if (digitalRead(BTN_PINS[i]) == LOW) {
      delay(50);
      if (digitalRead(BTN_PINS[i]) == LOW) {
        handleButtonPress(i + 1);
      }
    }
  }

  if (millis() - roundStartTime > (currentT1 * 1000)) {
    gameOver();
  }
}

void handleButtonPress(int buttonNum) {
  int pin = BTN_PINS[buttonNum - 1];

  if (SEQUENCE[buttonIndex] == buttonNum) {
    turnOnLED(buttonNum);
    lcd.setCursor(7, 1);
    lcd.print(buttonNum);
    delay(300);
    turnOffAllLEDs();

    buttonIndex++;

    if (buttonIndex == 4) {
      score++;
      currentT1 *= F_FACTOR[difficulty];

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("GOOD! Score:");
      lcd.print(score);

      delay(2000);
      playRound();
    }
  } else {
    gameOver();
    return;
  }

  while (digitalRead(pin) == LOW) {
    delay(10);
  }
}

void gameOver() {
  currentState = GAME_OVER;
  turnOffAllLEDs();

  digitalWrite(LED_LS, HIGH);
  delay(2000);
  digitalWrite(LED_LS, LOW);

  displayGameOver();
  stateStartTime = millis();
}

void displayGameOver() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game Over");
  lcd.setCursor(0, 1);
  lcd.print("Final Score:");
  lcd.print(score);
}

void updateGameOver() {
  if (millis() - stateStartTime > 10000) {
    currentState = WELCOME;
    stateStartTime = millis();
    displayWelcome();
  }
}

void generateSequence() {
  boolean used[5] = {false, false, false, false, false};

  for (int i = 0; i < 4; i++) {
    int digit;
    do {
      digit = random(1, 5);
    } while (used[digit]);

    SEQUENCE[i] = digit;
    used[digit] = true;
  }
}

void turnOnLED(int ledNum) {
  int ledPin = LED_L1 + ledNum - 1;
  digitalWrite(ledPin, HIGH);
}

void turnOffAllLEDs() {
  digitalWrite(LED_L1, LOW);
  digitalWrite(LED_L2, LOW);
  digitalWrite(LED_L3, LOW);
  digitalWrite(LED_L4, LOW);
  digitalWrite(LED_LS, LOW);
}

void pulseLED_LS() {
  unsigned long elapsed = millis() - pulseTimer;
  int period = 600;

  if ((elapsed % period) < (period / 2)) {
    analogWrite(LED_LS, (elapsed % (period / 2)) * 255 / (period / 2));
  } else {
    analogWrite(LED_LS, 255 - ((elapsed % (period / 2)) * 255 / (period / 2)));
  }
}

void readEncoderDifficulty() {
  if (currentState != WELCOME) return;

  int currentCLKState = digitalRead(ENCODER_CLK);

  if (lastCLKState == HIGH && currentCLKState == LOW) {
    if (digitalRead(ENCODER_DT) == LOW) {
      difficulty++;
    } else {
      difficulty--;
    }

    if (difficulty > 4) difficulty = 4;
    if (difficulty < 1) difficulty = 1;

    stateStartTime = millis();
  }

  lastCLKState = currentCLKState;
}

void wakeISR() {}

void goToSleep() {
  currentState = SLEEPING;
  turnOffAllLEDs();
  lcd.noBacklight();
  lcd.clear();

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(BTN_B1), wakeISR, LOW);

  sleep_cpu();
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(BTN_B1));
  while (digitalRead(BTN_B1) == LOW) delay(10);
  delay(50);

  wakeUp();
}

void wakeUp() {
  lcd.backlight();
  currentState = WELCOME;
  stateStartTime = millis();
  displayWelcome();
}
