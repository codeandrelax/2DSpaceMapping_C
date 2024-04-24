unsigned value;
float real_value;

float Vref = 3.3;
float delta_V;
unsigned no_of_quantums;


void main() {

   AD1PCFG = 0xFBFF;        // set all pins to digital except pin AN10(RB14)
   TRISB.F14 = 1;          // set pin AN10(RB14) as input

   /* Set pin RB13 as output for LED */
   TRISB.F13 = 0;   	  // Initialize RB13 as output
   LATB.F13 = 0;  	  // Set RB13 to zero


   //ADC1_Init();
   
   ADC1_Init_Advanced(_ADC_INTERNAL_REF);       // Init ADC to use 10-bit module, and use Internal voltage reference(from AVDD to AVSS)

   no_of_quantums = 1023;                          // 10-bit module - number of possible values is 2^10 = 1023
   delta_V = Vref / no_of_quantums;                // delta_V is quantum of input voltage


   while(1){
      value = ADC1_Get_Sample(10);                        // get the value from analog input, channel 10 (AN10)
      real_value =  value * Vref / no_of_quantums;       // calculate the value of the input voltage

      /* setting threshold */
      if(real_value > 1.7){
         LATB.F13 = 1;        // LED turn on
      } else {
        LATB.F13 = 0;        // LED turn off
      }

      Delay_ms(100);
   }
}