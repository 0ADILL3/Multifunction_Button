#pragma once

#include <Arduino.h>

/**
 * @class Multifunction_Button
 * @brief Pustaka pengelola input tombol serbaguna dengan fitur debounce terintegrasi.
 * 
 * Kelas ini mempermudah interaksi tombol fisik maupun virtual secara non-blocking. 
 * Menyediakan berbagai jenis deteksi peristiwa pembacaan tombol:
 * 
 * - Klik tunggal (clicked), lepas (released), dan deteksi multi-klik (clicked_times).
 * 
 * - Penekanan tahan lama (long press) dan pemicu berulang (repeat).
 * 
 * - Beroperasi sebagai sakelar toggle (as_switch).
 * 
 * - Mendukung input dari sumber eksternal melalui update().
 */
class Multifunction_Button
{
  private:
    int8_t button_pin_ = -1;
    uint16_t timeout_ = 1000;
    uint8_t trigger_ = HIGH;
    
    bool pressed_state_ = false;

    bool last_clicked_state_ = false;
    bool last_released_state_ = false;
    bool last_multiclicked_state_ = false;
    bool last_switch_state_ = false;
    
    unsigned long pressed_time_ = 0;
    uint8_t clicked_times_ = 0;
    bool switch_state_ = false;

    uint16_t debounce_delay_ = 50;
    unsigned long last_debounce_time_ = 0;

    unsigned long last_time_ = 0;
    unsigned long last_repeat_time_ = 0;
  
  public:
    /**
     * @brief Konstruktor kelas Multifunction_Button.
     */
    Multifunction_Button();

    /**
     * @brief Menginisialisasi mode dan pin tombol.
     * 
     * Fungsi ini mengatur pin mode pada mikrokontroler dan menetapkan status pemicu (trigger) menjadi LOW jika mode adalah INPUT_PULLUP, atau HIGH untuk mode lainnya.
     * 
     * @param button_pin Pin yang terhubung ke tombol.
     * @param button_mode Mode pin (misalnya INPUT_PULLUP).
     * @param timeout Batas waktu (dalam milidetik) yang digunakan untuk mendeteksi multi click (default 1000 ms).
     */
    void init(int8_t button_pin = -1, uint8_t button_mode = INPUT, uint16_t timeout = 1000);

    /**
     * @brief Memperbarui status tombol secara manual dari sumber eksternal (mode virtual).
     * 
     * Fungsi ini digunakan untuk menyuntikkan status tombol secara langsung ke dalam class 
     * tanpa melalui pembacaan pin fisik maupun proses debounce. Sangat berguna ketika tombol 
     * tidak terhubung ke pin I/O secara langsung, melainkan dikontrol melalui sumber lain 
     * seperti komunikasi I2C, shift register, atau variabel internal dari perangkat lunak.
     * 
     * @param state Status input tombol (true = aktif/ditekan, false = nonaktif/dilepas).
     */
    void update(bool state);

    /**
     * @brief Memeriksa apakah tombol sedang ditekan.
     * 
     * Fungsi ini menggunakan pembacaan digital (digitalRead) yang disertai dengan logika penundaan (debounce) agar status tombol stabil.
     * 
     * @return true jika tombol ditekan, false jika dilepas.
     */
    bool pressed();

    /**
     * @brief Memeriksa apakah tombol ditekan secara tahan lama.
     * 
     * @param pressed_long Durasi waktu penekanan dalam satuan ms.
     * @return true jika tombol ditahan lebih lama dari nilai pressed_long, false jika sebaliknya.
     */
    bool pressed(uint16_t pressed_long);

    /**
     * @brief Memeriksa apakah tombol baru saja diklik.
     * 
     * Mendeteksi transisi perubahan status pada saat tombol mulai ditekan.
     * 
     * @return true hanya pada satu siklus (saat tombol berubah menjadi ditekan), false di siklus lainnya.
     */
    bool clicked();

    /**
     * @brief Memeriksa apakah tombol baru saja dilepas.
     * 
     * Mendeteksi transisi perubahan status pada saat tombol berubah menjadi tidak ditekan.
     * 
     * @return true hanya pada satu siklus (saat tombol dilepas), false di siklus lainnya.
     */
    bool released();

    /**
     * @brief Memeriksa berapa kali tombol diklik (n kali) dalam rentang waktu (timeout) tertentu.
     * 
     * Fungsi ini akan menghitung jumlah klik dan baru akan mereset dan mengembalikan jumlah klik (final_clicks) ketika batas waktu terlewati.
     * 
     * @return Jumlah klik akhir. Mengembalikan 0 jika proses penghitungan belum selesai atau belum ada klik.
     */
    uint8_t clicked_times();

    /**
     * @brief Menjalankan pemicu berulang secara otomatis selama tombol ditahan.
     * 
     * @param interval Jarak waktu antarpemicu dalam satuan ms.
     * @return true setiap kali waktu interval tercapai saat tombol ditahan, false jika belum waktunya atau dilepas.
     */
    bool repeat(uint16_t interval);

    /**
     * @brief Menjadikan tombol bertindak seperti sakelar (toggle switch).
     * 
     * Status variabel sakelar akan berbalik (toggle) setiap kali ada transisi tombol yang diklik.
     * 
     * @return Status sakelar terbaru (true atau false).
     */
    bool as_switch();

    /**
     * @brief Mengambil informasi berapa lama tombol telah ditahan.
     * 
     * Waktu penekanan ini dikalkulasi dengan mencari selisih waktu sistem (millis()) dengan variabel pressed_time_.
     * 
     * @return Waktu penekanan berjalan dalam satuan ms.
     */
    unsigned long get_pressed_time();

    /**
     * @brief Mengambil nilai sementara dari jumlah klik yang sudah dilakukan (n times).
     * 
     * @return Variabel internal clicked_times_ dalam bentuk integer.
     */
    uint8_t get_clicked_times();

    /**
     * @brief Mengatur waktu tunda debounce pada tombol.
     * 
     * Mengubah nilai debounce_delay_ internal.
     * 
     * @param debounce_delay Nilai waktu tunda dalam satuan ms (default 50).
     */
    void set_debounce_delay(uint16_t debounce_delay = 50);
};