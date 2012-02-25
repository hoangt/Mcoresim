//Message format for the network on chip
//interactions. 
//
// The network packets are similar to barebones 
// IP or Ethernet packet. The main fields are 
// SA, DA, Operation type, optional fields.
// 
// The semantics of the optional fields are 
// based on the type of operation that is 
// being performed by the packet. Currently 
// the field size is set to  Currently 
// the field size is set to 6. Change later 
// as and when needed.
//
// The network packet can be generated/consumed at 
// the MMU, NI or NoC elements. Beyond the MMU all 
// packets must be translated into relevant accesses.

packet NetworkAccess
{
  int counter;
  short operation enum (OperationType);
  int source_address;
  int destination_address;
  int field[6];
  bool isAck;
}

//right now I can only see the use of 
// accessing memory and passing interrupts
// from core to core. 
enum OperationType
{
  MEMORY_ACCESS = 0;
  INTERRUPT = 1;
}
