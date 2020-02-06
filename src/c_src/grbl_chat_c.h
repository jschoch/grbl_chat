/*
 * grblcomm.c - collects, parses and dispatches lines of data from grbls serial output stream
 *
 * part of MPG/DRO for grbl on a secondary processor
 *
 * v0.0.1 / 2018-09-04 / ©Io Engineering / Terje
 */

/*
Copyright (c) 2018, Terje Io
All rights reserved.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
· Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
· Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.
· Neither the name of the copyright holder nor the names of its contributors may
be used to endorse or promote products derived from this software without
specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _GRBL_CHAT_C_H_
#define _GRBL_CHAT_C_H_

#include <stdbool.h>

#include "grbl.h"
//#include "serial.h"

#define NUMSTATES 13

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

typedef enum {
    Unknown = 0,
    Idle,
    Run,
    Jog,
    Hold0,
    Hold1,
    Alarm,
    Check,
    Door0,
    Door1,
    Door2,
    Door3,
    Tool
} grbl_state_t;

typedef struct {
    grbl_state_t state;
    char state_text[8];
} grbl_t;

typedef struct {
    float x;
    float y;
    float z;
} coord_values_t;

typedef struct {
    float rpm_programmed;
    float rpm_actual;
    bool on;
    bool ccw;
} spindle_data_t;

typedef struct {
    bool flood;
    bool mist;
} coolant_data_t;

typedef union {
    uint16_t flags;
    struct {
        uint16_t mpg :1,
                 state :1,
                 xpos :1,
                 ypos :1,
                 zpos :1,
                 offset :1,
                 leds :1,
                 dist : 1,
                 msg: 1,
                 feed: 1,
                  buffer: 1,
                  buffer_rx: 1,
                 rpm: 1;
    };
} changes_t;

typedef struct {
    grbl_t grbl;
    float position[3];
    float offset[3];
    spindle_data_t spindle;
    coolant_data_t coolant;
    float feed_rate;
    bool useWPos;
    bool awaitWCO;
    bool absDistance;
    bool mpgMode;
    changes_t changed;
    char pins[10];
    char block[255];
    int buffer;
    int buffer_rx;
} grbl_data_t;

grbl_data_t *setGrblReceiveCallback (void (*fn)(char *line));
void setGrblTransmitCallback (void (*fn)(bool ok, grbl_data_t *grbl_data));
bool grblParseState (char *state, grbl_t *grbl);
void parseData(char *);
grbl_data_t * getData();

#endif
