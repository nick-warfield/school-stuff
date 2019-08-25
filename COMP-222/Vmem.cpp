// Nicholas Warfield
// Comp 222 - Computer Organization - 2:00PM T/R
// due 4/18/19
// std=c++11

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class VirtualMem
{
    public:
        VirtualMem() : pageCount(0), pageSize(0), FIFO(false), pageTable() { };

        void Map(void)
        {
            uint address, offset, page;
            cout << "Enter virtual memory address to access: ";
            cin >> address;
            page = address / pageSize;
            offset = address % pageSize;

            int frame = -1;
            for (int i = 0; i < pageTable.size(); ++i)
            {
                if (page == get<0>(pageTable[i])) { frame = i; }
            }

            if (frame != -1)
            {
                cout << "Virtual Address " << address << " mapped to physical address ";
                cout << get<1>(pageTable[frame]) + offset << endl;

                if (!FIFO)
                {
                    for (int i = frame - 1; i >= 0; --i)
                    {
                        auto temp = pageTable[i + 1];
                        pageTable[i + 1] = pageTable[i];
                        pageTable[i] = temp;
                    }
                }
            }
            else
            {
                cout << "Page Fault!\n";
                if (pageTable.size() != pageCount)
                {
                    pageTable.emplace_back(page, pageTable.size());
                }
                else if (FIFO)
                {
                    pageTable[0] = make_tuple(page, get<1>(pageTable[0]));
                    for (int i = 1; i < pageTable.size(); ++i)
                    {
                        auto temp = pageTable[i - 1];
                        pageTable[i - 1] = pageTable[i];
                        pageTable[i] = temp;
                    }
                }
                else
                {
                    auto a = make_tuple(page, get<1>(pageTable[pageTable.size() - 1]));
                    pageTable[pageTable.size() - 1] = a;
                }

                if (!FIFO)
                {
                    for (int i = pageTable.size() - 2; i >= 0; --i)
                    {
                        auto temp = pageTable[i + 1];
                        pageTable[i + 1] = pageTable[i];
                        pageTable[i] = temp;
                    }
                }
            }
        }

        void Print(void)
        {
            for (int i = 0; i < 16; ++i) { cout << "-"; }
            cout << endl << "|VP\t|PF\t|\n";
            for (int i = 0; i < 16; ++i) { cout << "-"; }
            cout << endl;

            for (int i = 0; i < pageTable.size(); ++i)
            {
                cout << "|";
                cout << get<0>(pageTable[i]) << "\t|";
                cout << get<1>(pageTable[i]) << "\t|\n";

                for (int i = 0; i < 16; ++i) { cout << "-"; }
                cout << endl;
            }
        }

        void EnterParams(void)
        {
            cout << "Enter physical memory size in words: ";
            cin >> pageCount;
            cout << "Enter page size in words per page: ";
            cin >> pageSize;
            pageCount /= pageSize;
            cout << "Enter replacement policy (0=LRU, 1=FIFO): ";
            cin >> FIFO;

            pageTable.clear();
        }

    private:
        vector<tuple<int, int>> pageTable;
        int pageCount;
        int pageSize;
        bool FIFO;
};

int menu(void)
{
    int input = 4;
    cout << endl;
    cout << "Virtual memory to Physical memory  mapping:\n";
    cout << "-------------------------------------------\n";
    cout << "1) Enter Parameters\n";
    cout << "2) Map virtual address to physical address\n";
    cout << "3) Print page table\n";
    cout << "4) Quit\n\n";
    cout << "Enter Selection: ";
    cin >> input;
    return input;
}

int main(void)
{
    bool exit = false;
    VirtualMem vm;

    while (!exit)
    {
        switch (menu())
        {
            case 1: vm.EnterParams();   break;
            case 2: vm.Map();           break;
            case 3: vm.Print();         break;
            case 4: exit = true;        break;
        }
    }
    return 0;
}
