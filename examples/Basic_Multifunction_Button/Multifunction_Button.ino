#include <Multifunction_Button.h>

// Definisikan pin yang akan digunakan untuk tombol
const int BUTTON_PIN = 2;

// Buat objek dari class Multifunction_Button
Multifunction_Button button;

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi tombol pada pin 2, mode INPUT_PULLUP
  // Artinya tidak butuh resistor eksternal dan tertekan = LOW
  // Timeout multi-click diatur 1000 ms (default)
  button.init(BUTTON_PIN, INPUT_PULLUP, 1000);
  
  Serial.println("Program Test Multifunction Button Dimulai!");
  Serial.println("Silakan klik, tahan, atau lepaskan tombol.");
}

void loop() {
  // 1. Cek apabila tombol diklik biasa (single click)
  if (button.clicked()) {
    Serial.println("Tombol diklik!");
  }

  // 2. Cek apabila tombol diklik beberapa kali (multi click)
  if (button.clicked(3)) {
    Serial.println("Tombol diklik 3 kali!");
  }

  // 3. Cek apabila tombol ditahan (long press) selama lebih dari 2000 ms (2 detik)
  // Ini akan dieksekusi terus-menerus selama tombol masih ditahan melewati 2 detik
  if (button.pressed(2000)) {
    Serial.println("Tombol sedang ditahan lama (> 2 detik)!");
  }

  // 4. Cek apabila tombol dilepas
  if (button.released()) {
    Serial.println("Tombol dilepas!");
  }
}