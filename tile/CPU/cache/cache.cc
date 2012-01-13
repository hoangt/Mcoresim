#include "cache.h"

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

  delay = (double) (1.0/par("clock_rate"));

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
    CAST_MSG(access,msg,MemoryAccess);
    int address =  access->getAddress();
    if(IS_CACHE_HIT(address)){
      if(access->getAccessType() == READ)
      {
       // 
      }
      if(access->getAccessType() == WRITE)
      {

      }
    }

  }
  if(INCOMING_GATE(msg,fromMMU)){
  }
}

bool Cache::IS_CACHE_HIT(int address)
{
  if(tags[((address>>num_drop_bits)&(tag_check_mask))] == address){
    return true;
  }
  return false;
}

