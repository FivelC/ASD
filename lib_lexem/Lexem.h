#include <string>
#include <cfloat>

enum TypeLexem {
    Number,
    Variable,
    Degree,
    Power,
    Sign
};

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    char var;

    Lexem(const std::string& _name = "",
        TypeLexem _type = Sign,
        double _value = DBL_MAX,
        int _priority = -1,
        char _var = 'x')
        : name(_name),
        type(_type),
        value(_value),
        var(_var)
    {
    }    
};