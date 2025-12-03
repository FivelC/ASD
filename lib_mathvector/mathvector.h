
#include <iostream>
#include "../lib_TVector/TVector.h"

template <typename T>
class MathVector : public TVector<T> {
public:
    using TVector<T>::TVector;


};