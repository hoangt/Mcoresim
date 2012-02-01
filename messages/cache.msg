///******************************************
//Message format for the processor-cache-MMU
//interactions. 
//
//The processor-cache-MMU interactions are 
//modelled as a set of read, write and a
//special test-and-set instructions.
//
//The counter is for simply counting the 
//instructions. 
//The access type indicates the type of 
//access. The test-and-set is a hack, since
//it is actually the memory that does the
//test and set (because it is just easier).
//The other two are pretty obvious and self
//explanatory.
//
//******************************************/

packet MemoryAccess
{
  int counter;
  short access_type enum (MemoryAccessType);
  int address;
  int value;
  int size;
  bool isRemote;
  bool isAck;
}

enum MemoryAccessType
{
  READ_M = 0;
  WRITE_M = 1;
  TEST_AND_SET_M = 2;
}

