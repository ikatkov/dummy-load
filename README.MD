# Journal

## Aug 7, 2023

Testing transformers, for small projects, the max power seems to be 1A/24V.

I need a dummy load that can dissipate around 15W of power for at least 3h. Two power FETs or two power BJT seems to be enough.

Current precision is +/- 10mA seems to be also enough.

Current measurement can be done by arduino  

0.05 Ohm shunt x 3A = 0.15V
use ina180 high side current sense IC, x20 multiplication
3V max on ADC imput
1 LSB ~ 2.9mA


## Aug X, 2023
See https://community.element14.com/members-area/personalblogs/b/blog/posts/lt-spice-loop-gain-and-an-electronic-load
This is how you do stability simulation. I used it in LTSpice simulations - see files that has "stability-pulse" suffix.


## Aug 20, 2023
Tested temperature measurement circuit on the breadboard
PTC + LM324 opmamp that does voltage shifting and x10 scaling
it looks like two 7segments displays is not enough, decided to go use-up one of these large LCD displays I have left.
SLC A5
SDA A4

## Aug 22, 2023

Regular power resistor 5W, goes to 130C at 4W dissipation. Whole cement block evenly heated up.

Tried gimmic power resistors

* Nichrome wire (1 Ohm) potted in plaster. Looks ugly/ok. Nichrome can't be soldered, need to use ferules to crimp to copper wire. With such small resistances, 1/2 cm of nichrome wire is non negligible resistance, percetagewise. It seems that plaster does not transfer heat properly. I think the wire is cooking inside. Ourside plaster temp 135C
* Strapper metal film (?) resistor to a heatsink. Heatsink goes to 100C, resistor to 150C. Even with thermopaste the transfer from cyclidnrical body to the flat hearsink is not ideal.
* Need to buy factory made 5W 1 Ohm resistors.


To set ref voltage

* tried to do high freq PWM https://github.com/AlexGyver/GyverLibs/blob/master/GyverPWM/examples/PWMfrequency/PWMfrequency.ino . Also see LTSpice simulation. Riple can be addressed with low-pass RC filter. But 8bit PWM resolution of 256 is rather coarse 
* Need to try 10 or 11 or 12bit PWM on a breakoard https://github.com/AlexGyver/GyverLibs/blob/master/GyverPWM/GyverPWM.h to see if is acceptable. Fewer parts than DAC IC, $0.75 cheaper. May be just use 12bit DAC?
* Yet another options is use two digipots ICs - coarse + fine as simple analog voltage divider.
* Ultimate fallback is to use 12b DAC. Becasue it's 12bits can just feed 4.55 vref into it. And programmatically limit to 2V output i.e. 2A per channel.
  
All these DAC solutions are alternatives to analog pot - this way I don't need to measure current. 
Can calculate, given precise 1 Ohm resistor hooked to the control loop (opAmp driving darlington pair)


## Aug 23, 2023
Tried high freq PWM. Works. Need 3 pole RC low pass filter to get ripple down to 1mA. The real problem is that arduino PWM HIGH level is voltage regulator voltage. Witch is not precise, drifts with temp etc. Could not find an easy way to shift voltage from arbitrary ~5V to precision. High current buffer IC are $2 a piece, while DAC is $0.75. Also DAC lets me modulate voltage in any way. For example PWM with 300Hz to stress test power supplies. See https://www.eevblog.com/forum/projects/dynamic-electronic-load-project/

Found a way - voltage reference into opamp into npn transtistor. This is a DIY buffer.
https://www.allaboutcircuits.com/technical-articles/how-to-buffer-an-op-amp-output-for-higher-current-part-1/

https://www.renesas.com/us/en/document/apn/r13an0008-boosting-op-amp-output-current

It should be possible to buffer v_ref voltage for arbitrary current.


## Feb 18, 2024
After a few unfinished (sic!) projects with AC/DC power supplies, and finished battery capacity meter I got back to this.
The simplistic approach with darlington BJT and LM358, resulted in problems with high-side current measuring.

One interesting problem - on power on, opAmp will swing all the way to positive rail, so need to control On/Off in software or button somewhere. Look at the HP6060-schematic.png - orange lines are the on/off. I presume it's has to be pulled HIGH to enable opamps. Probably schotky diodes, otherwirse power darlinton migh leak some current. Or regular diodes to some negative rail.
