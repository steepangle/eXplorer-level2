# eXplorer-level2-demo

# PINS

## code definitions

```cpp
#define PIN_LED_L 7
#define PIN_LED_R 8
#define PIN_LED_C 6

#define PIN_DIST_L A1
#define PIN_DIST_R A0
#define PIN_SENS_C A5
#define PIN_SENS_D A4

#define PIN_M1_F 3
#define PIN_M1_R 11
#define PIN_M2_F 9
#define PIN_M2_R 10

#define PIN_SPKR 5
#define PIN_S1 4
#define PIN_S2 2
#define PIN_RGB 13

#define PIN_RX 2
#define PIN_TX 3
```

## ATmega328P PINS

|Physical Pin| IDE PIN      |Device       |
|:----------:|--------------|-------------|
|          1 | **`/RST`**   |-
|          2 | **`D0 RX`**  | X3 Bluetooth
|          3 | **`D1 TX`**  | X3 Bluetooth
|          4 | **`D2`**     | /S2
|          5 | **`D3~`**    | Motor 1 FWD
|          6 | **`D4`**     | S1
|          7 | **`+5V`**    | -
|          8 | **`GND`**    | -
|          9 | **`X1`**     | XTAL1
|         10 | **`X2`**     | XTAL2
|         11 | **`D5~`**    | Piezo Spkr
|         12 | **`D6~`**    | /LED Front
|         13 | **`D7`**     | /LED Left
|         14 | **`D8`**     | LED Right
|         15 | **`D9~`**    | Motor 2 FWD
|         16 | **`D10~`**   | Motor 2 REV
|         17 | **`D11~`**   | Motor 1 REV
|         18 | **`D12~`**   | -
|         19 | **`D13~`**   | RGB-LED DATA
|         20 | **`+5V`**    | -
|         21 | **`AREF`**   | -
|         22 | **`GND`**    | -
|         23 | **`A0`**     | Sens Dist R
|         24 | **`A1`**     | Sens Dist L
|         25 | **`A2`**     | -
|         26 | **`A3`**     | -
|         27 | **`A4 SDA`** | Sens D
|         28 | **`A5 SCL`** | Sens Dist C