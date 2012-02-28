/************************************************
//NED for router.
//
//the router is the element that is responsible for
//routing of packets on the NoC and delivering them
//from tile to tile. 
//************************************************/

package mcoresim.tile.Router.router;


simple Router
{
  parameters:
    int tile_id;
    double clock_rate;
    @display("i=device/cpu");

  gates:

    input fromNorth;
    output toNorth;

    input fromEast;
    output toEast;

    input fromSouth;
    output toSouth;

    input fromWest;
    output toWest;

    inout north_control;
    inout east_control;
    inout south_control;
    inout west_control;

    input fromNI;
    output toNI;

    inout ni_control;
}
