/**
 * @file servo_motor.c
 * @author 2DSpaceMapping_C
 * @date 19 April 2024
 * @brief File containing source code for testing servo motor.
 *
 * This file tests correctess of the servo motor. Test cases are
 * moving in three spots 0, 90 and 180 degrees. Servo is controled via
 * PWM module set on channel 1.
 * @see https://github.com/codeandrelax/2DSpaceMapping_C/wiki/Servo-motor-control
 */

/**
 * @brief PWM parameters
 *
 * Variables that are crucial for PWM
 */
unsigned int frequency = 50; /* PWM freq. in Hz */
unsigned int period;         /* period = 1 / frequency */
unsigned int duty;           /* duty = t_on / period */

void main() 
{  
  /* Configure analog pins as digital */
  AD1PCFG= 0xFFFF;
  
  /* Set RB2(RP2) as output */  
  TRISB.F2 = 0;
  
  /* Init start value RB2(RP2) as 0 */
  LATB.F2 = 0;
  
  /**
   * RB2 is open-drain.
   * High value 5V - low value 0V
   */
  ODCB.F2 = 1;
  
  
  /* char PPS_Mapping_NoLock(char rp_num, char input_output, char funct_name);
  * rp_num    - remappable pin number
  * func_name - selects internal mcu module for usage ( 18 = OC1(Output Compare 1) )
  */
  Unlock_IOLOCK();
  PPS_Mapping_NoLock(2, _OUTPUT, 18);
  Lock_IOLOCK();
  
  /* Initialize PWM module with duty = 0
  * unsigned long freq_hz         - 50Hz
  * unsigned int enable_channel_x - channel 1
  * unsigned int timer_prescale   - no clock prescale
  * unsigned int use_timer_x      - Timer2
  * RETURNS calculated timer period
  */
  period = PWM_Init(frequency, 1, 0, 2);
  
  /* Starts PWM at requested channel 1*/
  PWM_Start(1);
  
  while(1)
  {
    /* Changing PWM duty
    * unsigned duty    - valid values 0 to period
    * unsigned channel - PWM channel to change duty to 
    */
    PWM_Set_Duty(period/20, 1);  /* 5%   od 20ms = 1ms */
    Delay_ms(5000);
    
    PWM_Set_Duty(period/14, 1);  /* 7.5% od 20ms = 1.5ms */
    Delay_ms(5000);
    
    PWM_Set_Duty(period/10, 1);  /* 10%  od 20ms = 2ms */
    Delay_ms(5000);
    
     PWM_Set_Duty(period/14, 1);  /* 7.5% od 20ms = 1.5ms */
    Delay_ms(5000);
    
    PWM_Set_Duty(period/20, 1);  /* 5%   od 20ms = 1ms */
    Delay_ms(5000);
 }

}
