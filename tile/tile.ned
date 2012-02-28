package mcoresim.tile;

module tile
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

  double router_clock_rate;

gates:
  
  input north_in;
  output north_out;
  inout north_control;
  
  input south_in;
  output south_out;
  inout south_control;
  
  input east_in;
  output east_out;
  inout east_control;

  input west_in;
  output west_out;
  inout west_control;

submodules:

 cpu:CPU{
   tile_id = tile_id;
   processor_clock_rate = processor_clock_rate;
   cache_size = cache_size;
   cache_line_size = cache_line_size;
   cache_clock_rate = cache_clock_rate;
   mmu_clock_rate = mmu_clock_rate;
   local_memory_size = local_memory_size;
   ram_size = ram_size;
   ram_enable = ram_enable;
   local_memory_clock_rate = local_memory_clock_rate;
   ram_clock_rate = ram_clock_rate;
 }

 router:Router{
   router_clock_rate = router_clock_rate;
 }

connection allowunconnected:

  cpu.cpu_in <-- router.toNI;
  router.fromNI <-- cpu.cpu_out;

  north_in <-- router.toNorth;
  router.fromNorth <-- north_out;
  north_control <--> router.north_control;
  
  south_in <-- router.toSouth;
  router.fromSouth <-- south_out;
  south_control <--> router.south_control;
  
  west_in <-- router.toWest;
  router.fromWest <-- west_out;
  west_control <--> router.west_control;
  
  east_in <-- router.toEast;
  router.fromEast <-- East_out;
  east_control <--> router.east_control;
  
}
