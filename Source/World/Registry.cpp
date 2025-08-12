    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Registry.cpp                //
////////////////////////////////////////

#include "Registry.h"

#include "Item/Item.h"
#include "Location/Location.h"
#include "Npc/Npc.h"
#include "Thing/Thing.h"

using namespace ylife;

std::shared_ptr<Item> Registry::get_item(const Id& id)
{
	return get_object<Item, Id::EType::ITEM>(id, items_);
}

std::shared_ptr<Location> Registry::get_location(const Id& id)
{
	return get_object<Location, Id::EType::LOCATION>(id, locations_);
}

std::shared_ptr<Npc> Registry::get_npc(const Id& id)
{
	return get_object<Npc, Id::EType::NPC>(id, npcs_);
}

std::shared_ptr<Thing> Registry::get_thing(const Id& id)
{
	return get_object<Thing, Id::EType::THING>(id, things_);
}
