#pragma once
#include "driver/elevio.h"
#include "FSM.h"

typedef enum State
{
    IDLE,
    MOVING,
    DEST_REACHED,
    STOP
} State;

MotorDirection* current_dir;

int queue[4][3];
void update_queue();
int compare_queue_floor();
int check_queue_floor();
int check_queue_empty();
void delete_queue_elm(int floor, ButtonType button);
void delete_more_queue();
void open_door();
int valid_floor();
int current_floor();
int check_request();
void move_elv(MotorDirection dir);
void turnOffAllLights();
