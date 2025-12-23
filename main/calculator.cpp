#include <iostream>
#include <string>
#include "..\lib_TVector\TVector.h"
//#include "..\lib_parser\Parser.h"
#include "..\lib_expression\Expression.h"
void printExpressions(const TVector<Expression>& expressions) {
    std::cout << "\n=== ALL EXPRESSIONS ===\n";

    if (expressions.size() == 0) {
        std::cout << "No expressions\n";
        return;
    }

    for (size_t i = 0; i < expressions.size(); i++) {
        std::cout << "ID: " << i << "\n";
        std::cout << "  Expression: " << expressions[i].getExpression() << "\n";

        // Получаем переменные
        auto& vars = expressions[i].getVariables();
        if (vars.size() == 0) {
            std::cout << "  Variables: not set\n";
        }
        else {
            std::cout << "  Variables: ";
            for (const auto& var : vars) {
                std::cout << var.first << "=" << var.second << "; ";
            }
            std::cout << "\n";
        }
        std::cout << "-----------------\n";
    }
}

void printMenu() {
    std::cout << "\n=== MENU ===\n";
    std::cout << "1. Create new expression\n";
    std::cout << "2. Delete expression\n";
    std::cout << "3. Set variables\n";
    std::cout << "4. Calculate expression\n";
    std::cout << "0. Exit\n";
    std::cout << "Your choice: ";
}

int main() {
    TVector<Expression> expressions;

    std::cout << "=== CALCULATOR ===\n";

    while (true) {
        printExpressions(expressions);

        printMenu();

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input!\n";
            continue;
        }

        switch (choice) {
        case 1: {
            std::cout << "Enter expression: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string exprStr;
            std::getline(std::cin, exprStr);

            if (exprStr.empty()) {
                std::cout << "Expression cannot be empty!\n";
                break;
            }

            try {
                expressions.push_back(Expression(exprStr));
                std::cout << "Expression created with ID: " << expressions.size() - 1 << "\n";
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            break;
        }

        case 2: {
            size_t id;
            std::cout << "Enter ID to delete: ";
            std::cin >> id;

            if (id >= expressions.size()) {
                std::cout << "Invalid ID!\n";
            }
            else {
                expressions.erase(id);
                std::cout << "Expression deleted\n";
            }
            break;
        }

        case 3: {
            size_t id;
            std::cout << "Enter expression ID: ";
            std::cin >> id;

            if (id >= expressions.size()) {
                std::cout << "Invalid ID!\n";
                break;
            }

            Expression& expr = expressions[id];
            std::cout << "Expression: " << expr.getExpression() << "\n";

            std::cout << "Enter variable name and value (format: name value)\n";
            std::cout << "Enter 'done' to finish\n";

            while (true) {
                std::string varName;
                std::cout << "Variable name: ";
                std::cin >> varName;

                if (varName == "done") break;

                double value;
                std::cout << "Value: ";
                if (!(std::cin >> value)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid value!\n";
                    continue;
                }

                expr.setVariable(varName, value);
                std::cout << "Variable '" << varName << "' = " << value << " set\n";
            }
            break;
        }

        case 4: {
            size_t id;
            std::cout << "Enter expression ID: ";
            std::cin >> id;

            if (id >= expressions.size()) {
                std::cout << "Invalid ID!\n";
                break;
            }

            Expression& expr = expressions[id];
            std::cout << "Calculating: " << expr.getExpression() << "\n";
            try {
                double result = expr.evaluate();
                std::cout << "Result: " << result << "\n";
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";

                // Если ошибка из-за неопределенных переменных, показываем какие есть
                if (std::string(e.what()).find("Undefined variable") != std::string::npos) {
                    std::cout << "Current variables:\n";
                    auto& vars = expr.getVariables();
                    if (vars.size() == 0) {
                        std::cout << "  No variables set\n";
                    }
                    else {
                        for (const auto& var : vars) {
                            std::cout << "  " << var.first << " = " << var.second << "\n";
                        }
                    }
                }
            }
            break;
        }

        default: {
            std::cout << "Invalid choice! Enter 0-4\n";
            break;
        }
        }
    }

    return 0;
}



//Check parser

//int main() {
//    std::string s = "1x+(2y* 16)";
//    List<Lexem> expr = Parser::parse(s);
//    for (auto it = expr.begin(); it != nullptr; ++it) {
//        const Lexem& lex = *it;
//        std::cout << "Name: " << lex.name << ", Type: " << lex.type;
//        if (lex.type == Constant) {
//            std::cout << ", Value: " << lex.value;
//        }
//        if (lex.type == Operator) {
//            std::cout << ", Priority: " << lex.priority;
//        }
//        std::cout << std::endl;
//    }
////Name: x, Type: 1
////Name: +, Type: 5, Priority: 2
////Name: y, Type: 1
////Name: *, Type: 5, Priority: 3
////Name: 16, Type: 0, Value: 16
//return 0;
//}


//Check buildRPN
//int main() {
//    //Test1
//    std::string s1 = "x+(y* 16)";
//    List<Lexem> expr1 = Parser::buildRPN(Parser::parse(s1));
//    for (auto it = expr1.begin(); it != nullptr; ++it) {
//        const Lexem& lex = *it;
//        std::cout << lex.name;
//    }
//    std::cout << "\n";
//    //Test2
//    std::string s2 = "(x+y)*(6*x-2*y)";
//    List<Lexem> expr2 = Parser::buildRPN(Parser::parse(s2));
//    for (auto it = expr2.begin(); it != nullptr; ++it) {
//        const Lexem& lex = *it;
//        std::cout << lex.name;
//    }
//    //xy16*+
//    //xy+6x*2y*-*
//    return 0;
//}

//Check Expression 
//int main() {
//    Expression expr1("2*3 *4");
//    try {
//        double result = expr1.evaluate();
//        std::cout << "Result: " << result << std::endl;
//    }
//    catch (const std::exception& e) {
//        std::cout << "Error: " << e.what() << std::endl;
//    }
//    Expression expr2("a+2*7");
//    expr2.setVariable("a", 5.0);
//    try {
//        double result = expr2.evaluate();
//        std::cout << "Result: " << result << std::endl;
//    }
//    catch (const std::exception& e) {
//        std::cout << "Error: " << e.what() << std::endl;
//    }
//// Result: 24
//// Result: 19
//}