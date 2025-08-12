    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Registry.h                  //
////////////////////////////////////////

#pragma once

#include <map>
#include <memory>

#include "Id.h"

namespace ylife
{

class Id;

class Item;
class Location;
class Npc;
class Thing;

// Loads the game objects and keeps references to them
class Registry
{
public:
	template<typename T>
	using Map = std::map<Id, std::weak_ptr<T>>;

private:
	Map<Item> items_;
	Map<Location> locations_;
	Map<Npc> npcs_;
	Map<Thing> things_;

public:
	std::shared_ptr<Item> get_item(const Id& id);
	std::shared_ptr<Location> get_location(const Id& id);
	std::shared_ptr<Npc> get_npc(const Id& id);
	std::shared_ptr<Thing> get_thing(const Id& id);

private:
	template<typename T, Id::EType TYPE>
	std::shared_ptr<T> get_object(const Id& id, const Map<T>& map);
};


template<typename T, Id::EType TYPE>
std::shared_ptr<T> Registry::get_object(const Id& id, const Map<T>& map)
{
	if (id.is_empty() || id.get_type() != TYPE)
	{
		return nullptr;
	}

	std::weak_ptr<T>& ptr = MAP[id];
	std::shared_ptr<T> obj = ptr.lock();
	if (!obj)
	{
		obj = std::make_shared<T>(); // Todo: load an object properly
		ptr = obj;
	}
	return obj;
}

}
