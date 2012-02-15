#include "memory.h"
#include "defs.h"

Memory::~Memory()
{
  if(the_memory){
    free(the_memory);
  }
  if(the_off_chip_memory){
    free(the_off_chip_memory);
  }

  the_memory = NULL;
  the_off_chip_memory = NULL;
}


void Memory::initialize()
{
  tile_id = par("tile_id");

  x_tile = par("x_tile");
  y_tile = par("y_tile");

  //calculate the coords of this memory tile.
  x_coord = tile_id % x_tile;
  y_coord = (int)(tile_id / 5);
   
  memory_size = par("memory_size");
  off_chip_memory_size = par("off_chip_memory_size");
  off_chip_memory_enable = par("off_chip_memory_enable");

  delay = 1.0/ ((double)par("clock_rate"));
  delay_off_chip = 1.0/((double)par("off_chip_clock_rate"));

  fromMMU = gate("fromMMU");
  toMMU = gate("toMMU");
  
  mmu_control_in = gateHalf("mmu_control",cGate::INPUT);
  mmu_control_out = gateHalf("mmu_control",cGate::OUTPUT);

  the_memory = (char*)malloc(sizeof(char) * memory_size);
  if(!the_memory){
  }
  //figure out how much memory is actually local memory.
  int local_memory_total = x_tile * y_tile * memory_size;
  local_start = tile_id * memory_size;

  if(off_chip_memory_enable){
    the_off_chip_memory = (char*)malloc(sizeof(char) * off_chip_memory_size);
    if(!the_off_chip_memory){
    }
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

void Memory::handleMessage(cMessage *msg)
{
  if(INCOMING_GATE(msg,fromMMU)){
    CAST_MSG(access,msg,MemoryAccess);

    int address = access->getAddress();
    int b_ctr;
    int a_size = access->getSize();
    char byte;
    int r_value = 0;
    char *the_mem = NULL;
    if(IS_ADDRESS_LOCAL(address)){
      REDUCE_ON_CHIP_TO_LOCAL_ADDRESS(address);
      the_mem = the_memory;
    }
    else{
      if(off_chip_memory_enable){
        REDUCE_OFF_CHIP_TO_LOCAL_ADDRESS(address);
        the_mem = the_off_chip_memory;
      }
      else{
        //throw error and delete message.
        delete msg;
        return;
      }
    }
    if(access->getAccess_type() == READ_M){
      for(b_ctr=0;b_ctr<a_size;b_ctr++){
        byte = the_memory[address+b_ctr];
        r_value = (r_value<<8) | byte;
      }
      access->setValue(r_value);
      //this is to acknowledge that this read is done.
      access->setIsAck(true);
      return;
    }
    if(access->getAccess_type() == WRITE_M){
      //this is slightly dirty way of doing things
      //but i am too irritated to do it the clean 
      //way.
      switch(a_size){
        case 1: //one byte value
          byte = (char)(access->getValue() & 0xff);
          the_mem[address] = byte;
          break;
        case 4: //four byte value
          byte = (char)(access->getValue() & 0xff);
          the_mem[address + 3] = byte;
          byte = (char)((access->getValue()>>8) & 0xff);
          the_mem[address + 2] = byte;
          byte = (char)((access->getValue()>>8) & 0xff);
          the_mem[address + 1] = byte;
          byte = (char)((access->getValue()>>8) & 0xff);
          the_mem[address] = byte;
          break;
      }
      //this is to acknowledge that this write is done.
      access->setIsAck(true);
      return;
    }

    //The test and set semantics are as follows
    // 1. if the location to be modified is 0x00
    //    then set it to 0x01 and return a 1 in the response
    // 2. if the location is non zero then do nothing and return
    //    0 in the respone. 
    if(access->getAccess_type() == TEST_AND_SET_M){
      if(the_mem[address] == 0x00){
        the_mem[address] = 0x01;
        access->setIsAck(true);
        access->setValue(1);
      }
      else{
        access->setIsAck(true);
        access->setValue(0);
      }
    }
    //this is the response from memory - read or an ack or test and set response. 
    sendDelayed(access,delay,toMMU);
  }
  return;
}
