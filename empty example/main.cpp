#include "Jail.h"

#include <iostream>
#include <fstream>

void read(JAIL::JObject *o, void *data) {

    std::string response;
    std::getline(std::cin, response);
    o->getReturnVar()->setString(response);
    
}

void print(JAIL::JObject *o, void *data) {

    std::cout << o->getParameter("val")->getString();
    
}

int main(int argc, char **argv) {

    JAIL::JInterpreter *interpreter = new JAIL::JInterpreter();
    
    interpreter->addNative("function read()", read, 0);
    interpreter->addNative("function print(val)", print, 0);

    std::string code, line;
    std::ifstream f(argv[1]);
    while(std::getline(f, line)) 
      code += line;
    
    try {
    
        interpreter->execute(code);        
        
    } catch(JAIL::Exception *e) {
    
        std::cout << e->text;
        
    }
    
    return 1;

}