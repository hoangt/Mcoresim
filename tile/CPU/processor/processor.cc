#include "processor.h"
#include "processor_isa_m.h"
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
}
