//simulator.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

int bin_to_dec(string bin);

int main()
{
    ifstream fin("sum.o");                  // the file with binary code (0s and 1s)
    
    if(fin.fail())                          // make sure file opened okay
    {
        cout << "File open failed\n";
        exit(0);
    }
    
    string instruction;                     // hold the entire binary instruction
    string opcode;                          // hold the binary opcode (4 bits)
    map<string, int> reg_map;               // a map from strings to ints used for registers
    map<string, vector<int>> ary_map;        // a map from strings to vector<int> used for arrays
    reg_map["000"] = 0;                     //r1
    reg_map["001"] = 0;                     //r2
    reg_map["010"] = 0;                     //r3
    reg_map["011"] = 0;                     //r4
    reg_map["100"] = 0;                     //r5
    reg_map["101"] = 0;                     //r6
    reg_map["110"] = 0;                     //r7
    reg_map["111"] = 0;                     //r8
    
    while(!fin.eof())
    {
        fin >> instruction;                         // read in the entire line of instrcution (13 bits)
        opcode = instruction.substr(0,4);           // take the first 4 bits of the instruction
        
        if(opcode == "0100") //PUT                  // if the first 4 bits are PUT
        {
            string n = instruction.substr(4,3);     // read the 6 bits related to numerical value
            int val = bin_to_dec(n);                // convert binary to decimal
            
            string regis = instruction.substr(7,3);    // find the 3 bits related to the register
            reg_map[regis] = val;                       // use those 3 bits as location to store value
        }
        else if(opcode == "0001") //SUM                 // SUM instruction is followed by three registers
        {
            string regisA = instruction.substr(4,3);    // bits 4-6 are the first register
            string regisB = instruction.substr(7,3);    // bits 7-9 are the second register
            // bits 10-12 are the last register
            
            int sum_result = reg_map[regisA] + reg_map[regisB]; // add the first two registers
            reg_map[regisA] = sum_result;                       // place the result in the third register
            
        }
        else if(opcode == "0001") //multiply                 // SUM instruction is followed by three registers
        {
            string regisA = instruction.substr(4,3);    // bits 4-6 are the first register
            string regisB = instruction.substr(7,3);    // bits 7-9 are the second register
            // bits 10-12 are the last register
            
            int product_result = reg_map[regisA] * reg_map[regisB]; // add the first two registers
            reg_map[regisA] = product_result;                       // place the result in the third register
            
        }
        else if(opcode == "0010") //OUT                 // print to screen
        {
            string regis = instruction.substr(4,3);     // find which register to print
            cout << reg_map[regis] << endl;             // use those 3 bits with map to find value.
        }
        else if(opcode == "0011")
        {
            break;
        }
        else if(opcode == "0101") //MAKE THE ARRAY
        {
            string n = instruction.substr(4,3);         // read the 6 bits related to size of array
            int val = bin_to_dec(n);                    // convert binary to decimal
            string regis = instruction.substr(7,3);    // find the 3 bits related to the array
            ary_map[regis] = vector<int>(val);
            
            /* Quick test to make sure this works (assume vector set to size 5)
             ary_map["000"][0] = 1;
             ary_map["000"][1] = 3;
             ary_map["000"][2] = 5;
             ary_map["000"][3] = 7;
             ary_map["000"][4] = 9;
             
             for(int &i: ary_map["000"])
             cout << i << endl
             */
        }
        else if(opcode == "0110")
        {
            string regisA = instruction.substr(4,3);
            string regisB = instruction.substr(7,3);
            int val = reg_map[regisA];
            vector<int> vec = ary_map[regisB];
            for(int i = 0;i<vec.size();i++)
            {
                if(vec[i] == val)
                {
                    cout<<i<<endl;
                    break;
                }
            }
        }
        else if(opcode == )
            
            
            }
    
    fin.close();
    
    return 0;
}

int bin_to_dec(string bin)
{
    int num = 0;
    for (int i = 0; i < bin.length(); i++)
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);
    
    return num;
}
