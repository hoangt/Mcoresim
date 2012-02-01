#include "processor.h"
#include "defs.h"

void Processor::initialize()
{

  tile_id = par("tile_id");
  delay = 1.0/ ((double)par("clock_rate"));

  fromApp = gate("fromApp");
  toApp = gate("toApp");

  fromCache = gate("fromCache");
  toCache = gate("toCache");

  app_control_in = gateHalf("app_control",cGate::INPUT);
  app_control_out = gateHalf("app_control",cGate::OUTPUT);
  
  cache_control_in = gateHalf("cache_control",cGate::INPUT);
  cache_control_out = gateHalf("cache_control",cGate::OUTPUT);

  return;
}

void Processor::handleMessage(cMessage *msg)
{
  if(INCOMING_GATE(msg,fromApp)){
    //decode instruction
    CAST_MSG(inst,msg,Instruction);
    MemoryAccess *access = new MemoryAccess();
    switch(inst->getOpcode()){
      case READ:
        stall_application();
        buffer_request(inst);
        translate_to_cache_instruction(inst,access);
        break;
      case WRITE:
        //I am not sure if it makes sense to do this.
        //maybe the application could keep sending write messages
        //to the processor till it gets a read instruction or test-and-set.
        stall_application();
        buffer_request(inst); 
        translate_to_cache_instruction(inst,access);
        break;
      case TEST_AND_SET:
        stall_application();
        buffer_request(inst);
        translate_to_cache_instruction(inst,access);
        break;
      default:
        //error - illegal instruction or not yet supported.
        delete msg;
        return;
    }
    sendDelayed(access,delay,toCache);
  }
  if(INCOMING_GATE(msg,fromCache)){
  }
}

void Processor::stall_application()
{
}

void Processor::buffer_request(Instruction *inst)
{
}

void Processor::translate_to_cache_instruction(Instruction *inst, MemoryAccess *access)
{
}
