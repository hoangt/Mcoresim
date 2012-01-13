#ifndef __MCORESIM_REDUX_CUSTOM_HEADER__
#define __MCORESIM_REDUX_CUSTOM_HEADER__

//some generic stuff with message arrivals - all use
#define INCOMING_GATE(MSG,GATE)  (MSG->getArrivalGate() == GATE)
#define CAST_MSG(NEW_MSG,MSG,TYPE)        TYPE* NEW_MSG = check_and_cast<TYPE*> (MSG)


//some macros for memory access checks and r/w - for MMU,memory
#define REDUCE_ON_CHIP_TO_LOCAL_ADDRESS(X)      X= X - (local_start)
#define REDUCE_OFF_CHIP_TO_LOCAL_ADDRESS(X)     X= X - (off_chip_start)

#define IS_ADDRESS_LOCAL(X)         ((X>=local_start) && (X < (local_start + memory_size))) 
#define IS_ADDRESS_OFF_CHIP_HERE(X) ((X>=off_chip_start) && (X < (off_chip_start + off_chip_memory_size)))  

#endif
