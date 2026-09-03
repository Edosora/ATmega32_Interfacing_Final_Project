# ATmega32 Digital Countdown Timer

A digital countdown timer built on the **ATmega32** microcontroller. The user enters a time (HH:MM:SS) using a keypad, the LCD acts as the input guide, and the time counts down on a bank of six seven-segment displays. When the countdown reaches zero, a buzzer sounds.

## Features

- Set time via a 4x4 keypad (hours `<= 32`, minutes/seconds `<= 59`)
- LCD used for input only (shows the entered time while typing)
- Six 7-segment displays show the live countdown
- Buzzer alarm + `TIME UP!` message when the timer ends

## Hardware Requirements

- ATmega32 microcontroller (8 MHz)
- 6 x seven-segment displays (common cathode)
- 16x2 LCD (4-bit mode)
- 4x4 keypad
- Buzzer
- Push button (reset, optional)
- 5V power supply

## Pin Map

| Part                | Connected to                |
|---------------------|-----------------------------|
| 7-seg data (a-g, dp)| PORTA (shared for all 6)   |
| 7-seg commons (6)   | PORTC0 -> PORTC5            |
| LCD data D4-D7      | PB4 -> PB7                  |
| LCD RS / RW / E     | PB0 / PB1 / PB2             |
| Buzzer              | PB3                         |
| Keypad rows R1-R4   | PD0 -> PD3                  |
| Keypad cols C1-C4   | PD4 -> PD7                  |
| Reset button        | RESET pin (9) -> GND        |

## How It Works

1. **Setup** : type the time on the keypad; the LCD echoes each digit into the `HH : MM : SS` slots. Each pair is validated, and an invalid pair resets to `__`.
2. **Countdown** : press `=` to start. Timer1 runs in **CTC mode** and raises an interrupt every **1 second** (31250 ticks at 8 MHz with a prescaler of 256). The 7-segment displays count down SS -> MM -> HH.
3. **Alarm** : at `00:00:00` the buzzer beeps and the LCD shows `TIME UP!`.

