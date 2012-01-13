//Control messages.
// This a generic message format for control messages
// between the various modules.
// Possibly should derive if you need extra fields.
// Currently, it just consists of two fields a response
// code and a identifier (typically the id from the 
// message to which it is a response).
// The code ideally should be in a headerfile as 
// a #define that the pair involved would both include
// so that they may decode/encode it correctly. 

packet ControlMessage
{
  int response_code;
  int response_id;
}
