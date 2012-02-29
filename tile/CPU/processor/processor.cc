#include "processor.h"
#include "defs.h"

#include "control_defs.h"

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
  
  counter =0;
  return;
}

void Processor::handleMessage(cMessage *msg)
{
  if(INCOMING_GATE(msg,fromApp)){
    //decode instruction
    CAST_MSG(inst,msg,Instruction);
    MemoryAccess *access = new MemoryAccess();
    counter++;
    access->setCounter(counter);
    buffer_request(inst);
    switch(inst->getOpcode()){
      case READ:
        access->setAccess_type(READ_M);
        access->setAddress(inst->getOperand1());
        access->setSize(inst->getOp_type1());
        stall_application();
        break;
      case WRITE:
        //I am not sure if it makes sense to do this.
        //maybe the application could keep sending write messages
        //to the processor till it gets a read instruction or test-and-set.
        access->setAccess_type(WRITE_M);
        access->setAddress(inst->getOperand1());
        access->setValue(inst->getOperand2());
        access->setSize(inst->getOp_type1()); 
        break;
      case TEST_AND_SET:
        access->setAccess_type(TEST_AND_SET_M);
        access->setAddress(inst->getOperand1());
        access->setSize(inst->getOp_type1());
        stall_application(); 
        break;
      default:
        //error - illegal instruction or not yet supported.
        delete msg;
        delete access;
        return;
    }
    sendDelayed(access,delay,toCache);
  }
  if(INCOMING_GATE(msg,fromCache)){
    //ideally the message that comes from the cache should be a response
    //to something that has been buffered and is pending.
    //but just check anyways. 
    CAST_MSG(response,msg,MemoryAccess);
    if(response->getCounter() == buffered_counter){
      //we are good. Respond to the application.
      switch(response->getAccess_type()){
        case READ_M:
        case TEST_AND_SET_M:
          //this requires response. in both cases the value part of the 
          //access should just be copied to the operand1 location. 
          //NOTE this is a hack for now, but hell, this is just a 
          //simulator.
          unstall_application();
          send(buffered_inst,toApp);
          break;
        case WRITE_M:
          //for write we do nothing. its already been done.
        default:
          //something that is wrong or hasn't been implemented yet.
          if(buffered_inst){
            delete buffered_inst;
          }
      }
      buffered_counter = -1;
    }
    else{
      //argh what do i do now???
    }
  }
  delete msg;
}

void Processor::stall_application()
{
  //TODO:: currently not implemented. Hack around it by making sure
  //that the application does not hit the next instruction to the processor
  //till the current instruction is done. Write will be the problem here
  //because how does one really acknowledge a write to the application from
  //the processor. Seems a silly thing. I will come back to this once I get
  //the remainder of the stuff at the bottom working.
  ControlMessage *cntl = new ControlMessage();
  cntl->setResponse_code(APP_PROCESSOR_STATE_BLOCKED);
  send(cntl,app_control_out);
  return;
}

void Processor::unstall_application()
{
  ControlMessage *cntl = new ControlMessage();
  cntl->setResponse_code(APP_PROCESSOR_STATE_RUN);
  send(cntl,app_control_out);
  return;
}

void Processor::buffer_request(Instruction *inst)
{
  buffered_inst = inst->dup();
  buffered_counter = counter;
  return;
}
