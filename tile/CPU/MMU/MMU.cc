#include "MMU.h"
#include "defs.h"
#include "frequency_scale.h"

Define_Module(MMU);

void MMU::initialize()
{
  tile_id = par("tile_id");

  x_tile = par("x_tile");
  y_tile = par("y_tile");

  x_coord = tile_id % x_tile;
  y_coord = (int)(tile_id / x_tile);

  memory_size = par("memory_size");
  off_chip_memory_size = par("off_chip_memory_size");
  off_chip_memory_enable = par("off_chip_memory_enable");

#ifndef NO_DELAY
  delay = 1.0/ ((double)par("clock_rate") * MMU_SCALE_FACTOR);
#else
  delay = 0.0;
#endif

  fromLocalMem = gate("fromLocalMem");
  toLocalMem = gate("toLocalMem");

  fromCache = gate("fromCache");
  toCache = gate("toCache");

  fromNI = gate("fromNI");
  toNI = gate("toNI");

  local_mem_control_in = gateHalf("local_mem_control",cGate::INPUT);
  local_mem_control_out = gateHalf("local_mem_control",cGate::OUTPUT);
  
  cache_control_in = gateHalf("cache_control",cGate::INPUT);
  cache_control_out = gateHalf("cache_control",cGate::OUTPUT);
  
  NI_control_in = gateHalf("NI_control",cGate::INPUT);
  NI_control_out = gateHalf("NI_control",cGate::OUTPUT);

  //figure out how much memory is actually local memory.
  int local_memory_total = x_tile * y_tile * memory_size;
  local_start = tile_id * memory_size;

  if(off_chip_memory_enable){
    //now figure out what is the memory address for the offchip memory
    //sitting here.
    if((x_coord == 0) && (y_coord == 0)){
      //first bank
      off_chip_start = local_memory_total;
    }
    if((x_coord == x_tile) && (y_coord == 0)){
      //second bank
      off_chip_start = local_memory_total + off_chip_memory_size;
    }
    if((x_coord == 0) && (y_coord == y_tile)){
      //third bank
      off_chip_start = local_memory_total + (2 * off_chip_memory_size);
    }
    if((x_coord == x_tile) && (y_coord == y_tile)){
      //third bank
      off_chip_start = local_memory_total + (3 * off_chip_memory_size);
    }

  }
  return;
}

void MMU::handleMessage(cMessage *msg)
{

  if(INCOMING_GATE(msg,fromLocalMem)){
    CAST_MSG(access_response,msg,MemoryAccess);
    if(access_response->getIsRemote()){
      //figure out how to handle this later.
      //TODO:later
      //the idea is that this a response to a request
      //for access from somewhere else on the chip.
      //this must be retranslated back into a network
      // packet and sent out through the NI.
    }
    else{
      //this access was triggered by the local 
      //cache.
      sendDelayed(msg,delay,toCache);
    }
  }
  if(INCOMING_GATE(msg,fromCache)){
    CAST_MSG(access,msg,MemoryAccess);
    int address = access->getAddress();
    if((IS_ADDRESS_LOCAL(address))||(IS_ADDRESS_OFF_CHIP_HERE(address))){
      sendDelayed(msg,delay,toLocalMem);
    }
    else{
      //this is an access to some remote
      //memory location from the local 
      //cache.
      //TODO:later
      //the idea is that this a request
      //for access to memroy somewhere else on the chip.
      //this must be translated into a network 
      // packet and sent out to the NI.
    }
  }
  if(INCOMING_GATE(msg,fromNI)){
    //TODO:later
    //the idea is that this a request
    //for access from somewhere else on the chip.
    //this must be translated into a local memory access
    // packet and sent out to the local memory.

    //the other thing that this can be is an interrupt that has been
    //sent to this core from someother core. in which case feed it directly to 
    //the processor. 
  }
}

