#include "Zork_main.hpp"
#include <fstream>
#include <vector>
#include "rapidxml/rapidxml.hpp"

Game::Game(string filename) {
	try {
	    gameReady = loadXML(filename);
	} catch (int error) {
	    cout << "Error parsing the XML." << endl;
	}
}

Game::~Game() {

}

bool Game::loadXML(string filename) {
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream f;
	f.open(filename);
	if (f.fail()) {
	    perror("Error!:");
	    cout << "Opening file error, exit!!! " << endl;
	    return false;
	}
	vector<char> buffer((streambuf_iterator<char>(f)), istreambuf_iterator<char>());
	buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);
    
    // Find root node
    root_node = doc.first_node();
    
    
    queue<xml_node<> *> rooms_xml;
    queue<xml_node<> *> items_xml;
    queue<xml_node<> *> containers_xml;
    queue<xml_node<> *> creatures_xml;
    
    
    xml_node<> * node = root_node->first_node();

    
    //Split top level nodes into respective category
    seperatateTopXmlNodes(node, rooms_xml, items_xml, containers_xml, creatures_xml);


    string name;
    string status;
    string tagName;
    string tagValue;
    string writing;
    queue accept;
    
    
    
    
    //Add items to zork map
    Item * newItem;
    while ((items_xml.size()) != 0) {
        node = (items_xml.front())->first_node();
        
        string tagValue;
        string tagName;
        
        while (node != NULL) {
            
            //Get title and value of current node(tag)
            tagTitle = node->name();
            tagValue = node->value();
            
            if (tagName == "name") { name = (tagValue); }
            
            else if (tagName == "writing") { writing = (tagValue);  }
            
            else if (tagName == "status") { status = (tagValue); }
            
            else if (tagName == "turnon") { setUpTurnOn(node->first_node()); }
            
            
            node = node->next_sibling();
        }

        newItem = new Item(name, writing, status, enable); /// enable is not initialed
        items[newItem->name] = newItem;
        items_xml.pop();
    }
    
    //Add containers to zork map
  
    Container * newContainer;
    while ((containers_xml.size()) != 0){
        childOfCreature = (containers_xml.front())->first_node();
        while (childOfCreature != NULL) {
            
            tagName = childOfCreature->name();
            tagValue = childOfCreature->value();
            //cout << "tagname = " << tagName << ", tagvalue = " << tagValue << endl;
            
            if (tagName == "name") { name = tagValue; }
            else if (tagName == "status") { status = tagValue; }
            else if (tagName == "accept") { accept[tagValue] = tagValue; }                        // accept list
            else if (tagName == "trigger") { triggers.push_back(new Trigger(childOfCreature)); }  // 再次遍历
            else if (tagName == "attack") { dealWithAtackSetup(childOfCreature); }                // same as above
            childOfCreature = childOfCreature->next_sibling();
        }
        
        newContainer = new Container(name,'', status);   // turn on values not added
        containers[newContainer->name] = newContainer;
        containers_xml.pop();
    }
    
    //Add creatures to zork map
    Creature * newCreature;
    while ((creatures_xml.size()) != 0){
        
        
        while (childOfCreature != NULL) {
            tagName = childOfCreature->name();
            tagValue = childOfCreature->value();
            //cout << "tagname = " << tagName << ", tagvalue = " << tagValue << endl;
            
            if (tagName == "name") { name = tagValue; }
            else if (tagName == "status") { status = tagValue; }
            else if (tagName == "description") { description = tagValue; }
            else if (tagName == "trigger") { triggers.push_back(new Trigger(childOfCreature)); }
            else if (tagName == "attack") { dealWithAtackSetup(childOfCreature); }
            
        
        
            childOfCreature = childOfCreature->next_sibling();
        }
        creatures[newCreature->name] = newCreature;
        newCreature = new Creature(name, description, status);
        creatures_xml.pop();
    }
    
    //Add rooms to zork map
    Room * newRoom;
    while ((rooms_xml.size()) != 0) {
        
        while (roomChildNode != NULL) {
            tagName = roomChildNode->name();
            tagValue = roomChildNode->value();
            
            if (tagName == "name") { name = tagValue; }
            else if (tagName == "description") { description = tagValue; }
            else if (tagName == "item") { items[tagValue] = tagValue; }
            else if (tagName == "trigger") { triggers.push_back(new Trigger(roomChildNode)); }
            else if (tagName == "border") { setUpBorder(roomChildNode); }
            else if (tagName == "creature") { creatures[tagValue] = tagValue; }
            else if (tagName == "container") { containers[tagValue] = tagValue; }
            else if (tagName == "type") { type = tagValue; }
            
            roomChildNode = roomChildNode->next_sibling();
        }
        newRoom = new Room(name, description, status, type);
        rooms[newRoom->name] = newRoom;
        rooms_xml.pop();
    }
    
    return true;
	
}



void Game::setUpTurnOn(rapidxml::xml_node<> * turnonChild) {
    
    
    // return values for turnon
    vector<string> turnonMessages;
    vector<string> turnonActions;
    
    string tagTitle;
    string tagValue;
    
    while (turnonChild != NULL) {
        tagTitle = turnonChild->name();
        tagValue = turnonChild->value();
        
        if (tagTitle == "print") { this->turnonMessages.push_back(tagValue); }
        
        if (tagTitle == "action") { this->turnonActions.push_back(tagValue); }
        
        //get next tag node
        turnonChild = turnonChild->next_sibling();
    }
}


void Game::startGame() {
	//Always start at entrance
	currentRoom = "Entrance";

}
    
    
    
    
void Game::seperatateTopXmlNodes(xml_node<> * node, queue<xml_node<> *>& rooms_xml, queue<xml_node<> *>& items_xml, queue<xml_node<> *>& containers_xml, queue<xml_node<> *>& creatures_xml) {
        while (node != NULL) {
            
            //Current node is a room
            if (string((node->name())) == string("room")) {
                //roomC++;
                rooms_xml.push(node);
            }
            else if (string((node->name())) == string("item")) {
                //itemC++;
                items_xml.push(node);
            }
            else if (string((node->name())) == string("container")) {
                //containerC++;
                containers_xml.push(node);
            }
            else if (string((node->name())) == string("creature")) {
                //creatureC++;
                creatures_xml.push(node);
            }
            
            
            node = node->next_sibling();
            
        }
        
    }


