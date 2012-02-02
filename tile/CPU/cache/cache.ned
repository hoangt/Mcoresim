///************************************************
//NED for cache. 
//
//The cache sits between the processor and the MMU
//trapping memory accesses that the processor makes.
//Note that this is only a data cache and not an 
//instruction cache. 
//
//************************************************/

package mcoresim.tile.CPU.cache;

simple Cache
{
  parameters:
    int tile_id;
    int cache_size;
    int cache_line_size;
    double clock_rate;
    bool cache_enable;

  gates:
    input fromProc;
    output toProc;

    input fromMMU;
    output toMMU;

    inout processor_control;
    inout mmu_control;

}
