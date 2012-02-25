//////////////////////////////////////////////////////
// NED for the network interface. 
// 
// the network interface is the module that will talk
// to the NoC and the routers. the network interface. 
// 
// the network interface is connected to the MMU on one
// side and to the router on the other. 
//////////////////////////////////////////////////////

package mcoresim.tile.CPU.netif;

simple NetIf
{
  parameters:
    int tile_id;
    double clock_rate;
    
  gates:
    input fromMMU;
    output toMMU;

    input fromRouter;
    output toRouter;

    inout MMU_control;
    inout router_control;
}
