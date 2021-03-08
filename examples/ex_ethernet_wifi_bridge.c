// System Includes
#include <assert.h>
#include <stdint.h>
#include <ucxh_library.h>

// Local Includes
#include "ucxh_serial.h"
#include "ucxh_mode.h"
#include "ex_config.h"

static const char *atList[] = {
        "AT+UBRGC=0,1,2,3",
        "AT+UBRGC=0,0,1",
        "AT+UBRGCA=0,1",
        "AT+UBRGCA=0,3",
        "AT+UETHC=1,0",
        "AT+UETHC=0,1",
        "AT+UETHCA=1",
        "AT+UETHCA=3",
        "AT+UWAPC=0,2,\"myssid\"",
        "AT+UWAPC=0,4,1",
        "AT+UWAPC=0,5,1,1",
        "AT+UWAPC=0,0,1",
        "AT+UWAPCA=0,1",
        "AT+UWAPCA=0,3"
};


static int on_eth_up(ucxhPARSER_urcEthernetUpEvent_t* event)
{
    event->isUp = 1;
    return event->isUp;
}

static int on_eth_down(ucxhPARSER_urcEthernetDownEvent_t* event)
{
    event->isUp = 0;
    return event->isUp;
}

int main(int argc, char** argv)
{
    int result;
    ucxhPARSER_setOnEthernetUp(on_eth_up);
    ucxhPARSER_setOnEthernetDown(on_eth_down);

    printf("Opening serial port...\n");
    result = ucxhSERIAL_open();
    assert(result == true);

    printf("Entering AT mode...\n");
    result = ucxhMODULE_enterAtMode();
    assert(result == true);

    printf("Handling stray responses\n");
    ucxhPARSER_wait(1);

    printf("Talking to NINA...\n");
    ucxhPARSER_sendAtCommands(atList, ELEMENTS_OF(atList));
    ucxhPARSER_wait(1);


    while(1)
    {
        ucxhPARSER_wait(1);
    }


    return 0;
}