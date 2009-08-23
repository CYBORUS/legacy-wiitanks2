#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char** argv)
{
    string newClassName;
    cout << "Enter the name of the class you would like to build:" << endl;
    cin >> newClassName;

    if (newClassName.length() < 2)
    {
        cerr << "invalid class name!\n";
        return 1;
    }

    newClassName[0] = toupper(newClassName[0]); // must be capitalized!

    ofstream newFile;
    string s;

    s = newClassName + ".h";
    newFile.open(s.c_str(), ios_base::out);

    s = newClassName;
    for (size_t i = 0; i < s.length(); i++) s[i] = toupper(s[i]);
    //cerr << "checking s: " << s << endl;

    newFile << "#ifndef _" << s << "_H" << endl;
    newFile << "#define _" << s << "_H" << endl;
    newFile << endl << "class " << newClassName << endl;
    newFile << "{" << endl;
    newFile << "    public:" << endl;
    newFile << "        " << newClassName << "();" << endl;
    newFile << "        virtual ~" << newClassName << "();" << endl;
    newFile << endl;
    newFile << "    private:" << endl;
    newFile << "        // private member variables" << endl;
    newFile << "};" << endl;
    newFile << endl << "#endif" << endl << endl;

    newFile.close();

    s = newClassName + ".cpp";
    newFile.open(s.c_str(), ios_base::out);

    newFile << "#include \"" << newClassName << ".h\"" << endl;
    newFile << endl << newClassName << "::" << newClassName << "()" << endl;
    newFile << "{" << endl << "}" << endl;
    newFile << endl << newClassName << "::~" << newClassName << "()" << endl;
    newFile << "{" << endl << "}" << endl << endl;

    newFile.close();

    return 0;
}
