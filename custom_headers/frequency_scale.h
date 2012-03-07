#ifndef __MCORESIM_REDUX_FREQUENCY_SCALER__
#define __MCORESIM_REDUX_FREQUENCY_SCALER__

//This header defines the frequency scaling that is applied based on the 
//tile frequency to the various components in the tile.
//The offchip ram frequency is set separately through a ddr_frequency param 

#define LOCAL_MEMORY_SCALE_FACTOR  1
#define PROCESSOR_SCALE_FACTOR     4
#define CACHE_SCALE_FACTOR         3 
#define MMU_SCALE_FACTOR           3
#define NETIF_SCALE_FACTOR         5

#define ROUTER_SCALE_FACTOR        5 



#endif

