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