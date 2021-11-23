#include <iostream>
#include <fstream>

#include "Jail.h"

namespace JAIL {

    extern void registerChar(JInterpreter* interpreter);
    extern void registerInteger(JInterpreter* interpreter);
    extern void registerDouble(JInterpreter* interpreter);
    extern void registerString(JInterpreter* interpreter);
    extern void registerArray(JInterpreter* interpreter);
    extern void registerObject(JInterpreter* interpreter);

};

void print(JAIL::JObject *c, void *data) {

    std::cout << c->getParameter("str")->getString();  

}

int main(int argc, char **argv) {                         
    
    JAIL::JInterpreter interpreter;
    
    interpreter.addNative("function print(str)", print, &interpreter);

    registerString(&interpreter);

    std::ifstream file(argv[1]);
    std::string code, line;
    while (std::getline(file, line))
        code += line;

    try {

        interpreter.execute(code);
        
    } catch (JAIL::Exception *e) { 
    
        printf("%s", (char *)e->text.c_str());
        return 0;
        
    } 
    
    return 1;  
                       
}   