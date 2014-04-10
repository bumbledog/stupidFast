using namespace std;
#include <string>;
#include <algorithm>;
#include "XMLParser.h";


XMLParser::XMLParser(string input)
:_XML(input),_level(0), exclude(false){
}

XMLParser::~XMLParser(){
}

void XMLParser::parseXML(){
	//iterates through the XML
	for(int iter = 0; iter < _XML.length(); iter++){
		if(_XML[iter] == '<'){
			//determines if Element or End Element
			if(_XML[iter+1] == '/'){
				//printEndElement(iter+2);
			}
			else{
				printElement(iter+1);
			}
		}
		//checks for content after an element node
		if(_XML[iter] == '>' && _level != 0){
			int contentCheck = iter +1 ;
			//finds anything that isn't white space between elements
			while(contentCheck < _XML.length() && _XML[contentCheck] ==  ' '){
				contentCheck++;
			}
			if (contentCheck < _XML.length() && _XML[contentCheck] != '<'){
				if (!exclude){
					printContent(contentCheck);
				}
			}
		}
	}
}

void XMLParser::clearXML(){
	_XML = "";
}

void XMLParser::printElement(int place){
	int iter = place;
	//checks for the element name
	while(_XML[iter] != ' ' && _XML[iter] != '>'){
		iter++;
	}
	string name = _XML.substr(place, iter - place);

	exclude = (name == "DOCNO")? true: false;
	
	//searches for attributes
	for(iter; _XML[iter] != '>'; iter++){
		//attributes come after spaces, so it searches for spaces
		if(_XML[iter] == 39){
			iter++;
			//skips any area within the quotes
			while(!(_XML[iter] == 39 && (_XML[iter+1] == ' ' || _XML[iter+1] == '>'))){
				iter++;
			}
		}
		if(_XML[iter] == ' '){
			printAttribute(iter+1);
		}
	} 

	//lets the Parser know we are inside an element
	_level++;
}

void XMLParser::printEndElement(int place){
	//end element so we remove a level
	_level--;

	int iter = place;
	//checks for the element name
	while(_XML[iter] != '>'){
		iter++;
	}
	string name = _XML.substr(place, iter - place);
}

void XMLParser::printAttribute(int place){
	int iter = place;
	while(_XML[iter] != ' ' && _XML[iter] != '>'){
		//the char 39 is '
		if(_XML[iter] == 39){
			iter++;
			while(!(_XML[iter] == 39 && (_XML[iter+1] == ' ' || _XML[iter+1] == '>'))){
				iter++;
			}
		}
		iter++;
	}
	string attribute = _XML.substr(place, iter - place);

	int deliminator = attribute.find("=");
	//splits the attribute into parts
	string attributeName = attribute.substr(0, deliminator);
	string attributeContent = attribute.substr(deliminator + 2, (attribute.length() - 1) - (deliminator + 2));

}

void XMLParser::printContent(int place){
	//finds the content start and end
	int iter = place;
	while (_XML[iter] != '<' && iter < _XML.length()){
		iter++;
	}
	//puts the content into a new string
	string content = _XML.substr(place, iter - place);
	//prints the content out
	for (int iter = content.length() - 1; iter >= 0; iter--){
		if (content[iter] <97 || content[iter]> 122)
			content[iter] = ' ';
	}
	_output += content + "\n";
}

string XMLParser::printOutput(){
	return _output;
}

void XMLParser::nextLine(string input){
	if (input != "."){
		_XML += " " + input;
	}
}
