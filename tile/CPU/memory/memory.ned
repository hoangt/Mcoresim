///************************************************
//NED for the memory. 
//
//This is memory that is locally located on the tile
//which can be globally accessed. In addition, this
//module when attached to tiles at the corners will
//also contain off-chip memory which is globally 
//accessed. 
//
//Memory is addressed in the size of one-byte (8-bits).
//Internally this is stored as a character array. 
//Complex data types such as int are typically stored
//the way they are in normal memory. 
//************************************************/

package mcoresim.tile.CPU.memory;

simple Memory
{
  parameters:
    int tile_id;
    int x_tile;
    int y_tile;
    int memory_size;
    bool off_chip_memory_enable;
    int off_chip_memory_size;
    double clock_rate;
    double off_chip_clock_rate;

  gates:
    input fromMMU;
    input toMMU;

    inout mmu_control;
}
