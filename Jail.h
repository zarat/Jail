#ifndef JAIL_H
#define JAIL_H

#include <string>
#include <vector>

#ifndef TRACE
  #define TRACE printf
#endif

namespace JAIL {

    const int JAIL_LOOP_MAX_ITERATIONS = 8192 * 1024;
    
    enum LEXER_TYPES {
        LEXER_EOF = 0,
        LEXER_ID = 256,
        LEXER_INT,
        LEXER_FLOAT,
        LEXER_STR,
        LEXER_CHAR,
        LEXER_EQUAL,
        LEXER_TYPEEQUAL,
        LEXER_NEQUAL,
        LEXER_NTYPEEQUAL,
        LEXER_LEQUAL,
        LEXER_LSHIFT,
        LEXER_LSHIFTEQUAL,
        LEXER_GEQUAL,
        LEXER_RSHIFT,
        LEXER_RSHIFTUNSIGNED,
        LEXER_RSHIFTEQUAL,
        LEXER_PLUSEQUAL,
        LEXER_MINUSEQUAL,
        LEXER_PLUSPLUS,
        LEXER_MINUSMINUS,
        LEXER_ANDEQUAL,
        LEXER_ANDAND,
        LEXER_OREQUAL,
        LEXER_OROR,
        LEXER_MULEQUAL,
        LEXER_DIVEQUAL,
        
        // reserved words
    #define LEXER_RESERVED_LIST_START LEXER_RESERVED_IF
        LEXER_RESERVED_IF,
        LEXER_RESERVED_ELSE,
        LEXER_RESERVED_DO,
        LEXER_RESERVED_WHILE,
        LEXER_RESERVED_FOR,
        LEXER_RESERVED_BREAK,
        LEXER_RESERVED_CONTINUE,
        LEXER_RESERVED_FUNCTION, 
        LEXER_RESERVED_RETURN,
        LEXER_RESERVED_VAR,
        LEXER_RESERVED_TRUE,
        LEXER_RESERVED_FALSE,
        LEXER_RESERVED_NULL,
        LEXER_RESERVED_UNDEFINED,
        LEXER_RESERVED_NEW,
    	LEXER_RESERVED_LIST_END 
    };
    
    enum VARIABLE_FLAGS {
        VARIABLE_UNDEFINED   = 0,
        VARIABLE_FUNCTION    = 1,
        VARIABLE_OBJECT      = 2,
        VARIABLE_ARRAY       = 4,
        VARIABLE_DOUBLE      = 8,  // floating point double
        VARIABLE_INTEGER     = 16, // integer number
        VARIABLE_STRING      = 32, // string
        VARIABLE_NULL        = 64, // it seems null is its own data type
        VARIABLE_NATIVE      = 128, // to specify this is a native function
        VARIABLE_CHAR        = 256,
        VARIABLE_NUMERICMASK = VARIABLE_NULL | VARIABLE_DOUBLE | VARIABLE_INTEGER,
        VARIABLE_TYPEMASK = VARIABLE_DOUBLE | VARIABLE_INTEGER | VARIABLE_STRING | VARIABLE_FUNCTION | VARIABLE_OBJECT | VARIABLE_ARRAY | VARIABLE_NULL | VARIABLE_CHAR,
    };
    
    #define JAIL_RETURN_VAR "return"
    #define JAIL_PROTOTYPE_CLASS "prototype"
    #define JAIL_TEMP_NAME ""
    #define JAIL_BLANK_DATA ""
    
    /// convert the given string into a quoted string suitable for javascript
    std::string getJSString(const std::string &str);
    
    class Exception {
        public:
            std::string text;
            Exception(const std::string &exceptionText);
    };
    
    class Lexer {
        public:
            Lexer(const std::string &input);
            Lexer(Lexer *owner, int startChar, int endChar);
            ~Lexer(void);
            char currCh, nextCh;
            int tk;
            int tokenStart; 
            int tokenEnd; 
            int tokenLastEnd;
            std::string tkStr; 
            void match(int expected_tk); 
            static std::string getTokenStr(int token); 
            void reset();
            std::string getSubString(int pos); 
            Lexer *getSubLex(int lastPosition);
            std::string getPosition(int pos = -1);
        protected:
            char *data;
            int dataStart, dataEnd; 
            bool dataOwned;
            int dataPos;
            void getNextCh();
            void getNextToken(); 
    };
    
    class Variable;
    typedef void (*JSCallback)(Variable *var, void *userdata);
    
    class VariableLink {
        public:
          std::string name;
          VariableLink *nextSibling;
          VariableLink *prevSibling;
          Variable *var;
          bool owned;
          VariableLink(Variable *var, const std::string &name = JAIL_TEMP_NAME);
          VariableLink(const VariableLink &link); 
          ~VariableLink();
          void replaceWith(Variable *newVar); 
          void replaceWith(VariableLink *newVar); 
          int getIntName() const; 
          void setIntName(int n); 
    };
    
    class Variable {
        public:
            Variable(); 
            Variable(const std::string &varData, int varFlags); 
            Variable(const std::string &str); 
            Variable(double varData);
            Variable(int val);
            Variable(const std::vector<unsigned char> &val);
            ~Variable(void);
            Variable *getReturnVar(); 
            void setReturnVar(Variable *var); 
            Variable *getParameter(const std::string &name); 
            VariableLink *findChild(const std::string &childName) const; 
            VariableLink *findChildOrCreate(const std::string &childName, int varFlags=VARIABLE_UNDEFINED);
            VariableLink *findChildOrCreateByPath(const std::string &path); 
            VariableLink *addChild(const std::string &childName, Variable *child=NULL);
            VariableLink *addChildNoDup(const std::string &childName, Variable *child=NULL); 
            void removeChild(Variable *child);
            void removeLink(VariableLink *link); 
            void removeAllChildren();
            Variable *getArrayIndex(int idx) const;
            void setArrayIndex(int idx, Variable *value); 
            int getArrayLength() const; 
            int getChildren() const; 
            const std::vector<unsigned char> getArray() const;
            int getInt() const;
            bool getBool() const { return getInt() != 0; }
            double getDouble() const;
            const std::string getString() const;
            std::string getParsableString() const; 
            void setInt(int num);
            void setDouble(double val);
            void setString(const std::string &str);
            void setUndefined();
            void setArray();
            void setArray(const std::vector<unsigned char> &val);
            bool equals(const Variable *v);
            bool isInt() const { return (flags&VARIABLE_INTEGER)!=0; }
            bool isDouble() const { return (flags&VARIABLE_DOUBLE)!=0; }
            bool isString() const { return (flags&VARIABLE_STRING)!=0; }
            bool isChar() const { return (flags&VARIABLE_CHAR)!=0; }
            bool isNumeric() const { return (flags&VARIABLE_NUMERICMASK)!=0; }
            bool isFunction() const { return (flags&VARIABLE_FUNCTION)!=0; }
            bool isObject() const { return (flags&VARIABLE_OBJECT)!=0; }
            bool isArray() const { return (flags&VARIABLE_ARRAY)!=0; }
            bool isNative() const { return (flags&VARIABLE_NATIVE)!=0; }
            bool isUndefined() const { return (flags & VARIABLE_TYPEMASK) == VARIABLE_UNDEFINED; }
            bool isNull() const { return (flags & VARIABLE_NULL)!=0; }
            bool isBasic() const { return firstChild==0; } 
            Variable *mathsOp(const Variable *b, int op); 
            void copyValue(const Variable *val);
            Variable *deepCopy() const; 
            void trace(const std::string &indentStr = "", const std::string &name = "") const; 
            std::string getFlagsAsString() const; 
            void getJSON(std::ostringstream &destination, const std::string &linePrefix="") const; 
            void setCallback(JSCallback callback, void *userdata);
            VariableLink *firstChild;
            VariableLink *lastChild;
            Variable *ref(); 
            void unref(); 
            int getRefs() const; 
        protected:
            int refs;
            std::string stringData; 
            long intData;
            double doubleData; 
            int flags;
            JSCallback jsCallback; 
            void *jsCallbackUserData; 
            void init();
            void copySimpleData(const Variable *val);
            friend class Interpreter;
    };
    
    class Interpreter {
        public:
            Interpreter();
            ~Interpreter();
            bool stepping;
            void reset();
            void Stepping(bool state);
            void execute(const std::string &code);
            VariableLink evaluateComplex(const std::string &code);
            std::string evaluate(const std::string &code);
            void addNative(const std::string &funcDesc, JSCallback ptr, void *userdata);
            void addNative(const std::string &returnType, const std::string &funcDesc, JSCallback ptr, void *userdata);
            Variable *getScriptVariable(const std::string &path) const;
            bool getVariable(const std::string &path, std::string &varData) const;
            bool setVariable(const std::string &path, const std::string &varData);
            void trace();
            Variable *root;   
        private:
            Lexer *l;             
            std::vector<Variable*> scopes; 
            #ifdef JAIL_CALL_STACK
            std::vector<std::string> call_stack; 
            #endif
            Variable *stringClass; 
            Variable *objectClass; 
            Variable *arrayClass;
            Variable *integerClass;
            VariableLink *functionCall(bool &execute, VariableLink *function, Variable *parent);
            VariableLink *factor(bool &execute);
            VariableLink *unary(bool &execute);
            VariableLink *term(bool &execute);
            VariableLink *expression(bool &execute);
            VariableLink *shift(bool &execute);
            VariableLink *condition(bool &execute);
            VariableLink *logic(bool &execute);
            VariableLink *ternary(bool &execute);
            VariableLink *base(bool &execute);
            void block(bool &execute);
            void statement(bool &execute);
            VariableLink *parseFunctionDefinition();
            void parseFunctionArguments(Variable *funcVar);
            VariableLink *findInScopes(const std::string &childName) const; ///< Finds a child, looking recursively up the scopes
            VariableLink *findInParentClasses(Variable *object, const std::string &name) const;
    };

}; 

#endif
