🌱 Real-Time Plant Environment Monitoring System. Mengintegrasikan ESP8266 (NodeMCU) + DHT11 dengan Supabase untuk menampilkan data suhu dan kelembaban tanaman secara real-time melalui web dashboard modern.
# 🌱 PlantGrow: Real-Time Plant Environment Monitoring System



Proyek **PlantGrow** adalah solusi *monitoring* lingkungan yang efisien dan murah untuk memantau suhu dan kelembaban tanaman secara *real-time*. Proyek ini dirancang menggunakan arsitektur *full-stack* modern, menggabungkan perangkat keras populer (ESP8266 + DHT11) dengan layanan *backend* tanpa server (Supabase) dan *dashboard* berbasis *browser* yang *responsive* (Tailwind CSS).

Tujuan utama dari proyek ini adalah memberikan data lingkungan yang akurat dan *up-to-date* untuk membantu petani atau penghobi tanaman mengambil keputusan yang tepat.

## 🌟 Fitur Utama

* **Real-Time Data:** Pengambilan data suhu (°C) dan kelembaban (%) dari sensor DHT11 setiap 30 detik.
* **Serverless Backend:** Menggunakan **Supabase** (PostgreSQL) sebagai database utama, menghilangkan kebutuhan untuk mengelola server.
* **Web Dashboard Modern:** Tampilan *dashboard* web yang bersih, *dark-mode friendly*, dan *responsive* menggunakan **Tailwind CSS**.
* **Log & Analisis:** Fitur log data dan *pagination* tabel untuk meninjau riwayat pembacaan sensor.
* **Status Alert:** Penentuan status (**Normal, Warning, Critical**) berdasarkan ambang batas suhu dan kelembaban.

---

## 🏗️ Arsitektur Proyek

Proyek ini terbagi menjadi tiga komponen utama:

### 1. 💾 Hardware / Microcontroller

| Komponen | Deskripsi |
| :--- | :--- |
| **Microcontroller** | ESP8266 (NodeMCU) |
| **Sensor** | DHT11 (Suhu dan Kelembaban) |
| **Komunikasi** | WiFi, Protokol HTTP/HTTPS |
| **Codebase** | Arduino IDE (C++) |

### 2. ☁️ Backend / Database

| Komponen | Deskripsi |
| :--- | :--- |
| **Platform** | Supabase |
| **Database** | PostgreSQL |
| **Fungsi** | Menerima data JSON dari ESP8266 dan menyediakan API REST untuk *dashboard* web. |

### 3. 🌐 Frontend / Dashboard

| Komponen | Deskripsi |
| :--- | :--- |
| **Framework** | Tailwind CSS |
| **Fungsi** | Mengambil data dari Supabase API, memprosesnya, dan menampilkannya dalam tabel log yang *paginated*. |
| **Bahasa** | HTML, Vanilla JavaScript |

---

## ⚙️ Panduan Instalasi (Setup)

Ikuti langkah-langkah sederhana ini untuk menjalankan proyek Anda:

### A. Setup Supabase

1.  Buat akun Supabase baru dan buat proyek baru.
2.  Di bagian **Table Editor**, buat tabel baru (misalnya `Sensor`) dengan kolom berikut:
    * `id` (int8 - Primary Key, Identity)
    * `time` (timestamp with timezone - default: `now()`)
    * `suhu` (float8)
    * `kelembaban` (float8)
3.  Ambil **SUPABASE_URL** dan **API_KEY** Anda dari Settings -> API.

### B. Setup ESP8266 (Kode Arduino)

1.  Buka kode Arduino (file `esp8266_code.ino` atau sejenisnya) di repositori ini.
2.  Ganti variabel berikut dengan kredensial WiFi dan Supabase Anda:
    ```cpp
    const char* ssid = "NAMA_WIFI_ANDA";
    const char* password = "PASSWORD_WIFI_ANDA";
    
    const char* supabase_url = "URL_REST_ANDA"; 
    const char* api_key = "KEY_API_ANDA";
    ```
3.  Upload kode ke ESP8266 Anda. Pastikan Wiring DHT11 sudah benar (misalnya ke D2/GPIO4).

### C. Setup Web Dashboard

1.  Buka file `index.html` (atau file dashboard utama Anda).
2.  Di dalam tag `<script>` (JavaScript), ganti konstanta `SUPABASE_URL` dan `API_KEY` dengan kredensial Supabase Anda (sama seperti langkah A.3).
3.  Buka file `index.html` di browser Anda. Data harus otomatis mulai dimuat ke dalam tabel.

---

## 🤝 Kontribusi

Proyek ini bersifat *open-source*. Setiap kontribusi, laporan *bug*, atau saran sangat disambut baik!

1.  *Fork* repositori ini.
2.  Buat *branch* baru: `git checkout -b feature/nama-fitur-anda`.
3.  *Commit* perubahan Anda: `git commit -m 'feat: Tambahkan fitur X'`.
4.  *Push* ke *branch*: `git push origin feature/nama-fitur-anda`.
5.  Buat Pull Request baru.

## 📜 Lisensi

Proyek ini dilisensikan di bawah Lisensi MIT. Lihat file [LICENSE] untuk detail lebih lanjut.

***

### File-file Tambahan yang Disarankan

Untuk membuat repositori lebih lengkap, pertimbangkan untuk menyertakan file-file ini (jika belum ada):

1.  **`esp8266_code.ino`**: File utama kode Arduino untuk ESP8266.
2.  **`LICENSE`**: File lisensi (MIT disarankan).
3.  **`index.html`**: File utama *dashboard* web.
4.  **`WIRING.md`** (Opsional): Diagram atau deskripsi singkat tentang cara menghubungkan DHT11 ke ESP8266.
