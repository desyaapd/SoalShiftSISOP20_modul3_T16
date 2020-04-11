# SoalShiftSISOP20_modul3_T16

1. I Gede Arimbawa Putra Teja Wardana - 05311840000045
2. Desya Ananda Puspita Dewi - 05311840000046

## Soal 3

Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan. 

Program ini memiliki ketentuan untuk beberapa opsi yang tersedia yakni :
- `-f` untuk kategorisasi file yang telah ditentukan 
- `-d` untuk kategorisasi di folder yang telah ditentukan 
- `\*` untuk kategorisasi di folder dimana program tersebut berada

**Penyelesaian:**

___Source code :[ Soal3.c ](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/soal3/soal3.c)___

```bash
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>

char *getNamaFile(char *fName, char buff[]) {
  char *token = strtok(fName, "/");
  while (token != NULL) {
    sprintf(buff, "%s", token);
    token = strtok(NULL, "/");
  }
}
```

Setelah menuliskan beberapa library yang membantu jalannya program, kita akan mendapatkan nama dari file tersebut dengan menggunakan fungsi `*getNamaFile`

```bash
char *getExtension(char *fName, char buff[]) {
  char buffNamaFile[1337];
  char *token = strtok(fName, "/");
  while (token != NULL) {
    sprintf(buffNamaFile, "%s", token);
    token = strtok(NULL, "/");
  }
  ```
 
 - Selain mendapatkan namadari file, kita juga harus mendapatkan ekstensi dari file sebagai kunci untuk melakukan kateorisasi tiap file
 
  ```bash
  if (count <= 1) {
    strcpy(buff, "unknown");
  }

  return buff;
}
```

- Setelah mendapatkan ekstensinya, maka ekstensi akan ditampilkan dalam `buffer` . jika terdapat file yang tidak memiliki ekstensi, maka `buffer` akan berisi `"unknown"`

```bash
void dirChecking(char buff[]) {
  DIR *dr = opendir(buff);
  if (ENOENT == errno) {
    mkdir(buff, 0775);
    closedir(dr);
  }
}
```

- Berikutnya, akan dilakukan pembuatan direktori baru dengan fungsi `mkdir`, setelah itu nama dari direktori tersebut akan disimpan didalam `buffer`

```bash
  if (access(buffFrom, F_OK) == -1) {
    printf("File %s tidak ada\n", buffFrom);
    pthread_exit(0);
  }
  DIR* dir = opendir(buffFrom);
  if (dir) {
    printf("file %s berupa folder\n", buffFrom);
    pthread_exit(0);
  }
  closedir(dir);
  ```
  - Lalu, program akan melakukan pengecekan terhadap ekstensi dan file yang telah diinputkan oleh user
  - kemudian terdapat pemanggilan fungsi `getNamaFile` yang namanya tersimpan di dalam `buffer` kemudian berpindah ke `buffNamaFile`, sama halnya dengan `getExtension` untuk mengambil setiap ekstensi yang berada di `buffFrom` 
  
```bash
int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("Argument kurang\n");
    exit(1);
  }
  if (strcmp(argv[1], "-f") != 0 && strcmp(argv[1], "*") != 0 && strcmp(argv[1], "-d")) {
    printf("Argument tidak ada\n");
    exit(1);
  }

  if (strcmp(argv[1], "-f") == 0) {
    if (argc <= 2) {
      printf("Argument salah\n");
      exit(1);
    }

    pthread_t tid[argc-2];
    for (int i = 2; i < argc; i++) {
      pthread_create(&tid[i-2], NULL, &routine, (void *)argv[i]);
    }
    for (int i = 2; i < argc; i++) {
      pthread_join(tid[i-2], NULL);
    }
    exit(0);
  }
  ```
  - Dalam fungsi `main` terdapat beberapa fungsi untuk melakukan pengecekan untuk setiap argumen yang diinputkan.
  
  - Code di atas akan menampilkan "Argumen Kurang" apabila argumen yang diberikan tidaklah berjumlah dua argumen. Dalam program ini, user diminta untuk menginputkan dua argumen yakni `argc` dan `argv`.

   - Apabila argumen yang diinputkan oleh user tidak sesuai dengan ketentuan argumen yang diminta oleh soal maka program akan menampilkan bahwa "Argumen tidak ada" atau "Argumen salah". Code berikut untuk argumen `-f` 
```bash
  char *directory;
  if (strcmp(argv[1], "*") == 0) {
    if (argc != 2) {
      printf("Argument salah\n");
      exit(1);
    }
    char buff[1337];
    getcwd(buff, sizeof(buff));
    directory = buff;
  }
  ```
  - Apabila argumen yang diinputkan oleh user tidak sesuai dengan ketentuan argumen yang diminta oleh soal maka program akan menampilkan bahwa "Argumen tidak ada" atau "Argumen salah". Code berikut untuk argumen `*` 
  
```bash
  if (strcmp(argv[1], "-d") == 0) {
    if (argc != 3) {
      printf("Argument salah\n");
      exit(1);
    }
    DIR* dir = opendir(argv[2]);
    if (dir) {
      directory = argv[2];
    } else if (ENOENT == errno) {
      printf("Directory tidak ada\n");
      exit(1);
    }
    closedir(dir);
  }
  ```  
  
  - Apabila argumen yang diinputkan oleh user tidak sesuai dengan ketentuan argumen yang diminta oleh soal maka program akan menampilkan bahwa "Argumen tidak ada" atau "Argumen salah". Code berikut untuk argumen `-d` 

```bash
  pthread_t tid[file_count];
  char buff[file_count][1337];
  int iter = 0;

  dir = opendir(directory);
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
      sprintf(buff[iter], "%s/%s", directory, entry->d_name);
      iter++;
    }
  }
  closedir(dir);
```

- Perlu diketahui bahwa untuk menyimpan _absolute path_ dan variabel iterasi, kita telah membuat buffer. Nilai `tid` telah diatur sejumlah nilai pada counter per direktori untuk thread yang dibuat.

```bash
  for (int i = 0; i < file_count; i++) {
    char  *test = (char*)buff[i];
    printf("%s\n", test);
    pthread_create(&tid[i], NULL, &routine, (void *)test);
  }

  for (int i = 0; i < file_count; i++) {
    pthread_join(tid[i], NULL);
  }
}
```

- Looping akan terus terjadi sejumlah file yang telah tersimpan di dalam buffer. Sebelum menjalankan program ini pada thread, kita harus melakukan penyimpanan _absolute path_ dari setiap file. Dan pada code berikut ini juga terdapat code untuk membuat thread yakni `pthread_create(&tid[i], NULL, &routine, (void *)test);`

- Terakhir terdapat proses looping yang melakukan `pthread_join` yaitu proses join untuk setiap thread yang telah dibuat

**Output `-f`**

![Capture](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/image/soal3_1.PNG)

**Output `\*`**

![Capture](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/image/soal3_2.PNG)

**Output `-d`**

![Capture](https://github.com/desyaapd/SoalShiftSISOP20_modul3_T16/blob/master/image/soal3_3.PNG)


## Soal 4
Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan setiap batunya memiliki warna yang berbeda. 

Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di pilar tersebut. Norland menghampiri setiap pilar secara bergantian. 


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


### Kendala

- Soalnya terlalu panjang, sehingga susah untuk kami memahami serta menemukan inti dari persoalan dengan cepat, dimohon apabila membuat soal jangan sesusah yang nomor 1 2 3 ya mas hehehee
