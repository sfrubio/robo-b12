/*Pinagem do arduino*/
//motor_A
const int IN1 = 2;
const int IN2 = 3;

//motor_B
const int IN3 = 4;
const int IN4 = 5;

//sonar
const int TRIG = 7;
const int ECHO = 6;
unsigned int intervalo, distancia;

const int DIST_MIN = 20;
const int DIST_MAX = 60;

//buzzer e leds
const int BUZZER = 8;
const int LEDR = 13;
const int LEDY = 12;
const int LEDG = 11;

//Inicializa Pinos
void setup(){
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDY,OUTPUT);
  pinMode(LEDG,OUTPUT);
}

void loop() {

  distancia = sensor_morcego(TRIG,ECHO); // Chamada da função de leitura.
  Serial.println(distancia);
  if (distancia <= DIST_MIN) { // Condicional para leituras inferiores a 10cm.
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDY,HIGH);
    digitalWrite(LEDG,HIGH);
    tone(BUZZER, 1750);
    frear();
    engatarRe();
  }
  else if (distancia > DIST_MAX) { // Condicional para leituras superiores a 60cm.
      digitalWrite(LEDR,LOW);
      digitalWrite(LEDY,LOW);
      digitalWrite(LEDG,LOW);
      noTone(BUZZER);
      acelerar();
  } 
  else { // Condicional para leitura intermediarias.
    if (distancia <= (DIST_MAX - DIST_MIN)) { 
      digitalWrite(LEDR,LOW);
      digitalWrite(LEDY,HIGH);
      digitalWrite(LEDG,HIGH);
      intervalo = 100;
    }
    else if (distancia <= DIST_MAX) {
      digitalWrite(LEDR,LOW);
      digitalWrite(LEDY,LOW);
      digitalWrite(LEDG,HIGH);
      intervalo = 200;
    }
    tone(BUZZER,1750);
    delay(intervalo);
    noTone(BUZZER);
    delay(intervalo);
    acelerar();
  }
}

int sensor_morcego(int pinotrig,int pinoecho){ // Função para leitura do sensor
  digitalWrite(pinotrig,LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig,LOW);

  return pulseIn(pinoecho,HIGH)/58;
}

void frear(){
  //Freia Motor_A
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  //Freia Motor_B
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  delay(1000);
}

void acelerar(){
  //Freia Motor_A
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  //Freia Motor_B
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void engatarRe(){
  //Freia Motor_A
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  //Freia Motor_B
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(1000);
}
