/*
  -------------------------------------------------------------
       ScampKey - Alternative firmware for the ShrimpKey
  .............................................................

  - To configure, edit Scampkey_settings.h  

    . REPEAT false/true :
        Set to false disables key repeat when holding on input.
        
    . NR_SAMPLES :
        More samples make it less susceptible to noise.
        A number from 8 onwards works fine.
        
    . THRESHOLD :
        The samples are averaged and this average gets compared
        to the THRESHOLD. A value of 0.5 seems to work fine.

  - To compile

    . Copy the included UsbKeyboard folder to the Arduino
      library path.
    
    . The Shrimpkey board uses pin D3 for D-, pin D2 for D+
      and D7 for the pull up.
    
    . You can configure alternative values for these in
      UsbKeyboard/usbconfig.h
      
 Thanks to Sjoerd Dirk Meijer for creating the shrimpkey!
 http://fromscratched.nl/index.php/category/shrimpkey/
 
 This work is licensed under the MIT license.
 http://opensource.org/licenses/MIT

  ().()
  (*.*)
  (”_”)  .:: (c) 2013 - Johan VdB ::.
  
  -------------------------------------------------------------
*/
#include <Arduino.h>
#include "UsbKeyboard.h"

#include "Scampkey_settings.h"
#include "Scampkey_private.h"

Input inputs[NR_INPUTS];
int led_key_pressed_on_timeout = 0;

void usb_disable_timer0_overflow_interrupt() {
  TIMSK0&=!(1<<TOIE0);  
}

void usb_update() {
  UsbKeyboard.update(); 
}

void usb_press_key(int keycode ) {
  UsbKeyboard.sendKeyStroke(keycode); 
}

void inputs_setup() {
  for (int i=0; i<NR_INPUTS; i++) {
    Input *input = &inputs[i];
    input->sample_counter = 0;
    input->pressed = false;
    input->pin = input_pins[i];
    input->key = input_keys[i];
    input_zero_samples( input );
    pinMode( input->pin, INPUT );
    digitalWrite( input->pin, LOW );
  }
}  

void input_zero_samples( Input *input ) {
      for(int j=0; j<NR_SAMPLES; j++) {
      input->samples[j] = false; 
    }  
}  

boolean input_pressed(Input *input) {
  double average = 0;
  for(size_t i=0; i<NR_SAMPLES; i++) {
    average += input->samples[i];
  }
  average /= NR_SAMPLES;     
  
  if ( average > THRESHOLD ) {
    return true;
  }
  
  return false;
}

boolean input_pressed_no_repeat( Input *input) {
  boolean pressed = input_pressed( input );

  boolean report_pressed = false;

  if ( ! input->pressed && pressed ) {
    report_pressed = true;
    input->pressed = true;
  }

  if ( input->pressed && !pressed ) {
    input->pressed = false;
  }  
  
  return report_pressed;  
}

void input_sample(Input *input) {
  input->samples[input->sample_counter] = ! digitalRead( input->pin );
  input->sample_counter++;
  if ( input->sample_counter >= NR_SAMPLES) {
    input->sample_counter = 0;
  }  
}

void led_on()
{
  digitalWrite( LED_KEY_PRESSED, 1 );
  led_key_pressed_on_timeout = LED_KEY_PRESSED_ON_TIMEOUT;
}

void led_off_after_timeout()
{
  if (led_key_pressed_on_timeout > 0 ) {
    led_key_pressed_on_timeout--;
    return;
  }
  digitalWrite(LED_KEY_PRESSED, 0);   
}

void setup() {
  inputs_setup();
  
  pinMode( LED_POWER, OUTPUT );
  digitalWrite( LED_POWER, 1 );
  pinMode( LED_KEY_PRESSED, OUTPUT );
  digitalWrite( LED_KEY_PRESSED, 0 );
  
  usb_disable_timer0_overflow_interrupt();
}

void loop() {
  usb_update();
  for(int i=0; i<NR_INPUTS; i++) {
    Input *input = &inputs[i];
    boolean pressed = (REPEAT) ? input_pressed(input) : input_pressed_no_repeat(input);
    if (pressed) {
      led_on();
      usb_press_key( input->key );
    }  
    input_sample(input);  
  }
  led_off_after_timeout();
}
