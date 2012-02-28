#ifndef __MCORESIM_REDUX_CONTROL_HEADERS__
#define __MCORESIM_REDUX_CONTROL_HEADERS__

//these are control message code definitions
//ideally these should be defined for each pair of 
//modules that are connected. 
//these control messages should be sent only over the 
//control lines that exist between modules.


/******************************/
// Application - processor
/******************************/

#define APP_PROCESSOR_STATE_RUN         0
#define APP_PROCESSOR_STATE_BLOCKED     1

#endif
