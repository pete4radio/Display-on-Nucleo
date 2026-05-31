#ifndef ARDUINO_H
#define ARDUINO_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <cstring>
#include <cmath>

#define ARDUINO 10800
#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline void pinMode(int, int) {}
inline void digitalWrite(int, int) {}
inline void analogWrite(int, int) {}
inline void yield(void) {}
inline float radians(float deg) { return deg * (float)M_PI / 180.0f; }

class __FlashStringHelper {};

class String {
public:
  String(const char *s = "") : _s(s) {}
  const char *c_str() const { return _s; }
  size_t length() const { return _s ? strlen(_s) : 0; }
private:
  const char *_s;
};

#endif // ARDUINO_H
