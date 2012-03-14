#include "cache.h"
#include "defs.h"
#include "cache_m.h"
#include "frequency_scale.h"

Define_Module(Cache);

Cache::~Cache()
{
  if(clines){
    int i;
    for(i=0;i<cache_size;i++){
      free(clines[i]);
      }
      free(clines);
  }
  if(flags)
    free(flags);
  if(age)
    free(age);
}


void Cache::initialize()
{
  tile_id = par("tile_id");
  cache_size = par("cache_size"); //note: this indicates the number of lines in the cache
  cache_line_size = par("cache_line_size"); //this indicates the number of bytes per line

#ifndef NO_DELAY
  delay = 1.0/ ((double)par("clock_rate") * CACHE_SCALE_FACTOR);
#else
  delay = 0.0;
#endif

  cache_enable = par("cache_enable");

  fromProc = gate("fromProc");
  toProc = gate("toProc");

  fromMMU = gate("fromMMU");
  toMMU = gate("toMMU");

  processor_control_in = gateHalf("processor_control",cGate::INPUT);
  processor_control_out = gateHalf("processor_control",cGate::OUTPUT);

  mmu_control_in = gateHalf("mmu_control",cGate::INPUT);
  mmu_control_out = gateHalf("mmu_control",cGate::OUTPUT);

  //the cache is written thus - clines is an cache_size array of pointers
  //to char buffers that are cache_line_size long.

  clines = NULL;
  flags = NULL;
  age = NULL;
  tags = NULL;
  num_drop_bits = 0;
  num_line_bits = 0;
  tag_check_mask = 0x0;

  if(cache_enable){
    //TODO: handle cases of failure.
    clines = (char**)malloc(sizeof(char*)*cache_size);
    int i;
    for(i=0;i<cache_size;i++){
      clines[i] = (char*)malloc(sizeof(char)*cache_line_size);
      memset((void*)clines[i],0,sizeof(char)*cache_line_size);
    }
    flags = (char*)malloc(sizeof(char) * cache_size);
    memset((void*)flags,0,sizeof(char)*cache_size);
    age = (int*)malloc(sizeof(int) * cache_size);
    memset((void*)age,0,sizeof(int)*cache_size);
    tags = (int*)malloc(sizeof(int) * cache_size);
    memset((void*)tags,0,sizeof(int)*cache_size);

    //calculate the shifts and bit positions etc 
    //TODO:later
    num_drop_bits = 0;
    num_line_bits = 0;
    tag_check_mask = 0x0;
  }

  return;
}

/*
 the cache organization is as follows. 
1. log2(cache_line_size) of the lowest address bits do not matter.
2. log2(cache_size) number of the next bits from 1 determine which line
   the data goes into.
3. flags contain the status of the line and the age. 
4. the cache uses a LRU replacement policy. 
*/

void Cache::handleMessage(cMessage *msg)
{
  if(INCOMING_GATE(msg,fromProc)){
    if(cache_enable){
      CAST_MSG(access,msg,MemoryAccess);
      int address =  access->getAddress();
      if(IS_CACHE_HIT(address)){
        if(access->getAccess_type() == READ_M)
        {
          handle_read_hit(access); 
        }
        if(access->getAccess_type() == WRITE_M)
        {
          handle_write_hit(access);
        }
      }
      else{
        if(access->getAccess_type() == READ_M)
        {
          handle_read_miss(access);
        }
        if(access->getAccess_type() == WRITE_M)
        {
          handle_write_miss(access);
        }
      }
    }
    else{
      send(msg,toMMU);
    }
  }
  if(INCOMING_GATE(msg,fromMMU)){
    if(cache_enable){
      if(isCacheLocked()){

      }
      else{
        //would I ever see something coming from the 
        //MMU if I am not refreshing or trying to
        //populate the cache???
        //What I mean to say is that the MMU only
        //responds to requests from the cache.
      }
    }
    else{
      send(msg,toProc);
    }
  }
}

int Cache::handle_read_hit(MemoryAccess *access)
{
  //we have what we need in the cache. TODO: partial hits???
  //get it from the cache and then age the lines
  //send it back to the processor
  return 0;
}

int Cache::handle_write_hit(MemoryAccess *access)
{
  //we have the address we are modifying in the cache. TODO: partial hits???
  //modify the data in the cache. 
  //mark the line dirty and then age the lines.
  return 0;
}

int Cache::handle_read_miss(MemoryAccess *access)
{
  //we do not have the address we need in the cache.
  //lock the cache.
  //set the pending read_miss and save the address to be read.
  //locate a line that can accomodate this and flush it if needed.
  //generate reads
  //when the reads are done, unset the pending read_miss, unlock the cache and return val
  return 0;
}

int Cache::handle_write_miss(MemoryAccess *access)
{
  //we do not have the address we need in the cache.
  //lock the cache. 
  //set the pending_write_miss and cache the address and the value
  //locate a line that can accomodate this and flush it if needed.
  //generate the reads
  //when the reads are done, modify the value, unset the pending_write_miss, unlock cache
  return 0;
}

void Cache::lockCache()
{
  lock = true;
  return;
}

void Cache::unlockCache()
{
  lock = false;
  return;
}

bool Cache::isCacheLocked()
{
  return lock;
}

bool Cache::IS_CACHE_HIT(int address)
{
  return false;
}

bool Cache::isLineDirty(int address)
{
  return false;
}

void Cache::generate_reads(int start_address)
{
}

void Cache::flush_line(int start_address)
{
}
