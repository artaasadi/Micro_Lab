#include <Wire.h>
#include<LiquidCrystal.h>
#include <Keypad.h>

#define SLAVE_ADDRESS 0b1010000    // slave address

#define RS_PIN 13
#define EN_PIN 12
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11

#define preWash_LED A0
#define detergents_LED  A3
#define water_LED A5
#define dry_LED A8



LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN );

const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'s', '0', '=', '+'}
};
byte rowPins[rows] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[cols] = {23, 25, 27, 29}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

void eeprom_write(uint8_t memAddress, uint8_t writtenData);
uint8_t eeprom_read(uint8_t memAddress);

int i = 0;
int numberOfPrograms = 1;

int preWash_time = 2;
int detergents_time = 2;
int water_time = 2;
int dry_time = 2;


bool set = false;
bool select = false;

char input[4];
int selectedProgram = 0;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.cursor();

  memset(input, '2', sizeof(input));


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setting up...");   // setting default program in memory
  lcd.setCursor(0, 1);
  lcd.print("Please wait...");


  eeprom_write(0, 0);
  delay(1000);    // waiting for memry to accomplish

  eeprom_write(1, preWash_time);
  delay(1000);    // waiting for memry to accomplish

  eeprom_write(2, detergents_time);
  delay(1000);    // waiting for memry to accomplish

  eeprom_write(3, water_time);
  delay(1000);    // waiting for memry to accomplish

  eeprom_write(4, dry_time);
  delay(1000);      // waiting for memry to accomplish

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("done!");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("The default is:");
  lcd.setCursor(0, 1);
  lcd.print("5 5 5 5 sec");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Use ON to wash");
  lcd.setCursor(0, 1);
  lcd.print("Or + to add new");


}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    switch (key) {
      case's':  // start to wash

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pre Wash...");
        lcd.setCursor(0, 1);
        lcd.print(eeprom_read((selectedProgram * 5) + 1));
        digitalWrite(preWash_LED, HIGH);
        delay(eeprom_read((selectedProgram * 5) + 1) * 1000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Detergents...");
        lcd.setCursor(0, 1);
        lcd.print(eeprom_read((selectedProgram * 5) + 2));
        digitalWrite(detergents_LED, HIGH);
        delay(eeprom_read((selectedProgram * 5) + 2) * 1000);     // 2

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Water...");
        lcd.setCursor(0, 1);
        lcd.print(eeprom_read((selectedProgram * 5) + 3));
        digitalWrite(water_LED, HIGH);
        delay(eeprom_read((selectedProgram * 5) + 3) * 1000);     // 3

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Drying...");
        lcd.setCursor(0, 1);
        lcd.print(eeprom_read((selectedProgram * 5) + 4));
        digitalWrite(dry_LED, HIGH);
        delay(eeprom_read((selectedProgram * 5) + 4) * 1000);     // 4


        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Washing is done.");
        lcd.setCursor(0, 1);
        lcd.print("Use - to reset");

        break;

      case '-':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Resetting...");

        digitalWrite(preWash_LED, LOW);
        delay(200);
        digitalWrite(detergents_LED, LOW);
        delay(200);
        digitalWrite(water_LED, LOW);
        delay(200);
        digitalWrite(dry_LED, LOW);
        delay(200);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Resetting done.");
        delay(1000);

        break;

      case'/':  // select a program
        lcd.clear();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Choose one:");
        lcd.setCursor(0, 1);
        for (int i = 0; i < numberOfPrograms ; i++) {
          lcd.print(eeprom_read(i * 5));
          lcd.print(" ");
        }
        lcd.print(": ");
        select = true;
        i = 0;

        break;


      case '+':   // set a new program
        lcd.clear();
        lcd.setCursor(0, 0);
        if (numberOfPrograms == 5) {
          lcd.print("No more programs");
          lcd.setCursor(0, 1);
          lcd.print("are accepted!");
        }
        else {
          lcd.print("Enter 4 digits:");
          i = 0;
          set = true;
        }

        break;

      case '=': // accomplish setting or selecting a program
        if (set) {
          i = 0;

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Setting up...");   // setting default program in memory
          lcd.setCursor(0, 1);
          lcd.print("Please wait...");

          eeprom_write((numberOfPrograms * 5), numberOfPrograms);
          delay(1000);    // waiting for memry to accomplish

          eeprom_write((numberOfPrograms * 5) + 1, input[0] - 48);
          delay(1000);    // waiting for memry to accomplish

          eeprom_write((numberOfPrograms * 5) + 2, input[1] - 48);
          delay(1000);    // waiting for memry to accomplish

          eeprom_write((numberOfPrograms * 5) + 3, input[2] - 48);
          delay(1000);    // waiting for memry to accomplish

          eeprom_write((numberOfPrograms * 5) + 4, input[3] - 48);
          delay(1000);    // waiting for memry to accomplish

          set = false;
          memset(input, '2', 4);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("New program");
          lcd.setCursor(0, 1);
          lcd.print("was Saved!");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Use / to select.");

          numberOfPrograms++;

        }
        else if (select) {
          i = 0;
          select = false;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Current program:");
          lcd.setCursor(7, 1);
          lcd.print(selectedProgram);
          delay(1500);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Use On to wash.");

        }

        break;

      default:
        if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') {
          if (select) {    // select a program
            selectedProgram = key - 48;
            i = 0;
            lcd.setCursor(13, 1);
            lcd.print(selectedProgram);
          }
          else if (set) {   // set a new program
            input[i] = key;
            lcd.setCursor(i, 1);
            lcd.print(input[i]);
            i++;
            if (i == 4) {
              i = 0;
            }
          }
          break;

        }

    }
  }
}

void eeprom_write(uint8_t memAddress, uint8_t writtenData) {
  Wire.beginTransmission(SLAVE_ADDRESS); // start bit + slave address + w/r (write is selected)

  Wire.write(memAddress);    // memory block address
  Wire.write(writtenData);  // data on that block

  Wire.endTransmission();   // stop bit
}

uint8_t eeprom_read(uint8_t memAddress) {
  Wire.beginTransmission(SLAVE_ADDRESS); // start bit + slave address
  Wire.write(memAddress);    // memory block address
  Wire.endTransmission();   // stop bit

  Wire.requestFrom(SLAVE_ADDRESS, 1);  // request Slave to read 1 Byte from it

  uint8_t readData = Wire.read();
  return readData;
}
