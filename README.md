| Date | Who | What |
|:-----|:--------:|------:|
| 2/26/25 | Cass & Becky| tested PCBs, had issues with basic communications. More work investigating electrical connections needed. Set up github |
|  3/6/25  | Cass & Becky   | decided to change from a 4 pin protocol to a 5 pin protocol. Pin 5 on the left hand side is adc in, and pin 5 on the right hand side is add out. We are using the  the adc value to determine which i2c devices are neighbors while constructing a ring buffer. need to create a system to encode the addresses based on resistor values & test that the adc value doesn't change when we read from pin to pin. |
|   |  |    |
