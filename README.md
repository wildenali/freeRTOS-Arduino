# freeRTOS-Arduino

https://embeddednesia.com/v1/tutorial-freertos-1-rtos-ber-open-source-untuk-perangkat-embedded-dan-iot/

Arsitektur FreeRTOS

FreeRTOS merupakan aplikasi yang relatif berukuran kecil. Inti dari FreeRTOS hanya terdiri 3 file kode sumber C, yang didapat dibagi menjadi tiga bagian, yaitu task, communication dan antarmuka perangkat keras.

Task: Hampir setengah dari inti code FreeRTOS memusatkan perhatiannya pada task. Sebuah task didefinisikan oleh programmer  dalam sebuah fungsi C dengan prioritas yang telah ditentukan. Pengelolaan task yang berupa pembuatan task, penjadwalan, dan pemeliharaan ini dilaksanakan oleh code di dalam task.c dan task.h 
Komunikasi: Pada bagian ini, FreeRTOS mengelola komunikasi antar task, sekitar 40% program inti dari dari FreeRTOS menangani masalah ini. Pekerjaan tersebut diimplementasikan pada queue.c dan queue.h yang berfungsi untuk menangani komunikasi task, dan interupsi menggunakan antrean (queue) untuk mengirim data antar satu task dengan yang lain sekaligus memberikan sinyal penggunaan sumber daya kritikal dengan menggunakan semaphore dan mutex
Hardware Interface : Sekitar 9000 baris program FreeRTOS bersifat hardware independent. code yang sama menjalankan FreeRTOS pada banyak platform mikrokontroler, mulai dari 8051 hingga mikrokontroler dengan arsitektur ARM yang terbaru. Namun 6% inti programnya bergantung pada masing – masing hardware yang digunakan, yang akan dibahas lebih lanjut di dalam sesi yang lain

Fitur FreeRTOS
FreeRTOS memiliki fitur-fitur  standar sebagai berikut

Operasi Pre-emptive atau co-operative
Prioritas penugasan task yang sangat fleksibel
Antrian (Queue)
Semaphore Biner
Mutexes
Mutex Rekursif
Pewaktu Software
Event Groups
Fungsi tick hook
Fungsi idle hook
Pengecekan Stack overflow
Trace Recording
Task run-time statistic gathering
Pilihan dukungan dan lisensi komersial
Model full interupt nesting (untuk beberapa arsitektur mikrokontroler)
Kemampuan tick-less untuk aplikasi di daya yang sangat rendah
Stack interrupt yang dikelola oleh software ketika diperlukan



Sebuah RTOS memberikan manfaat, seperti:

Task scheduling – task dipanggil ketika dibutuhkan menjamin aliran program dan respons event yang lebih baik.
Multitasking – penjadwalan task memberikan ilusi menjalankan sejumlah task secara simultan.
Deterministic behaviour – event dan interupsi ditangani dalam sebuah waktu yang ter-definisi.
Shorter ISR – memungkinkan perilaku interupsi yang lebih dapat ditentukan.
Inter-task communication – mengelola sharing data, memori dan sumber daya perangkat keras diantara beberapa task.
Defined stack usage – setiap task dialokasikan ruang stack, memungkinkan penggunaan memori yang dapat diperkirakan.
System management – memungkinkan kita untuk fokus pada pengembangan aplikasi daripada mengelola sumber daya.


This tutorial use Arduino Mega

# Install FreeRTOS on platformio
pio lib install "feilipu/FreeRTOS"


# 1_BlinkLed