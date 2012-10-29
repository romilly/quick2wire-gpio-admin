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

void allow_access_by_user(unsigned int pin, const char *filename) {
  char path[PATH_MAX];
  int size = snprintf(path, PATH_MAX, "/sys/devices/virtual/gpio/gpio%u/%s", pin, filename);
  
  if (size >= PATH_MAX) {
    error(7, 0, "path of GPIO pin is too long!");
  }
  
  if (chown(path, getuid(), getgid()) != 0) {
    error(5, errno, "failed to change group ownership of %s", path);
  }
  
  if (chmod(path, S_IRUSR|S_IWUSR) != 0) {
    error(6, errno, "failed to set permissions of %s", path);
  }
}

unsigned int parse_gpio_pin(const char *pin_str) {
  char *endp;
  
  if (pin_str[0] == '\0') {
    error(2, 0, "empty string given for GPIO pin number");
  }
  
  unsigned int pin = strtoul(pin_str, &endp, 0);
  
  if (*endp != '\0') {
    error(2, 0, "%s is not a valid GPIO pin number", pin_str);
  }
  
  return pin;
}

void write_pin_to_path(const char *path, unsigned int pin) {
  FILE * out = fopen(path, "w");
  
  if (out == NULL) {
    error(3, errno, "could not open %s", path);
  }
  
  if (fprintf(out, "%u\n", pin) < 0) {
    error(4, errno, "could not write GPIO pin number to %s", path);
  }
  
  if (fclose(out) == EOF) {
    error(4, errno, "could not flush data to %s", path);
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    usage_error(argv);
  }
  
  const char *command = argv[1];
  const char *pin_str = argv[2];
  
  unsigned int pin = parse_gpio_pin(pin_str);
  
  if (strcmp(command, "export") == 0) {
    write_pin_to_path(GPIO_EXPORT_PATH, pin);
    allow_access_by_user(pin, "direction");
    allow_access_by_user(pin, "value");
    allow_access_by_user(pin, "active_low");
    allow_access_by_user(pin, "edge");
  }
  else if (strcmp(command, "unexport") == 0) {
    write_pin_to_path(GPIO_UNEXPORT_PATH, pin);
  }
  else {
    usage_error(argv);
  }
  
  return 0;
}
