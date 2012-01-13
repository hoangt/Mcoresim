///******************************************
//Message format for the processor. 
//
//Essentially this is the instruction set that
//the processor supports. These are what the 
//application module would issue to the
//processor as part of program execution.
//
//The instruction is as follows:
//the counter is like the program instruction counter for that application
//the opcode specifies the type of operation
//the operands are the arguments to the operator specified by the opcode
//
//******************************************/

packet Instruction
{
  int counter;
  int opcode enum (OP_CODE);
  int operand1;
  short op_type1 enum (OP_TYPE);
  int operand2;
  short op_type2 enum (OP_TYPE);
  int operand3;
  short op_type3 enum (OP_TYPE);
}

enum OP_CODE
{
  READ = 0;
  WRITE = 1;
  TEST_AND_SET = 2;
  INTERRUPT_CORE = 3;
  COPY = 4;
  COPYN = 5;
  FLUSH_CACHE = 6;
}

enum OP_TYPE
{
  RESERVED1 = 0;
  CHAR = 1;
  SHORT_INT = 2;
  RESERVED2 = 3;
  INT = 4;
}
