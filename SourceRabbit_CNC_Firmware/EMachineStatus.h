#ifndef EMACHINESTATUS_H
#define EMACHINESTATUS_H

enum EMachineStatus
{
    MACHINESTATUS_IDLE,
    MACHINESTATUS_RUN,
    MACHINESTATUS_HOLD,
    MACHINESTATUS_JOG,
    MACHINESTATUS_HOMING,
    MACHINESTATUS_ALARM
};

#endif