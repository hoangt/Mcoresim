#ifndef __MCORESIM_REDUX_CACHE__
#define __MCORESIM_REDUX_CACHE__

#include <omnetpp.h>
#include <control_m.h>
#include <cache_m.h>

class Cache : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    int tile_id;
    int cache_size;
    int cache_line_size;
    simtime_t delay;

    char **clines; //the cache itself
    char *flags; //flags for the cache
    int  *age;   //age of the lines
    int  *tags; //the tags


    cGate* fromProc;
    cGate* toProc;

    cGate* fromMMU;
    cGate* toMMU;

    cGate* processor_control_in;
    cGate* processor_control_out;

    cGate* mmu_control_in;
    cGate* mmu_control_out;

};
#endif