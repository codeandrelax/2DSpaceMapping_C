char error, byte_read;                 // Auxiliary variables

void main()
{
     AD1PCFG = 0xFFFF; // Setting all analog pins as digital

     TRISB.F11 = 0;    // Set RB11 as output (error signalization)
     PORTB.F11 = 0;    // No error
     
    /* Configures and initializes the software UART module
       char Soft_UART_Init(char *port, char rx_pin, char tx_pin, unsigned long baud_rate, char inverted)
    */
    error = Soft_UART_Init(&PORTB, 15, 10, 9600, 0); // Initialize Soft UART at 9600 bps
    if (error > 0) {
      PORTB.F11 = error;                    // Signalize Init error
      while(1) ;                            // Stop program
    }
    Delay_ms(100);

    while(1) {                              // Endless loop
      byte_read = Soft_UART_Read(&error);   // Read byte, then test error flag
      if (error)                            // If error was detected
        PORTB.F11 = error;                      //   signal it on PORTB
      else
        Soft_UART_Write(byte_read);         // If error was not detected, return byte read
    }
}