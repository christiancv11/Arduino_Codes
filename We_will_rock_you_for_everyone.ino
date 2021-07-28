//////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Código para el ejercicio de inclusión de comunidad con hipoacusia en la introducción        //////////////
/// a la teoría musical. En este caso el ejercicio es la clave rítmica de la canción            //////////////
/// "We will rock you" de la banda británica de rock Queen. Se establecen las claves rítmicas   //////////////
/// de la voz, las palmas, y otra superficie percutiva (mesa).                                  //////////////
/// Código elavorado por Christian David para Creatvra el 28/07/2021.                           //////////////
/// La acomodación de las señales lumínicas puede encontrarse en:                               //////////////
/// https://drive.google.com/file/d/1qXQ-SxBZsPOYnPcsFeeUkCrVxUeDEv0H/view?usp=sharing          //////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Librerías para el OLED ////
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
/////////////////////////////////////////

/// Constantes //////////

//---------------------------------------------------------------
#define BUZZER  13      // buzzer pin
#define MIN_BPM 1      // minimum bpm value
#define MAX_BPM 240     // maximum bpm value
#define POT A0          // pot analog pin
//---------------------------------------------------------------


/// Comandos para inicializar el OLED ///////
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

//---------------------------------------------------------------
int bpm;                // bpm value
//---------------------------------------------------------------

void setup() {
  
  pinMode(BUZZER, OUTPUT);  // buzer pin as output
  pinMode(2, OUTPUT);//Led azul - Voz.
  pinMode(3, OUTPUT);//Led azul - Voz.
  pinMode(4, OUTPUT);//Led azul - Voz.
  pinMode(5, OUTPUT);//Led azul - Voz.
  pinMode(6, OUTPUT);//Led amarillo - Palmas.
  pinMode(7, OUTPUT);//Led amarillo - Palmas.
  pinMode(8, OUTPUT);//Led amarillo - Palmas.
  pinMode(9, OUTPUT);//Led amarillo - Palmas.
  pinMode(10, OUTPUT);//Led verde - Mesa.
  pinMode(11, OUTPUT);//Led verde - Mesa.
  pinMode(12, OUTPUT);//Led verde - Mesa.
  pinMode(1, OUTPUT);//Led verde - Mesa.
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
}
//---------------------------------------------------------------

void loop() {

    bpm = map(analogRead(POT), 0, 1023, MIN_BPM, MAX_BPM);  
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(bpm);
    display.display();
    
    tone(BUZZER, 210);       
    digitalWrite(2, HIGH); //Negra 1: We
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW); //Silencio de negra de palmas 1
    digitalWrite(7, LOW); //Silencio de negra de palmas 1
    digitalWrite(8, LOW); //Silencio de negra de palmas 1
    digitalWrite(9, LOW); //Silencio de negra de palmas 1
    digitalWrite(10, HIGH); //Corchea mesa 1
    digitalWrite(11, HIGH); //Corchea mesa 1
    digitalWrite(12, LOW);
    digitalWrite(1, LOW);
    delay((60000 * 0.125) / (bpm));        
    
    noTone(BUZZER);           
    digitalWrite(2, HIGH); //Negra 1: We
    digitalWrite(3, LOW); 
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW); //Silencio de negra de palmas 1
    digitalWrite(7, LOW); //Silencio de negra de palmas 1
    digitalWrite(8, LOW); //Silencio de negra de palmas 1
    digitalWrite(9, LOW); //Silencio de negra de palmas 1
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH); //Corchea mesa 2
    digitalWrite(1, HIGH);  //Corchea mesa 2
    delay((60000 * 0.125) / bpm);       
    
    noTone(BUZZER);           
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH); //Negra 2: Will
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);//Negra de palmas 2
    digitalWrite(7, HIGH);//Negra de palmas 2
    digitalWrite(8, HIGH);//Negra de palmas 2
    digitalWrite(9, HIGH);//Negra de palmas 2
    digitalWrite(10, LOW); //Silencio de negra mesa 3
    digitalWrite(11, LOW); //Silencio de negra mesa 3
    digitalWrite(12, LOW); //Silencio de negra mesa 3
    digitalWrite(1, LOW); //Silencio de negra mesa 3
    delay((60000 * 0.125) / bpm);       
    
    noTone(BUZZER);          
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH); //Negra 2: Will
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);//Negra de palmas 2
    digitalWrite(7, HIGH);//Negra de palmas 2
    digitalWrite(8, HIGH);//Negra de palmas 2
    digitalWrite(9, HIGH);//Negra de palmas 2
    digitalWrite(10, LOW); //Silencio de negra mesa 3
    digitalWrite(11, LOW); //Silencio de negra mesa 3
    digitalWrite(12, LOW); //Silencio de negra mesa 3
    digitalWrite(1, LOW); //Silencio de negra mesa 3
    delay((60000 * 0.125) / bpm);       

    noTone(BUZZER);           
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH); //Negra 3: We
    digitalWrite(5, LOW);
    digitalWrite(6, LOW); //Silencio de negra de palmas 3
    digitalWrite(7, LOW); //Silencio de negra de palmas 3
    digitalWrite(8, LOW); //Silencio de negra de palmas 3
    digitalWrite(9, LOW); //Silencio de negra de palmas 3
    digitalWrite(10, HIGH); //Corchea mesa 4
    digitalWrite(11, HIGH); //Corchea mesa 4
    digitalWrite(12, LOW);
    digitalWrite(1, LOW);
    delay((60000 * 0.125) / bpm);      

    noTone(BUZZER);           
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH); //Negra 3: We
    digitalWrite(5, LOW);
    digitalWrite(6, LOW); //Silencio de negra de palmas 3
    digitalWrite(7, LOW); //Silencio de negra de palmas 3
    digitalWrite(8, LOW); //Silencio de negra de palmas 3
    digitalWrite(9, LOW); //Silencio de negra de palmas 3
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH); //Corchea mesa 5
    digitalWrite(1, HIGH);  //Corchea mesa 5
    delay((60000 * 0.125) / bpm);      

    noTone(BUZZER);           
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH); //Negra 4: Will
    digitalWrite(6, HIGH); //Negra de palmas 4
    digitalWrite(7, HIGH); //Negra de palmas 4
    digitalWrite(8, HIGH); //Negra de palmas 4
    digitalWrite(9, HIGH); //Negra de palmas 4
    digitalWrite(10, LOW); //Silencio de negra mesa 6
    digitalWrite(11, LOW); //Silencio de negra mesa 6
    digitalWrite(12, LOW); //Silencio de negra mesa 6
    digitalWrite(1, LOW); //Silencio de negra mesa 6
    delay((60000 * 0.125) / bpm);       

    noTone(BUZZER);           
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH); //Negra 4: Will
    digitalWrite(6, HIGH); //Negra de palmas 4
    digitalWrite(7, HIGH); //Negra de palmas 4
    digitalWrite(8, HIGH); //Negra de palmas 4
    digitalWrite(9, HIGH); //Negra de palmas 4
    digitalWrite(10, LOW); //Silencio de negra mesa 6
    digitalWrite(11, LOW); //Silencio de negra mesa 6
    digitalWrite(12, LOW); //Silencio de negra mesa 6
    digitalWrite(1, LOW); //Silencio de negra mesa 6
    delay((60000 * 0.125) / bpm); 
    
    ////////////////////////////////////////
    //////  Segundo compás ////////////////
    ////////////////////////////////////////
  
  
    tone(BUZZER, 210);       
    digitalWrite(2, HIGH); //Corchea 5: Rock
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW); //Silencio de negra de palmas 5
    digitalWrite(7, LOW); //Silencio de negra de palmas 5
    digitalWrite(8, LOW); //Silencio de negra de palmas 5
    digitalWrite(9, LOW); //Silencio de negra de palmas 5
    digitalWrite(10, HIGH); //Corchea mesa 7
    digitalWrite(11, HIGH); //Corchea mesa 7
    digitalWrite(12, LOW);
    digitalWrite(1, LOW);
    delay((60000 * 0.125) / (bpm));        
  
    noTone(BUZZER);           
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH); //Corchea 6: You
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW); //Silencio de negra de palmas 5
    digitalWrite(7, LOW); //Silencio de negra de palmas 5
    digitalWrite(8, LOW); //Silencio de negra de palmas 5
    digitalWrite(9, LOW); //Silencio de negra de palmas 5
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH); //Corchea mesa 8
    digitalWrite(1, HIGH);  //Corchea mesa 8
    delay((60000 * 0.125) / bpm);      
    
    noTone(BUZZER);           
    digitalWrite(2, LOW);//Silencio de negra 7
    digitalWrite(3, LOW);//Silencio de negra 7
    digitalWrite(4, LOW);//Silencio de negra 7
    digitalWrite(5, LOW);//Silencio de negra 7
    digitalWrite(6, HIGH); //Negra de palmas 6
    digitalWrite(7, HIGH); //Negra de palmas 6
    digitalWrite(8, HIGH); //Negra de palmas 6
    digitalWrite(9, HIGH); //Negra de palmas 6
    digitalWrite(10, LOW); //Silencio de negra mesa 9
    digitalWrite(11, LOW); //Silencio de negra mesa 9
    digitalWrite(12, LOW); //Silencio de negra mesa 9
    digitalWrite(1, LOW); //Silencio de negra mesa 9
    delay((60000 * 0.125) / bpm);       
    
    noTone(BUZZER);           
    digitalWrite(2, LOW);//Silencio de negra 7
    digitalWrite(3, LOW);//Silencio de negra 7
    digitalWrite(4, LOW);//Silencio de negra 7
    digitalWrite(5, LOW);//Silencio de negra 7
    digitalWrite(6, HIGH); //Negra de palmas 6
    digitalWrite(7, HIGH); //Negra de palmas 6
    digitalWrite(8, HIGH); //Negra de palmas 6
    digitalWrite(9, HIGH); //Negra de palmas 6
    digitalWrite(10, LOW); //Silencio de negra mesa 9
    digitalWrite(11, LOW); //Silencio de negra mesa 9
    digitalWrite(12, LOW); //Silencio de negra mesa 9
    digitalWrite(1, LOW); //Silencio de negra mesa 9
    delay((60000 * 0.125) / bpm);       

    noTone(BUZZER);           
    digitalWrite(2, LOW);//Silencio de negra 7
    digitalWrite(3, LOW);//Silencio de negra 7
    digitalWrite(4, LOW);//Silencio de negra 7
    digitalWrite(5, LOW);//Silencio de negra 7
    digitalWrite(6, LOW); //Silencio de negra de palmas 7
    digitalWrite(7, LOW); //Silencio de negra de palmas 7
    digitalWrite(8, LOW); //Silencio de negra de palmas 7
    digitalWrite(9, LOW); //Silencio de negra de palmas 7
    digitalWrite(10, HIGH); //Corchea mesa 10
    digitalWrite(11, HIGH); //Corchea mesa 10
    digitalWrite(12, LOW);
    digitalWrite(1, LOW);
    delay((60000 * 0.125) / bpm);       
  
    noTone(BUZZER);           
    digitalWrite(2, LOW);//Silencio de negra 7
    digitalWrite(3, LOW);//Silencio de negra 7
    digitalWrite(4, LOW);//Silencio de negra 7
    digitalWrite(5, LOW);//Silencio de negra 7
    digitalWrite(6, LOW); //Silencio de negra de palmas 7
    digitalWrite(7, LOW); //Silencio de negra de palmas 7
    digitalWrite(8, LOW); //Silencio de negra de palmas 7
    digitalWrite(9, LOW); //Silencio de negra de palmas 7
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH); //Corchea mesa 11
    digitalWrite(1, HIGH);  //Corchea mesa 11
    delay((60000 * 0.125) / bpm);       

    noTone(BUZZER);           
    digitalWrite(2, LOW); //Silencio de negra 7
    digitalWrite(3, LOW); //Silencio de negra 7
    digitalWrite(4, LOW); //Silencio de negra 7
    digitalWrite(5, LOW); //Silencio de negra 7
    digitalWrite(6, HIGH); //Negra de palmas 8
    digitalWrite(7, HIGH); //Negra de palmas 8
    digitalWrite(8, HIGH); //Negra de palmas 8
    digitalWrite(9, HIGH); //Negra de palmas 8
    digitalWrite(10, LOW); //Silencio de negra mesa 6
    digitalWrite(11, LOW); //Silencio de negra mesa 6
    digitalWrite(12, LOW); //Silencio de negra mesa 6
    digitalWrite(1, LOW); //Silencio de negra mesa 6
    delay((60000 * 0.125) / bpm);       

    noTone(BUZZER);           
    digitalWrite(2, LOW); //Silencio de negra 7
    digitalWrite(3, LOW); //Silencio de negra 7
    digitalWrite(4, LOW); //Silencio de negra 7
    digitalWrite(5, LOW); //Silencio de negra 7
    digitalWrite(6, HIGH); //Negra de palmas 8
    digitalWrite(7, HIGH); //Negra de palmas 8
    digitalWrite(8, HIGH); //Negra de palmas 8
    digitalWrite(9, HIGH); //Negra de palmas 8
    digitalWrite(10, LOW); //Silencio de negra mesa 6
    digitalWrite(11, LOW); //Silencio de negra mesa 6
    digitalWrite(12, LOW); //Silencio de negra mesa 6
    digitalWrite(1, LOW); //Silencio de negra mesa 6
    delay((60000 * 0.125) / bpm);  
    


   

    

    

    

}
