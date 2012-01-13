///************************************************
//NED for the CPU block. The CPU block consists of 
//an application, a processor, a cache, an MMU, a
//local memory bank.
//
//************************************************/
package mcoresim.tile.CPU;

module CPU
{
  parameters:
    int tile_id;

    double processor_clock_rate;
    
    int cache_size;
    int cache_line_size;
    double cache_clock_rate;
    
    double mmu_clock_rate;

    int local_memory_size;
    int ram_size;
    bool ram_enable;
    double local_memory_clock_rate;
    double ram_clock_rate;
    
  gates:

    input cpu_in;
    output cpu_out;

    inout network_control;
    

  submodules:
    app:Application{
      tile_id = tile_id;
    }

    proc:Processor{
      tile_id = tile_id;
      clock_rate = processor_clock_rate;
    }

    cache:Cache{
      tile_id = tile_id;
      cache_size = cache_size;
      cache_line_size = cache_line_size;
      clock_rate = cache_clock_rate;
    }

    mmu:MMU{
      tile_id = tile_id;
      clock_rate = mmu_clock_rate;
    }

    lmb:memory{
      tile_id = tile_id;
      memory_size = local_memory_size;
      off_chip_memory_enable = ram_enable;
      off_chip_memory_size = ram_size;
      clock_rate = local_memory_clock_rate;
      off_chip_clock_rate = ram_clock_rate;
    }

  connections allowunconnected:

    //data path connections first.
    app.fromProc <-- proc.toApp;
    proc.fromApp <-- app.toProc;

    proc.fromCache <-- cache.toProc;
    cache.fromProc <-- proc.toCache;

    cache.fromMMU <-- mmu.toCache;
    mmu.fromCache <-- cache.toMMU;

    lmb.fromMMU <-- mmu.toLocalMem;
    mmu.fromLocalMem <-- lmb.toMMU;

    mmu.fromNI <-- cpu_in;
    cpu_out <-- mmu.toNI;


    //control connections
    app.processor_control <--> proc.app_control;
    proc.cache_control <--> cache.processor_control;
    cache.mmu_control <--> mmu.cache_control;
    mmu.local_mem_control <--> lmb.mmu_control;

    mmu.NI_control <--> network_control;
    

}
