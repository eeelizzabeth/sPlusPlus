//simulator.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include <stack>
using namespace std;

int bin_to_dec(string bin);

int main()
{
    ifstream fin("find.o");                  // the file with binary code (0s and 1s)

    if(fin.fail())                          // make sure file opened okay
    {
        cout << "File open failed\n";
        exit(0);
    }
    ifstream& GotoLine(ifstream& file,unsigned int num);
    string instruction;                     // hold the entire binary instruction
    string opcode;                          // hold the binary opcode (4 bits)
    map<string, int> reg_map;               // a map from strings to ints used for registers
    vector<string> commands;
    map<string, vector<int> > ary_map;        // a map from strings to vector<int> used for arrays
    reg_map["000"] = 0;                     //r1
    reg_map["001"] = 0;                     //r2
    reg_map["010"] = 0;                     //r3
    reg_map["011"] = 0;                     //r4
    reg_map["100"] = 0;                     //r5
    reg_map["101"] = 0;                     //r6
    reg_map["110"] = 0;                     //r7
    reg_map["111"] = 0;                     //r8
    //int i=0;
    stack<int> loop;
    stack<int> vals;
    while(!fin.eof())
    {

        fin >> instruction;
        commands.push_back(instruction);
    }                        // read in the entire line of instrcution (13 bits)
    for(int i=0;i<commands.size();i++)
    {
        instruction = commands[i];
        opcode = instruction.substr(0,4);           // take the first 4 bits of the instruction
        if(opcode == "0100") //PUT                  // if the first 4 bits are PUT
        {
            string n = instruction.substr(4,3);     // read the 6 bits related to numerical value
            int val = reg_map[n];                // convert binary to decimal
            //ncout<<"here "<<val<<endl;
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
        else if(opcode == "1001") //multiply                 // SUM instruction is followed by three registers
        {
            string regisA = instruction.substr(4,3);    // bits 4-6 are the first register
            string regisB = instruction.substr(7,3);    // bits 7-9 are the second register
            // bits 10-12 are the last register

            int product_result = reg_map[regisA] * reg_map[regisB]; // add the first two registers
            reg_map[regisA] = product_result;                       // place the result in the third register

        }
        else if(opcode == "0010") //Donkey                // print to screen
        {
            string regis = instruction.substr(4,3);     // find which register to print
            cout << reg_map[regis] << endl;             // use those 3 bits with map to find value.
        }
        else if(opcode == "0011") //halt
        {
            break;
        }
        else if(opcode == "0101") //FarFarArray
        {
            string regis = instruction.substr(4,3);    // find the 3 bits related to the array
            ary_map[regis] = vector<int>();

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
        else if(opcode == "0110") //MirrorMirror
        {
            string regisA = instruction.substr(4,3);
            string regisB = instruction.substr(7,3);
            int val = reg_map[regisA];
            vector<int> vec = ary_map[regisB];
            int index= -1;
            for(int i = 0;i<vec.size();i++)
            {
                if(vec[i] == val)
                {
                    index = i;

                    break;
                }
            }
            cout << index << endl;
        }
        else if(opcode == "0111" )  //fairyGodMother
        {
            string regisA = instruction.substr(4,3);
            string regisB = instruction.substr(7,3);
            int val = reg_map[regisA];
            vector<int> vec = ary_map[regisB];
            for(int i = 0;i<vec.size();i++)
            {
                if(vec[i]==val)
                {
                    vec.erase(vec.begin()+i);
                    break;
                }
            }
        }
        else if(opcode == "1000" )  //rumpelstiltskin
        {
            for(map<string,int>::iterator it = reg_map.begin();it!=reg_map.end();it++)
            {
                it->second =0;
            }
            for(map<string,vector<int> >::iterator it = ary_map.begin();it!=ary_map.end();it++)
            {
                vector<int> vec;
                it->second = vec;
            }
        }
        else if(opcode == "1111") //mongo
        {
            string regisA = instruction.substr(4,3);
            int val;
            cin>>val;
            reg_map[regisA] = val;
        }
        else if(opcode =="1010")//Forever after
        {
            string regisA = instruction.substr(4,3);
            int val = reg_map[regisA];
            if(loop.empty())
            {
                loop.push(i);
                vals.push(val);
            }
            if(loop.top()!= i)
            {
                loop.push(i);
                vals.push(val);
            }
            //cout<<val<<endl;
            if(val >= 1)
            {
                val--;
                reg_map[regisA] =val;
                vals.pop();
                vals.push(val);
                //cout<<"Loop Top: "<<loop.top()<<endl;
                //cout<<"Val: "<<val<<endl;
            }


        }
        else if(opcode == "1011") //neverAfter
        {
            //cout<<"End Loop Top"<<loop.top()<<endl;
            if(!loop.empty())
            {
                if(vals.top()<=0)
                {
                    loop.pop();
                    vals.pop();
                }
                else
                {
                    int temp = loop.top();
                    i =temp-1;
                }



            }
        }
        else if(opcode == "1110")//andTheyDontStopComing
        {
            string regisA = instruction.substr(4,3);
            string regisB = instruction.substr(7,3);
            int val = reg_map[regisA];
            vector<int> vec = ary_map[regisB];
            vec.push_back(val);
            ary_map[regisB] = vec;
        }
        else if(opcode == "1100")//andTheyDontStopComing
        {
            string regisA = instruction.substr(4,3);
            string regisB = instruction.substr(7,3);
            int val = reg_map[regisA];
            vector<int> vec = ary_map[regisB];
            vec.push_back(val);
            ary_map[regisB] = vec;
        }

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
