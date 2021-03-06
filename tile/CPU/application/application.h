#ifndef __MCORESIM_REDUX_APPLICATION__
#define __MCORESIM_REDUX_APPLICATION__

#include <omnetpp.h>
#include "control_m.h"
#include "processor_isa_m.h"
#include <queue>
using namespace std;
//some local #defines for the application to track the state of the application
#define APP_STATE_RUNNING 0
#define APP_STATE_BLOCKED 1


typedef queue<Instruction> Program;

class Application : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    int tile_id;
    simtime_t delay;
    
    cGate* fromProc;
    cGate* toProc;

    cGate* processor_control_in;
    cGate* processor_control_out;

    private:
    
    bool isBlocked();
    bool isRunning();
    void wakeup();
    void block();
    Instruction* nextInstruction();
    void createProgram();
    void dumpInstruction(Instruction* ins);
    
    int state;
    bool isActive;
    int program_counter;
    Program theProgram;

};

#endif
