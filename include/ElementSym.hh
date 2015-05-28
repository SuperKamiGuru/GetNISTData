#ifndef ELEMENTSYM_HH
#define ELEMENTSYM_HH

#include <string>
#include <iostream>

using namespace std;

class ElementSym
{
    public:
        ElementSym();
        virtual ~ElementSym();
        static void ClearStore();
        static void SetElementSymbols();
        static string GetSym(int Z)
        {
            return elementSym[Z];
        }
        static string *elementSym;
    protected:
    private:
};

#endif // ELEMENTSYM_HH
