////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Código para un prototipo de radio emisora en AM con Arduino.                              /////////////////////////////
//// Se ha adicionado un display OLED para dar un mensaje y mostrar la frecuencia de emisión.  /////////////////////////////
//// Se puede conectar un micrófono o directamente una fuente de sonido.                       /////////////////////////////
////                                                                                           /////////////////////////////
//// Elaborado por Christian David para Creatvra en el marco del proyecto .                    /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//dar permisos desde Linux sudo chmod a+rw /dev/ttyACM0

///// Librerías para el display OLED //////////////////

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//---------------------------------------------------------------

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





#define ANTENNA_PIN PB3 //Arduino Nano/Uno Pin D11

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	//Secuencia para la generación de la frecuencia
	uint32_t fTransmit = 1600; //KHz -- Se ha escogido 1600 porque así emite en 1600. Cuando se escoge, por ejemplo, 600 emite en 615. La mayoría de dispositivos en Colombia saltan de 10 en 10.
	DDRB |= (1 << ANTENNA_PIN);
	TCCR2A = (0 << COM2A1) + (1 << COM2A0); //Toggle OC0A on Compare Match
	TCCR2A |= (1 << WGM21) + (0 << WGM20); //CTC
	TCCR2B = (0 << CS22) + (0 << CS21) + (1 << CS20); //No Prescaling
	OCR2A = F_CPU / (2000 * fTransmit) - 1;
	
	char strbuf[255];
	sprintf(strbuf, "Emitiendo en %d KHz", (F_CPU / (2 * (1 + OCR2A)) / 1000)); //Mensaje de confirmación.
	Serial.println(strbuf);

	//PWM Signal generation
	//TCCR1A |= (0 << WGM11) + (1 << WGM10);  //Fast PWM 8 Bit
	//TCCR1A |= (1 << WGM11) + (0 << WGM10);  //Fast PWM 9 Bit
	TCCR1A |= (1 << WGM11) + (1 << WGM10); //Fast PWM 10 Bit
	TCCR1B = (1 << WGM12);					
	TCCR1B |= (0 << CS12) + (0 << CS11) + (1 << CS10); //No Prescaling
	TIMSK1 = (1 << OCIE1A) + (1 << TOIE1);

	//ADC Settings
	ADMUX = (1 << REFS1) + (1 << REFS0); //Reference internal 1.1V
	ADCSRA = (1 << ADEN) + (1 << ADSC) + (1 << ADATE); //Auto Trigger enable, free running
	ADCSRA |= (1 << ADPS2) + (1 << ADPS1) + (0 << ADPS0); //Divide by 64 -> 18.5k Sample rate
	DIDR0 = (1 << ADC0D);

  // Aspectos para el display OLED //
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0); // Fija la posición de la primera frase que aparece de arriba hacia abajo.
  display.println("Radio Comunitaria"); //Texto de la frase.
  display.setCursor(20,10);// Fija la posición de la continuación de la frase.
  display.println("Cali"); // Texto de la continuación.
  display.setCursor(0,20); // Fija la posición de la frase de confirmación.
  display.println(strbuf); // Texto de confirmación.
  
  display.display();

  pinMode(7, OUTPUT); // Definición del pin del led que indica que está emitiendo.
  digitalWrite(7, HIGH);
}

//Aspectos adicionales del código de emisión.
ISR(TIMER1_OVF_vect) {
	uint8_t adcl = ADCL;
	uint8_t adch = ADCH;
	OCR1A = (adch << 8) + adcl;
	DDRB |= (1 << ANTENNA_PIN);
}

ISR(TIMER1_COMPA_vect) {
	DDRB &= ~(1 << ANTENNA_PIN);
}

void loop() {
}
