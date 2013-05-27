#ifndef DEF_DARKPORTAL_H
#define DEF_DARKPORTAL_H

#define MAX_ENCOUNTERS 5

enum Creatures
{
    // Moruzond Encounter
    BOSS_MUROZOND                   = 54432,
    NPC_INFINITE_SUPRESSOR          = 54920,
    NPC_INFINITE_WARDEN             = 54923,
    NPC_HOURGLASS_OF_TIME_TRIGGER   = 54928,
    NPC_NOZDORMU                    = 54751,
};

enum GameObjects
{
    // Moruzond Kalle
    GO_HOURGLASS_OF_TIME        = 209249,
    GO_TEMPORAL_CACHE           = 209547,
};

enum Data
{
    DATA_ECHO_OF_JAINA      = 1,
    DATA_ECHO_OF_BAINE      = 2,
    DATA_ECHO_OF_SYLVANAS   = 3,
    DATA_ECHO_OF_TYRANDE    = 4,
    DATA_MUROZOND           = 5,

    DATA_TEMPORAL_CACHE     = 6,
    DATA_HOURGLASS_OF_TIME  = 7,
};

#endif