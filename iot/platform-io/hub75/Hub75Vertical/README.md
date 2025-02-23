# 64x64 Hub75 Matrix via DMA

## ESP32 WROM

| Matrix | Pins left    | Pins right  | Matrix |
|--------|--------------|-------------|--------|
|        | 1-3V3        | 38-GND      | GND    |
|        | 2-EN (RESET) | 37-G23      | A      |
|        | 3-SP (G36)   | 36-G22      |        |
|        | 4-SN (G39)   | 35-TXD (G1) |        |
|        | 5-G34        | 34-RXD (G3) |        |
|        | 6-G35        | 33-G21      |        |
| E      | 7-G32        | 32-GND      |        |
|        | 8-G33        | 32-G19      | B      |
| DR1    | 9-G25        | 30-G18      |        |
| DG1    | 10-G26       | 29-G5       | C      |
| DB1    | 11-G27       | 28-G17      | D      |
| DR2    | 12-G14       | 27-G16      | CLK    |
| DG2    | 13-G12       | 26-G4       | LAT    |
|        | 14-GND       | 25-G0       |        |
| DB2    | 15-G13       | 24-G2       |        |
|        | 16-SD2 (G9)  | 23-G15      |        |
|        | 17-SD3 (G10) | 22-SD1 (G8) |        |
|        | 18-CMD       | 21-SD0 (G7) |        |
|        | 19-V5        | 20-CLK      |        |

