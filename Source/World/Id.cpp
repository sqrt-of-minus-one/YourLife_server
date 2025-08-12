    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Id.cpp                      //
////////////////////////////////////////

#include "Id.h"

using namespace ylife;

Id::Id(EType type, const std::string& nspace, const std::string& id) :
	type_(type),
	nspace_(nspace),
	id_(id)
{}

Id::Id(EType type, std::string&& nspace, std::string&& id) :
	type_(type),
	nspace_(std::move(nspace)),
	id_(std::move(id))
{}

Id::Id(EType type, const std::string& id) :
	type_(type),
	nspace_(),
	id_()
{
	extract_parts_from_string_(id, false);
}

Id::Id(const std::string& id) :
	type_(),
	nspace_(),
	id_()
{
	extract_parts_from_string_(id, true);
}

Id::EType Id::get_type() const
{
	return type_;
}

const std::string& Id::get_nspace() const
{
	return nspace_;
}

const std::string& Id::get_id() const
{
	return id_;
}

void Id::set_type(EType type)
{
	type_ = type;
}

void Id::set_nspace(const std::string& nspace)
{
	nspace_ = nspace;
}

void Id::set_nspace(std::string&& nspace)
{
	nspace_ = std::move(nspace);
}

void Id::set_id(const std::string& id)
{
	id_ = id;
}

void Id::set_id(std::string&& id)
{
	id_ = std::move(id);
}

void Id::set_full_id(EType type, const std::string& id)
{
	type_ = type;
	extract_parts_from_string_(id, false);
}

void Id::set_full_id(const std::string& id)
{
	extract_parts_from_string_(id, true);
}

bool Id::is_empty() const
{
	return id_.empty();
}

const std::string& Id::to_string(bool include_type) const
{
	return include_type ?
		type_to_string(type_) + TYPE_SEP + nspace_ + NSPACE_SEP + id_ :
		nspace_ + NSPACE_SEP + id_;
}

Id Id::get_parent() const
{
	auto last_dot = id_.find_last_of(ID_SEP);
	return Id(type_, nspace_,
		last_dot == id_.npos ? "" : id_.substr(last_dot + 1));
}

Id Id::get_common_ancestor(const Id& id) const
{
	if (type_ != id.type_)
	{
		// No common ancestors
		return Id();
	}
	if (nspace_ != id.nspace_)
	{
		// No common ancestors
		return Id(type_, "", "");
	}
	if (id_.empty() || id.id_.empty() || id_[0] != id.id_[0])
	{
		// No common ancestors
		return Id(type_, nspace_, "");
	}

	int first_diff_pos = 0; // The id's are equal up to this position
	int last_dot_pos = 0; // The last dot of the common part of id's
	int min_length = std::min(id_.length(), id.id_.length()); // The minimum length of the two ids
	while (first_diff_pos < min_length && id_[first_diff_pos] == id.id_[first_diff_pos])
	{
		if (id_[first_diff_pos] == ID_SEP)
		{
			last_dot_pos = first_diff_pos;
		}
		++first_diff_pos;
	}
	return Id(type_, nspace_, id_.substr(0,
		first_diff_pos == min_length ? min_length : last_dot_pos));
}

bool Id::is_parent_of(const Id& id) const
{
	return is_ancestor_of(id) && id_.find(ID_SEP, id.id_.length() + 1) == id_.npos;
}

bool Id::is_child_of(const Id& id) const
{
	return id.is_parent_of(*this);
}

bool Id::is_ancestor_of(const Id& id) const
{
	if (type_ != id.type_ || nspace_ != id.nspace_ || id_.length() <= id.id_.length())
	{
		return false;
	}

	for (int i = 0; i < id.id_.length(); ++i)
	{
		if (id_[i] != id.id_[i])
		{
			return false;
		}
	}
	return id_[id.id_.length()] == ID_SEP;
}

bool Id::is_descendant_of(const Id& id) const
{
	return id.is_ancestor_of(*this);
}

Id& Id::operator=(const std::string& id)
{
	extract_parts_from_string_(id, true);
}

Id Id::operator-() const
{
	return get_parent();
}

Id Id::operator/(const std::string& str) const
{
	Id id = *this;
	return id /= str;
}

std::strong_ordering Id::operator<=>(const Id& id) const
{
	if (type_ != id.type_)
	{
		return type_ <=> id.type_;
	}
	else if (nspace_ != id.nspace_)
	{
		return nspace_ <=> id.nspace_;
	}
	return id_ <=> id.id_;
}

Id& Id::operator/=(const std::string& str)
{
	if (str.front() != ID_SEP)
	{
		id_.push_back(ID_SEP);
	}
	id_.append(str);
	return *this;
}

const std::string& Id::type_to_string(EType type)
{
	switch (type)
	{
	case EType::ITEM:
		return ITEM_TYPE;
	case EType::LOCATION:
		return LOCATION_TYPE;
	case EType::NPC:
		return NPC_TYPE;
	case EType::THING:
		return THING_TYPE;
	default:
		return COMMON_TYPE;
	}
}

Id::EType Id::string_to_type(const std::string& string)
{
	if (string == ITEM_TYPE)
	{
		return EType::ITEM;
	}
	else if (string == LOCATION_TYPE)
	{
		return EType::LOCATION;
	}
	else if (string == NPC_TYPE)
	{
		return EType::NPC;
	}
	else if (string == THING_TYPE)
	{
		return EType::THING;
	}
	return EType::COMMON;
}

const std::string Id::COMMON_TYPE = "common";
const std::string Id::ITEM_TYPE = "item";
const std::string Id::LOCATION_TYPE = "location";
const std::string Id::NPC_TYPE = "npc";
const std::string Id::THING_TYPE = "thing";

void Id::extract_parts_from_string_(const std::string& id, bool extract_type)
{
	auto slash_pos = id.find(TYPE_SEP);
	auto colon_pos = id.find(NSPACE_SEP,
		slash_pos != id.npos ? slash_pos + 1 : 0);

	if (extract_type && slash_pos != id.npos)
	{
		type_ = string_to_type(id.substr(0, slash_pos - 1));
	}

	if (colon_pos != id.npos)
	{
		if (slash_pos != id.npos)
		{
			nspace_ = id.substr(slash_pos + 1, colon_pos - slash_pos - 1);
		}
		else
		{
			nspace_ = id.substr(0, colon_pos - 1);
		}
		id_ = id.substr(colon_pos + 1);
	}
	else
	{
		nspace_ = "";
		if (slash_pos != id.npos)
		{
			id_ = id.substr(slash_pos + 1);
		}
		else
		{
			id_ = id;
		}
	}
}
