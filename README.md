# Tablet Foot Pedal
A foot pedal for a tablet for hands-free page turning.

![Foot pedal connected to tablet turning pages of sheet music](https://github.com/kvriet/Tablet-pedal/blob/main/Pictures/pedal-turning-pages.gif?raw=true)

## Instructions
### Pairing
The pedal has a power switch that turns on the pedal and automatically puts it in bluetooth pairing mode. When the pedal is turning on, the blue LED will flash rapidly three times. For first-time pairing, open the bluetooth menu on your sheet music device, select your pedal (Pedal Name) and agree to pair. That's all that is needed. On most devices pairing will be automatic after that.

### Power and sleep mode
To conserve energy, turn the pedal off with the black power switch when you're not using the pedal for a longer time. If you forget to switch it off, the pedal will go into deep sleep after 15 minutes. To wake the pedal up again, turn it off and on with the power switch.

How many minutes it takes before the pedal goes to sleep can be changed in the code with the timeUntilSleepMins variable.

On a single full charge, the battery should last roughly 12 hours of use.

### Low battery warning
When the battery is running low, the pedal will flash the blue LED rapidly four times. It does this every minute.
This feature can be disabled in the code by setting lowBatteryMessage to 'false'.

### Charging
The pedal runs on a 3100mAh, 18650 Li-ion battery. The battery can be charged via the micro-USB port using a common USB phone charger. When charging, the red LED will turn on. Once charging is done, the green LED will turn on.

Safety: The pedal contains a protection circuit for the battery to prevent charging and discharging too much. However, always take care with Li-ion batteries. It's best to charge them where you can keep an eye on them. For good battery health, don't leave the battery discharged for many months. Don't use the pedal in environments below 0 degrees Celsius.
