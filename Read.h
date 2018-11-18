#ifndef READ
#define READ

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

typedef vector<string> vString;

class Read {
private:
    ifstream input;
    string line;
    vector<string> binaryLine;
    //int counter = 0;

public:
    Read() : binaryLine(10) {}
    void readFromFile();
    vector<string> getBinaryLine();
};

//Read::Read() {
//    //binaryLine = new vector<string>(32);
//}
void Read::readFromFile() {
    input.open("ManBinary.txt");

    if(input.is_open()) {
        int i = 0;
        while (getline(input, line)) {
            binaryLine[i] = line;
            i++;
            if(i == 10) break;
        }
        input.close();
    }
    else {
        cout << "Unable to open the file" << endl;
    }
}

vector<string> Read::getBinaryLine() {
    return binaryLine;
}
#endif // READ
