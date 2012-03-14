package tile;

module tile
{
parameters:

  int tile_id;
  int x_tile;
  int y_tile;

  double tile_frequency;
  double ddr_frequency;

  double router_clock_rate;

  int cache_size;
  int cache_line_size;
  int local_memory_size;
  int ram_size;
  bool ram_enable;

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
   x_tile = x_tile;
   y_tile = y_tile;

   tile_frequency = tile_frequency;
   ddr_frequency = ddr_frequency;

   cache_size = cache_size;
   cache_line_size = cache_line_size;


   local_memory_size = local_memory_size;
   ram_size = ram_size;
   ram_enable = ram_enable;
 }

router:Router{
   router_clock_rate = router_clock_rate;
 }

connections allowunconnected:

  cpu.cpu_in <-- router.toNI;
  router.fromNI <-- cpu.cpu_out;
  router.ni_control <--> cpu.network_control;

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
