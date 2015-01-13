#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void swap(int state[2][3][3], int i, int j)
{
  if (j < 9)
  {
    int temp = state[i/9][i/3][i%3];
    state[i/9][i/3][i%3] = state[j/9][j/3][j%3];
    state[j/9][j/3][j%3] = temp;
  }
  else
  {
    int temp = state[i/9][i/3][i%3];
    state[i/9][i/3][i%3] = state[j/9][j/3-3][j%3];
    state[j/9][j/3-3][j%3] = temp;
  }
  
}

void R2(int state[2][3][3])
{
  swap(state, 8, 11);
  swap(state, 5, 14);
  swap(state, 2, 17);
}

void L2(int state[2][3][3])
{
  swap(state, 6, 9);
  swap(state, 3, 12);
  swap(state, 0, 15);
}

void F2(int state[2][3][3])
{
  swap(state, 6, 17);
  swap(state, 7, 16);
  swap(state, 8, 15);
}

void B2(int state[2][3][3])
{
  swap(state, 0, 11);
  swap(state, 1, 10);
  swap(state, 2, 9);
}

void U2(int state[2][3][3])
{
  swap(state, 0, 8);
  swap(state, 1, 7);
  swap(state, 2, 6);
  swap(state, 3, 5);
}

void U(int state[2][3][3])
{
  swap(state, 0, 2);
  swap(state, 0, 8);
  swap(state, 0, 6);

  swap(state, 1, 5);
  swap(state, 1, 7);
  swap(state, 1, 3);
}

void Uprime(int state[2][3][3])
{
  swap(state, 0, 6);
  swap(state, 0, 8);
  swap(state, 0, 2);

  swap(state, 1, 3);
  swap(state, 1, 7);
  swap(state, 1, 5);
}

bool state_equal(int state1[2][3][3], int state2[2][3][3])
{
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 3; k++)
      {
        if (state1[i][j][k] != state2[i][j][k])
        {
          return false;
        }
      }
    }
  }

  return true;
}

void state_copy(int state1[2][3][3], int state2[2][3][3])
{
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 3; k++)
      {
        state2[i][j][k] = state1[i][j][k];
      }
    }
  }
}
void gen_seq(int A[], int len)
{
  rand();
  A[0] = (int) (7.0 * (rand() / (RAND_MAX + 1.0)));
  for (int i = 1; i < len; i++)
  {
    A[i] = rand()%7;
    while(A[i] == A[i - 1])
    {
      A[i] = rand()%7;
    }  
  }
}

void app_seq(int state[2][3][3], int A[], int len)
{
  for (int i = 0; i < len; i++)
  {
    switch(A[i]){
      case 0:{
        R2(state);
        break;
      }
      case 1:{
        L2(state);
        break;
      }
      case 2:{
        F2(state);
        break;
      }
      case 3:{
        B2(state);
        break;
      }
      case 4:{
        U2(state);
        break;
      }
      case 5:{
        U(state);
        break;
      }
      case 6:{
        Uprime(state);
        break;
      }
    }
  }
}

void print_cube(int state[2][3][3])
{
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 3; k++)
      {
        printf("%d ", state[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
}

void print_seq(int A[], int len)
{
  for (int i = 0; i < len; i++)
  {
    printf("%d, ", A[i]);
  }
  printf("\n");
}

void alg(int state[2][3][3], int limit)
{
  int *seq = calloc(limit + 1, sizeof(int));
  int solved[2][3][3]= {
                       {{0,1,2},{3,4,5},{6,7,8}},
                       {{9,10,11},{12,13,14},{15,16,17}}
                                                 };
  int copy[2][3][3]= {
  {{0,1,2},{3,4,5},{6,7,8}},
  {{9,10,11},{12,13,14},{15,16,17}}
  };
  state_copy(state, copy);
  long i = 1;
  while(true)
  {
    int len = rand()%limit;
    gen_seq(seq, len);
    app_seq(state, seq, len);
    if (state_equal(state, solved))
    {
      printf("\n%ldth: ", i);
      print_seq(seq, len);
      return;
    }
    printf("\r%ldth: ", i);
    print_seq(seq, len);
    state_copy(copy, state);
    i++;
  }
}

int main()
{
  srand(time(NULL));
  int state[2][3][3]= {
                       {{0,1,2},{3,4,5},{6,7,8}},
                       {{9,10,11},{12,13,14},{15,16,17}}
                                                 };
  int seq[] = {0,1,2,3,4};    
  gen_seq(seq, 5);
  print_seq(seq, 5);                                
  //alg(state, 30);
  return 0;
}
