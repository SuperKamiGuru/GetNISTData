using namespace std;

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <dirent.h>
#include "include/ElementSym.hh"
#include <iomanip>

// add header file to the original string stream
// use findDouble() when determining if the constructor is a single isotope or not

enum  OutFilter {characters=1, numbers, NA, symbols};

void GetDataStream( string, std::stringstream&);

void FormatData(std::stringstream& streamS);
bool MovePastWord(std::stringstream& stream, string word);
string ExtractString(std::stringstream &stream, char delim, int outType=7);
void CropStream(std::stringstream& stream, int firstChar, int lastChar=0);
void SetDataStream( string, std::stringstream&);



int main(int argc, char **argv)
{
    string NISTSourceName, outFileName;
    std::stringstream streamS;

    if(argc==3)
    {
        NISTSourceName = argv[1];
        outFileName = argv[2];

            GetDataStream(NISTSourceName, streamS);
            FormatData(streamS);
            SetDataStream( outFileName, streamS);
    }
    else
    {
        cout << "\nGive the the G4NISTElementBuilder.cc file and the output file name\n" <<  endl;
    }

    return 0;
}

void GetDataStream( string geoFileName, std::stringstream& ss)
{
    string* data=NULL;

    // Use regular text file
    std::ifstream thefData( geoFileName.c_str() , std::ios::in | std::ios::ate );
    if ( thefData.good() )
    {
        int file_size = thefData.tellg();
        thefData.seekg( 0 , std::ios::beg );
        char* filedata = new char[ file_size ];
        while ( thefData )
        {
            thefData.read( filedata , file_size );
        }
        thefData.close();
        data = new string ( filedata , file_size );
        delete [] filedata;
    }
    else
    {
    // found no data file
    //                 set error bit to the stream
        ss.setstate( std::ios::badbit );
    }
    if (data != NULL)
    {
        ss.str(*data);
        if(data->back()!='\n')
            ss << "\n";
        ss.seekg( 0 , std::ios::beg );
    }

    delete data;
}

void FormatData(std::stringstream& stream)
{
    std::vector<double> isotopeMass;
    isotopeMass.reserve(500);
    std::vector<int> elemNumIso;
    elemNumIso.reserve(120);
    std::vector<int> elemBaseA;
    elemBaseA.reserve(120);

    isotopeMass.push_back(0.);
    elemNumIso.push_back(1);
    elemBaseA.push_back(0);

    int numIso, baseA;
    double mass;
    stringstream numConv;

    ElementSym elementSyms;
    elementSyms.SetElementSymbols();

    MovePastWord(stream, "::Initialise()");
    int pos = stream.tellg();
    CropStream(stream, pos);

    for(int i=1; i<119; i++)
    {

        if(MovePastWord(stream, (elementSyms.GetSym(i)+'N')))
        {
            ExtractString(stream, '{', 0);
            numConv.str(ExtractString(stream, ',', int(numbers)));

            numConv >> baseA;
            numConv.str("");
            numConv.clear();

            if(MovePastWord(stream, (elementSyms.GetSym(i)+'A')))
            {
                numConv.str(ExtractString(stream, ']', int(numbers)));
                numConv >> numIso;
                numConv.str("");
                numConv.clear();
                for(int j=0; j<numIso; j++)
                {
                    if(j==numIso-1)
                    {
                        numConv.str(ExtractString(stream, ';', int(numbers)));
                    }
                    else
                    {
                        numConv.str(ExtractString(stream, ',', int(numbers)));
                        stream.get();
                    }
                    numConv >> mass;
                    isotopeMass.push_back(mass);
                    numConv.str("");
                    numConv.clear();
                }
                elemBaseA.push_back(baseA);
                elemNumIso.push_back(numIso);
            }
            else
            {
                stream.clear();
                stream.seekg(0, std::ios::beg);
                if(MovePastWord(stream, (elementSyms.GetSym(i)+'A')))
                {
                    numConv.str(ExtractString(stream, ']', int(numbers)));
                    numConv >> numIso;
                    numConv.str("");
                    numConv.clear();
                    for(int j=0; j<numIso; j++)
                    {
                        if(j==numIso-1)
                        {
                            numConv.str(ExtractString(stream, ';', int(numbers)));
                        }
                        else
                        {
                            numConv.str(ExtractString(stream, ',', int(numbers)));
                        }
                        numConv >> mass;
                        isotopeMass.push_back(mass);
                        numConv.str("");
                        numConv.clear();
                    }
                    elemBaseA.push_back(baseA);
                    elemNumIso.push_back(numIso);
                }
                else
                {
                    cout << "\nError: couldn't find mass data for element " << i << endl;
                }
            }
        }
        else
        {
            stream.clear();
            stream.seekg(0, std::ios::beg);

            if(MovePastWord(stream, (elementSyms.GetSym(i)+'N')))
            {
                ExtractString(stream, '{', 0);
                numConv.str(ExtractString(stream, ',', int(numbers)));

                numConv >> baseA;
                numConv.str("");
                numConv.clear();

                if(MovePastWord(stream, (elementSyms.GetSym(i)+'A')))
                {
                    numConv.str(ExtractString(stream, ']', int(numbers)));
                    numConv >> numIso;
                    numConv.str("");
                    numConv.clear();
                    for(int j=0; j<numIso; j++)
                    {
                        if(j==numIso-1)
                        {
                            numConv.str(ExtractString(stream, ';', int(numbers)));
                        }
                        else
                        {
                            numConv.str(ExtractString(stream, ',', int(numbers)));
                        }
                        numConv >> mass;
                        isotopeMass.push_back(mass);
                        numConv.str("");
                        numConv.clear();
                    }
                    elemBaseA.push_back(baseA);
                    elemNumIso.push_back(numIso);
                }
                else
                {
                    stream.clear();
                    stream.seekg(0, std::ios::beg);
                    if(MovePastWord(stream, (elementSyms.GetSym(i)+'A')))
                    {
                        numConv.str(ExtractString(stream, ']', int(numbers)));
                        numConv >> numIso;
                        numConv.str("");
                        numConv.clear();
                        for(int j=0; j<numIso; j++)
                        {
                            if(j==numIso-1)
                            {
                                numConv.str(ExtractString(stream, ';', int(numbers)));
                            }
                            else
                            {
                                numConv.str(ExtractString(stream, ',', int(numbers)));
                            }
                            numConv >> mass;
                            isotopeMass.push_back(mass);
                            numConv.str("");
                            numConv.clear();
                        }
                        elemBaseA.push_back(baseA);
                        elemNumIso.push_back(numIso);
                    }
                    else
                    {
                        cout << "\nError: couldn't find mass data for element " << i << endl;
                    }
                }
            }
            else
            {
                cout << "\nError: couldn't find mass data for element " << i << endl;
            }
        }
    }

    int arraySize = elemNumIso.size();

    stream.str("");
    stream.clear();

    stream << "\n" << endl;

    stream << "void IsotopeMass::SetIsotopeMass()\n{\n\telemNumIso = new int [" << arraySize << "];\n\telemBaseA = new int [" << arraySize << "];\n\tisotopeMass = new double *[" << arraySize << "];\n" << endl;

    for(int i=0; i<int(elemNumIso.size()); i++)
    {
        stream << "\telemNumIso[" << i << "] = " << elemNumIso[i] << ";" << endl;
    }

    stream << "\n" << endl;

    for(int i=0; i<int(elemBaseA.size()); i++)
    {
        stream << "\telemBaseA[" << i << "] = " << elemBaseA[i] << ";" << endl;
    }

    stream << "\n" << endl;

    stream << "\tfor(int i=0; i<" << arraySize << "; i++)\n\t{\n\t\tisotopeMass[i] = new double [elemNumIso[i]];\n\t}";

    int count=0;
    for(int i=0; i<int(elemNumIso.size()); i++)
    {
        for(int j=0; j<int(elemNumIso[i]); j++, count++)
        {
            stream << "\tisotopeMass[" << i << "]" << "[" << j << "] = " << isotopeMass[count] << ";" << endl;
        }
    }

    stream << "\n}" << endl;

    elementSyms.ClearStore();

}

bool MovePastWord(std::stringstream& stream, string word)
{
    std::vector<string> wordParts;
    int pos=0, start;
    bool check=true, firstPass=true;

    start = stream.tellg();

    for(int i=0; i<int(word.length()); i++)
    {
        if(word[i]==' ')
        {
            if(check)
            {
                pos=i+1;
            }
            else
            {
                wordParts.push_back(word.substr(pos,i-pos));
                pos=i+1;
                check=true;
            }
        }
        else
        {
            check=false;
            if(i==int(word.length()-1))
            {
                wordParts.push_back(word.substr(pos,i-pos+1));
            }
        }
    }

    if(wordParts.size()==0)
    {
        wordParts.push_back(word);
    }

    string wholeWord, partWord;
    check=false;
    char line[256];

    while(!check)
    {
        if(!stream)
        {
            if(firstPass)
            {
                stream.clear();
                stream.seekg(start, std::ios::beg);
                firstPass=false;
            }
            else
            {
                break;
            }
        }
        if(stream.peek()=='/')
        {
            stream.get();
            if(stream.peek()=='/')
            {
                stream.getline(line,256);
            }
            else if(stream.peek()=='*')
            {
                stream.get();
                while(stream)
                {
                    if(stream.get()=='*')
                    {
                        if(stream.get()=='/')
                        {
                            break;
                        }
                    }
                }
            }
        }
        else if(stream.peek()=='\n')
        {
            stream.getline(line,256);
        }
        else if(stream.peek()=='\t')
        {
            stream.get();
        }
        else if(stream.peek()==' ')
        {
            stream.get();
        }
        else
        {
            for(int i=0; i<int(wordParts.size()); i++)
            {
                stream >> wholeWord;
                if(int(wholeWord.length())>=int((wordParts[i]).length()))
                {
                    if(firstPass)
                    {
                        check=(wholeWord==(wordParts[i]));
                        if(!check)
                        {
                            break;
                        }
                    }
                    else
                    {
                        partWord = wholeWord.substr(0, (wordParts[i]).length());
                        check=(partWord==(wordParts[i]));

                        if(check)
                        {
                            stream.seekg((partWord.length()-wholeWord.length()),std::ios_base::cur);
                        }
                        else if(0==i)
                        {
                            partWord = wholeWord.substr(wholeWord.length()-(wordParts[i]).length(), (wordParts[i]).length());
                            check=(partWord==(wordParts[i]));
                        }

                        if(!check)
                        {
                            break;
                        }
                    }

                }
                else
                {
                    break;
                }
            }
        }

    }

    if(!check)
    {
        stream.clear();
        stream.seekg(start, std::ios::beg);
    }

    return check;
}

string ExtractString(std::stringstream &stream, char delim, int outType)
{
    string value="";
    bool charOut=false, numOut=false, symOut=false;
    char letter;
    //bool first=true;

    if(outType==0)
    {

    }
    else if(outType==1)
    {
        charOut=true;
    }
    else if(outType==2)
    {
        numOut=true;
    }
    else if(outType==3)
    {
        charOut=true;
        numOut=true;
    }
    else if(outType==4)
    {
        symOut=true;
    }
    else if(outType==5)
    {
        charOut=true;
        symOut=true;
    }
    else if(outType==6)
    {
        numOut=true;
        symOut=true;
    }
    else
    {
        charOut=true;
        numOut=true;
        symOut=true;
    }

    while(stream&&(stream.peek()!=delim))
    {
        letter = stream.get();
        if(((letter>='A')&&(letter<='Z'))||((letter>='a')&&(letter<='z')))
        {
            if(charOut)
            {
                value+=letter;
                //first=true;
            }
            /*else if(first)
            {
                value+=' ';
                first=false;
            }*/
        }
        else if(((letter>='0')&&(letter<='9'))||(letter=='.')||(letter=='-'))
        {
            if(numOut)
            {
                value+=letter;
                //first=true;
            }
            /*else if(first)
            {
                value+=' ';
                first=false;
            }*/
        }
        else
        {
            if(symOut)
            {
                value+=letter;
                //first=true;
            }
            /*else if(first)
            {
                value+=' ';
                first=false;
            }*/
        }
    }
    return value;
}

void CropStream(std::stringstream& stream, int firstChar, int lastChar)
{
    if(lastChar==0)
        stream.seekg( 0 , std::ios::end );
    else
        stream.seekg( lastChar , std::ios::beg );

    int file_size = int(stream.tellg())-firstChar;
    stream.seekg( firstChar , std::ios::beg );
    char* filedata = new char[ file_size ];

    stream.read( filedata , file_size );
    if(!stream)
    {
        cout << "\n #### Error reading string stream ###" << endl;
        return;
    }
    stream.str("");
    stream.clear();

    stream.write( filedata, file_size);
    stream.seekg(0 , std::ios::beg);

    delete filedata;
}

void SetDataStream( string macroFileName, std::stringstream& ss)
{
  std::ofstream out( macroFileName.c_str() , std::ios::out | std::ios::trunc );
  if ( ss.good() )
  {
     ss.seekg( 0 , std::ios::end );
     int file_size = ss.tellg();
     ss.seekg( 0 , std::ios::beg );
     char* filedata = new char[ file_size ];

     while ( ss )
     {
        ss.read( filedata , file_size );
        if(!file_size)
        {
            cout << "\n #### Error the size of the stringstream is invalid ###" << endl;
            break;
        }
     }

     out.write(filedata, file_size);
     if (out.fail())
    {
        cout << endl << "writing the ascii data to the output file " << macroFileName << " failed" << endl
             << " may not have permission to delete an older version of the file" << endl;
    }
     out.close();
     delete [] filedata;
  }
  else
  {
// found no data file
//                 set error bit to the stream
     ss.setstate( std::ios::badbit );

     cout << endl << "### failed to write to ascii file " << macroFileName << " ###" << endl;
  }
   ss.str("");
}
