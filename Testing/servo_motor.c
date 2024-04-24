unsigned pwm;
float left_left, left, left_center, center, right_center, right, right_right;



void main() {
     AD1PCFG = 0XFFFF;
     TRISB = 0;
     PORTB = 0;
     ODCB.F2=1;
     
     Unlock_IOLOCK();
     PPS_Mapping_NoLock(2, _OUTPUT, 18);
     Lock_IOLOCK();
     
     pwm=PWM_Init(50, 1, 0, 2);
     PWM_Start(1);
     
     left_left= 2.0*pwm/100;
     left = 4.0*pwm/100;
     left_center = 6.0*pwm/100;
     center = 7.5*pwm/100;
     right_center= 9.0*pwm/100;
     right=11.0*pwm/100;
     right_right= 13.5*pwm/100;
     
     while(1){
              PWM_Set_Duty(left_left, 1);
              delay_ms(500);
              PWM_Set_Duty(left, 1);
              delay_ms(500);
              PWM_Set_Duty(left_center, 1);
              delay_ms(500);
              PWM_Set_Duty(center, 1);
              delay_ms(500);
              PWM_Set_Duty(right_center, 1);
              delay_ms(500);
              PWM_Set_Duty(right, 1);
              delay_ms(500);
              PWM_Set_Duty(right_right, 1);
              delay_ms(500);
              PWM_Set_Duty(right, 1);
              delay_ms(500);
              PWM_Set_Duty(right_center, 1);
              delay_ms(500);
              PWM_Set_Duty(center, 1);
              delay_ms(500);
              PWM_Set_Duty(left_center, 1);
              delay_ms(500);
              PWM_Set_Duty(left, 1);
              delay_ms(500);
     }
}