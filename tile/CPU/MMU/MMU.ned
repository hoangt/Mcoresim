///************************************************
//NED for MMU 
//
//The memory management unit sits below the cache
//and is connected to the local memory bank on the 
//tile and the NI on the tile. The MMU decides 
//if the access is local or needs to be forwarded
//to the NI. The NI also forwards remote accesses
//to the MMU for a remote tile accessing the memory
//on this tile.
//************************************************/

package tile.CPU.MMU;

simple MMU
{
  parameters:
    int tile_id;
    int x_tile;
    int y_tile;
    int memory_size;
    bool off_chip_memory_enable;
    int off_chip_memory_size;
    int clock_rate;

  gates:
    input fromLocalMem;
    output toLocalMem;

    input fromNI;
    output toNI;

    input fromCache;
    output toCache;

    inout NI_control;
    inout local_mem_control;
    inout cache_control;
}
