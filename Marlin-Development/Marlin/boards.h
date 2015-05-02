#ifndef BOARDS_H
#define BOARDS_H

#define BOARD_UNKNOWN -1

#define BOARD_RAMPS_OLD         3    // MEGA/RAMPS up to 1.2
#define BOARD_RAMPS_13_EFB      33   // RAMPS 1.3 / 1.4 (Power outputs: Extruder, Fan, Bed)
#define BOARD_RAMPS_13_EEB      34   // RAMPS 1.3 / 1.4 (Power outputs: Extruder0, Extruder1, Bed)
#define BOARD_RAMPS_13_EFF      35   // RAMPS 1.3 / 1.4 (Power outputs: Extruder, Fan, Fan)
#define BOARD_RAMPS_13_EEF      36   // RAMPS 1.3 / 1.4 (Power outputs: Extruder0, Extruder1, Fan)

#define BOARD_99                99   // This is in pins.h but...?

#define MB(board) (MOTHERBOARD==BOARD_##board)

#endif //__BOARDS_H
