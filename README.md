# Compiler-Tokenizer-Parser

• Read 8-bit ASCII strings from standard input and use the lexical specification to break the stream into tokens by C++.

• Utilize the token stream and the BNF specification to parse the input into a XML-like parse tree.


    <stmt>            ::= <while_stmt> <stmt>
                      | <for_stmt> <stmt>
                      | <if_stmt> <stmt>
                      | <assignment_stmt> ';' <stmt> | <output_stmt> <stmt>
                      | ε
                 
    <while_stmt>      ::= 'while' '(' <cond_expr> ')' '{' <stmt> '}'
    
    <for_stmt>        ::= 'for' '(' <opt_assign> ';' <opt_cond_expr>';' <opt_assign> ')' '{' <stmt> '}'
    
    <if_stmt>         ::= 'if' '(' <cond_expr> ')' '{' <stmt> '}' <opt_else>
    
    <opt_else>        ::= 'else' '{' <stmt> '}'
                      |ε
    
    <assignment_stmt> ::= ID ':=' <expr>
    
    <output_stmt>     ::= '[' <expr> ']' ';'
    
    <expr>            ::= <expr> '+' <mult_expr>
                      | <mult_expr>
                      
    <mult_expr>       ::= <mult_expr> '*' <unary_expr>
                      | <unary_expr> 
                      
    <unary_expr>      ::= '!' <expr>
                      | '+' <expr>
                      | '-' <expr>
                      | <paren_expr>
                      
    <paren_expr>      ::= '(' <expr> ')'
                      | <basic_expr>
                      
    <basic_expr>      ::= ID
                      |  STR
                      |  NUM
                      |  FLOAT
                     
    <cond_expr>       ::= <cond_expr> '|' <and_expr>
                      | <and_expr>
                      
    <and_expr>        ::= <and_expr> '&' <cmp_expr>
                      | <eq_expr>
    
    <eq_expr>         ::= <eq_expr> '=' <cmp_expr> 
                      | <eq_expr> '!=' <cmp_expr> 
                      | <cmp_expr>

    <cmp_expr>        ::= <cmp_expr> '<' <expr>
                      | <cmp_expr> '>' <expr> 
                      | <cmp_expr> '<=' <expr>
                      | <cmp_expr> '>=' <expr>
                      | <expr>
                      
    <opt_cond_expr>   ::= <cond_expr> 
                      | ε
                      
    <opt_assign>      ::= <assign_stmt>
                      |ε                 
