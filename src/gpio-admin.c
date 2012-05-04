/*
 * Copyright 2012, Quick2Wire.com.
 * Dual licensed under MIT or LGPL licenses: http://license.quick2wire.com
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <limits.h>

#define GPIO_CLASS_PATH "/sys/class/gpio/"
#define GPIO_EXPORT_PATH (GPIO_CLASS_PATH "export")
#define GPIO_UNEXPORT_PATH (GPIO_CLASS_PATH "unexport")

void usage_error(char **argv) {
  fprintf(stderr, "usage: %s {export|unexport} <gpio-pin>\n", argv[0]);
  exit(1);
}

void allow_access_by_group(const char *pin_str, const char *filename) {
  char path[PATH_MAX];
  snprintf(path, PATH_MAX, "/sys/devices/virtual/gpio/gpio%s/%s", pin_str, filename);
  
  if (chown(path, -1, getegid()) != 0) {
    error(5, errno, "failed to change group ownership of %s", path);
  }
  
  if (chmod(path, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP) != 0) {
    error(6, errno, "failed to set permissions of %s", path);
  }
}

unsigned int check_is_valid_gpio_pin(const char *pin_str) {
  char *endp;
  
  if (pin_str[0] == '\0') {
    error(2, 0, "empty string given for GPIO pin number");
  }
  
  unsigned int pin = strtoul(pin_str, &endp, 0);
  
  if (*endp != '\0') {
    error(2, 0, "%s is not a valid GPIO pin number", pin_str);
  }
  
  /* Pointless but addresses warning about unused variable, which is caused 
   * by addressing warning about ignoring result of strtoul
   */
  return pin;
}

void write_text_to_path(const char *path, const char *text) {
  int fd = open(path, O_WRONLY);
  if (fd == -1) {
    error(3, errno, "could not open %s", path);
  }
  
  if (write(fd, text, strlen(text)) == -1) {
    error(4, errno, "could not write GPIO pin number to %s", path);
  }
  
  close(fd);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    usage_error(argv);
  }
  
  const char *command = argv[1];
  const char *pin_str = argv[2];
  
  (void)check_is_valid_gpio_pin(pin_str);
  
  if (strcmp(command, "export") == 0) {
    write_text_to_path(GPIO_EXPORT_PATH, pin_str);
    allow_access_by_group(pin_str, "direction");
    allow_access_by_group(pin_str, "value");
    allow_access_by_group(pin_str, "active_low");
  }
  else if (strcmp(command, "unexport") == 0) {
    write_text_to_path(GPIO_UNEXPORT_PATH, pin_str);
  }
  else {
    usage_error(argv);
  }
  
  return 0;
}
