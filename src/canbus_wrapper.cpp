/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "canbus_wrapper.h"
#include <stdio.h>

#include "can4linux.h"

#define DEBUG_CAN

using namespace top_level::canbus;
using namespace std;

top_level::canbus::CANbusWrapper::CANbusWrapper(char device_name[5], unsigned int baudrate, unsigned int message_length, bool blocking){
  sprintf(DEVICE, "/dev/%s", device_name);
  BAUD = baudrate;
  MAX = message_length;
  BLOCK = blocking;
  open_can();
#ifdef DEBUG_CAN
  printf("CANbusWrapper: Using CAN device: %s\n", DEVICE);
#endif /*DEBUG_CAN*/
}

int CANbusWrapper::write_can(unsigned long msg_id, unsigned char* msg_data, int msg_length){
  canmsg_t tx;
  tx.id = msg_id;
  tx.length = msg_length;
  for(int i=0; i<msg_length; i++){
    tx.data[i] = msg_data[i];
  }
#ifdef DEBUG_CAN
  printf("CANbusWrapper: Writing following message to id: %lu: \t",tx.id);
  for(int i=0;i<msg_length;i++){printf("%i ",msg_data[i]);}
  printf("\n");
#endif
      
  return write(fd, &tx, 1);
}


int CANbusWrapper::read_all(canmsg_t* data) {
  int ret = read(fd, data, MAX);

#ifdef DEBUG_CAN
  printf("Received %i messages", ret);
  if(ret>0){
    for(int i = 0; i<ret;i++){
      printf("Message #%i: id = %lu \t data = ", i, data[i].id);
      for(int j =0; j<data[i].length;j++){
        printf("%i ",data[i].data[j]);
      }
      printf("\n");
    }
  }
#endif /*DEBUG_CAN*/
  
  return ret;
 }

int CANbusWrapper::read_filtered(unsigned long msg_id, canmsg_t* data){
  canmsg_t buffer[MAX];
  int ret = read(fd, buffer, MAX);
  int count = -1;
  if(ret>0){    
# ifdef DEBUG_CAN
    printf("Received %i messages", ret);
# endif
    count = 0;
    for(int i=0; i<ret;i++){
      if(buffer[i].id == msg_id){
        //Copy the data from the buffer to the data
        memcpy(&data[count].data[0],&buffer[i].data[0],buffer[i].length);
        count++;
      }
    }
      
  }
  return count;
}


int CANbusWrapper::close_can() {
  return close(fd);
 }


int CANbusWrapper::open_can(){
  if(BLOCK){
    if(( fd=open(DEVICE, O_RDWR))<0){
      printf("CANbusWrapper: Unable to open CAN device\n");
      return 1;
    }
  } else{
    if(( fd=open(DEVICE,O_RDWR|O_NONBLOCK))<0){
      printf("CANbusWrapper: Unable to open CAN device\n");
      return 1;
    }
  }
  return 0;
}

int CANbusWrapper::set_baud(unsigned int baudrate){
  Config_par_t cfg;
  volatile Command_par_t cmd;
  
  cmd.cmd = CMD_STOP;
  ioctl(fd, CAN_IOCTL_COMMAND, &cmd);
  
  cfg.target = CONF_TIMING;
  cfg.val1 = baudrate;
  ioctl(fd, CAN_IOCTL_CONFIG, &cfg);
  
  cmd.cmd = CMD_START;
  ioctl(fd, CAN_IOCTL_COMMAND, &cmd);
  return 0;
}

int CANbusWrapper::set_blocking(bool blocking){
  BLOCK = blocking;
  int close_success = close_can();
  int open_success = open_can();
  if(close_success==-1 or open_success ==-1){
    return -1;
  }else{
    return 0;
  }
}