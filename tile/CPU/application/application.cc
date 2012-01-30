#include "application.h"
#include "defs.h"

void Application::initialize()
{

  tile_id = par("tile_id");
  
  fromProc = gate("fromProc");
  toProc = gate("toProcessor");
  
  processor_control_in = gateHalf("processor_control",cGate::INPUT);
  processor_control_out = gateHalf("processor_control",cGate::OUTPUT);

  state = APP_STATE_BLOCKED; //the application starts being blocked.

  return;
}

void Application::handleMessage(cMessage* msg)
{
  if(INCOMING_GATE(msg,fromProc)){
    CAST_MSG(res,msg,Instruction);
  }
  if(INCOMING_GATE(msg,processor_control_in)){
  }
  return;
}

bool Application::isBlocked()
{
  return (state == APP_STATE_BLOCKED);
}

bool Application::isRunning()
{
  return (state == APP_STATE_RUNNING);
}

void Application::wakeup()
{
  state = APP_STATE_RUNNING;
  return;
}

void Application::block()
{
  state = APP_STATE_BLOCKED;
  return;
}
