#include "router.h"

void Router::initialize()
{
  tile_id = par("tile_id");
  delay = 1.0/ ((double)par("clock_rate"));

  fromNorth = gate("fromNorth");
  toNorth = gate("toNorth");

  fromSouth = gate("fromSouth");
  toSouth = gate("toSouth");

  fromWest = gate("fromWest");
  toWest = gate("toWest");

  fromEast = gate("fromEast");
  toEast = gate("toEast");

  north_control_in = gateHalf("north_control",cGate::INPUT);
  north_control_out = gateHalf("north_control",cGate::OUTPUT);

  south_control_in = gateHalf("south_control",cGate::INPUT);
  south_control_out = gateHalf("south_control",cGate::OUTPUT);

  west_control_in = gateHalf("west_control",cGate::INPUT);
  west_control_out = gateHalf("west_control",cGate::OUTPUT);

  east_control_in = gateHalf("east_control",cGate::INPUT);
  east_control_out = gateHalf("east_control",cGate::OUTPUT);

  fromNI = gate("fromNI");
  toNI = gate("toNI");

  ni_control_in = gateHalf("ni_control",cGate::INPUT);
  ni_control_out = gateHalf("ni_control",cGate::OUTPUT);

  return;
}

void Router::handleMessage(cMessage *msg)
{

  return;
}
