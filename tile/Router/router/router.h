#ifndef __MCORESIM_REDUX_ROUTER__
#define __MCORESIM_REDUX_ROUTER__


#include <omnetpp.h>
#include "network_m.h"

class Router : public cSimpleModule
{
  public:

  protected:

    void initialize();
    void handleMessage(cMessage *msg);

    int tile_id;
    simtime_t delay;

    cGate* fromNorth;
    cGate* toNorth;

    cGate* fromSouth;
    cGate* toSouth;

    cGate* fromWest;
    cGate* toWest;

    cGate* fromEast;
    cGate* toEast;

    cGate* north_control_in;
    cGate* north_control_out;

    cGate* south_control_in;
    cGate* south_control_out;

    cGate* west_control_in;
    cGate* west_control_out;

    cGate* east_control_in;
    cGate* east_control_out;

    cGate* fromNI;
    cGate* toNI;

    cGate* ni_control_in;
    cGate* ni_control_out;


  private:

};


#endif
