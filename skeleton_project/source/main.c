#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "queue.h"



int main(){
    elevio_init();

    State state = IDLE;

    while (1)
    {
        update_queue();
        elevio_floorIndicator(current_floor);   //For at riktig lys for hvilken etasje
        if (elevio_stopButton())                //heisen er i skal lyse
        {
        state = STOP;;
        }                                         

        switch (state) 
        {
            case IDLE: 
            {
                state = handleIdle();
                break;
            }

            case MOVING:
            {
                state = handleMoving();
                break;
            }
            
            case DEST_REACHED:
            {
                state = handleDest_reached();
                break;
            }

            case STOP:
            {
                state = handleStop();
                break;
            }
        }
            

    }
}