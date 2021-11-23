#include "Jail.h"

#include <iostream>
#include <fstream>

namespace JAIL {

    extern void registerChar(JAIL::JInterpreter*);
    extern void registerInteger(JAIL::JInterpreter*);
    extern void registerDouble(JAIL::JInterpreter*);
    extern void registerString(JAIL::JInterpreter*);
    extern void registerArray(JAIL::JInterpreter*);
    extern void registerObject(JAIL::JInterpreter*);
    extern void registerFunctions(JAIL::JInterpreter*);
    extern void registerMathFunctions(JAIL::JInterpreter*);
    
};

int main(int argc, char **argv) {

    JAIL::JInterpreter *interpreter = new JAIL::JInterpreter();
    
    registerChar(interpreter);
    registerInteger(interpreter);
    registerDouble(interpreter);
    registerString(interpreter);
    registerArray(interpreter);
    registerObject(interpreter);
    registerFunctions(interpreter);
    registerMathFunctions(interpreter);
    registerFunctions(interpreter);
    registerMathFunctions(interpreter);
    
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