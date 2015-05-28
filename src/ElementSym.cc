#include "../include/ElementSym.hh"

using namespace std;

string* ElementSym::elementSym=NULL;

ElementSym::ElementSym()
{
    //ctor
}

ElementSym::~ElementSym()
{
    //dtor
}

void ElementSym::ClearStore()
{
    if(elementSym != NULL)
        delete [] elementSym;
}

void ElementSym::SetElementSymbols()
{
    elementSym = new string[119];

    elementSym[0] = "Error";
    elementSym[1] = "H";
    elementSym[2] = "He";
    elementSym[3] = "Li";
    elementSym[4] = "Be";
    elementSym[5] = "B";
    elementSym[6] = "C";
    elementSym[7] = "N";
    elementSym[8] = "O";
    elementSym[9] = "F";
    elementSym[10] = "Ne";
    elementSym[11] = "Na";
    elementSym[12] = "Mg";
    elementSym[13] = "Al";
    elementSym[14] = "Si";
    elementSym[15] = "P";
    elementSym[16] = "S";
    elementSym[17] = "Cl";
    elementSym[18] = "Ar";
    elementSym[19] = "P";
    elementSym[20] = "Ca";
    elementSym[21] = "Sc";
    elementSym[22] = "Ti";
    elementSym[23] = "V";
    elementSym[24] = "Cr";
    elementSym[25] = "Mn";
    elementSym[26] = "Fe";
    elementSym[27] = "Co";
    elementSym[28] = "Ni";
    elementSym[29] = "Cu";
    elementSym[30] = "Zn";
    elementSym[31] = "Ga";
    elementSym[32] = "Ge";
    elementSym[33] = "As";
    elementSym[34] = "Se";
    elementSym[35] = "Br";
    elementSym[36] = "Kr";
    elementSym[37] = "Rb";
    elementSym[38] = "Sr";
    elementSym[39] = "Y";
    elementSym[40] = "Zr";
    elementSym[41] = "Nb";
    elementSym[42] = "Mo";
    elementSym[43] = "Tc";
    elementSym[44] = "Ru";
    elementSym[45] = "Rh";
    elementSym[46] = "Pd";
    elementSym[47] = "Ag";
    elementSym[48] = "Cd";
    elementSym[49] = "In";
    elementSym[50] = "Sn";
    elementSym[51] = "Sb";
    elementSym[52] = "Te";
    elementSym[53] = "I";
    elementSym[54] = "Xe";
    elementSym[55] = "Cs";
    elementSym[56] = "Ba";
    elementSym[57] = "La";
    elementSym[58] = "Ce";
    elementSym[59] = "Pr";
    elementSym[60] = "Nd";
    elementSym[61] = "Pm";
    elementSym[62] = "Sm";
    elementSym[63] = "Eu";
    elementSym[64] = "Gd";
    elementSym[65] = "Tb";
    elementSym[66] = "Dy";
    elementSym[67] = "Ho";
    elementSym[68] = "Er";
    elementSym[69] = "Tm";
    elementSym[70] = "Yb";
    elementSym[71] = "Lu";
    elementSym[72] = "Hf";
    elementSym[73] = "Ta";
    elementSym[74] = "W";
    elementSym[75] = "Re";
    elementSym[76] = "Os";
    elementSym[77] = "Ir";
    elementSym[78] = "Pt";
    elementSym[79] = "Au";
    elementSym[80] = "Hg";
    elementSym[81] = "Tl";
    elementSym[82] = "Pb";
    elementSym[83] = "Bi";
    elementSym[84] = "Po";
    elementSym[85] = "At";
    elementSym[86] = "Rn";
    elementSym[87] = "Fr";
    elementSym[88] = "Ra";
    elementSym[89] = "Ac";
    elementSym[90] = "Th";
    elementSym[91] = "Pa";
    elementSym[92] = "U";
    elementSym[93] = "Np";
    elementSym[94] = "Pu";
    elementSym[95] = "Am";
    elementSym[96] = "Cm";
    elementSym[97] = "Bk";
    elementSym[98] = "Cf";
    elementSym[99] = "Es";
    elementSym[100] = "Fm";
    elementSym[101] = "Md";
    elementSym[102] = "No";
    elementSym[103] = "Lr";
    elementSym[104] = "Rf";
    elementSym[105] = "Db";
    elementSym[106] = "Sg";
    elementSym[107] = "Bh";
    elementSym[108] = "Hs";
    elementSym[109] = "Mt";
    elementSym[110] = "Ds";
    elementSym[111] = "Rg";
    elementSym[112] = "Cp";
    elementSym[113] = "Uut";
    elementSym[114] = "Uuq";
    elementSym[115] = "Uup";
    elementSym[116] = "Uuh";
    elementSym[117] = "Uus";
    elementSym[118] = "Uuo";
}
