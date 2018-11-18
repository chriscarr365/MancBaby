#ifndef SIMULATOR
#define SIMULATOR

#include <string>
#include <vector>
#include <sstream>
#include "Read.h"


using namespace std;



class Simulator{
private:
  bool isStop = false;
  int accumulator = 0; //holds for maths stuff
  int programCounter = 0; //line counter
  string operationCode = ""; // full bin code from text file
  string presentIntruction = "000"; // instructionn word
  int controlInstruction = 0; //Memory adress ni decimal form
  vector<string> binaryLine; // gets from read.h  -> ManBinary.txt
  vector<string> mainMemory; //

public:
  Simulator() : mainMemory(32) {
    Read read;
    read.readFromFile();
    binaryLine = read.getBinaryLine();
} //Constructor


  void incrementProgramCounter(); //curr line
  void fetchOperationCode(); //Full bin code
  void fetchPresentInstruction(); // instruction
  void storeControlInstruction(); // Memory adress for instruction
  int returnMemoryAddress(); // temp memoryHold
  bool getStop();
  void execute(); //
  void displayEverything();

  void JMP();
  void JRP();
  void LDN();
  void STO();
  void SUB();
  void CMP();
  void STP();

};

//Simulator::Simulator(){
//  Read read;
//  read.readFromFile();
//  binaryLine = read.getBinaryLine();
//}

bool Simulator::getStop(){
  return isStop;
}


void Simulator::incrementProgramCounter(){
  programCounter++;
}

void Simulator::fetchOperationCode(){
  incrementProgramCounter();
  operationCode = binaryLine.at(programCounter);
//  incrementProgramCounter();
}

int Simulator::returnMemoryAddress(){
  return stoi(operationCode.substr(0,5), nullptr ,2);
}


void Simulator::fetchPresentInstruction(){
  presentIntruction = operationCode.substr(13,3);
}

void Simulator::execute(){
fetchPresentInstruction();
  if (presentIntruction == "000") {
    JMP();
  }
  if(presentIntruction == "001") {
    SUB();
  }
  if (presentIntruction =="010") {
    LDN();
  }
  if (presentIntruction == "011") {
    CMP();
  }
  if (presentIntruction == "100") {
    JRP();
  }
  if (presentIntruction == "101") {
    SUB();
  }
  if (presentIntruction == "110"){
    STO();
  }
  if (presentIntruction == "111") {
    STP();
  }

}

void Simulator::displayEverything(){
  cout << "Program Counter : " << programCounter << endl;
  cout << "Control Instruction : " << controlInstruction << endl;
  cout << "Opertion Code : " << operationCode << endl;
  cout << "Accumulator : " << accumulator << endl;
  cout << "Present Intruction : " << presentIntruction << endl;

  for (size_t i = 0; i < mainMemory.size(); i++) {
    if(mainMemory.at(i) != ""){
        cout << "Memory Location: " << i << "\tMemory Content: " << mainMemory.at(i) << endl;
    }
  }
}







//ALL THE INSTRUCTIONS BELOW! BABY!
void Simulator::JMP(){

  controlInstruction =  returnMemoryAddress();
}

void Simulator::JRP(){

  controlInstruction = controlInstruction + returnMemoryAddress();
}

void Simulator::LDN(){

  accumulator = returnMemoryAddress() * -1;
}

void Simulator::STO(){
  mainMemory[returnMemoryAddress()] = to_string(accumulator);
}

void Simulator::SUB(){
  stringstream ss;
  int result = 0;
  ss << mainMemory.at(returnMemoryAddress());
  ss >> result;
  accumulator = accumulator - result;
}

void Simulator::CMP(){
  if (accumulator < 0) {
    controlInstruction += 1;
  }
}

void Simulator::STP(){
  isStop = true;
}

#endif
