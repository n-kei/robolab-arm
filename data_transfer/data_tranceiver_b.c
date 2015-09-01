#include "data_type.h"
#include "data_tranceiver.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int fd[USB_PORT_NUM];

char *usb_df_name[USB_PORT_NUM] = {
  USB_DF_NAME_A, USB_DF_NAME_B,
  USB_DF_NAME_B, USB_DF_NAME_C
};

void serial_init(int fd, speed_t baud_rate) 
{
  struct termios tio;

  memset(&tio, 0, sizeof(tio));
  tio.c_cflag = CS8 | CLOCAL | CREAD;
  tio.c_cc[VTIME] = 100;

  cfsetispeed(&tio, baud_rate);
  cfsetospeed(&tio, baud_rate);

  tcsetattr(fd, TCSANOW, &tio);
}

void USBs_init(speed_t baud_rate)
{
  struct termios tio;
  int i;

  for(i = 0; i < USB_PORT_NUM; i++) {
    fd[i] = open(usb_df_name[i], O_RDWR);
    //fd[i] = open(usb_df_name[i], O_RDWR | O_NONBLOCK);
    if(fd[i] < 0) {
      perror(usb_df_name[i]);
      //exit(1);
      return;
    }
    
    serial_init(fd[i], baud_rate);
  }

}

int receive_MeasureValue(void)
{
  union ServoData tmp;
  int receive_data_len, receive_data;
  int i;
  unsigned char buffer[BUFF_SIZE]; 

  receive_data = -1;
  for(i = 0; i < USB_PORT_NUM; i++) {
    receive_data_len = read(fd[i], buffer, BUFF_SIZE);

    if(receive_data_len == 0) 
	continue;

    /*
    if(receive_data_len < 0) {
      perror("data_transfer.c");
      exit(2);
    }
    */
    receive_data = atoi(buffer);
    return(receive_data);
  }
  
  return(-1);
}

void transfer_CommandValue(int target_servo, int transfer_data)
{
  char buffer[BUFF_SIZE];
  int transfer_data_len;

  sprintf(buffer, "%d", transfer_data);
  transfer_data_len = write(fd[target_servo], buffer, strlen(buffer));
  /*if(transfer_data_len < 0) {
    perror(usb_df_name[target_servo]);
    exit(1);
    }*/

}
