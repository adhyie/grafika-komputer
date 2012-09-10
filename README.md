grafika-komputer
================

Source Code Kuliah Komputer Grafis Informatika UB 

Panduan untuk menjalankan demo program kuliah :

1. Pastikan sebelumnya anda sudah menginstall Visual Studio 2010 Express / Professional
2. Download repository menggunakan tortoise-git atau kopi tarball dari repositori 
   dengan memilih menu ZIP atau https://github.com/e4dams/grafika-komputer/zipball/master.
3. Setelah berhasil mengunduh, buka file (klik 2x di Windows Explorer) Computer_Graphics.sln 
   yang berada di direktori support/msvc100.
4. Untuk membuat project baru copy paste folder ProjectTemplate yang berada di direktori 
   your_projects dan rename folder dan semua file didalamnya.
5. Pada Visual Studio C++ 2010, pilih menu add -> existing projects -> browse file project anda
   lalu perbaiki references project dengan klik kanan project anda di solution explorer lalu pilih 
   references -> Remove Reference -> Add New Reference ... -> pilih GLFW dari daftar reference.

