#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string.h>

// terminals
#define EMPTY "EMPTY"
#define SEMI "SEMI" 
#define COMMA "COMMA" 
#define STMT_LIST "STMT_LIST"
#define LPAREN "LPAREN" 
#define RPAREN "RPAREN" 
#define LBRACKET "LBRACKET"
#define RBRACKET "RBRACKET" 
#define LBRACE "LBRACE" 
#define RBRACE "RBRACE" 

#define ASSIGN "ASSIGN" 
#define INC "INC"
#define DEC "DEC"
#define PLUS "ADD"
#define MINUS "SUB"
#define MUL "MUL"
#define DIV "DIV"
#define MOD "MOD"
#define EQ "EQ"
#define NEQ "NEQ"
#define LT "LT"
#define GT "GT"
#define LEQ "LEQ"
#define GEQ "GEQ"
#define POW "POW"
#define AND "AND"
#define OR "OR"

// non terminals
#define IDENTIFIER "IDENTIFIER"
#define VARIABLE "VARIABLE"
#define INTEGER "INTEGER"

std::set<std::string> KEYWORDS;

using namespace std;

class Token {

    private:
    
    	std::string type;
    	std::string value; 
              
    public:
    
    	Token() {
    		type = "";
    		value = "";
    	} 
           
    	Token(std::string _type, std::string _value) {
    		type = _type;
    		value = _value;
    	}  
           
        ~Token(){};	
        
    	std::string _value() { 
            return value; 
        }
        
    	std::string _type() { 
            return type; 
        } 
           
        std::string str() { 
            return ("Token("+type+","+value+")"); 
        }  
          
};

class ASTNode {
    
    public:        
        std::vector<ASTNode*> child;                    
    	Token token;                
        
        ASTNode() {};                        
    	
        ASTNode(Token _token) {
    		token = _token;
    	}         
        
        ~ASTNode() {}; 
    	
        void make_child(ASTNode _node) {
    		ASTNode *temp = new ASTNode(_node._token());
    		temp->child = _node.child;
    		child.push_back(temp);
    	}            
    	
        Token _token() {
    		return token;
    	}        
        
        std::string escape(const std::string& str) {
            std::string result;
            for(auto c : str) {
                switch(c) {
                    case '\n': result += "\\n"; break;
                    case '\t': result += "\\t"; break;
                    default: result += c;
                }
            }
            return result;
        }
                
    	void show(int level) {                
            
            if(level<2 && level != 0) 
                std::cout << std::string(level*2, ' ') << "Token('" << token._type() << "', '" << escape(token._value()) << "')\n";

            else 
                std::cout << std::string(level*2, ' ') << "Token('" << token._type() << "', '" << escape(token._value()) << "')\n";   

            for(auto it = child.begin(); it != child.end(); it++) 
                (*it)->show(level+1);
    	
        } 
               
};

class Lexer {

    private:    

        std::string text;
        char current_char;
        int pos;            

    public:    

        Lexer() {
            text = "";
            pos = 0;
            current_char = EOF;
        }
                    
        Lexer(std::string _text) {
            text = _text;
            pos = 0;
            current_char = text[pos];
        } 
               
        ~Lexer() {};
        
        void error() {
            std::cout << "lexer: unknown '" << text[pos] << "' at position " << pos << "\n";
            std::exit(0);
        }
        
        void skip_whitespaces();        
        void skip_comments();        
        void skip_inlinecomments();
        void skip_directives();        
        void advance_pos();
        void reduce_pos();             
        char peek(); 
        char peek(int n);    
        Token getNextToken();
        Token identifier();    
        std::string number();
        std::string string();   

};

void Lexer::skip_whitespaces() {
    while(text[pos] == ' ' or text[pos] == '\t' or text[pos] == '\n') 
		advance_pos();
}

void Lexer::skip_directives() {
	advance_pos();
	while( !(current_char == '#' )) advance_pos();
    advance_pos();
}

void Lexer::skip_comments() {
	advance_pos(); 
	advance_pos();
	while( !(current_char == '*' && peek() == '/') ) 
		advance_pos();
	advance_pos(); advance_pos();
}

void Lexer::skip_inlinecomments() {
	advance_pos(); 
    advance_pos();
	while( current_char != '/' && peek() != '/' ) { 
        advance_pos();
    }
	advance_pos();
}

void Lexer::advance_pos() {
    pos++;
    if(pos >= text.length()) 
		current_char = EOF;
    else 
		current_char = text[pos];
}

void Lexer::reduce_pos() {
    pos--;
    if(pos <= 0) 
		current_char = EOF;
    else 
		current_char = text[pos];
}

std::string Lexer::number() {
    std::string str;    
    
    while(current_char >= 48 && current_char <= 57) { 
            str.push_back(current_char); advance_pos(); 
    } 
    
    return str;
}

Token Lexer::identifier() {   
    
    std::string result;
    Token token;        
    int i = 0;                                             /*               A                    Z                       a                    z */
    
    while( (current_char >= 48 && current_char <= 57) || (current_char >= 65 && current_char <=90) || (current_char >= 97 && current_char <=122) ) {        
        result.push_back(current_char); advance_pos(); i++;
    }
         
    token = Token(VARIABLE, result); // a variable         

    return token; 
       
}

char Lexer::peek() {
    
    if(pos+1 >= text.length()) 
        return EOF;        
    else 
        return text[pos+1]; 
               
}

char Lexer::peek(int n) {

    if(pos + n >= text.length()) 
        return EOF;       
    else 
        return text[pos+n];  
              
}

Token Lexer::getNextToken() {

    std::string temp_str;
	skip_whitespaces();
        
	while(current_char == '#') {
		skip_directives();
	}

	while(current_char == '/' && peek() == '*') {
		skip_comments();
	}
         
    if( (current_char >= 65 && current_char <=90) || (current_char >= 97 && current_char <=122) ) {
        return identifier(); 
    }  
     
    else if(current_char >= 48 && current_char <= 57) {
        temp_str = number(); 
        return Token(INTEGER, temp_str);
    }
    
    if(current_char == '[') { 
        advance_pos();
        return Token(LBRACE, "[");
    }
    
    if(current_char == ']') { 
        advance_pos();
        return Token(RBRACE, "]");
    }
    
    if(current_char == '^') { 
        advance_pos();
        return Token(POW, POW);
    }
    
    if(current_char == '+') {
        temp_str.push_back(current_char);
        advance_pos();
        return Token(PLUS, temp_str);
    }
    
    if(current_char == '-') {
        temp_str.push_back(current_char);
        advance_pos();
        return Token(MINUS, temp_str);
    }
    
    if(current_char == '*') {
        temp_str.push_back(current_char);
        advance_pos();
        return Token(MUL, temp_str);
    }
    
    if(current_char == '/') {
        temp_str.push_back(current_char);
        advance_pos();
        return Token(DIV, temp_str);
    }
    
    if(current_char == '%') {
        temp_str.push_back(current_char);
        advance_pos();
        return Token(MOD, temp_str);
    }
    
    if(current_char == '&' && peek() == '&') {
        temp_str.push_back(current_char);
        advance_pos(); 
        temp_str.push_back(current_char);
        advance_pos();
        return Token(AND, temp_str);
    }
    
    if(current_char == '|' && peek() == '|') {
        temp_str.push_back(current_char);
        advance_pos(); 
        temp_str.push_back(current_char);
        advance_pos();
        return Token(OR, temp_str);
    }
    
    if(current_char == '(') {
        temp_str.push_back(current_char);
        advance_pos();
        return Token(LPAREN, temp_str);
    }
    
    if(current_char == ')') {
        temp_str.push_back(current_char);
        advance_pos();
        return Token(RPAREN, temp_str);
    }
    
    if(current_char == EOF) {
        temp_str.push_back(current_char);
        return Token("EOF", temp_str);
    }
    
    if(current_char == '=' && peek() == '=') {
        advance_pos();
        advance_pos();
        return Token(EQ, "==");
    }
    
    if(current_char == '!' && peek() == '=') {
        advance_pos();
        advance_pos();
        return Token(NEQ, "!=");
    }  
          
    if(current_char == '<' && peek() == '=') {
        advance_pos();
        advance_pos();
        return Token(LEQ, "<=");
    }  
      
    if(current_char == '>' && peek() == '=') {
        advance_pos();
        advance_pos();
        return Token(GEQ, ">=");
    }
    
    if(current_char == '<') {
        advance_pos();
        return Token(LT, "<");
    }
    
    if(current_char == '>') {
        advance_pos();
        return Token(GT, ">");
    }
    
    if(current_char == '=' && peek() != '=') {
        Token token(ASSIGN, "=");
        advance_pos();
        return token;
    }
    
    if(current_char == ';') {
        advance_pos();
        return Token(SEMI, ";");
    }
    
    if(current_char == ',') {
        advance_pos();
        return Token(COMMA, ",");
    }
    
    if(current_char == '{') {
        advance_pos();
        return Token(LBRACKET, "{");
    }
    
    if(current_char == '}') {
        advance_pos();
        return Token(RBRACKET, "}");
    }
        
    error();
        
}

class Parser {

    private:

        Lexer lexer;
        Token current_token;   

    public:

        Parser(){};       
        Parser(Lexer _lexer) {
            lexer = _lexer;
            current_token = lexer.getNextToken();
        }     
        ~Parser(){};                    
        void error(std::string str) {
            std::cout<<"parser: "<< str <<"\n";
            std::exit(0);
        }    
        ASTNode parse() {
            ASTNode node = statement_list();
            return node;
        }     
        int consumed = 0; // Todo
        void consume(std::string token_type);

		ASTNode statement_list();
		ASTNode statement();
		ASTNode declare_statement();
		ASTNode assignment_statement();
		ASTNode variable();
        ASTNode factor();      
        ASTNode term();  
        ASTNode expression();     
        ASTNode condition();  

};

void Parser::consume(std::string token_type) {
    if(current_token._type() == token_type) current_token = lexer.getNextToken();
    else error("[parser::consume] unexpected '" + current_token._value() + "', expected '" + token_type + "'\n");
    consumed++;
}

ASTNode Parser::statement_list() {

	ASTNode node(Token(STMT_LIST, "STMT_LIST"));

	while (current_token._type() != "EOF" and current_token._type() != RBRACKET) {

		node.make_child(statement());

	}

	return node;

}

ASTNode Parser::statement() {

	ASTNode node;

	if (current_token._type() == VARIABLE) {
		node = assignment_statement(); 
	}

	else
		error("[parser::statement] unknown Token '" + current_token._type() + "'");
	
	return node;

}

ASTNode Parser::assignment_statement() {

	ASTNode left = variable();
	consume(ASSIGN);
	ASTNode right;
	right = expression();
	ASTNode node(Token(ASSIGN, "="));
	node.make_child(left);
	node.make_child(right);
	if(current_token._type() == SEMI)
		consume(SEMI);
	return node;
    
}

ASTNode Parser::variable() {

	ASTNode node(current_token);
	consume(VARIABLE);
	return node;
    
}

ASTNode Parser::factor() {
    
	if(current_token._type() == PLUS) {
        ASTNode node(current_token);
        consume(PLUS);
        node.make_child(factor());
        return node;
    } 
	
	else if(current_token._type() == MINUS) {
        ASTNode node(current_token);
        consume(MINUS);
        node.make_child(factor());
        return node;
    } 
	
	else if(current_token._type() == INC) {
        ASTNode node(current_token);
        consume(INC);
        node.make_child(factor());
        return node;
    } 
	
	else if(current_token._type() == DEC) {
        ASTNode node(current_token);
        consume(DEC);
        node.make_child(factor());
        return node;
    } 
	
	else if(current_token._type() == LPAREN) {
        consume(LPAREN);
        ASTNode node = expression();
        consume(RPAREN);
        return node;
    } 
	
	else if(current_token._type() == INTEGER) {
        ASTNode node(current_token);
        consume(INTEGER);
        return node;
    } 
    
	else if (current_token._type() == VARIABLE) {
		ASTNode node(variable());
		return node;
	}

    else 
		error("[parser::factor] unknown Token '" + current_token._type() + "'\n");

}

ASTNode Parser::term() {

    ASTNode node = factor();

    while(true) {      

        ASTNode temp;

        if(current_token._type() == MUL) {
            consume(MUL);
            temp = ASTNode(Token(MUL, "*"));
        } 
		
		else if(current_token._type() == DIV) {
            consume(DIV);
            temp = ASTNode(Token(DIV, "/"));
        } 
		
		else if(current_token._type() == MOD) {
            consume(MOD);
            temp = ASTNode(Token(MOD, "%"));
        } 
		
		else if(current_token._type() == POW) {
            consume(POW);
            temp = ASTNode(Token(POW, "^"));
        } 

        else 
			break;

        temp.make_child(node);
        temp.make_child(factor());
        node = temp;

    }

    return node;

}
  
ASTNode Parser::expression() {

    ASTNode node = term(); 

    while(true) {

        ASTNode temp;
        
		if(current_token._type() == PLUS) {
            consume(PLUS);
            temp = ASTNode(Token(PLUS, "+"));
        } 
		
		else if(current_token._type() == MINUS) {
            consume(MINUS);
            temp = ASTNode(Token(MINUS, "-"));
        } 
		
		else 
			break; 

        temp.make_child(node);
        temp.make_child(term());
        node = temp;

    }

    return node;

}

ASTNode Parser::condition() {

    ASTNode node;

    ASTNode left = expression(); 

    if(current_token._type() == EQ) {
        node = Token(EQ, EQ);
        consume(EQ);
    } 
	
	else if(current_token._type() == NEQ) {
        node = Token(NEQ, NEQ);
        consume(NEQ);
    } 
	
	else if(current_token._type() == LT) {
        node = Token(LT, LT);
        consume(LT);
    } 
	
	else if(current_token._type() == GT) {
        node = Token(GT, GT);
        consume(GT);
    } 
	
	else if(current_token._type() == LEQ) {
        node = Token(LEQ, LEQ);
        consume(LEQ);
    } 
	
	else if(current_token._type() == GEQ) {
        node = Token(GEQ, GEQ);
        consume(GEQ);
    } 
	
	else if(current_token._type() == AND) {
        node = Token(AND, AND);
        consume(AND);
    } 
	
	else if(current_token._type() == OR) {
        node = Token(OR, OR);
        consume(OR);
    }  

    else 
		error("[parser::condition] unknown Token '" + current_token._type() + "'");

    node.make_child(left); 
    node.make_child(expression()); 

    return node;

}

class Interpreter {

	private:

		Parser parser;  

	public:
    
		Interpreter(Parser _parser) {
			parser = _parser;
		} 
    
		~Interpreter() {};

		Token interpret() {
			
            ASTNode tree = parser.parse();
			return visit(tree);
            
		}
        
        Token visit(ASTNode node) {
        
			if(node._token()._type() == EMPTY) {

				return Token(INTEGER, "0");

			}
            
            else if(node._token()._type() == STMT_LIST) { // executed immediately

				for(auto it = node.child.begin(); it != node.child.end(); it++) {

					Token token = visit(**it);
				
				} 

				return (Token(INTEGER, "0"));

			}
            
            else if(node._token()._type() == INTEGER) {

				return node._token();

			}
               
		}

};

int main(int argc, char **argv) {

    FILE *f;
    f = fopen(argv[1], "r");
    fseek(f, 0L, SEEK_END); 
    int len = ftell(f); 
    rewind(f);
    char c, buffer[len];    
    int i = 0;
    while( fread(&c, sizeof(char), 1, f) > 0 ) buffer[i++] = c;
    fclose(f);
    buffer[i] = '\0';
    
    Lexer lexer(buffer);
    
    Parser parser(lexer);
    Parser _parser(lexer);
    
    Interpreter interpreter(parser);
    
    ASTNode program = _parser.parse();    
    program.show(0);
    
    //Token result = interpreter.interpret();    
    //printf("result: %s", result._value().c_str());
    
    return 0;

}
