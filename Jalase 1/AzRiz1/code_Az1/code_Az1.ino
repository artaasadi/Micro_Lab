#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
#define BUTTON1 10
#define BUTTON2 11
#define BUTTON3 12


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
}

void loop() {
   if (digitalRead(BUTTON1) == 1){
    digitalWrite(LED1, HIGH);
    delay(1000);
    digitalWrite(LED2, HIGH);
    delay(1000);    
    digitalWrite(LED3, HIGH);
    delay(1000);    
    digitalWrite(LED4, HIGH);
    delay(1000);
    digitalWrite(LED5, HIGH);
    delay(1000);
  }
  else if (digitalRead(BUTTON2)== 1){  
      const int counter = strlen("kiana");
    for (int i =0 ; i<counter ; i++){
        digitalWrite(LED1, HIGH);   
        digitalWrite(LED2, HIGH); 
        digitalWrite(LED3, HIGH); 
        digitalWrite(LED4, HIGH); 
        digitalWrite(LED5, HIGH); 
        delay(1000);                 
        digitalWrite(LED1, LOW); 
        digitalWrite(LED2, LOW);    
        digitalWrite(LED3, LOW);    
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
        delay(1000);
      }
        digitalWrite(LED1, HIGH);   
        digitalWrite(LED2, HIGH); 
        digitalWrite(LED3, HIGH); 
        digitalWrite(LED4, HIGH); 
        digitalWrite(LED5, HIGH); 
  }else if (digitalRead(BUTTON3) == 1){
    digitalWrite(LED1, LOW); 
    digitalWrite(LED2, LOW);    
    digitalWrite(LED3, LOW);    
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
  }
}
