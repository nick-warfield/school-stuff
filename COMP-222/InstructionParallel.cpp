// Nicholas Warfield
// Comp 222 - Computer Organization - 2:00PM T/R
// due 5/16/19
// std=c++11

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Instruction
{
    Instruction(string str = "       ") :
        dest(str[1] - '0'), op1(str[4] - '0'), op2(str[7] - '0') { }
    int dest, op1, op2;
};

class Pipeline
{
    public:
        void EnterParams(void)
        {
            cout << "\nEnter total number of instructions: ";
            cin >> count;
            instruction.clear();
            instruction.push_back(Instruction());
            for (int i = 0; i < count; ++i)
            {
                string s;
                cout << i + 1 << ") ";
                cin >> s;
                instruction.push_back(Instruction(s));
            }
            cout << endl;
        }

        void CalcNormal(void) { CalcSuper(1); }
        void CalcSuper(float offStart = 0.5)
        {
            string output(gantt());
            float cycles = 6;
            int end = 0;
            for (int i = 2; i < instruction.size(); ++i)
            {
                float offset = offStart;
                for (int j = 1; i - j > end ; ++j)
                {
                    int destination = instruction[i - j].dest;
                    if (destination == instruction[i].op1 ||
                            destination == instruction[i].op2)
                    {
                        offset = round(offset);
                        offset += 3 - j;
                        end = i - j;
                    }
                }
                cycles += offset;
                output += gantt(cycles);
            }
            cout << "\nTotal Cycles: " << round(cycles) << endl << output << endl;
        }

    private:
        int count;
        vector<Instruction> instruction;
        string gantt(float cycle = 6)
        {
            string s;
            float i = cycle - 6;
            for (; i > 0.5; --i) { s += "    "; }
            if (i > 0) { s += "  "; }
            return s + "|F_I|D_I|C_O|F_O|E_I|W_O|\n";
        }
};

int menu(void)
{
    cout << "Instruction-Level Parallelism\n";
    cout << "-----------------------------\n";
    cout << "1) Enter Instructions\n";
    cout << "2) Calculate total cycle count on a 6-stage pipeline architecture\n";
    cout << "3) Calculate total cucle count on a 6-stage superpipeline architecture\n";
    cout << "4) Quit Program\n\n";
    cout << "Enter Selection: ";
    int value;
    cin >> value;
    return value;
}

int main(void)
{
    bool exit = false;
    Pipeline pl;
    while (!exit)
    {
        switch(menu())
        {
            case 1: pl.EnterParams(); break;
            case 2: pl.CalcNormal(); break;
            case 3: pl.CalcSuper(); break;
            case 4: exit = true; break;
        }
    }

    return 0;
}
