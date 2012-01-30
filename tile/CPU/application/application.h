#ifndef __MCORESIM_REDUX_APPLICATION__
#define __MCORESIM_REDUX_APPLICATION__

#include <omnetpp.h>
#include "control_m.h"
#include "processor_isa_m.h"

class Application : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    int tile_id;
    
    cGate* fromProc;
    cGate* toProc;

    cGate* processor_control_in;
    cGate* processor_control_out;
};

#endif
