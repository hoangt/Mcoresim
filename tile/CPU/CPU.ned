///************************************************
//NED for the CPU block. The CPU block consists of 
//an application, a processor, a cache, an MMU, a
//local memory bank.
//
//************************************************/
package tile.CPU;
import tile.CPU.application.Application;
import tile.CPU.processor.Processor;
import tile.CPU.cache.Cache;
import tile.CPU.MMU.MMU;
import tile.CPU.memory.Memory;
import tile.CPU.netif.NetIf;

module CPU
{
  parameters:
    int tile_id;
    int x_tile;
    int y_tile;

    double tile_frequency;
    double ddr_frequency;

    int cache_size;
    int cache_line_size;
    

    int local_memory_size;
    int ram_size;
    bool ram_enable;
    
  gates:

    input cpu_in;
    output cpu_out;

    inout network_control;
    

  submodules:
    app:Application{
      tile_id = tile_id;
      clock_rate = tile_frequency;
    }

    proc:Processor{
      tile_id = tile_id;
      clock_rate = tile_frequency;
    }

    //cache:Cache{
    //  tile_id = tile_id;
    //  cache_size = cache_size;
    //  cache_line_size = cache_line_size;
    //  clock_rate = tile_frequency;
    //}

    mmu:MMU{
      tile_id = tile_id;
      clock_rate = tile_frequency;
      memory_size = local_memory_size;
      x_tile = x_tile;
      y_tile = y_tile;
      off_chip_memory_enable = ram_enable;
      off_chip_memory_size = ram_size;
    }

    lmb:Memory{
      tile_id = tile_id;
      memory_size = local_memory_size;
      off_chip_memory_enable = ram_enable;
      off_chip_memory_size = ram_size;
      clock_rate = tile_frequency;
      off_chip_clock_rate = ddr_frequency;
      x_tile = x_tile;
      y_tile = y_tile;
    }

    ni:NetIf{
      tile_id = tile_id;
      clock_rate = tile_frequency;
    }

  connections allowunconnected:

    //data path connections first.
    app.fromProc <-- proc.toApp;
    proc.fromApp <-- app.toProc;

    //Cache present connections.
    //proc.fromCache <-- cache.toProc;
    //cache.fromProc <-- proc.toCache;

    //cache.fromMMU <-- mmu.toCache;
    //mmu.fromCache <-- cache.toMMU;
    
    //Cacheless connections
    proc.fromCache <-- mmu.toCache;
    mmu.fromCache <-- proc.toCache;

    lmb.fromMMU <-- mmu.toLocalMem;
    mmu.fromLocalMem <-- lmb.toMMU;

    mmu.fromNI <-- ni.toMMU;
    ni.fromMMU <-- mmu.toNI;

    ni.fromRouter <-- cpu_in;
    cpu_out <-- ni.toRouter;


    //control connections
    app.processor_control <--> proc.app_control;
    //proc.cache_control <--> cache.processor_control;
    //cache.mmu_control <--> mmu.cache_control;
    proc.cache_control <--> mmu.cache_control;
    mmu.local_mem_control <--> lmb.mmu_control;

    mmu.NI_control <--> ni.MMU_control;

    ni.router_control <--> network_control;
}
