#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

class Print {
public:
  virtual size_t write(uint8_t) = 0;
  virtual size_t write(const char *str) {
    size_t n = 0;
    if (!str) return 0;
    while (*str) {
      write((uint8_t)*str++);
      n++;
    }
    return n;
  }
  virtual size_t write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    if (!buffer) return 0;
    while (size--) {
      write(*buffer++);
      n++;
    }
    return n;
  }
  size_t print(const char *str) {
    return write(str);
  }
  size_t print(int value, int base = 10) {
    char buf[32];
    if (base == 16) {
      sprintf(buf, "%X", value);
    } else {
      sprintf(buf, "%d", value);
    }
    return write(buf);
  }
  size_t print(unsigned int value, int base = 10) {
    char buf[32];
    if (base == 16) {
      sprintf(buf, "%X", value);
    } else {
      sprintf(buf, "%u", value);
    }
    return write(buf);
  }
  size_t print(float value, int digits = 2) {
    char buf[32];
    sprintf(buf, "%.*f", digits, value);
    return write(buf);
  }
  size_t println(const char *str = "") {
    size_t n = write(str);
    n += write((uint8_t)'\r');
    n += write((uint8_t)'\n');
    return n;
  }
  size_t println(int value, int base = 10) {
    size_t n = print(value, base);
    n += write((uint8_t)'\r');
    n += write((uint8_t)'\n');
    return n;
  }
  size_t println(unsigned int value, int base = 10) {
    size_t n = print(value, base);
    n += write((uint8_t)'\r');
    n += write((uint8_t)'\n');
    return n;
  }
  size_t println(float value, int digits = 2) {
    size_t n = print(value, digits);
    n += write((uint8_t)'\r');
    n += write((uint8_t)'\n');
    return n;
  }
};

#endif // PRINT_H
