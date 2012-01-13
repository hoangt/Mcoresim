#ifndef __MCORESIM_REDUX_MMU__
#define __MCORESIM_REDUX_MMU__

#include<omnetpp.h>
#include "control_m.h"
#include "cache_m.h"


class MMU : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    int tile_id;

    int x_tile;
    int y_tile;
    int x_coord;
    int y_coord;
    int local_start;
    int off_chip_start;
    int memory_size;
    int off_chip_memory_size;
    bool off_chip_memory_enable;

    simtime_t delay;

    cGate* fromLocalMem;
    cGate* toLocalMem;

    cGate* fromCache;
    cGate* toCache;

    cGate* fromNI;
    cGate* toNI;

    cGate* local_mem_control_in;
    cGate* local_mem_control_out;

    cGate* cache_control_in;
    cGate* cache_control_out;
    
    cGate* NI_control_in;
    cGate* NI_control_out;
};

#endif
