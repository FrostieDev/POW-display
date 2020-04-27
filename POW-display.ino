// Pins til skifteregister
//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

// Mode for displayet (Ur/Demo etc)
char mode;

// Magnetføler omgangstid
volatile unsigned long time = 0;
volatile unsigned long last_time = 0;
volatile unsigned long omgangstid;
volatile unsigned long step_tid;
volatile unsigned long udskriv_tid;
int udskriv_raekke;
unsigned long udskriv_tid2 = 0;

//Bluetooth
#include <SoftwareSerial.h>

int bluetoothTx = 4;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 5;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);


// Bytes til skiferegister - Kan også kaldes bølger, hvilket viser hvad den skal vise per bølge.
const int ANTAL_RAEKKER = 60;
int raekke;
int raekke2;
byte tabel[ANTAL_RAEKKER][3];
byte tabel1[ANTAL_RAEKKER][3] = {{
      0b00000000  //1 //RØD
    , 0b11111111      //GRØN
    , 0b11111111      //BLÅ
  },
  {   0b00000000 //2
    , 0b11111111
    , 0b11111111
  },
  {   0b11100111  //3
    , 0b11111111
    , 0b11111111
  },
  {   0b11100111  //4
    , 0b11111111
    , 0b11111111
  },
  {   0b00000000  //5
    , 0b11111111
    , 0b11111111
  },
  {   0b00000000  //6
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //7
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //8
    , 0b11111111
    , 0b11111111
  },
  {   0b00000000  //9
    , 0b11111111
    , 0b11111111
  },
  {   0b00000000  //10
    , 0b11111111
    , 0b11111111
  },
  {   0b00100100  //11
    , 0b11111111
    , 0b11111111
  },
  {   0b00100100  //12
    , 0b11111111
    , 0b11111111
  },
  {   0b00100100  //13
    , 0b11111111
    , 0b11111111
  },
  {   0b00100100  //14
    , 0b11111111
    , 0b11111111
  },
  {   0b00111111  //15
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //16
    , 0b11111111
    , 0b11111111
  },
  {   0b00011111  //17
    , 0b11111111
    , 0b11111111
  },
  {   0b00111111  //18
    , 0b11111111
    , 0b11111111
  },
  {   0b00111111  //19
    , 0b11111111
    , 0b11111111
  },
  {   0b00111111  //20
    , 0b11111111
    , 0b11111111
  },
  {   0b00111111  //21
    , 0b11111111
    , 0b11111111
  },
  {   0b00000000  //22
    , 0b11111111
    , 0b11111111
  },
  {   0b00000000  //23
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //24
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //25
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //26
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //27
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //28
    , 0b11111111
    , 0b11111111
  },
  {   0b11001111  //29
    , 0b11001111
    , 0b11111111
  },
  {   0b11001111  //30
    , 0b11001111
    , 0b11111111
  },
  {   0b11111111  //31
    , 0b11111111
    , 0b10000111
  },
  {   0b11111111  //32
    , 0b11001111
    , 0b00000011
  },
  {   0b11011111  //33
    , 0b11011111
    , 0b00000011
  },
  {   0b11111100  //34
    , 0b11111100
    , 0b00000011
  },
  {   0b11111100  //35
    , 0b11111100
    , 0b00000011
  },
  {   0b11111111  //36
    , 0b11100011
    , 0b10011111
  },
  {   0b11111111  //37
    , 0b11100011
    , 0b10011111
  },
  {   0b11111111  //38
    , 0b11000111
    , 0b10111111
  },
  {   0b11111111  //39
    , 0b11001111
    , 0b11111111
  },
  {   0b11111111  //40
    , 0b11011111
    , 0b11111111
  },
  {   0b11111111  //41
    , 0b10111111
    , 0b11111111
  },
  {   0b11111111  //42
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //43
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //44
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //45
    , 0b11111111
    , 0b11111111
  },
  {   0b11111111  //46
    , 0b11111111
    , 0b11111111
  },
  {   0b10101010  //47
    , 0b10101010
    , 0b11111111
  },
  {   0b01010101  //48
    , 0b11111111
    , 0b01010101
  },
  {   0b11111111  //49
    , 0b10101010
    , 0b10101010
  },
  {   0b01010101  //50
    , 0b01010101
    , 0b01010101
  },
  { 0b11111111  //51
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //52
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //53
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //54
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //55
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //56
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //57
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //58
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //59
    , 0b11111111
    , 0b11111111
  },
  { 0b11111111  //60
    , 0b11111111
    , 0b11111111
  }
}; // Tabel med 2x3 elementer;


void setup() {
  //set pins to output because they are addressed in the main loop - Skifteregister Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  flyt(); // Sørger for at flytte om på bytesne fra skifteregistrene. Så de står i rigtig rækkefølge i forhold til farver i. Se void flyt
  mode = 'D';

  //Magnet interrupt
  attachInterrupt(0, magnet_interrupt, FALLING);

  //Bluetooth
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600

}



void loop() {

  if (micros() > udskriv_tid) {
    if (udskriv_raekke < ANTAL_RAEKKER) {
      digitalWrite(latchPin, LOW);
      // Blå LEDs
      shiftOut(dataPin, clockPin, LSBFIRST, tabel[udskriv_raekke][2]);
      // Grøn LEDs
      shiftOut(dataPin, clockPin, LSBFIRST, tabel[udskriv_raekke][1]);
      // Rød LEDs
      shiftOut(dataPin, clockPin, LSBFIRST, tabel[udskriv_raekke][0]);

      //return the latch pin high to signal chip that it
      //no longer needs to listen for information
      digitalWrite(latchPin, HIGH);
    }
    udskriv_tid = udskriv_tid + step_tid;
    udskriv_raekke = udskriv_raekke + 1;
  }


  if (bluetooth.available()) // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    char c = (char)bluetooth.read();
    Serial.print(c);
    if (c == 'O') {
      bluetooth.print("RPS: ");
      bluetooth.println(1000000.0 / omgangstid);
      Serial.print("RPS: ");
      Serial.println(1000000.0 / omgangstid);
    }
    if (c == 'U') {
      urStart();
      mode = 'U';
    }
    if (c == 'D') {
      flyt();
      mode = 'D';
    }
  }

  if (mode == 'U') {
    urKor();
  }


  if (Serial.available()) // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
  }
}

void urStart() {
  for (int i = 0; i < ANTAL_RAEKKER; i++) {
    for (int j = 0; j < 3; j++) {
      tabel[i][j] = 0;
    }
  }
  raekke = ANTAL_RAEKKER;
  raekke2 = ANTAL_RAEKKER;
  udskriv_tid2 = micros() + 16667;
}

void urKor() {
  if (micros() > udskriv_tid2) {
    udskriv_tid2 = udskriv_tid2 + 16667;
    //   sluk raekke;
    raekke = raekke - 1;
    tabel[raekke][0] = tabel[raekke][0] | 0b11111111;
    tabel[raekke][1] = tabel[raekke][1] | 0b11111110;
    tabel[raekke][2] = tabel[raekke][2] | 0b00000000;
    if (raekke == 0) {
      raekke = ANTAL_RAEKKER;

      for (int i = 0; i < ANTAL_RAEKKER; i++) {
        tabel[i][0] = tabel[i][0] & 0b00000000;
        tabel[i][1] = tabel[i][1] & 0b00000001;
        tabel[i][2] = tabel[i][2] & 0b11111111;
      }
      raekke2 = raekke2 - 1;
      tabel[raekke2][0] = tabel[raekke2][0] | 0b00000000;
      tabel[raekke2][1] = tabel[raekke2][1] | 0b00000001;
      tabel[raekke2][2] = tabel[raekke2][2] | 0b11111111;
      if (raekke2 == 0) {
        raekke2 = ANTAL_RAEKKER;
        for (int j = 0; j < ANTAL_RAEKKER; j++) {
          tabel[j][0] = tabel[j][0] & 0b11111111;
          tabel[j][1] = tabel[j][1] & 0b11111110;
          tabel[j][2] = tabel[j][2] & 0b00000000;
        }
        bluetooth.println("---!!! ALARM !!!---");
      }
    }
  }
}

void flyt() { // Flytter bytes - Se flyt()
  for (int i = 0; i < ANTAL_RAEKKER; i++) {
    //led 1
    bitWrite(tabel[i][2], 0, bitRead(tabel1[i][2], 0));
    bitWrite(tabel[i][2], 1, bitRead(tabel1[i][1], 0));
    bitWrite(tabel[i][2], 2, bitRead(tabel1[i][0], 0));
    //led 2
    bitWrite(tabel[i][2], 3, bitRead(tabel1[i][2], 1));
    bitWrite(tabel[i][2], 4, bitRead(tabel1[i][1], 1));
    bitWrite(tabel[i][2], 5, bitRead(tabel1[i][0], 1));
    //led 3
    bitWrite(tabel[i][2], 6, bitRead(tabel1[i][2], 2));
    bitWrite(tabel[i][2], 7, bitRead(tabel1[i][1], 2));
    bitWrite(tabel[i][1], 0, bitRead(tabel1[i][0], 2));
    //led 4
    bitWrite(tabel[i][1], 1, bitRead(tabel1[i][2], 3));
    bitWrite(tabel[i][1], 2, bitRead(tabel1[i][1], 3));
    bitWrite(tabel[i][1], 3, bitRead(tabel1[i][0], 3));
    //led 5
    bitWrite(tabel[i][1], 4, bitRead(tabel1[i][2], 4));
    bitWrite(tabel[i][1], 5, bitRead(tabel1[i][1], 4));
    bitWrite(tabel[i][1], 6, bitRead(tabel1[i][0], 4));
    //led 6
    bitWrite(tabel[i][1], 7, bitRead(tabel1[i][2], 5));
    bitWrite(tabel[i][0], 0, bitRead(tabel1[i][1], 5));
    bitWrite(tabel[i][0], 1, bitRead(tabel1[i][0], 5));
    //led 7
    bitWrite(tabel[i][0], 2, bitRead(tabel1[i][2], 6));
    bitWrite(tabel[i][0], 3, bitRead(tabel1[i][1], 6));
    bitWrite(tabel[i][0], 4, bitRead(tabel1[i][0], 6));
    //led 8
    bitWrite(tabel[i][0], 5, bitRead(tabel1[i][2], 7));
    bitWrite(tabel[i][0], 6, bitRead(tabel1[i][1], 7));
    bitWrite(tabel[i][0], 7, bitRead(tabel1[i][0], 7));
  }
}


void magnet_interrupt() {
  last_time = time;
  time = micros();
  omgangstid = (time - last_time);

  step_tid = omgangstid / ANTAL_RAEKKER;
  udskriv_tid = time;
  udskriv_raekke = 0;
}



