#include <Servo.h>
#include <TM1637Display.h>
#include <SoftwareSerial.h>

// Pin definitions
const int SERVO_PIN = 9;        // Servo di pin 9
const int PROXIMITY_PIN = 2;    // Sensor proximity di pin 4
const int CLK = 5;             // TM1637 Clock pin
const int DIO = 4;             // TM1637 Data IO pin
const int METAL_LED = 6;       // LED indikator metal
const int SERVO_LED = 7;       // LED indikator servo
const int BT_RX = 10;          // Bluetooth RX pin
const int BT_TX = 11;          // Bluetooth TX pin

// Buat objek servo, display dan bluetooth
Servo myServo;
TM1637Display display(CLK, DIO);
SoftwareSerial BT(BT_RX, BT_TX); // Rename bluetooth ke BT

// Variable untuk menghitung gerakan
int counter = 0;
bool isServoOpen = false;      // Status servo
bool lastProximityState = HIGH; // Status terakhir sensor
char command;                  // Variable untuk menyimpan command bluetooth

void setup() {
  // Inisialisasi servo
  myServo.attach(SERVO_PIN);
  myServo.write(0);  // Set posisi awal ke 0 derajat
  
  // Inisialisasi display
  display.setBrightness(5);  // Set kecerahan (0-7)
  display.showNumberDec(0);  // Tampilkan angka 0
  
  // Set pin mode
  pinMode(PROXIMITY_PIN, INPUT);
  pinMode(METAL_LED, OUTPUT);
  pinMode(SERVO_LED, OUTPUT);
  
  // Inisialisasi Serial dan Bluetooth
  Serial.begin(9600);
  BT.begin(9600);
}

void loop() {
  // Baca status sensor proximity
  int proximityState = digitalRead(PROXIMITY_PIN);
  
  // Cek command dari Bluetooth
  if (BT.available() > 0) {
    command = BT.read();
    Serial.print("Received: ");
    Serial.println(command);
    
    switch(command) {
      case '1':
        if (!isServoOpen) {
          openServo();
          BT.println("Command: Servo dibuka");
        }
        break;
        
      case '2':
        if (isServoOpen) {
          closeServo();
          BT.println("Command: Servo ditutup");
        }
        break;
        
      case 'R':
      case 'r':
        resetCounter();
        BT.println("Counter direset");
        break;
    }
  }
  
  // Deteksi perubahan status proximity (edge detection)
  if (proximityState == LOW && lastProximityState == HIGH) {
    // Metal terdeteksi dan servo belum terbuka
    if (!isServoOpen) {
      digitalWrite(METAL_LED, HIGH);  // Nyalakan LED metal
      openServo();
      delay(2000);  // Delay 2 detik
    }
  } 
  else if (proximityState == HIGH && lastProximityState == LOW) {
    // Metal tidak terdeteksi lagi
    digitalWrite(METAL_LED, LOW);   // Matikan LED metal
    if (isServoOpen) {
      closeServo();
    }
  }
  
  // Update status terakhir proximity
  lastProximityState = proximityState;
  
  // Delay kecil untuk stabilitas pembacaan
  delay(50);
}

// Fungsi untuk membuka servo
void openServo() {
  myServo.write(90);  // Gerakkan servo ke 90 derajat
  digitalWrite(SERVO_LED, HIGH);  // Nyalakan LED servo
  counter++;  // Tambah hitungan
  display.showNumberDec(counter);  // Update display
  isServoOpen = true;
  
  // Kirim informasi ke Serial dan Bluetooth
  String message = "Servo terbuka - Hitungan: " + String(counter);
  Serial.println(message);
  BT.println(message);
}

// Fungsi untuk menutup servo
void closeServo() {
  myServo.write(0);   // Servo ke posisi awal
  digitalWrite(SERVO_LED, LOW);   // Matikan LED servo
  isServoOpen = false;
  
  // Kirim informasi ke Serial dan Bluetooth
  Serial.println("Servo tertutup");
  BT.println("Servo tertutup");
}

// Fungsi untuk reset counter
void resetCounter() {
  counter = 0;
  display.showNumberDec(counter);  // Update display
  Serial.println("Counter direset ke 0");
}