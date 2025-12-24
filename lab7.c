/********************************************
 *
 *  Name: isabeella assefa
 *  Email: iassefa@usc.edu
 *  Section: 11am friday
 *  Assignment: Lab 7 - ADC and PWM
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "lcd.h"
#include "adc.h"

//variable to hold adc value
unsigned char var;
char buffer[10];//buffer to displaying the value on lcd
unsigned char state = 0; //state variable
unsigned char pwm_changed = 255; //variable to track if the pwm value has changed

int main(void)
{

    // Initialize the LCD
    lcd_init();

    // Initialize the ADC
    adc_init();

    // Initialize TIMER2
    timer2_init();


    // Write splash screen and delay for 1 second
        // Show the splash screen
    lcd_moveto(0,3);
    lcd_stringout("Isabella"); //prints my name
        //lcd_moveto(1,2); //moves to second line 
        //lcd_stringout("EE109 Lab 5"); //prints lab title
    _delay_ms(1000);
    lcd_writecommand(0x01); //clear the screen

   // lcd_moveto(1,5);
   // lcd_stringout("PWM=");


    while (1) {                 // Loop forever
	// Check buttons and determine state
    //variable mode: OCR2A is controlled by the potentiometer setting
    //left: left button pressed, servo goes to leftmost position = 155
    //right: right button pressed, servo goes to rightmost position = 0
    //stay in these modes until select, left or right is pressed to switch it to a different mode
    unsigned char button = adc_sample(0); //read the adc value from buttons
    if(button < 25){
        state = 2; //right 
        _delay_ms(10);
    }
    else if(button < 170){
        state = 1; //left
        _delay_ms(10);
    }
   else if(button < 230){
        state = 0; //variable
        _delay_ms(10);
    }

	// Change output based on state
    int8_t new_pwm;
        // If RIGHT or LEFT button pressed, move servo accordingly
    var = adc_sample(1);
    snprintf(buffer,10,"%5d",var);

    if(state == 0){
        //variable mode
        var = adc_sample(1); //read the adc value from potentiometer
        //do nothing here bc the ocr2a value is based on the potentiometer
        //OCR2A = 34 - ((var * (34 - 11)) / 255); //map adc value to ocr2a value 
        int16_t map = var * 23; //23 is the range between 11 and 34
        new_pwm = 34 - (map/255);
    }
    else if(state == 1){ //left
        new_pwm = 34; //leftmost position
    }
    else if(state == 2){ //right
        new_pwm = 11; //rightmost position
    }

        //check the status of the buttons to see if the state has to be changed
        //if select was pressed, set the state to variable mode
        


    //ocr2a value ranges from 11-34
    //formula to map the two ranges

    if(pwm_changed != new_pwm){
        OCR2A = new_pwm; 
        pwm_changed = new_pwm;   
        // Display the PWM value on the LCD
        snprintf(buffer,10,"%5d",new_pwm);
        lcd_moveto(0,0);
        lcd_stringout("PWM=");
        lcd_moveto(0,5);
        lcd_stringout(buffer);
    }
}

    return 0;   /* never reached */
}





/*
  timer2_init - Initialize Timer/Counter2 for Fast PWM
*/
void timer2_init(void)
{
    TCCR2A |= (0b11 << WGM20);  // Fast PWM mode, modulus = 256
    TCCR2A |= (0b10 << COM2A0); // Turn D11 on at 0x00 and off at OCR2A
    OCR2A = 23;        // Initial pulse width (calculate this)
    TCCR2B |= (0b111 << CS20);  // Prescaler = 1024 for 16ms period
    DDRB |= (1 << PB3);  // Set D11 (OC2A) as output
   
}


//11 to 34 is the range for the servo
//turning the potentiometere one will will change the OCR2A value between 11 and 34
//thus changing the angle of the servo
