#include "queue.h"

void reset_FSM()
{
    elevio_doorOpenLamp(0);
    turnOffAllLights();
    while (elevio_floorSensor() == -1)
    {
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
}

State handleIdle()
{
    if (compare_queue_floor())
    {
        return DEST_REACHED;
    }

    else if (check_queue_empty())
    {
        return IDLE;
    }

    return MOVING;
}

State handleMoving()
{
    if (queue[current_floor()][BUTTON_CAB]) // Tallet trykket i kabinen er lik heisens nåværende etasje
    {
        return DEST_REACHED;
    }

    else if ((queue[current_floor()][BUTTON_HALL_UP]) && (current_dir = DIRN_UP)) // Heis på vei oppover, knapp trykket inn utenfor heis
    {
        return DEST_REACHED;
    }

    else if ((queue[current_floor()][BUTTON_HALL_DOWN]) && (current_dir = DIRN_DOWN)) // Heis på vei nedover, knapp trykket inn utenfor heis
    {
        return DEST_REACHED;
    }

    else if ((current_floor() < check_queue_floor()) && (check_queue_floor() != 5))
    {
        move_elv(DIRN_UP);
    }

    else if ((current_floor() > check_queue_floor()) && (check_queue_floor() != 5))
    {
        move_elv(DIRN_DOWN);
    }

    return MOVING;
}

State handleDest_reached()
{

    open_door();
    elevio_motorDirection(DIRN_STOP);
    delete_more_queue();

    if (check_queue_empty())
    {
        return IDLE;
    }

    return MOVING;
}

State handleStop()
{
    while (elevio_stopButton)
    {
        move_elv(DIRN_STOP);
        turnOffAllLights();
        if (current_floor())
        {
            open_door();
        }
    }
    return IDLE;
}