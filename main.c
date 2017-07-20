#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define debug printf("%s", "[DEBUG]: " );
#define PAGE_SIZE 4096
static unsigned long hashed, actual, zeros, total;

void compare(char * F1, char *F2); // compare two mem files
bool isZero(unsigned char *str);
unsigned long hash(unsigned char *str); // hash similarity
unsigned long actu(unsigned char *str1, unsigned char *str2); // actural similarity


int main(int argc, char *argv[]) {
  char *f1, *f2;
  hashed = 0, total = 0, zeros = 0;

  if(argc !=4){
    printf("./hash_similarity [bin1] [bin2] [number of pages]\n" );
    return EXIT_FAILURE;
  }


  debug;
  f1 = argv[1];
  f2 = argv[2];

  printf("file compared: %s\t%s\n", f1, f2);
  compare(f1, f2);
  
  debug;
  printf("hashed-total-(hash/total)%% %lu-%lu-%.2f%%\n", hashed, total,
                            100*((float)hashed / total));
  debug;
  printf("actual-total-(actual/total)%% %lu-%lu-%.2f%%\n", actual, total,
                            100*((float)actual / total));
  debug;
  printf("zeros: %lu-%.2f%%\n", zeros, 100*((float)zeros / total) );


  return 0;
}


unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (*str) {
        c = *str++;
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
      }

    return hash;
}

unsigned long actu(unsigned char *str1, unsigned char *str2){
    unsigned long same = 0; // same bytes;
    unsigned int i = 0;

    for (i = 0; i < PAGE_SIZE; i++){
      if((int) str1[i] == (int) str2[i]){
        same++;
      }
    }

    return same;
}

void compare(char * F1, char *F2){
  FILE *fp1, *fp2;
  unsigned long fsize1, fsize2;
  unsigned long i, jj;
  unsigned char *tmp1, *tmp2;
  unsigned long hash1, hash2;

  fp1 = fopen(F1, "rb");
  fp2 = fopen(F2, "rb");

  fseek (fp1 , 0 , SEEK_END);
  fsize1 = ftell (fp1);
  rewind (fp1);

  fseek (fp2 , 0 , SEEK_END);
  fsize2 = ftell (fp2);
  rewind (fp2);
  tmp1 = (unsigned char *) malloc ((PAGE_SIZE+1)*(sizeof(unsigned char)) );
  tmp2 = (unsigned char *) malloc ((PAGE_SIZE+1)*(sizeof(unsigned char)) );


  if(fsize1 < fsize2){
    total = fsize1;
  }
  else{
    total = fsize2;
  }

  i = 0;

  while(i+PAGE_SIZE <= total){

      fread(tmp1, PAGE_SIZE, 1, fp1);
      fread(tmp2, PAGE_SIZE, 1, fp2);

      hash1 = hash(tmp1);
      hash2 = hash(tmp2);

      if(isZero(tmp1) && isZero(tmp2)){
        zeros+=PAGE_SIZE;
      }
      else if(hash1 == hash2){
        hashed+= PAGE_SIZE;
        actual+= actu(tmp1,tmp2);
      }
      i+= PAGE_SIZE;
  }

  fread(tmp1, total - i, 1, fp1);
  fread(tmp2, total - i, 1, fp2);
  hash1 = hash(tmp1);
  hash2 = hash(tmp2);
  if(hash1 == hash2){
    hashed+= (total-i);
    for (jj = 0; jj <total -i; jj++){
      if((int) tmp1[jj] == (int) tmp2[jj]){
        actual++;
      }
    }
  }


  fclose(fp1);
  fclose(fp2);
}

bool isZero(unsigned char *str){
    int c;
    while(*str){
        c = *str++;
        if(c != 0 ){
            return false;
        }
    }
    return true;

}
