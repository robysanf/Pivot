#include "DualMC33926MotorShield.h"

// Constructors ////////////////////////////////////////////////////////////////
int TopSpeedProcessore = 1200;
DualMC33926MotorShield::DualMC33926MotorShield()
{
  //Pin map
  _nD2 = 4;
  _M1DIR = 7;
  _M1PWM = 9;
  _M2DIR = 8;
  _M2PWM = 10;
  _nSF = 12;
  _M1FB = A0;
  _M2FB = A1;
}

DualMC33926MotorShield::DualMC33926MotorShield(unsigned char M1DIR,
                                               unsigned char M1PWM,
                                               unsigned char M1FB,
                                               unsigned char M2DIR,
                                               unsigned char M2PWM,
                                               unsigned char M2FB,
                                               unsigned char nD2,
                                               unsigned char nSF)
{
  _nD2 = nD2;
  _M1DIR = M1DIR;
  _M1PWM = M1PWM;
  _M2DIR = M2DIR;
  _M2PWM = M2PWM;
  _nSF = nSF;
  _M1FB = M1FB;
  _M2FB = M2FB;
}

// Public Methods //////////////////////////////////////////////////////////////
void DualMC33926MotorShield::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_M1DIR,OUTPUT);
  pinMode(_M1PWM,OUTPUT);
  pinMode(_M1FB,INPUT);
  pinMode(_M2DIR,OUTPUT);
  pinMode(_M2PWM,OUTPUT);
  pinMode(_M2FB,INPUT);
  pinMode(_nD2,OUTPUT);
  digitalWrite(_nD2,HIGH); // default to on
  pinMode(_nSF,INPUT);

  #ifdef DUALMC33926MOTORSHIELD_TIMERCC0_AVAILABLE
    if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
    //if (_M2PWM == _M2PWM_TIMER1_PIN)
    {
      // Timer 1 configuration
      // prescaler: clockI/O / 1
      // outputs enabled
      // phase-correct PWM
      // top of 400
      //
      // PWM frequency calculation
      // 48MHz / 1 (prescaler) / 2 (phase-correct) / 1200 (top) = 20kHz
     REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) |          // Divide the 48MHz clock source by divisor 1: 48MHz/1=48MHz
                    GCLK_GENDIV_ID(4);            // Select Generic Clock (GCLK) 4
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |         // Enable GCLK4
                     GCLK_GENCTRL_SRC_DFLL48M |   // Set the 48MHz clock source
                     GCLK_GENCTRL_ID(4);          // Select GCLK4
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  // Enable the port multiplexer for the digital pin D10
  PORT->Group[g_APinDescription[_M2PWM].ulPort].PINCFG[g_APinDescription[_M2PWM].ulPin].bit.PMUXEN = 1;
 
  // Connect the TCC0 timer to digital output D10 - port pins are paired odd PMUO and even PMUXE
  // F & E specify the timers: TCC0, TCC1 and TCC2
  PORT->Group[g_APinDescription[_M2PWM].ulPort].PMUX[g_APinDescription[_M2PWM].ulPin >> 1].reg = PORT_PMUX_PMUXO_F | PORT_PMUX_PMUXE_F;
  
  // Enable the port multiplexer for the digital pin D9
  PORT->Group[g_APinDescription[_M1PWM].ulPort].PINCFG[g_APinDescription[_M1PWM].ulPin].bit.PMUXEN = 1;
 
  // Connect the TCC0 timer to digital output D10 - port pins are paired odd PMUO and even PMUXE
  // F & E specify the timers: TCC0, TCC1 and TCC2
  PORT->Group[g_APinDescription[_M1PWM].ulPort].PMUX[g_APinDescription[_M1PWM].ulPin >> 1].reg = PORT_PMUX_PMUXO_F | PORT_PMUX_PMUXE_F;

  // Feed GCLK4 to TCC0 and TCC1
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable GCLK4 to TCC0 and TCC1
                     GCLK_CLKCTRL_GEN_GCLK4 |     // Select GCLK4
                     GCLK_CLKCTRL_ID_TCC0_TCC1;   // Feed GCLK4 to TCC0 and TCC1
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  // Dual slope PWM operation: timers countinuously count up to PER register value then down 0
  REG_TCC0_WAVE |= TCC_WAVE_POL(0xF) |         // Reverse the output polarity on all TCC0 outputs
                    TCC_WAVE_WAVEGEN_DSBOTH;    // Setup dual slope PWM on TCC0
  while (TCC0->SYNCBUSY.bit.WAVE);               // Wait for synchronization

  // Each timer counts up to a maximum or TOP value set by the PER register,
  // this determines the frequency of the PWM operation:
  REG_TCC0_PER = TopSpeedProcessore;         // Set the frequency of the PWM on TCC0 to 20kHz
  while (TCC0->SYNCBUSY.bit.PER);                // Wait for synchronization
 
  
    }
  #endif
}

// Set speed for motor 2, speed is a number betwenn -400 and 400
void DualMC33926MotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;
  float conversione = 0.00;
  
  if (speed < 0){ speed = -speed; reverse = 1;}  // Make speed a positive quantity  // Preserve the direction
  if (speed > 400){ speed = 400;}                // Max PWM dutycycle

  conversione = float(speed);
  conversione = (conversione/400*TopSpeedProcessore);
  speed = conversione ;

  #ifdef DUALMC33926MOTORSHIELD_TIMERCC0_AVAILABLE
    
	                                                      // Set the PWM signal to output speed duty cycle
	  REG_TCC0_CC3 = speed;                               // TCC0 CC3 - on D10
	  while (TCC0->SYNCBUSY.bit.CC3);                     // Wait for synchronization
	                                                      // Divide the 48MHz signal by 1 giving 48MHz (20.83ns) TCC0 timer tick and enable the outputs
	  REG_TCC0_CTRLA |= TCC_CTRLA_PRESCALER_DIV1 |        // Divide GCLK4 by 1
		TCC_CTRLA_ENABLE;                                   // Enable the TCC0 output
	  while (TCC0->SYNCBUSY.bit.ENABLE);                  // Wait for synchronization
  #endif
  if (reverse)
    digitalWrite(_M2DIR,HIGH);
  else
    digitalWrite(_M2DIR,LOW);
}


// Set speed for motor 1, speed is a number betwenn -400 and 400
void DualMC33926MotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;
  float conversione = 0.00;
  
  if (speed < 0){ speed = -speed; reverse = 1;}  // Make speed a positive quantity  // Preserve the direction
  if (speed > 400){ speed = 400;}                // Max PWM dutycycle

  conversione = float(speed);
  conversione = (conversione/400*TopSpeedProcessore);
  speed = conversione ;

#ifdef DUALMC33926MOTORSHIELD_TIMERCC0_AVAILABLE
    // Set the PWM signal to output speed duty cycle
    REG_TCC0_CC2 = speed;         // TCC0 CC3 - on D10
    while (TCC0->SYNCBUSY.bit.CC2);                // Wait for synchronization
 
    // Divide the 48MHz signal by 1 giving 48MHz (20.83ns) TCC0 timer tick and enable the outputs
    REG_TCC0_CTRLA |= TCC_CTRLA_PRESCALER_DIV1 |    // Divide GCLK4 by 1
            TCC_CTRLA_ENABLE;             // Enable the TCC0 output
    while (TCC0->SYNCBUSY.bit.ENABLE);              // Wait for synchronization

  #endif
  if (reverse)
    digitalWrite(_M1DIR,HIGH);
  else
    digitalWrite(_M1DIR,LOW);
}
/*//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
void DualMC33926MotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 1200)  // Max PWM dutycycle
    speed = 1200;

 /* #ifdef DUALMC33926MOTORSHIELD_TIMER1_AVAILABLE
    if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
    {
      OCR1A = speed;
    }
    else
    {//questo viene usato per gli altri pin in cui non posso impostare la frequenza con il timer
      analogWrite(_M1PWM,speed * 51 / 80); // map 400 to 255
    }
  #else
    analogWrite(_M1PWM,speed * 51 / 80); // map 400 to 255
  #endif
  #ifdef DUALMC33926MOTORSHIELD_TIMERCC0_AVAILABLE
    // Set the PWM signal to output speed duty cycle
    REG_TCC0_CC2 = speed;         // TCC0 CC3 - on D10
    while (TCC0->SYNCBUSY.bit.CC3);                // Wait for synchronization
 
    // Divide the 48MHz signal by 1 giving 48MHz (20.83ns) TCC0 timer tick and enable the outputs
    REG_TCC0_CTRLA |= TCC_CTRLA_PRESCALER_DIV1 |    // Divide GCLK4 by 1
            TCC_CTRLA_ENABLE;             // Enable the TCC0 output
    while (TCC0->SYNCBUSY.bit.ENABLE);              // Wait for synchronization

  #endif

  if (reverse)
    digitalWrite(_M1DIR,HIGH);
  else
    digitalWrite(_M1DIR,LOW);
}
*/
// Return motor 2 current value in milliamps.
unsigned int DualMC33926MotorShield::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  //return analogRead(_M2FB) * 9;
   analogReadResolution(12);
  // Serial.print(" curr = ");Serial.println(_M2FB);
  return analogRead(_M2FB)*2.5;
}

// Return motor 1 current value in milliamps.
unsigned int DualMC33926MotorShield::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  //return analogRead(_M2FB) * 9;
   analogReadResolution(12);
  // Serial.print(" curr = ");Serial.println(_M2FB);
  return analogRead(_M1FB);
}

// Return error status
unsigned char DualMC33926MotorShield::getFault()
{
  return !digitalRead(_nSF);
}
