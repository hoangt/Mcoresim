#include "application.h"


void Application::initialize()
{

  tile_id = par("tile_id");
  
  fromProc = gate("fromProc");
  toProc = gate("toProcessor");
  
  processor_control_in = gateHalf("processor_control",cGate::INPUT);
  processor_control_out = gateHalf("processor_control",cGate::OUTPUT);

  return;
}

void Application::handleMessage(cMessage* msg)
{
  return;
}
