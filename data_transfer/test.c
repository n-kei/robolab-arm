#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <errno.h>
#include "data_type.h"
#include "data_tranceiver.h"

int main(int argc, char **argv) 
{
  int receive_data;
  int fd;
  int i = 5;

  USBs_init(9600);
  printf("init USB port\n");

  printf("start main loop...\n");
  while(1) {
    transfer_CommandValue(Aservo, 256);
    receive_data = receive_MeasureValue();
    if(receive_data == 256)
      printf("receive_data = %d\n", receive_data);
  }

  return(0);
}
      
