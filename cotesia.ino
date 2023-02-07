//Autor Gabriel Lima
//Dispeser de cotesia para drones agriculas.
//06/02/2023
#include <Servo.h>
//Declaracao de variaveis
#define SERVO 9 // Porta Digital 9 PWM
Servo s; // Variável Servo
int pos; // Posição Servo
int limiteDisparo = 1010; //leitura do sensor 
int pushbutton = 4; // declara o push button na porta 4
bool estadoled = 0; // variavel de controle
int led = 13; //led de verificacao
int transistor = 8;// Ligue o motor ao pino digital 8
int sensor = A0;// O fotoresistor (LDR) é conectado ao pino analógico 0
int sensorValue = 0;// Armazena o valor de leitura analógica
 
void setup() {
  
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(led, OUTPUT);// define LED como saida
  pinMode(transistor, OUTPUT);//defina o motor como saida
  pinMode(sensor, INPUT);// Define o fotoresistor como uma entrada
  s.attach(SERVO);
  s.write(0); // Inicia motor posição zero
  Serial.begin(9600);// Inicia a comunicação serial com uma taxa de transmissão de 9600 boud rate
}

//Função girar
void girar(){
  sensorValue = analogRead(sensor);// Lê o valor atual do fotoresistor

  if (sensorValue < limiteDisparo) {
      digitalWrite(transistor, HIGH);
  	}else {
      digitalWrite(transistor,LOW);
      for(pos = 0; pos < 90; pos++){
   	 s.write(pos);
  	 delay(15);
 	 }
	  delay(15);
  	for(pos = 90; pos >= 0; pos--){
    	s.write(pos);
    	delay(15);

  	}
  Serial.print ("Leitura atual do sensor: ");
  Serial.println(sensorValue);
  delay(130);
  }
  digitalWrite(transistor, HIGH);
  delay(15);
  digitalWrite(transistor,LOW);
}
 
void loop(){
  
  if (digitalRead(pushbutton) == LOW) // Se o botão for pressionado
  {
    estadoled = !estadoled; // troca o estado do LED
    digitalWrite(led, estadoled);
    girar();
    while (digitalRead(pushbutton) == HIGH);
    
  	}
}
