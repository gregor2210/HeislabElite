#include "queue.h"

void update_queue()
{
    for (int floor = 0; floor < 4; floor++)
    {
        for (ButtonType button = BUTTON_HALL_UP; button <= BUTTON_CAB; button++)
        {
            if (elevio_callButton(floor, button))
            {
                queue[floor][button] = 1;
                elevio_buttonLamp(floor, button, 1);

            }
    }
}
}

int compare_queue_floor() //Sjekker om en av knappene i hver etasje er trykket inn, og om
                          //knappen er trykket inn i den etasjen heisen befinner seg i.
                          //Returnerer 5 ellers, må returnere noe, og kan ikke returnere 0 siden det er en gyldig etasje
{
    for (int floor = 0; floor < 4; floor++)
    {
        for (ButtonType button = BUTTON_HALL_UP; button <= BUTTON_CAB; button++)
        {
            if ((queue[floor][button] == 1) && (floor == current_floor()))
            {
                return floor;
            }
        return 5;
    }
}
}

int check_queue_floor()     //returnerer etasje som ligger i queue
{
    for (int floor = 0; floor < 4; floor++)
    {
        for (ButtonType button = BUTTON_HALL_UP; button <= BUTTON_CAB; button++)
        {
            if (queue[floor][button])
            {
                return floor;
            }
        return 5;
    }
}
}

int check_queue_empty()
{
    for (int floor = 0; floor < 4; floor++)
    {
        for (ButtonType button = BUTTON_HALL_UP; button <= BUTTON_CAB; button++)
        {
            if (elevio_callButton(floor, button))
            {
                return 0;
            }
        }
    }   return 1;
}

void delete_queue_elm(int floor, ButtonType button)
{
    queue[floor][button] = 0;
    elevio_buttonLamp(floor, button, 0);
}

void delete_more_queue()        // For å finne hvilke av knappene i nåværende etasjen som skal slettes
{
    for (ButtonType button = BUTTON_HALL_UP; button <= BUTTON_CAB; button++)
    {
        if (queue[current_floor()][button] == 1)
        {
            delete_queue_elm(current_floor(), button);

        }
}
}

void open_door()
{
    elevio_doorOpenLamp(1);
    sleep(3);
    while (elevio_obstruction())
    {
        continue;
    }
    elevio_doorOpenLamp(0);
}


int valid_floor() //For å gi en etasje bare hvis heisen er i en definert etasje og derfor ikke -1
{
    if (elevio_floorSensor != -1)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int current_floor()  //Jeg sliter med å la current_floor beholde sin nåværende etasje så lenge floorsensor sender ut -1
                     // slik at jeg kan bruke current_floor forskjellige steder uten å få error, jeg vil at at current_floor
                     // alltid skal ha en verdi
{
    if (valid_floor())
    {
        return elevio_floorSensor();
    }
}

int check_request()
{
    for (int floor = 0; floor < 4; floor++)
    {
        for (ButtonType button = BUTTON_HALL_UP; button < BUTTON_CAB; button++)
        {
            if (elevio_callButton(floor, button))
            {
                return floor;
            }
    }
}
}

void move_elv(MotorDirection dir)
{
    elevio_motorDirection(dir);
    current_dir = dir;
}

void turnOffAllLights()
{
    for (int floor = 0; floor < 4; floor++)
    {
        for (ButtonType button = BUTTON_HALL_UP; button <= BUTTON_CAB; button++)
        {
            elevio_buttonLamp(floor, button, 0);
        }
    }
}