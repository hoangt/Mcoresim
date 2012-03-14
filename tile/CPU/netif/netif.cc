#include "netif.h"
#include "control_m.h"
#include "network_m.h"
#include "defs.h"

#include "frequency_scale.h"


Define_Module(NetIf);

void NetIf::initialize()
{
  tile_id = par("tile_id");

#ifndef NO_DELAY
  delay = 1.0/ ((double)par("clock_rate") * NETIF_SCALE_FACTOR);
#else
  delay = 0.0;
#endif

  fromMMU = gate("fromMMU");
  toMMU = gate("toMMU");

  fromRouter = gate("fromRouter");
  toRouter = gate("toRouter");

  MMU_control_in = gateHalf("MMU_control",cGate::INPUT);
  MMU_control_out = gateHalf("MMU_control",cGate::OUTPUT);
  
  router_control_in = gateHalf("router_control",cGate::INPUT);
  router_control_out = gateHalf("router_control",cGate::OUTPUT);
  
  return;
}


void NetIf::handleMessage(cMessage *msg)
{
  if(INCOMING_GATE(msg,fromMMU)){
    //stuff that comes from the mmu is stuff that is destined to be
    //put on the network. To make life simpler the MMU constructs
    //the network packet message. The NI simply has to put it out.
  }
  if(INCOMING_GATE(msg,fromRouter)){
    //stuff that comes from the router can be two things
    //a) a memory access to memory that is connected to this tile
    //b) an intercore interrupt
  }
}
