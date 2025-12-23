#include <string>
#include <cfloat>

enum TypeLexem {
    Constant,
    Variable,
    OpenBracket,
    CloseBracket,
    Function,
    Operator,
    UnOperator,
    OpenedAbs,
    ClosedAbs
};

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    double (*function)(double);

    Lexem(const std::string& _name = "",
        TypeLexem _type = Constant,
        double _value = DBL_MAX,
        int _priority = -1,
        double (*_function)(double) = nullptr)
        : name(_name),
        type(_type),
        value(_value),
        priority(_priority),
        function(_function)
    {
    }

    
};