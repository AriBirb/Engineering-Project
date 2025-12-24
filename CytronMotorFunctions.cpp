#include "CytronMotorFunctions.h"

CytronMD::CytronMD(MODE mode, uint8_t pin1, uint8_t pin2)
{
      _mode = mode;
      PWM = pin1;
      DIR = pin2;

      pinMode(PWM, OUTPUT);
      pinMode(DIR, OUTPUT);

      digitalWrite(PWM, LOW);
      digitalWrite(DIR, LOW);
}

void CytronMD::setSpeed(int16_t speed)
{
      
      // Make sure the speed is within the limit.
      if (speed > 255)
      {
        speed = 255;
      }
      else if (speed < -255)
      {
        speed = -255;
      }

      // Set the speed and direction.
      switch (_mode)
      {
      case PWM_DIR: //This is triggered
        if (speed >= 0) //This is triggered
          {
            #if defined(ARDUINO_ARCH_ESP32) //This is not triggered
              ledcWrite(PWM, speed);
            #else //This is triggered
              analogWrite(PWM, speed);
            #endif //This is triggered
              digitalWrite(DIR, LOW);
          }
        else //This is not triggered
          {
            #if defined(ARDUINO_ARCH_ESP32)
              ledcWrite(PWM, -speed);
            #else
              analogWrite(PWM, -speed);
            #endif
              digitalWrite(DIR, HIGH);
          }
        break;

      case PWM_PWM: //This is not triggered
        if (speed >= 0)
          {
            #if defined(ARDUINO_ARCH_ESP32)
              ledcWrite(PWM, speed);
            ledcWrite(DIR, 0);
            #else
              analogWrite(PWM, speed);
            analogWrite(DIR, 0);
            #endif
          }
        else
          {
            #if defined(ARDUINO_ARCH_ESP32)
              ledcWrite(PWM, 0);
            ledcWrite(DIR, -speed);
            #else
              analogWrite(PWM, 0);
            analogWrite(DIR, -speed);
            #endif
          }
        break;
      }
}
