Rotary-Encoder-Peripheral-System
Rotary-Encoder Hardware Peripheral and Firmware to Drive it
CPU-CCB GEN-1 DEVICE FIRMWARE v.1.00 Beta
----------------------------------------------------------------------------------------------------------------
Firmware to drive the MSP430-G2553 controller with Rotary-Encoder, LCD Disply, Cooling system, ST-Relayis, Leds.
----------------------------------------------------------------------------------------------------------------
David Zohrabyan (R&D Department)
----------------------------------------------------------------------------------------------------------------
Physalis Labs. Berlin 07.07.2017
----------------------------------------------------------------------------------------------------------------
There are many cases where one needs a button, encoder, or a device to use it as a input for several settings.
The rotary encoder being galvanically isolated from any circuitry is a very sophisticated and long term solution due to many reasons.

Reasons:
 
- no wearing of the parts

- no physical or electrical contact with the circuitry

- silent, without noisy sounds

- easy replaceable

Since couple of months I'm working with Ti microcontrollers. Mostly with the Launchpad Ecosystem and Energia IDE. I wanted to  connect display to Piccolo LaunchXL Launchpad, in order to test couple of programs I have written. One of the main tasks was to  control a Rotary-encoder with magnetic construction and use it as a input for volume, or other settings. First of all check the suitable controller/launchpad topology and datasheet to spot the suitable pins which can read the input (analog or digital etc..), in our case the rotary part is connected with shaft to a wheel which has predefined drilled holes on other side (Black part). The Silver metallic side corresponds to the part which user can touch to rotate. The holes are meant for 2x optocouplers, TCST-1103, from Vishay. Those 2 optocouplers are installed together for 2 digital- inputs. Basically in my setup I have two digital inputs from optocouplers which must be read by MCU. Those optopcouplers have defined laser aperture size and parameters, so when the  wheel rolls the beam is being interrupted and that can be read by the suitable digital pins.
