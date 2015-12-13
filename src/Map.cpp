#include <string>
#include "Map.hpp"
#include "Object.hpp"
#include "Zork_Def.hpp"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

Condition Map::parseCondition(xml_node<>* i)
{
	xml_node<>* inner = i->first_node();
	string name = inner->name();
	if(name=="has"){
		string intagname;
		bool has;
		string obj;
		string owner;
		string value;
		for(xml_node<> *intag = i->first_node(); intag; intag = intag->next_sibling()){
			intagname = intag->name();
			value = intag->value();
			if(intagname=="has")has=(value=="yes");
			else if(intagname=="object")obj=intag->value();
			else if(intagname=="owner")owner=intag->value();
		}
		return Condition(ConditionParser(has,obj,owner));
	}else{
		string intagname;
		string obj;
		string sta;
		for(xml_node<> *intag = i->first_node(); intag; intag = intag->next_sibling()){
			intagname = intag->name();
			if(intagname=="object")obj=intag->value();
			else if(intagname=="status")sta=intag->value();
		}
		return Condition(ConditionParser(obj,sta));
	}
}


Trigger Map::parseTrigger(xml_node<>* node)
{
	string tag;
	string CMD;
	string print;
	bool perm = false;
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="command") CMD = i->value();
		else if(tag=="type") perm = (string("permenant")==i->value());
		else if(tag=="print") print = i->value();
	}
	Trigger tri(CMD,print,perm);
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		if(tag=="condition") tri.addCondition(parseCondition(i));
		else if(tag=="action") tri.addAction(ActionParser(i->value()));
	}
	return tri;
}

Item Map::parseItem(xml_node<>* node)
{
	string tag;
	string name;
	string write;
	string status;
	bool enable = false;
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="name") name = i->value();
		else if(tag=="writing") write = i->value();
		else if(tag=="status") status = i->value();
		else if(tag=="turnon") enable = true;
	}
	return Item(name,write,status,enable);
}

Creature Map::parseCreature(xml_node<>* node)
{
	string tag;
	string name;
	string desc;
	string status;
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="name") name = i->value();
		else if(tag=="description") desc = i->value();
		else if(tag=="status") status = i->value();
	}
	return Creature(name,desc,status);
}

Room Map::parseRoom(xml_node<>* node)
{
	string tag;
	string name;
	string desc;
	string status;
	string type;
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="name") name = i->value();
		else if(tag=="description") desc = i->value();
		else if(tag=="status") status = i->value();
		else if(tag=="type") type = i->value(); 
	}
	return Room(name,desc,status,type);
}

Container Map::parseContainer(xml_node<>* node)
{
	string tag;
	string name;
	string desc;
	string status;
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="name") name = i->value();
		else if(tag=="description") desc = i->value();
		else if(tag=="status") status = i->value();
	}
	return Container(name,desc,status);
}

void Map::loader(const string& filename)
{
	file<>Fdoc(filename.c_str());
	xml_document<> doc;
	doc.parse<0>(Fdoc.data());
	xml_node<> *node = doc.first_node("map");
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		string tagname(i->name());
		if(tagname=="creature"){
			Creature new_creature = parseCreature(i);
			add(new_creature.getname(),new_creature);
			addnode(new_creature.getname(),i);
		}
		if(tagname=="room"){
			Room new_room = parseRoom(i);
			add(new_room.getname(),new_room);
			addnode(new_room.getname(),i);
		}
		if(tagname=="item"){
			Item new_item = parseItem(i);
			add(new_item.getname(),new_item);
			addnode(new_item.getname(),i);
		}
		if(tagname=="container"){
			Container new_container = parseContainer(i);
			add(new_container.getname(),new_container);
			addnode(new_container.getname(),i);
		}
	}
	map_table::iterator obji;
	for(obji=obj.begin();obji!=obj.end();obji++){
		Object* Objre = &(obji->second);
		if(dynamic_cast<Creature*>(Objre)!=NULL){
			Creature& crea = dynamic_cast<Creature&>(*Objre);
			parseCreature2(getnode(obji->first),crea);
		}
		if(dynamic_cast<Container*>(Objre)!=NULL){
			Container& cont = dynamic_cast<Container&>(*Objre);
			parseContainer2(getnode(obji->first),cont);
		}
		if(dynamic_cast<Item*>(Objre)!=NULL){
			Item& item = dynamic_cast<Item&>(*Objre);
			parseItem2(getnode(obji->first),item);
		}
		if(dynamic_cast<Room*>(Objre)!=NULL){
			Room& room = dynamic_cast<Room&>(*Objre);
			parseRoom2(getnode(obji->first),room);
		}
	}
	Inventory = new Container("Inventory","","");
	CurRoomPtr = &((Room&)get("Entrance"));
}

void Map::parseItem2(xml_node<>* node, Item& item)
{
	string tag;
	
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="turnon"){
			string intag;
			string print;
			list<Action> acts;
			for(xml_node<> *inn = node->first_node(); inn; inn = inn->next_sibling()){
				intag = inn->name();
				if(intag=="print")print=inn->value();
				else if(intag=="action")acts.push_back(ActionParser(inn->value()));
			}
			item.addTurnon(print,acts.begin(),acts.end());
		}
		else if(tag=="trigger"){
			item.addTrigger(parseTrigger(i));
		}
	}
}

void Map::parseCreature2(xml_node<>* node,Creature& crea)
{
	string tag;
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="vulnerablity") crea.addVul(get(i->value()));
		else if(tag=="attack"){
			list<Condition> cond;
			list<Action> acts;
			string prt;
			string intag;
			for(xml_node<> *inn = node->first_node(); inn; inn = inn->next_sibling()){
				intag = inn->name();
				if(intag=="print")prt=inn->value();
				else if(intag=="action")acts.push_back(ActionParser(inn->value()));
				else if(intag=="condition")cond.push_back(parseCondition(inn));
			}
			crea.addAttack(prt,cond.begin(),cond.end(),acts.begin(),acts.end());
		}
		else if(tag=="trigger"){
			crea.addTrigger(parseTrigger(i));
		}
	}
}

void Map::parseRoom2(xml_node<>* node, Room& room)
{
	string tag;
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="item")room.Add((Item&)get(i->value()));
		else if(tag=="container")room.Add((Container&)get(i->value()));
		else if(tag=="creature")room.Add((Creature&)get(i->value()));
		else if(tag=="border"){
			string intag;
			int dir=0;
			string rm;
			for(xml_node<> *inn = node->first_node(); inn; inn = inn->next_sibling()){
				intag = inn->name();
				if(intag=="direction"){
					string dr = inn->value();
					if(dr=="north")dir=0;
					else if(dr=="east")dir=1;
					else if(dr=="south")dir=2;
					else if(dr=="west")dir=3;
				}
				else if(intag=="name")rm = inn->value();
			}
			room.addBorder(rm,dir);
		}
		else if(tag=="trigger"){
			room.addTrigger(parseTrigger(i));
		}
	}
}

void Map::parseContainer2(xml_node<>* node, Container& cont)
{
	string tag;
	for(xml_node<> *i = node->first_node(); i; i = i->next_sibling()){
		tag = i->name();
		if(tag=="accept") {
			cont.addAccept((Item&)get(i->value()));
		}
		else if(tag=="item") cont.Add(get(i->value()));
		else if(tag=="trigger") cont.addTrigger(parseTrigger(i));
	}
}

void Map::Run()
{
	string input;
	cin>>input;
	CommandParser(input);
}
