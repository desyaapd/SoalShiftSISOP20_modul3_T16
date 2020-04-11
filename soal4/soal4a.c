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

//fungsi perkalian dari matriks
void* mult(void* arg) {
  i = row++;
for (j = 0; j < 5; j++) 
for (k = 0; k < 2; k++) matC[i][j] += mat1[i][k] * mat2[k][j];
}

//fungsi shared memory untuk soal berikutnya
int main() {
	key_t key = 1234;
  int shmid = shmget(key, sizeof(int[4][5]), IPC_CREAT | 0666);
  mat3 = shmat(shmid, 0, 0);
  pthread_t tid[4];

  //proses thread
  for (i = 0; i < 4; i++) 
    pthread_create(&(tid[i]), NULL, &mult, NULL);
  for (i = 0; i < 4; i++) 
    pthread_join(tid[i], NULL);
  for (i = 0; i < 4; i++) {
  for (j = 0; j < 5; j++) {
	
	//output hasil perkalian matriks
      printf("%2d ", matC[i][j]);
		}
		printf("\n");
  }
  // shmdt(matC);
  // shmctl(shmid, IPC_RMID, NULL);
}

