#include "mygpio.h"
#include <gpiod.h>

#define CONSUMER "bio_unit_gpio"

char *chipname = "gpiochip0";
bool line_state;
struct gpiod_chip* chip;
struct gpiod_line *line_20;
struct gpiod_line *line_21;
struct gpiod_line *line_10;
struct gpiod_line *line_17;
int ret;

void r_init(void){
   chip = gpiod_chip_open_by_name(chipname);
   if(!chip){
       perror("Chip open request");
   }

   line_20 = gpiod_chip_get_line(chip, 20);
   if(!line_20){
       perror("Get chip request 20");
   }
   line_21 = gpiod_chip_get_line(chip, 21);
   if(!line_21){
       perror("Get chip request 21");
   }
   line_10 = gpiod_chip_get_line(chip, 10);
   if(!line_10){
       perror("Get chip request 10");
   }
   line_17 = gpiod_chip_get_line(chip, 17);
   if(!line_17){
       perror("Get chip request 17");
   }

   ret = gpiod_line_request_output(line_20, CONSUMER, 0);
   if(ret == 0){
      printf("GPIO pin 20 is operational\n");
   } else {
      printf("Failed to initialize GPIO pin 20\n");
   }
   ret = gpiod_line_request_output(line_21, CONSUMER, 0);
   if(ret == 0){
      printf("GPIO pin 21 is operational\n");
   } else {
      printf("Failed to initialize GPIO pin 21\n");
   }
   ret = gpiod_line_request_output(line_10, CONSUMER, 0);
   if(ret == 0){
      printf("GPIO pin 10 is operational\n");
   } else {
      printf("Failed to initialize GPIO pin 10\n");
   }
   ret = gpiod_line_request_output(line_17, CONSUMER, 0);
   if(ret == 0){
      printf("GPIO pin 17 is operational\n");
   } else {
      printf("Failed to initialize GPIO pin 17\n");
   }
}

void r_close(void){
   gpiod_line_release(line_20);
   gpiod_line_release(line_21);
   gpiod_line_release(line_10);
   gpiod_line_release(line_17);
   gpiod_chip_close(chip);
}

void r_move_left(void){
   gpiod_line_set_value(line_10, 1);
}

void r_move_right(void){
   gpiod_line_set_value(line_20, 1);
}

void r_move_forward(void){
   gpiod_line_set_value(line_10, 1);
   gpiod_line_set_value(line_20, 1);
}

void r_move_backward(void){
   gpiod_line_set_value(line_21, 1);
   gpiod_line_set_value(line_17, 1);
}

void r_stop(void){
   gpiod_line_set_value(line_20, 0);
   gpiod_line_set_value(line_21, 0);
   gpiod_line_set_value(line_10, 0);
   gpiod_line_set_value(line_17, 0);
}
