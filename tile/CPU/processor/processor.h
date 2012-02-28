#ifndef __MCORESIM_REDUX_PROCESSOR__
#define __MCORESIM_REDUX_PROCESSOR__

#include<omnetpp.h>
#include "control_m.h"
#include "processor_isa_m.h"
#include "cache_m.h"

class Processor : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    int tile_id;
    simtime_t delay;

    cGate* fromApp;
    cGate* toApp;

    cGate* fromCache;
    cGate* toCache;

    cGate* app_control_in;
    cGate* app_control_out;

    cGate* cache_control_in;
    cGate* cache_control_out;

  private:

    void stall_application();
    void buffer_request(Instruction *inst);

    int counter;
    int buffered_counter;
    Instruction* buffered_inst;
};

#endif
