#ifndef __MCORESIM_REDUX_NETIF__
#define __MCORESIM_REDUX_NETIF__

#include<omnetpp.h>

class NetIf : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    int tile_id;
    simtime_t delay;

    cGate* fromMMU;
    cGate* toMMU;

    cGate* fromRouter;
    cGate* toRouter;

    cGate* router_control_in;
    cGate* router_control_out;

    cGate* MMU_control_in;
    cGate* MMU_control_out;

    private:

};
#endif
