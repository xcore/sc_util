Some Examples of the I/O Library
================================

Flashing LEDs
-------------

A simple flashing leds example::

   #include "cio.h"

   int main() {
     port p;
    
     p = port_enable(XS1_PORT_4F);
     while (1) {
       port_output_data(p, 1);
       timer_delay(1000);
       port_output_data(p, 0);
       timer_delay(1000);
     }
     port_disable(p);
   }


Two buttons controlling an LED
------------------------------

This example shows selects, it has two buttons - one of which turns
the led on and the other turns it off::

   void main()
   {
     port p_button0 = port_enable(PORT_BUTTON_0);
     port p_button1 = port_enable(PORT_BUTTON_1);
     port p_led = port_enable(PORT_LED_0);
     int led_val = 0;
     int choice;
     while (1) {
    
       // wait until either button0 or button1 is pressed
       choice = select(when_pinseq(p_button0, 1),
                       when_pinseq(p_button1, 1));
    
       switch (choice)
         {
         case 0:
           // button0 was pressed
    
           // delay to avoid any bouncing
           timer_delay(10000);
           // wait until the button is released
           port_input_when_pinsneq(p_button0, 1);
           // delay to avoid any bouncing
           timer_delay(10000);
    
           port_output(p_led, 0);
           break;
         case 1:
           // button1 was pressed
    
           // delay to avoid any bouncing
           timer_delay(10000);
           // wait until the button is released
           port_input_when_pinsneq(p_button1, 1);
           // delay to avoid any bouncing
           timer_delay(10000);
    
           port_output(p_led, 1);
           break;
         }
     }
   }

Channel communiction
--------------------

A simple example of channel communication:::

  void thread1(chanend c) {
     int data;
     data =  chan_input_word(c);
     printintln(data);
  }

  void thread2(chanend c) {
     chan_output_word(c, 5);
  }
