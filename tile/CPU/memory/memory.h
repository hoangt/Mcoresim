#ifndef __MCORESIM_REDUX_MEMORY__
#define __MCORESIM_REDUX_MEMORY__

#include<omnetpp.h>
#include "control_m.h"
#include "cache_m.h"

class Memory : public cSimpleModule
{
  public:
    ~Memory();

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
    simtime_t delay_off_chip;

    cGate* fromMMU;
    cGate* toMMU;

    cGate* mmu_control_in;
    cGate* mmu_control_out;

    private:
      char *the_memory;
      char *the_off_chip_memory;
};

#endif
