void adc_init(void);
uint8_t adc_sample(uint8_t);







/*  disregard these are my notes that were in lab7.c but made it difficult for me to follow code*/

    // Use this "while (1)" loop ONLY for doing Tasks 2 and 3
    //while (1) {
	 //Use adc_sample to read ADC value for buttons or potentiometer
   //var = adc_sample(1); //task 2 number 1
   //OCR2A = var; //set the ocr2a value to adc value
	// Use snprintf and lcd_stringout to display number on LCD
   //snprintf(buffer,10,"%4d",var);
   //lcd_moveto(0,0);
   //lcd_stringout(buffer);
   // _delay_ms(200);
    //}

    // If SELECT button pressed read potentiometer ADC channel
	//    Convert ADC value to OCR2A number for PWM signal
    //If the potentiometer is 0, the motor should go to the left fully (11) and also PWM signal is at max 
    //If the potentiometer is at max (255), the motor should go to the right fully (34) and also PWM signal is at max
    //(0, maxOCR2A) -> (255, minOCR2A)
    //map the adc value (0-255) to the ocr2a value (11-34)
    //var = adc_sample(1); //read the adc value from potentiometer
    //8bit adc value ranges from 0-255