##### Computes any expression with operations such as addition, subtraction, multiplication, division
### Allowed characters:
    ' ' '.' '+' '-' '/' '*' '(' ')' '0' '1' '2' '3' '4' '5' '6' '7' '8' '9'
### Use example
```sh
std::string str = "(1+23*51+(((913--13/4+8)*4*16))+-7*-11)";
Result res = Calculator().getResult(str);
if (res.ok)
	std::cout << "result: " << res.value << "\n"; // (double) result number
else
	std::cout << "error: " << res.error << "\n"; // (string) error message
```
### Expression grammar
    Expression:
        Term
        Expression "+" Term // addition
        Expression "–" Term // subtraction
    Term:
        Primary
        Term "*" Primary    // multiplication
        Term "/" Primary    // division
    Primary:
        Number
        "(" Expression ")"  // grouping
    Number:
        floating-point-literal
### Other examples:
```sh
"-1-2" // -3
"2 - -3" // 5
"-2" // -2
"(1+23)" // 24
"(1+2*5+(((91-( -13 / -1 + (23.1*1)-(9/2))+-8+23)*4*16))+7*-11)" // 4695.6
"1.2-2" // -0.8
"(1+23*51+(((913--13/4+8)*4*16))+7*11)" // 60403
"0" // 0
"-12 + 2" // -10
"(123/32)" // 3.84375
"123 - (21 - 12" // "')' expected"
") 123 + 2" // "incorrect input expression"
"-----++++" // "multiple sign"
"123//2" // "incorrect input expression"
" 90 = 9" // "incorrect input expression"
" 90 9" // "incorrect input expression"
"(123123)" // 123123
"()" // "incorrect input expression"
"-2222 + 8888 - (232 *    2)" // 6202
"*" // "incorrect input expression"
"2 * 6 *" // "incorrect input expression"
"3 / (23 - 10 - 13)" // "division by zero"
"3 / (2)" // 1.5
"23.123.32" // "incorrect number format"
"." // "incorrect number format"
".4" // 0.4
"4." // 4
".4" // 0.4
"" // "incorrect input expression"
"12 + 3" // 15
"1 ~ +3" // "incorrect input expression"
"-1-1-" // "incorrect input expression"
"-33-0-0-0" // -33
"-33" // -33
"+33-+-23" // "multiple sign"
"+2" // 2
"-(" // "incorrect input expression"
"+33-0-0" // 33
"-+33" // "multiple sign"
"+-4" // "multiple sign"
"23 - + 34" // -11
"4 + - 34" // -30
"- 2 + 4" // 2
"--2 + 4" // "multiple sign"
" 2 - - 5" // 7
"5 + + 7" // 12
"5++7" // 12
"+5++7" // 12
"-34.+-2" // -36
```