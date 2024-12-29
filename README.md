[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/OxmXQmdu)
# IF2110 - Algoritma dan Struktur Data 2024
> Tugas Besar - IF2110 Algoritma dan Struktur Data 2024

# PurryMail
![alt text](https://github.com/Labpro-21/if2110-tugas-besar-2024-if2110-01-a/blob/main/doc/PurryMailLogo.png?raw=true)

## Description
PurryMail adalah program simulasi berbasis CLI (_command-line interface_). Program ini dibentuk menggunakan bahasa pemrograman C dengan memanfaatkan berbagai macam struktur data yang telah dipelajari pada mata kuliah Algoritma dan Struktur Data. PurryMail menjadi _platform_ bagi pengguna untuk saling bertukar pesan, menandai pesan penting, mencari pesan menggunakan fitur _search_, melakukan enkripsi dan dekripsi data rahasia, menentukan jadwal kosong di antara dua pihak, dan berbagai fitur-fitur lainnya yang membantu Agen-Agen OWCA dalam melawan Tuan Asep Spakbor dan menyelamatkan hari.

## Kelompok A - Kelas 01
| Nama                  | NIM      |
|-----------------------|----------|
| Rafen Max Alessandro  | 13523031 |
| M. Rayhan Farrukh     | 13523035 |
| Muhammad Fithra Rizki | 13523049 |
| David Bakti Lodianto  | 13523083 |
| Reza Ahmad Syarif     | 13523119 |

Dengan Asisten: 
| Nama                  | NIM      |
|-----------------------|----------|
| Brian Kheng           | 13521049 |

## How To Run
### Prerequisites
- OS Berbasis UNIX  (Linux, macOS, atau WSL untuk Windows)
- GCC compiler
- Make utility
- Git

### Cloning and Execution
1. Jalankan perintah berikut pada terminal untuk melakukan _clone_ pada repositori:
```markdown
git clone https://github.com/Labpro-21/if2110-tugas-besar-2024-if2110-01-a.git
```
2. Buka folder repositori pada IDE lokal Anda.
3. Program dijalankan menggunakan Makefile pada sistem operasi berbasis UNIX. WSL dapat digunakan untuk membentuk _environment_ seperti UNIX.
4. Buka terminal di direktori repositori, lalu jalankan perintah berikut:
```markdown
make all
```
5. Program telah berhasil dijalankan! selamat berperan sebagai Agen OWCA! 🎉

## Features

Semua fitur yang ada di bawah ini 100% selesai dan terimplementasi di program utama.
(⭐ *Fitur Bonus)

- Inisiasi
- User
- Draft Email
- Inbox
- Reply
- Status Kepentingan
- Notifikasi
- Save & Load
- ⭐ Starred Email 
- ⭐ Searching
- ⭐ Enkripsi Pesan
- ⭐ Jadwal Kesibukan 
- ⭐ Scheduling

## Project Structure

```
│ README.md
│ .gitignore
│ Makefile
│
├─── bin
│       │ main
│       
├─── doc
│       │ IF2110-TB-A-01.pdf
│       │ PurryMailLogo.png
│
├─── src
│       | main.c
│       └─── modules
│               ├─── busy_schedule
│               ├─── datetime
│               ├─── display_inbox
│               ├─── email_list
│               ├─── encryption
│               ├─── importance_status
│               ├─── inisiasi
│               ├─── matrix
│               ├─── reply
│               ├─── search
│               ├─── stack
│               ├─── tree
│               ├─── user
│               ├─── utility
│
└─── config
        ├─── config1
        ├─── config2

```

## Task Distribution

| Nama                        | ADT                                                        | Fitur                                               |
| --------------------------- | ---------------------------------------------------------- | --------------------------------------------------- | 
| Rafen Max Alessandro        | Datetime                                                   | Inbox, Starred Email                                |
| M. Rayhan Farrukh           | Tree                                                       | Reply, Enkripsi Pesan                               |
| Muhammad Fithra Rizki       | Stack, Queue                                               | Draft Email, Notifikasi                             |
| David Bakti Lodianto        | List Statik, List Dinamis, String, Mesin Karakter dan Kata | User, Inisiasi, Save & Load, Searching              |
| Reza Ahmad Syarif           | Matriks, Mesin Karakter dan Kata                           | Status Kepentingan, Jadwal Kesibukan, Scheduling    |
