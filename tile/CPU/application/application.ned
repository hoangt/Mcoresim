///************************************************
//NED for the application. 
//
//The application represents the program that must
//execute on the processor. An application will 
//consist of a set of instructions that constitute
//the 'program' to be run. An application can 
//access local memory, off-chip memory and local 
//memory of a remote tile. 
//************************************************/

package tile.CPU.application;

simple Application
{
  parameters:
    int tile_id;
    double clock_rate;
    @display("i=block/app2");

  gates:
    input fromProc;
    output toProc;

    inout processor_control;
}
