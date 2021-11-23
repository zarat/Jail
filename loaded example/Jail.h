#ifndef JAIL_H
#define JAIL_H

#include <string>
#include <vector>

#ifndef TRACE
  #define TRACE printf
#endif

namespace JAIL {

    // deprecated
    const int JAIL_LOOP_MAX_ITERATIONS = 8192 * 1024;
    
    enum LEXER_TYPES {    
        LEXER_EOF = 0,    
        LEXER_IDENTIFIER = 256,    
        LEXER_INTEGER,
        LEXER_DOUBLE,
        LEXER_STRING,
        LEXER_CHARACTER,
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
        LEXER_MULEQUAL,
        LEXER_DIVEQUAL,
        LEXER_PLUSPLUS,
        LEXER_MINUSMINUS,
        LEXER_AND,
        LEXER_OR,
        LEXER_XOR,
        LEXER_ANDAND,
        LEXER_OROR,
    //#define LEXER_RESERVED_LIST_START LEXER_RESERVED_IF
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
        LEXER_RESERVED_CLASS,                                
        LEXER_RESERVED_PRIVATE,
    	LEXER_RESERVED_LIST_END 
    };
    
    enum VARIABLE_FLAGS {
        VARIABLE_UNDEFINED   = 0,
        VARIABLE_FUNCTION    = 1,
        VARIABLE_OBJECT      = 2,
        VARIABLE_ARRAY       = 4,
        VARIABLE_DOUBLE      = 8,  
        VARIABLE_INTEGER     = 16, 
        VARIABLE_STRING      = 32, 
        VARIABLE_NULL        = 64, 
        VARIABLE_NATIVE      = 128, 
        VARIABLE_CHAR        = 256,
        VARIABLE_NUMERICMASK = VARIABLE_NULL | VARIABLE_DOUBLE | VARIABLE_INTEGER | VARIABLE_CHAR,
        VARIABLE_TYPEMASK = VARIABLE_DOUBLE | VARIABLE_INTEGER | VARIABLE_STRING | VARIABLE_FUNCTION | VARIABLE_OBJECT | VARIABLE_ARRAY | VARIABLE_CHAR | VARIABLE_NULL,
    };
    
    #define JAIL_RETURN_VAR "return"
    #define JAIL_PROTOTYPE_CLASS "prototype"
    #define JAIL_TEMP_NAME ""
    #define JAIL_BLANK_DATA ""
    
    std::string getJSString(const std::string &str);
    
    class Exception {
        public:
            std::string text;
            Exception(const std::string &exceptionText);
    };
    
    class JLexer {
        public:
            JLexer(const std::string &input);
            JLexer(JLexer *owner, int startChar, int endChar);
            ~JLexer(void);
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
            JLexer *getSubLex(int lastPosition);
            std::string getPosition(int pos=-1);
        protected:
            char *data;
            int dataStart, dataEnd; 
            bool dataOwned;
            int dataPos;
            void getNextCh();
            void getNextToken(); 
    };
    
    class JObject;
    typedef void (*Callback)(JObject *var, void *userdata);
    
    class JLink {
        public:
            std::string name;
            
            JLink *nextSibling;
            JLink *prevSibling;
            JObject *var;
            bool owned;
            JLink(JObject *var, const std::string &name = JAIL_TEMP_NAME);
            JLink(const JLink &link); 
            ~JLink();
            void replaceWith(JObject *newVar); 
            void replaceWith(JLink *newVar); 
            int getIntName() const; 
            void setIntName(int n);
    };
    
    class JObject {
        public:
            JObject(); 
            JObject(const std::string &varData, int varFlags); 
            JObject(const std::string &str); 
            JObject(double varData);
            JObject(int val);
            JObject(char val);
            JObject(const std::vector<unsigned char> &val);
            ~JObject(void);
            JObject *getReturnVar(); 
            void setReturnVar(JObject *var); 
            JObject *getParameter(const std::string &name); 
            JLink *findChild(const std::string &childName) const; 
            JLink *findChildOrCreate(const std::string &childName, int varFlags=VARIABLE_UNDEFINED);
            JLink *findChildOrCreateByPath(const std::string &path); 
            JLink *addChild(const std::string &childName, JObject *child=NULL);
            JLink *addChildNoDup(const std::string &childName, JObject *child=NULL); 
            void removeChild(JObject *child);
            void removeLink(JLink *link); 
            void removeAllChildren();
            JObject *getArrayIndex(int idx) const;
            void setArrayIndex(int idx, JObject *value); 
            int getArrayLength() const; 
            int getChildren() const; 
            const std::vector<unsigned char> getArray() const;
            char getChar() const;
            int getInt() const;
            bool getBool() const { return getInt() != 0; }
            double getDouble() const;
            const std::string getString() const;
            std::string getParsableString() const; 
            void setChar(char val);
            void setInt(int num);
            void setDouble(double val);
            void setString(std::string str);
            void setUndefined();
            void setArray();
            void setArray(const std::vector<unsigned char> &val);
            bool equals(const JObject *v);
            
            bool isInt() const;
            bool isDouble() const;
            bool isString() const;
            bool isChar() const;
            bool isNumeric() const;
            bool isFunction() const;
            bool isObject() const;
            bool isArray() const;
            bool isNative() const;
            bool isUndefined() const;
            bool isNull() const;
            bool isBasic() const;
            bool isAnything() const;    
            
            bool hidden; 
            JObject *mathsOp(const JObject *b, int op); 
            void copyValue(const JObject *val);
            JObject *deepCopy() const; 
            void trace(const std::string &indentStr = "", const std::string &name = "") const; 
            std::string getFlagsAsString() const; 
            void getJSON(std::ostringstream &destination, const std::string &linePrefix="") const; 
            void setCallback(Callback callback, void *userdata);
            JLink *firstChild;
            JLink *lastChild;
            JObject *ref(); 
            void unref(); 
            int getRefs() const; 

        protected:
            int refs;
            std::string stringData; 
            char charData;
            long intData;
            double doubleData; 
            int flags;
            Callback jsCallback; 
            void *jsCallbackUserData; 
            void init();
            void copySimpleData(const JObject *val);
            friend class JInterpreter;
    };
    
    class JInterpreter {
        public:
            JInterpreter();
            ~JInterpreter();   
            bool stepping;
            void reset();
            void Stepping(bool state);
            void execute(std::string code);
            JLink evaluateComplex(const std::string &code);
            std::string evaluate(const std::string &code);
            
            void addNative(std::string funcDesc, Callback ptr, void *userdata);
            void addNative(std::string returnType, std::string funcDesc, Callback ptr, void *userdata);
            
            JObject *getScriptVariable(const std::string &path) const;
            bool getVariable(const std::string &path, std::string &varData) const;
            bool setVariable(const std::string &path, const std::string &varData);
            void trace();
            JObject *root;   
        private:
            JLexer *l;             
            std::vector<JObject*> scopes; 
        #ifdef JAIL_CALL_STACK
            std::vector<std::string> call_stack; 
        #endif    
            JObject *charClass;
            JObject *intClass;
            JObject *doubleClass;
            JObject *stringClass; 
            JObject *objectClass; 
            JObject *arrayClass;    
            JLink *functionCall(bool &execute, JLink *function, JObject *parent);
            JLink *factor(bool &execute);
            JLink *unary(bool &execute);
            JLink *term(bool &execute);
            JLink *expression(bool &execute);
            JLink *shift(bool &execute);
            JLink *condition(bool &execute);
            JLink *logic(bool &execute);
            JLink *ternary(bool &execute);
            JLink *base(bool &execute);
            void block(bool &execute);
            void statement(bool &execute);    
            JLink *parseFunctionDefinition();
            void parseFunctionArguments(JObject *funcVar);    
            JLink *findInScopes(const std::string &childName) const; ///< Finds a child, looking recursively up the scopes    
            JLink *findInParentClasses(JObject *object, const std::string &name) const;
    };

};  

#endif
