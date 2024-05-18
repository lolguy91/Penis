# Zig+QBE+Keystone rewrite coming soon™
# Penis

the penis lang

grammar:

```
program           : statement_list

statement_list    : statement
                  | statement_list statement

statement         : declaration_statement
                  | assignment_statement
                  | if_statement
                  | while_statement
                  | for_statement
                  | return_statement
                  | break_statement
                  | continue_statement
                  | expression_statement
                  | function_declaration
                  | call_statement

declaration_statement : type identifier '=' expression ';'

assignment_statement  : identifier '=' expression ';'

if_statement       : 'if' '(' expression ')' block ('else' block)?

while_statement    : 'while' '(' expression ')' block

for_statement      : 'for' '(' declaration_statement ';' expression ';' expression ')' block

return_statement   : 'return' expression ';'

break_statement    : 'break' ';'

continue_statement : 'continue' ';'

expression_statement : expression ';'

block              : '{' statement_list '}'

expression         : additive_expression

additive_expression : multiplicative_expression
                    | additive_expression '+' multiplicative_expression
                    | additive_expression '-' multiplicative_expression

multiplicative_expression : unary_expression
                          | multiplicative_expression '*' unary_expression
                          | multiplicative_expression '/' unary_expression
                          | multiplicative_expression '%' unary_expression

unary_expression  : primary_expression
                  | '-' primary_expression
                  | '!' primary_expression

primary_expression : identifier
                    | constant
                    | '(' expression ')'
                    | function_call

identifier         : IDENTIFIER

constant           : INTEGER_CONSTANT
                   | FLOAT_CONSTANT
                   | BOOLEAN_CONSTANT

type               : 'u8'
                   | 'u16'
                   | 'u32'
                   | 'i8'
                   | 'i16'
                   | 'i32'
                   | 'bool'
                   | 'float'

function_declaration : type IDENTIFIER '(' parameter_list? ')' block

parameter_list     : parameter
                   | parameter_list ',' parameter

parameter          : type IDENTIFIER

function_call      : IDENTIFIER '(' argument_list? ')'

argument_list      : expression
                   | argument_list ',' expression
```
