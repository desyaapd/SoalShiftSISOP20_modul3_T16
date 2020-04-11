# SoalShiftSISOP20_modul3_T16

- I Gede Arimbawa Putra Teja Wardana -- 05311840000045
- Desya Ananda Puspita Dewi -- 05311840000046


## Soal 4
Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan setiap batunya memiliki warna yang berbeda. 

Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di pilar tersebut. Norland menghampiri setiap pilar secara bergantian. 

-	**Batu mulia pertama. Emerald**. Batu mulia yang berwarna hijau mengkilat. Pada batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi: 

1. Buatlah program C dengan nama "4a.c", yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka). 

2. Tampilkan matriks hasil perkalian tadi ke layar. 

-	**Batu kedua adalah Amethyst**. Batu mulia berwarna ungu mengkilat. Teka-tekinya adalah: 

1. Buatlah program C kedua dengan nama "4b.c". Program ini akan mengambil variabel hasil perkalian matriks dari program "4a.c" (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar. 
(Catatan!: gunakan shared memory) 

2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan format seperti matriks. 

Contoh: misal array [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], ...], maka: 
1 2 6 24 120 720 ... ... ... (Catatan! : Harus menggunakan Thread dalam penghitungan faktorial) 

-	**Batu ketiga adalah Onyx**. Batu mulia berwarna hitam mengkilat. Pecahkan teka-teki berikut! 

1. Buatlah program C ketiga dengan nama "4c.c". Program ini tidak 
memiliki hubungan terhadap program yang lalu. 

2. Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command `ls | wc –l`. Karena sudah belajar IPC, Norland mengerjakannya dengan semangat. 

(Catatan! : Harus menggunakan IPC Pipes) 

Begitu batu terakhir berhasil didapatkan. Gemuruh yang semakin lama semakin besar terdengar. Seluruh tempat berguncang dahsyat, tanah mulai merekah. Sebuah batu yang di atasnya terdapat kotak kayu muncul ke atas dengan sendirinya. 

Sementara batu tadi kembali ke posisinya. Tanah kembali menutup, seolah tidak pernah ada lubang merekah di atasnya satu detik lalu. 

Norland segera memasukkan tiga buah batu mulia Emerald, Amethys, Onyx pada Peti Kayu. Maka terbukalah Peti Kayu tersebut. Di dalamnya terdapat sebuah harta karun rahasia. Sampai saat ini banyak orang memburu harta karun tersebut. Sebelum menghilang, dia menyisakan semua petunjuk tentang harta karun tersebut melalui tulisan dalam buku catatannya yang tersebar di penjuru dunia. "One Piece does exist".


### Soal 4a.c
___Source code :[ Soal4a.c ](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/soal4/soal4a.c)___

-	Buatlah program C dengan nama "4a.c", yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka). 

-	Tampilkan matriks hasil perkalian tadi ke layar. 

(Catatan!: gunakan shared memory) 

**Penjelasan:**

Menurut kami, soal ini merupakan program yang dijalankan untuk menghitung hasil perkalian matriks. Perkalian yang diinginkan yaitu perkalian matriks 4x2 dengan 2x5

```bash
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

//deklarasi isi matriks
int matA[4][2] = {{1,2},{2,3},{3,4},{4,5}};
int matB[2][5] = {{1,1,1,1,1},{1,1,1,1,1}};
int (*matC)[5];

int row = 0, i, j, k;
```

-	Pada bagian pertama, kami membuat array dan matriks ordo yang akan dihitung. matA merupakan matirks 4x2, matB merupakan matriks 2x5, dan matC merupakan variable untuk hasil output dari perkalian matriks

```bash
void* mult(void* arg) {
  i = row++;
for (j = 0; j < 5; j++) 
for (k = 0; k < 2; k++) matC[i][j] += matA[i][k] * matB[k][j];
}
```

-	Fungsi perklian menggunakan `arg` sebagai argumennya

-	Untuk for() loop, variable `k` digunakan sebagai nilai kesamaan pada ordo matriks yang mengulang sebanyak 2 kali (kolom matriks A dan baris matriks B)



-	Hasil perkalian akan masuk ke dalam `matC` yang merupakan perkalian dari baris pada matriks A dan kolom pada matriks B

```bash
//fungsi shared memory untuk soal berikutnya
int main() {
	key_t key = 1234;
  int shmid = shmget(key, sizeof(int[4][5]), IPC_CREAT | 0666);
  matC = shmat(shmid, 0, 0);
```
-	Argument ini merupakan pembuatan shared memory untuk `matC` yang sesuai dengan template di dalam modul3 

-	`key_t key = 1234;` merupakan requesting source yang digunakan dalam sebuah proses shared memory. Penggunaan kunci ini yaitu untuk membagikan resource yang sama. Resource yang diambil yaitu resource hasil matriks dari soal sebelumnya sehingga dibutuhkan lah key_t tersebut

-	` int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);` digunakan untuk menemukan akses pada system untuk mencari segmen memori kemudian membuat memori bersama dengan `IPC_CREAT`

-	Argument ini akan berbagi memori dengan soal selanjutnya yaitu soal 4b, dimana key yang digunakan yaitu `key_t key = 1234`. Key disini merupakan key *private* yang hanya mengizinkan adanya `0666` yairu berupa _read and write_.

```bash
pthread_t tid[4];
//proses thread
for (i = 0; i < 4; i++) 
pthread_create(&(tid[i]), NULL, &mult, NULL);
for (i = 0; i < 4; i++) 
pthread_join(tid[i], NULL);
```
-	Kemudian, `pthread_create(&tid[i], NULL, &mult, NULL);` membuat thread pada array dari thread bernama `tid` pada nilai `i`  dengan memanggil fungsi kali dengan parameter `NULL`

-	Lalu dilanjutkan dengan menggabungkan semua thread yang ada
```bash
  for (i = 0; i < 4; i++) {
for (j = 0; j < 5; j++) {
      printf("%2d ", matC[i][j]);
		}
		printf("\n");
  }
  // shmdt(matC);
  // shmctl(shmid, IPC_RMID, NULL);
}
```

-	`shmdt(matC);` melepaskan segmen memori bersama yang terletak pada alamat yang dituju, yaitu alamat matC

-	`shmctl(shmid, IPC_RMID, NULL);` kemudian dengan `IPC_RMID` digunakan untuk menghapus memori bersama yang telah berada dalam parameter `shmid	` lalu melampirkan hasil dari segmen memori bersama terakhir yang akan kembali ke `shmctl`,

-	Kemudian, kami melakukan printf dengan `printf(“%2d ”, matC[i][j]);` yang akan melakukan for() loop untuk masing masing baris serta kolom sebanyak jumlahnya, dimana `i` merupakan baris sebanyak 4 dan `j` merupakan kolom sebanyak 5.

**Output**

![Capture](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/image/soal4a.PNG)


### Soal 4b.c
___Source code : [ Soal4b.c ](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/soal4/soal4b.c)___

-	Buatlah program C kedua dengan nama "4b.c". Program ini akan mengambil variabel hasil perkalian matriks dari program "4a.c" (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar. 

-	Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan format seperti matriks. 

(Catatan!: gunakan shared memory) 

**Penjelasan:**

Maksud dari soal 4b adalah, kami membuat matriks yang akan digunakan sebagai shared memory

```bash
#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <stdlib.h>

//deklarasi variable hasil output soal4a
int (*matC)[5];
int row = 0, n, i, j, k;
```
Proses diawali dengan mendeklarasikan variable output dari soal 4a sebelumnya. Hasil output diambil dari hasil `matC`

```bash
//output dari soal4a difaktorial kan
void* func(void* arg) {
  i = row++;
  for (size_t j = 0; j < 5; j++) {
    n = 0;
    for (k = 1; k < matC[i][j]; k++) n += k;
    matC[i][j] += n;
  }
}
```
-	Fungsi `i = row++;` mengambil angka pada tiap row dari hasil output matriks sebelumnya untuk melakukan looping

-	`for (k = 1; k < matC[i][j]; k++) n += k;` proses factorial dari hasil output dimana faktorialnya tidak dikali namun ditambah. Hal ini diubah dengan perintah `matC[i][j] += n;` yang dapat menambah hasil output

```bash
//fungsi shared memory dari soal 4a
int main() {
  key_t key = 1234;
  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  matC = shmat(shmid, 0, 0);
```
-	Argument ini merupakan pembuatan shared memory untuk `matC` yang sesuai dengan template di dalam modul3 

-	`key_t key = 1234;` merupakan requesting source yang digunakan dalam sebuah proses shared memory. Penggunaan kunci ini yaitu untuk membagikan resource yang sama. Resource yang diambil yaitu resource hasil matriks dari soal sebelumnya sehingga dibutuhkan lah key_t tersebut

-	` int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);` digunakan untuk menemukan akses pada system untuk mencari segmen memori kemudian membuat memori bersama dengan `IPC_CREAT`

-	Argument ini akan berbagi memori dengan soal selanjutnya yaitu soal 4b, dimana key yang digunakan yaitu `key_t key = 1234`. Key disini merupakan key *private* yang hanya mengizinkan adanya `0666` yairu berupa _read and write_.

```bash
  //proses thread
pthread_t tid[4];
  for (i = 0; i < 4; i++) 
    pthread_create(&(tid[i]), NULL, &func, NULL);
  for (i = 0; i < 4; i++) 
    pthread_join(tid[i], NULL);
```
-	Kemudian, `pthread_create(&tid[i], NULL, &mult, NULL);` membuat thread pada array dari thread bernama `tid` pada nilai `i`  dengan memanggil fungsi kali dengan parameter `NULL`

-	Lalu dilanjutkan dengan menggabungkan semua thread yang ada

 ```bash
 //output hasil faktorial 
printf("MATRIKS :\n");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 5; j++) {
      printf("%2d ", matC[i][j]);
		}
		printf("\n");
  }
  shmdt(matC);
  shmctl(shmid, IPC_RMID, NULL);
}
```
-	`shmdt(matC);` melepaskan segmen memori bersama yang terletak pada alamat yang dituju, yaitu alamat matC

-	`shmctl(shmid, IPC_RMID, NULL);` kemudian dengan `IPC_RMID` digunakan untuk menghapus memori bersama yang telah berada dalam parameter `shmid	` lalu melampirkan hasil dari segmen memori bersama terakhir yang akan kembali ke `shmctl`,

-	Kemudian, kami melakukan printf dengan `printf(“%2d ”, matC[i][j]);` yang akan melakukan for() loop untuk masing masing baris serta kolom sebanyak jumlahnya, dimana `i` merupakan baris sebanyak 4 dan `j` merupakan kolom sebanyak 5.

**Output**

![Capture](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/image/soal4b.png)


### Soal 4c.c
___Source code : [ Soal4c.c ](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/soal4/soal4c.c)___

-	Buatlah program C ketiga dengan nama "4c.c". Program ini tidak memiliki hubungan terhadap program yang lalu. 

-	Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command `ls | wc –l`. Karena sudah belajar IPC, Norland mengerjakannya dengan semangat. 

(Catatan! : Harus menggunakan IPC Pipes) 

**Penjelasan:**

Program ini merupakan program yang akan menampilkan banyaknya file yang berada di dalam direktori yang sedang aktif pada saat itu dengan menggunakan IPC pipes

```bash
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  int fd[2];
  pid_t pid;
pipe(fd);
```
- Program ini dijalankan dengan menggunakan **IPC Pipes**, sehingga yang pertama kali yang haru sdilakukan yaitu mendeklarasikan pipes tersebut dengan `pipe (fd)`

- `fd` merupakan _file descriptor_ yang berjumlah 2 untuk menjalankan 2 pipes untuk fungsi _read_ fan untuk fungsi _write_

```bash
  pid = fork();
  if (pid == 0) {
    dup2(fd[1], 1);
    close(fd[0]);
    char *argv[] = {"ls", NULL};
    execv("/bin/ls", argv);
  }
  while(wait(NULL) > 0);
```
- Terdapat fungsi `fork()` untuk parent processnya, ia akan membuat copy terhadap `fd[1]` dimana `[1]` merupakan fungsi _write end_ dari pipe

- Kemudian `ls` disini akan menampilkan dema `dir` dan 	`file` yang tersimpan dalam pointer `*argv` yang akan berjalan satu kali saja, sehingga child process harus menunggu fungsi parent process dengan `while(wait(NULL) > 0);`

```bash
  dup2(fd[0], 0);
  close(fd[1]);
  char *argv[] = {"wc", "-l", NULL};
  execv("/usr/bin/wc", argv);
}
```
- `dup2(fd[0], 0);` merupakan fungsi _read_ dari pipe baru sehingga ia akan menjadi input baru dengan melakukan perintah `{"wc", "-l", NULL};` yang berfungsi untuk menghitung banyaknya file dan folder yang berada di direktori yang akan di set oleh pointer `*argv[]`

- Terakhir, program akan menjalankan `execv("/usr/bin/wc", argv);` yang kemudian akan menampilkan jumlah perhitungannya apabila dijalankan
 
**Output**

![Capture](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/image/soal4c.PNG)
