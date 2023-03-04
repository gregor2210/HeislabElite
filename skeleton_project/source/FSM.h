#include "queue.h"

void reset_FSM();

State handleIdle();

State handleMoving();

State handleDest_reached();

State handleStop();