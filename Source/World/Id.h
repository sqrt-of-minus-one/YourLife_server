    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Id.h                        //
////////////////////////////////////////

#pragma once

#include <optional>
#include <string>

namespace ylife
{

// Identifier for the world elements
// An Id has the form "type/nspace:id", e.g. "location/mygame:city.house.flat"
class Id
{
public:
	// Objects that can have an Id
	enum class EType
	{
		COMMON = 0,	// Should be considered as invalid
		ITEM,
		LOCATION,
		NPC,
		THING
	};

private:
	EType type_ = EType::COMMON;
	std::string nspace_;
	std::string id_;

	std::string string_;

public:
	Id() = default; // An invalid empty Id
	Id(const Id& id) = default;
	Id(Id&& id) = default;
	Id(EType type, const std::string& nspace, const std::string& id); // EType::TYPE, "nspace", "id"
	Id(EType type, std::string&& nspace, std::string&& id); // EType::TYPE, "nspace", "id"
	Id(EType type, const std::string& id); // EType::TYPE, "nspace:id"
	Id(const std::string& id); // "type/nspace:id"

	EType get_type() const;
	const std::string& get_nspace() const;
	const std::string& get_id() const;

	// Change elements of the id
	void set_type(EType type);
	void set_nspace(const std::string& nspace);
	void set_nspace(std::string&& nspace);
	void set_id(const std::string& id);
	void set_id(std::string&& id);
	void set_full_id(EType type, const std::string& id); // EType::TYPE, "nspace:id"
	void set_full_id(const std::string& id); // "type/nspace:id" or "nspace:id" (the type won't be changed in the latter case)

	bool is_empty() const;
	const std::string& to_string(bool include_type = true) const;

	// The id hierarchy is set via dots:
	// "location/mygame:city.house" is the parent of "location/mygame:city.house.flat"
	Id get_parent() const; // Empty id if there is no parent (e.g. for "location/mygame:city")
	Id get_common_ancestor(const Id& id) const; // Empty id if there is no common ancestor
	bool is_parent_of(const Id& id) const;
	bool is_child_of(const Id& id) const;
	bool is_ancestor_of(const Id& id) const;
	bool is_descendant_of(const Id& id) const;

	Id& operator=(const Id& id) = default;
	Id& operator=(Id&& id) = default;
	Id& operator=(const std::string& id);

	Id operator-() const; // Same as get_parent()
	Id operator/(const std::string& str) const;

	std::strong_ordering operator<=>(const Id& id) const;

	Id& operator/=(const std::string& str);

	static const std::string& type_to_string(EType type);
	static EType string_to_type(const std::string& string);

	static const std::string COMMON_TYPE;
	static const std::string ITEM_TYPE;
	static const std::string LOCATION_TYPE;
	static const std::string NPC_TYPE;
	static const std::string THING_TYPE;
	static constexpr char TYPE_SEP = '/';
	static constexpr char NSPACE_SEP = ':';
	static constexpr char ID_SEP = '.';

private:
	void extract_parts_from_string_(const std::string& id, bool extract_type);
};

}
