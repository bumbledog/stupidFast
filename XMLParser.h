using namespace std;
#include <string>;

class XMLParser{
public:
	XMLParser(string input);
	~XMLParser();
	void parseXML();
	string printOutput();
	void nextLine(string input);
	void clearXML();

private:
	string _XML;
	int _level;
	string _output;
	bool exclude;
	void printElement(int place);
	void printEndElement(int place);
	void printAttribute(int place);
	void printContent(int place);
};
