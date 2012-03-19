import tile.CPU.CPU;


network OneTile{

  parameters:

    double tile_frequency;
    double ddr_frequency;

    int cache_size;
    int cache_line_size;
    

    int local_memory_size;
    int ram_size;
    bool ram_enable;

  submodules:
    theCpu:CPU{
      tile_id = 0;
      x_tile = 1;
      y_tile = 1;
      tile_frequency = tile_frequency;
      ddr_frequency = ddr_frequency;
      cache_size = cache_size;
      cache_line_size = cache_line_size;
      local_memory_size = local_memory_size;
      ram_size = ram_size;
      ram_enable = ram_enable;
    }
  
  connections allowunconnected:


    //this hack just loops back the output of the tile to its own input. We 
    //still arent reaching the world outside(which doesnt exist now) so we are
    //good that way.
    theCpu.cpu_in <-- theCpu.cpu_out;
}
