#ifndef MAIN_H
#define MAIN_H

#ifdef ARDUINO
#include "Arduino.h"
#include "HardwareSerial.h"
#include <avr/interrupt.h>
#else
#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdio>
#endif

#include "../lib/Pins/Pins.h"
#include "../lib/Rstr/Rstr.h"
#include "../lib/XMLParser/XMLParser.h"
#include "../lib/Pins/Pins.h"

#ifdef ARDUINO
#define custom_println(str)                                                    \
    do { Serial.println((str)); } while (0)
#else
#define custom_println(str)                                                    \
    do { std::cout << (str) << ENDL; } while (0)
#endif

#define log(msg) custom_println((msg))

#define RESPONSE_BUFFER_SIZE 128
#define ENDL                 '\n'
#define INPUT_MAX_LEN        256

enum Command
{
    SET = 0,
    GET,
    PING,
    CCOUNT
};

static const char* commands[CCOUNT] = { "set", "get", "ping" };

enum State
{
    STOP = 0,
    READY,
    GO,
    CAUTION,
    OFF,
    SCOUNT
};

static const char* states[SCOUNT] = { "STOP", "READY", "GO", "CAUTION", "OFF" };

enum Retval
{
    BAD_FORMAT  = 0,
    UNKNOWN_CMD = 1,
    BAD_STATE   = 2
};

static const char* responses[3] = { "BAD_FORMAT", "UNKNOWN_CMD", "BAD_STATE" };

void               sem_off();
void               stop_sem();
void               ready_sem();
void               go_sem();
int8_t             set_state(char* response_buffer, const State state);
void               provide_err_msg(Retval id, char* response_buffer);
void               print_pong(char* response_buffer);
void               provide_curr_state(State curr_state, char* response_buffer);
[[nodiscard]] int8_t get_user_input(rstr& buffer);
Command              get_cmd(const str_view& ptr);
State                get_state(const str_view& ptr);
void                 print_view(const str_view& view);

#endif
