# Multifunction_Button Library

Library Arduino yang simpel dan multifungsi untuk menangani berbagai jenis interaksi tombol (push button). Library ini sudah dilengkapi dengan fitur *debouncing* internal sehingga pembacaan tombol menjadi lebih stabil.

## Fitur
* **Debouncing Internal:** Mengatasi *bouncing* mekanis pada tombol bawaan.
* **Single Click:** Mendeteksi saat tombol diklik sekali.
* **Multi Click:** Mendeteksi jumlah klik dalam rentang waktu (*timeout*) tertentu.
* **Long Press (Hold):** Mendeteksi apakah tombol ditahan selama durasi tertentu.
* **Released:** Mendeteksi saat tombol dilepas setelah ditekan.
* **Repeat Actions:** Mengeksekusi aksi berulang dengan interval tertentu selama tombol ditahan.

## Instalasi
1. Unduh repositori ini dalam bentuk `.zip`.
2. Buka Arduino IDE.
3. Masuk ke menu **Sketch** -> **Include Library** -> **Add .ZIP Library...**
4. Pilih file `.zip` yang baru saja diunduh.

## Referensi API (Fungsi-Fungsi)

* `void init(int8_t button_pin, uint8_t button_mode, uint16_t timeout = 1000)`: Menginisialisasi pin tombol, mode (misalnya `INPUT_PULLUP`), dan batas waktu untuk multi-click (default 1000ms). Jika mode yang dipilih adalah `INPUT_PULLUP`, library akan otomatis membaca logika `LOW` sebagai tombol tertekan.
* `bool pressed()`: Mengembalikan nilai `true` jika tombol sedang dalam status tertekan (ditekan dan ditahan).
* `bool pressed(uint16_t pressed_long)`: Mengembalikan nilai `true` jika tombol telah ditahan melebihi waktu `pressed_long` dalam satuan milidetik.
* `bool clicked()`: Mengembalikan nilai `true` tepat satu kali (transisi) saat tombol berhasil diklik.
* `bool released()`: Mengembalikan nilai `true` tepat satu kali (transisi) saat tombol dilepas dari tekanan.
* `bool clicked(uint8_t clicked_times)`: Mengembalikan nilai `true` jika tombol telah diklik sebanyak `clicked_times` dalam batas *timeout*.
* `bool repeat(uint16_t interval)`: Mengembalikan nilai `true` secara berulang setiap interval (ms) selama tombol ditahan.
* `void set_debounce_delay(uint16_t debounce_delay = 50)`: Mengubah waktu tunda untuk debounce (bawaannya adalah 50ms).

## Contoh Penggunaan
Lihat direktori `examples/` untuk contoh implementasi yang dapat diuji coba langsung.