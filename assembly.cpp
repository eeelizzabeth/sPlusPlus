#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

string dec_to_binary(int dec);
string reg_to_bin(string reg);

int main()
{
    ifstream fin("sum.spp");      // the file the assembler will interpret
    ofstream out("sum.o");          // the file generated with 0s and 1s

    if(fin.fail())                  // always make sure the file was opened properly
    {
        cout << "File open failed\n";
        exit(0);
    }

    string opcode;                  // store the instruction in opcode
    int num;                        // if i need to store a number from the instruction
    string regis;                   // if i am reading a register. Note I have 8 registered
    // which i call: R1, R2, R3, R4, R5, R6, R7, and R8.

    while(!fin.eof())                           // while not reached end of file
    {
        fin >> opcode;                          // the first line of every instruction is instruction

        if(opcode == "onions")                  // adding function
        {
            out << "0001";                      // number one
            for(int i = 0; i < 2; i++)
            {
                fin >> regis;                   // read in the register
                out << reg_to_bin(regis);       // this function will conver to appropriate address
            }
            out << "0";
            out << endl;                        // line break
        }
        else if(opcode == "donkey")             // output function
        {
            out << "0010";                      // number two
            fin >> regis;
            out << reg_to_bin(regis);
            out << "000" << endl;
        }
        else if(opcode == "shrek4")             // halt function
        {
            out << "0011";                      // number three
            out << "000000";
            out << endl;
            // this is padding, since instruction have to be fixed
        }
        else if(opcode == "putinboots")         // insert function
        {
            out << "0100";                      // number four
            fin >> num;
            out << dec_to_binary(num);
            fin >> regis;
            out << reg_to_bin(regis);
            out << endl;
        }
        else if(opcode == "farFarArray")        // create an array
        {
            out << "0101";                      // number five
            fin >> num;                         // read in the register
            out << dec_to_binary(num);          // this function will conver to appropriate address
            fin >> regis;
            out << reg_to_bin(regis);
            out << endl;
        }
        else if(opcode == "mirrorMirror")       // find function
        {
            out << "0110";                      // number six
            fin >> num;                         // read in the register
            out << dec_to_binary(num);          // this function will conver to appropriate address
            out << "000";
            out << endl;// this is padding, since instruction have to be fixed
        }
        else if(opcode == "fairyGodMother")        // erase function
        {
            out << "0111";                      // number seven
            fin >> regis;                         // read in the register
            out << reg_to_bin(regis);          // this function will conver to appropriate address
            out << "000";
            out << endl;// this is padding, since instruction have to be fixed
        }
        else if(opcode == "rumpelstiltskin")        // clear function
        {
            out << "1000";                      // number eight

            out << "000000";
            out << endl;// this is padding, since instruction have to be fixed
        }
        else if(opcode == "threeBlindMice")        // multiplication function
        {
            out << "1001";                      // number nine
            for(int i = 0; i < 2; i++)          // for loop that loops 2 times
            {
                fin >> regis;                   // read in the register
                out << reg_to_bin(regis);       // this function will conver to appropriate address
            }
            out << "0";
            out << endl;            // this is padding, since instruction have to be fixed
        }
        else if(opcode == "mongo")        // input
        {
            out << "1010";                      // number nine
            fin>>regis;
            out<<reg_to_bin(regis);
            out << "000"<<endl;            // this is padding, since instruction have to be fixed
        }


        else if(opcode == "foreverAfter")       // process the OUT instruction
        {
            out << "1010";              // OUT is 111 as described in my ISA
            fin >> regis;               // read in the register
            out << reg_to_bin(regis);   // this function will conver to appropriate address
            out << "000";
            out << endl;// this is padding, since instruction have to be fixed
        }
        else if(opcode == "neverAfter")       // process the OUT instruction
        {
            out << "1011";              // OUT is 111 as described in my ISA
            out << "000000";
            out << endl;// this is padding, since instruction have to be fixed
        }

        else
        {
            cout << "ERROR: INSTRUCTION DOESN'T EXIST\n";
            exit(0);
        }
    }

    fin.close();
    out.close();

    return 0;
}

string dec_to_binary(int dec)
{
    string bin = "";
    while(dec!=0)
    {
        int mod = dec%2;
        if(mod == 1)
        {
            bin = "1" + bin;
        }
        else
        {
            bin = "0" +bin;
        }
        dec = dec/2;

    }
    while(bin.length() < 6)
    {
        bin  = "0"+bin;
    }
    return bin;
}
string reg_to_bin(string reg)
{
    if(reg == "RegisterUno")         // basically a simple if.. else
        return "000";       // that will read in a register and
    else if(reg == "RegisterDoz")    // return the appropriate address.
        return "001";
    else if(reg == "RegisterTrez")
        return "010";
    else if(reg == "RegisterKuatro")
        return "011";
    else if(reg == "RegisterZinco")
        return "100";
    else if(reg == "RegisterZeiz")
        return "101";
    else if(reg == "RegisterZiete")
        return "110";
    else if(reg == "RegisterOsho")
        return "111";
    else if(reg == "ArrayA_Haon")
        return "000";
    else if(reg == "ArrayA_Do")
        return "111";
    else if(reg == "ArrayA_Tri")
        return "010";
    else if(reg == "ArrayA_Ceathair")
        return "101";
    else
    {
        cout << "Error\n";
        exit(2);           // kill the program if invalid register
    }                      // is addressed.
}
