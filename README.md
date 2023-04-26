# Gesture-Control-on-LED-Panel
The project aims to develop controller systems that utilize integrated gesture control sensors. It comprises two gesture controllers and an LED display. Each of the two controllers includes a gesture sensor, a reset button, a joystick, and a transceiver.

We will employ the PAJ7620 Gesture Recognition Module to detect left, right, up, and down hand motions. The NRF24L01 transceiver module will facilitate wireless communication between microcontrollers. Since this transceiver operates on a 2.4 GHz band, the range will be limited. We have chosen a 32x16 LED panel as our display because it is the maximum dimension that an Arduino UNO or equivalent microcontrollers can support. The content displayed on the LED panel will be interactive and based on the inputs received from the controllers. The joysticks being a part of the controllers as color pickers.

In addition, a tactile button will be added to each controller to provide extra input. In the case of this project, the LED panel is a canvas for pixelated drawing and coloring. Hence, the button act as a reset button to clear the canvas. Both gesture controllers will transmit signals to the LED panel's microcontroller. The microcontroller hosting the LED panel will be integrated with an RGB Matrix Shield to make the LED panel compatible with the microcontroller.
