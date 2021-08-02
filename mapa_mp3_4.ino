////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Código para un sistema electrónico de sonido para un mapa interactivo.                    /////////////////////////////
//// Cada vez que un interruptor magnético sea activado se reproducirá una canción aleatoria   /////////////////////////////
//// de una carpeta determinada asociada a ese interruptor. También se activa un led para      ///////////////////////////// 
//// indicar que un interruptor se ha activado.                                                /////////////////////////////
////                                                                                           /////////////////////////////
////                                                                                           /////////////////////////////
//// Elaborado por Christian David para Creatvra en el marco del proyecto E&ES 2021.           /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//dar permisos desde Linux sudo chmod a+rw /dev/ttyACM0


/// Librerías para el módulo reproductor de MP3 DF Player Mini ///

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//////////////////////////////////////////////////////////////////

/// Definición de los pines de los interruptores magnéticos /////
const int s1 = 2; 
const int s2 = 3;
const int s3 = 4;
/////////////////////////////////////////////////////////////////

/// Definición de los pines de los leds asociados a la activación de los interruptores ///
const int led = 5;
const int led2 = 6;
const int led3 = 7;
///////////////////////////////////////////////////////////////

/// Estados para las entradas digitales de los interruptores //
int state1 = 0; 
int last1 = 1;
int state2 = 0;
int last2 = 1;
int state3 = 0;
int last3 = 1;
//////////////////////////////////////////////////////////////

/// Comandos para la definición de pines del módulo DF Player ///
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
////////////////////////////////////////////////////////////////


void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Uso del softwareSerial para comunicarse con mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500); // Establece el tiempo de la comunicación serial en 500ms
  //----Set volume----
  myDFPlayer.volume(20);  //Establece el valor del volumen (0~30).
  myDFPlayer.volumeUp(); //Volumen arriba
  myDFPlayer.volumeDown(); //Volumen abajo
  //----Establece el ecualizador----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //----Establece el uso de la SD como default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  pinMode(s1, INPUT_PULLUP);
  pinMode(s2, INPUT_PULLUP);
  pinMode(s3, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop()
{
  /// Lecturas digitales de los interruptores ///
  state1 = digitalRead(s1);
  state2 = digitalRead(s2);
  state3 = digitalRead(s3);

  /// Condicional que activa las canciones de la carpeta asociada al primer interruptor ///
  if (state1 != last1) {
    if (state1 == HIGH) {
      int cancion_aleatoria1 = random(1, 5); // Generador de números aleatorios entre 1 y 5.
      myDFPlayer.playFolder(1, cancion_aleatoria1);  // Reproduce una canción específica de la carpeta 01.
      Serial.print("Interruptor 1: "); //Muestra el estado del interruptor 1 y la canción que reproduce.
      Serial.print(state1);
      Serial.print(" :: ");
      Serial.println(cancion_aleatoria1);
      digitalWrite(led, HIGH); // Prende el led asociado al interruptor 1.
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      delay(1000);
    }
  }
  last1  = state1;
  
  /// Condicional que activa las canciones de la carpeta asociada al segundo interruptor ///
  if (state2 != last2 ) {
    if (state2 == HIGH) {
       int cancion_aleatoria2 = random(1, 5); // Generador de números aleatorios entre 1 y 5.
       myDFPlayer.playFolder(2, cancion_aleatoria2);    // Reproduce una canción específica de la carpeta 02.
      Serial.print("Interruptor 2: "); //Muestra el estado del interruptor 2 y la canción que reproduce.
      Serial.print(state2);
      Serial.print(" :: ");
      Serial.println(cancion_aleatoria2);
      digitalWrite(led, LOW);
      digitalWrite(led2, HIGH); // Prende el led asociado al interruptor 1.
      digitalWrite(led3, LOW);
      delay(1000);
    }
  }
  last2  = state2;

  /// Condicional que activa las canciones de la carpeta asociada al tercer interruptor ///
  if (state3 != last3 ) {
    if (state3 == HIGH) {
       int cancion_aleatoria3 = random(1, 5); // Generador de números aleatorios entre 1 y 5.
       myDFPlayer.playFolder(3, cancion_aleatoria3);  // Reproduce una canción específica de la carpeta 03.
      Serial.print("Interruptor 3: "); //Muestra el estado del interruptor 3 y la canción que reproduce.
      Serial.print(state3);
      Serial.print(" :: ");
      Serial.println(cancion_aleatoria3);
      digitalWrite(led, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      delay(1000);
    }
  }
  last3  = state3;
}
