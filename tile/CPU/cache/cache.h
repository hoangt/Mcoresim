#ifndef __MCORESIM_REDUX_CACHE__
#define __MCORESIM_REDUX_CACHE__

#include <omnetpp.h>
#include <control_m.h>
#include <cache_m.h>

#define CACHE_STATE_FREE
#define CACHE_STATE_READ_CYCLE
#define CACHE_STATE_FLUSH_CYCLE

class Cache : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    ~Cache();

    int tile_id;
    int cache_size;
    int cache_line_size;
    simtime_t delay;

    char **clines; //the cache itself
    char *flags; //flags for the cache
    int  *age;   //age of the lines
    int  *tags; //the tags

    int num_drop_bits;
    int num_line_bits;
    int tag_check_mask;

    cGate* fromProc;
    cGate* toProc;

    cGate* fromMMU;
    cGate* toMMU;

    cGate* processor_control_in;
    cGate* processor_control_out;

    cGate* mmu_control_in;
    cGate* mmu_control_out;

  private:

    //private methods
    int handle_read_hit(MemoryAccess *access);
    int handle_write_hit(MemoryAccess *access);
    int handle_read_miss(MemoryAccess *access);
    int handle_write_miss(MemoryAccess *access);
    
    void lockCache();
    void unlockCache();
    bool isCacheLocked();
    
    bool IS_CACHE_HIT(int address);
    bool isLineDirty(int address);

    void flush_line(int start_address);
    void generate_reads(int start_address);

    //private variables
    bool lock;
    int cache_state;
    bool read_cycle_pending;

};
#endif
