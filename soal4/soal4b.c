#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

//deklarasi variable hasil output soal4a
int (*matC)[5];
int row = 0, n, i, j, k;

//output dari soal4a difaktorial kan
void* func(void* arg) {
  i = row++;
  for (size_t j = 0; j < 5; j++) {
    n = 0;
    for (k = 1; k < matC[i][j]; k++) n += k;
    matC[i][j] += n;
  }
}
//fungsi shared memory dari soal 4a
int main() {
  key_t key = 1234;
  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  matC = shmat(shmid, 0, 0);

  //proses thread
  pthread_t tid[4];
  printf("MATRIKS :\n");
  for (i = 0; i < 4; i++) 
    pthread_create(&(tid[i]), NULL, &func, NULL);
  for (i = 0; i < 4; i++) 
    pthread_join(tid[i], NULL);
  for (i = 0; i < 4; i++) {
  
  for (j = 0; j < 5; j++) {
 
 //output hasil faktorial
      printf("%2d ", matC[i][j]);
		}
		printf("\n");
  }
  shmdt(matC);
  shmctl(shmid, IPC_RMID, NULL);
}

