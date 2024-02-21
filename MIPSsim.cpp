/* On my honor, I have neither given nor received unauthorized aid on this assignment */
#include<iostream>
#include <vector>
#include <fstream>
#include<string>
#include<map>
#include<cmath>
#include<bitset>
#include<algorithm>
#include<sstream>
#include<queue>

#define UL unsigned long
#define SIZE_INS 32
#define __hyphens__ "--------------------"

#define SIZE_PRE_ISSUE 4
#define SIZE_PRE_ALU 2
#define SIZE_POST_ALU 1
#define SIZE_PRE_MEM 1
#define SIZE_POST_MEM 1

using namespace std;

enum Category
{
    one,
    two,
    twos_complement
};

class InputReader
{
private:
    /* data */
    void readInput(string fileName);
public:
    vector<string> instructions;
    InputReader(string fileName);
    ~InputReader();
};

void InputReader::readInput(string fileName)
{
    fstream newfile;
    newfile.open(fileName,ios::in);
    if (newfile.is_open())
    {   //checking whether the file is open
        string line;
        //cout << "Reading instructions in the input file - " << fileName << endl;
        while(getline(newfile, line))
        { //read data from file object and put it into string.
            instructions.push_back(line);
            //cout << line << "\n"; //print the data of the string
        }
        newfile.close(); //close the file object.
    }
        //cout << "Completed reading input" << endl;
}
InputReader::InputReader(string fileName)
{
    readInput(fileName);
}

InputReader::~InputReader()
{
}

class MipsDisassembly
{
private:
    /* data */
public:
    static string getRegister(string registerBits)
    {
        return "R" + to_string(bitset<32>(registerBits).to_ulong());
    }
    static string getAssemblyOffsetValue(string offsetBits, bool leftShift = true)
    {
        UL value  = bitset<32>(offsetBits).to_ulong();
        if (leftShift)
        {
            value = (value << 2);
        }
        return to_string(value);
    }

    MipsDisassembly(/* args */);
    ~MipsDisassembly();
};

class CategoryOneDisassembly
{
    public:
        static string J(string instruction);
        static string JR(string instruction);
        static string BEQ(string instruction);
        static string BLTZ(string instruction);
        static string BGTZ(string instruction);
        static string BREAK(string instruction);
        static string SW(string instruction);
        static string LW(string instruction);
        static string SLL(string instruction);
        static string SRL(string instruction);
        static string SRA(string instruction);
        static string NOP(string instruction); 
};

string CategoryOneDisassembly::J(string instruction)
{
    string d_instr = "J";
    d_instr += " #";
    
    string instr = instruction.substr(6, 26);
    UL value  = bitset<32>(instr).to_ulong();

    return d_instr + to_string(value << 2);
}

string CategoryOneDisassembly::JR(string instruction)
{
    string d_instr = "JR";
    d_instr += " ";

    string rs = MipsDisassembly::getRegister(instruction.substr(6, 5));
    d_instr += rs;
    return d_instr;
}

string CategoryOneDisassembly::BEQ(string instruction)
{
    string d_instr = "BEQ";
    d_instr += " ";

    string rs = MipsDisassembly::getRegister(instruction.substr(6, 5));
    d_instr += rs;
    d_instr += ", ";

    string rt = MipsDisassembly::getRegister(instruction.substr(11, 5));
    d_instr += rt;
    d_instr += ", ";

    d_instr += "#";
    d_instr += MipsDisassembly::getAssemblyOffsetValue(instruction.substr(16, 16));

    return d_instr;
}

string CategoryOneDisassembly::BLTZ(string instruction)
{
    string d_instr = "BLTZ";
    d_instr += " ";

    string rs = MipsDisassembly::getRegister(instruction.substr(6, 5));
    d_instr += rs;
    d_instr += ", #";
    d_instr += MipsDisassembly::getAssemblyOffsetValue(instruction.substr(16, 16));

    return d_instr;
}

string CategoryOneDisassembly::BGTZ(string instruction)
{
    string d_instr = "BGTZ";
    d_instr += " ";

    string rs = MipsDisassembly::getRegister(instruction.substr(6, 5));
    d_instr += rs;
    d_instr += ", #";
    d_instr += MipsDisassembly::getAssemblyOffsetValue(instruction.substr(16, 16));

    return d_instr;
}

string CategoryOneDisassembly::BREAK(string instruction)
{
    string d_instr = "BREAK";
    return d_instr;
}

string CategoryOneDisassembly::SW(string instruction)
{
    string d_instr = "SW";
    d_instr += " ";

    string base = MipsDisassembly::getRegister(instruction.substr(6, 5));
    string rt = MipsDisassembly::getRegister(instruction.substr(11, 5));
    string offset = MipsDisassembly::getAssemblyOffsetValue(instruction.substr(16, 16), false);

    d_instr += rt;
    d_instr += ", ";
    d_instr += offset;
    d_instr += "(";
    d_instr += base;
    d_instr += ")";

    return d_instr;
}

string CategoryOneDisassembly::LW(string instruction)
{
    string d_instr = "LW";
    d_instr += " ";

    string base = MipsDisassembly::getRegister(instruction.substr(6, 5));
    string rt = MipsDisassembly::getRegister(instruction.substr(11, 5));
    string offset = MipsDisassembly::getAssemblyOffsetValue(instruction.substr(16, 16), false);

    d_instr += rt;
    d_instr += ", ";
    d_instr += offset;
    d_instr += "(";
    d_instr += base;
    d_instr += ")";

    return d_instr;
}

string CategoryOneDisassembly::SLL(string instruction)
{
    string d_instr = "SLL";
    d_instr += " ";

    string sa = MipsDisassembly::getAssemblyOffsetValue(instruction.substr(21, 5), false);
    string rt = MipsDisassembly::getRegister(instruction.substr(11, 5));
    string rd = MipsDisassembly::getRegister(instruction.substr(16, 5));

    d_instr += rd;
    d_instr += ", ";
    d_instr += rt;
    d_instr += ", ";
    d_instr += "#";
    d_instr += sa;

    return d_instr;
}

string CategoryOneDisassembly::SRL(string instruction)
{
    string d_instr = "SRL";
    d_instr += " ";

    string sa = MipsDisassembly::getAssemblyOffsetValue(instruction.substr(21, 5), false);
    string rd = MipsDisassembly::getRegister(instruction.substr(11, 5));
    string rt = MipsDisassembly::getRegister(instruction.substr(16, 5));

    d_instr += rt;
    d_instr += ", ";
    d_instr += rd;
    d_instr += ", ";
    d_instr += "#";
    d_instr += sa;

    return d_instr;
}

string CategoryOneDisassembly::SRA(string instruction)
{
    string d_instr = "SRA";
    d_instr += " ";

    string sa = MipsDisassembly::getAssemblyOffsetValue(instruction.substr(21, 5), false);
    string rd = MipsDisassembly::getRegister(instruction.substr(11, 5));
    string rt = MipsDisassembly::getRegister(instruction.substr(16, 5));

    d_instr += rt;
    d_instr += ", ";
    d_instr += rd;
    d_instr += ", ";
    d_instr += "#";
    d_instr += sa;

    return d_instr;
}

string CategoryOneDisassembly::NOP(string instruction)
{
    string d_instr = "NOP";

    return d_instr;
}

class CategoryTwoDisassembly
{
    public:
        static vector<string> registerOnlyOps;
        static vector<string> nonRegisterOps;

        static string RegisterOnlyOps(string instruction, string op);
        static string NonRegisterOps(string instruction, string op);
        static string Disassembly(string instruction, string op);
};

vector<string> CategoryTwoDisassembly::registerOnlyOps = {"ADD", "SUB", "MUL", "AND", "OR", "XOR", "NOR", "SLT"};
vector<string> CategoryTwoDisassembly::nonRegisterOps = {"ADDI", "ANDI", "ORI", "XORI"};

string CategoryTwoDisassembly::Disassembly(string instruction, string op)
{
    if (count(registerOnlyOps.begin(), registerOnlyOps.end(), op))
    {
        return RegisterOnlyOps(instruction, op);
    }
    else
    {
        return NonRegisterOps(instruction, op);
    }
    
}
string CategoryTwoDisassembly::RegisterOnlyOps(string instruction, string op)
{
    string d_instr(op);
    d_instr += " ";

    string rs = MipsDisassembly::getRegister(instruction.substr(6, 5));
    string rt = MipsDisassembly::getRegister(instruction.substr(11, 5));
    string rd = MipsDisassembly::getRegister(instruction.substr(16, 5));

    d_instr += rd;
    d_instr += ", ";

    d_instr += rs;
    d_instr += ", ";

    d_instr += rt;

    return d_instr;
}

string CategoryTwoDisassembly::NonRegisterOps(string instruction, string op)
{
    string d_instr(op);
    d_instr += " ";

    string rs = MipsDisassembly::getRegister(instruction.substr(6, 5));
    string rt = MipsDisassembly::getRegister(instruction.substr(11, 5));
    string imm = MipsDisassembly::getAssemblyOffsetValue(instruction.substr(16, 16), false);

    d_instr += rt;
    d_instr += ", ";

    d_instr += rs;
    d_instr += ", #";

    d_instr += imm;

    return d_instr;
}


class Disassembler
{
private:
    bool break_ins_read = false;
    vector<string> instructions;
    void Init();
    void fillCategoryOneIdentificationBitsMap();
    void fillCategoryTwoIdentificationBitsMap();

public:

    map<string, string> catOneOpcodeMap; // category 1 instructions format
    map<string, string> catTwoOpcodeMap; // category 2 instructions format
    
    vector<string> asm_instructions; // store decoded instructions, will be needed in simulation

    Disassembler(vector<string> instructions);
    
    Category getCategory(string bits);
    string DisassembleCatOne(string instruction);
    string DisassembleCatTwo(string instruction);
    string DisassembleTwosComp(string instruction);
    string Disassembly(string instruction);
    void Disassembly();

    ~Disassembler();
};

void Disassembler::Disassembly()
{
    cout << "Disassembly started" << endl;
    ofstream outFile("disassembly.txt");
    outFile.open("disassembly.txt", ios::out);
    if (outFile.is_open())
    {
        int counter = 256;
        for (auto asm_ins : instructions)
        {
            asm_ins.erase(std::remove(asm_ins.begin(), asm_ins.end(), '\r'), asm_ins.end());
            string dasm_ins = asm_ins;
            dasm_ins += "\t";
            dasm_ins += to_string(counter);
            dasm_ins += "\t";
            string dasm_t = Disassembly(asm_ins);
            dasm_ins += dasm_t;
            if ((!break_ins_read) && dasm_t.find("BREAK") != string::npos)
            {
                break_ins_read = true;
            }
            asm_instructions.push_back(dasm_t);
            //outFile << dasm_ins << endl;
            counter += 4;
        }
    }
    cout << "Disassembly complete" << endl;
}

void Disassembler::fillCategoryOneIdentificationBitsMap()
{
    catOneOpcodeMap["0000"] = "J";
    catOneOpcodeMap["0001"] = "JR";
    catOneOpcodeMap["0010"] = "BEQ";
    catOneOpcodeMap["0011"] = "BLTZ";
    catOneOpcodeMap["0100"] = "BGTZ";
    catOneOpcodeMap["0101"] = "BREAK";
    catOneOpcodeMap["0110"] = "SW";
    catOneOpcodeMap["0111"] = "LW";
    catOneOpcodeMap["1000"] = "SLL";
    catOneOpcodeMap["1001"] = "SRL";
    catOneOpcodeMap["1010"] = "SRA";
    catOneOpcodeMap["1011"] = "NOP";
}

void Disassembler::fillCategoryTwoIdentificationBitsMap()
{
    catTwoOpcodeMap["0000"] = "ADD";
    catTwoOpcodeMap["0001"] = "SUB";
    catTwoOpcodeMap["0010"] = "MUL";
    catTwoOpcodeMap["0011"] = "AND";
    catTwoOpcodeMap["0100"] = "OR";
    catTwoOpcodeMap["0101"] = "XOR";
    catTwoOpcodeMap["0110"] = "NOR";
    catTwoOpcodeMap["0111"] = "SLT";
    catTwoOpcodeMap["1000"] = "ADDI";
    catTwoOpcodeMap["1001"] = "ANDI";
    catTwoOpcodeMap["1010"] = "ORI";
    catTwoOpcodeMap["1011"] = "XORI";
}

void Disassembler::Init()
{
    // Category 1
    fillCategoryOneIdentificationBitsMap();

    // category 2
    fillCategoryTwoIdentificationBitsMap();

}

Disassembler::Disassembler(vector<string> instructions)
{
    this->instructions = instructions;
    Init();
}

Category Disassembler::getCategory(string instruction)
{
    if (break_ins_read)
    {
        return Category::twos_complement;
    }
    
    string lsb = instruction.substr(0, 2);

    if (lsb.compare("11") == 0)
    {
        return Category::two;
    }
    else if (lsb.compare("01") == 0)
    {
        return Category::one;
    }
    throw invalid_argument("is not a valid least significant bits");
}

string Disassembler::Disassembly(string instruction)
{
    int len = instruction.length();
    if (len != 32)
    {
        __throw_invalid_argument("invalid instruction length");
    }
    
    Category cat = getCategory(instruction);
    string dasm_ins;
    if (cat == Category::one)
    {
        dasm_ins = DisassembleCatOne(instruction);
    }
    else if(cat == Category::two)
    {
        dasm_ins = DisassembleCatTwo(instruction);
    }
    else
    {
        dasm_ins = DisassembleTwosComp(instruction);
    }

    return dasm_ins;
}

string Disassembler::DisassembleCatOne(string instruction)
{
    string opCode = instruction.substr(2, 4);
    CategoryOneDisassembly cat_one_dasm;
    string asm_ins;

    if (catOneOpcodeMap[opCode] == "J")
    {
        asm_ins = cat_one_dasm.J(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "JR")
    {
        asm_ins = cat_one_dasm.JR(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "BEQ")
    {
        asm_ins = cat_one_dasm.BEQ(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "BLTZ")
    {
        asm_ins = cat_one_dasm.BLTZ(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "BGTZ")
    {
        asm_ins = cat_one_dasm.BGTZ(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "BREAK")
    {
        asm_ins = cat_one_dasm.BREAK(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "SW")
    {
        asm_ins = cat_one_dasm.SW(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "LW")
    {
        asm_ins = cat_one_dasm.LW(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "SLL")
    {
        asm_ins = cat_one_dasm.SLL(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "SRL")
    {
        asm_ins = cat_one_dasm.SRL(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "SRA")
    {
        asm_ins = cat_one_dasm.SRA(instruction);
    }
    else if (catOneOpcodeMap[opCode] == "NOP")
    {
        asm_ins = cat_one_dasm.NOP(instruction);
    }
    return asm_ins;
}

string Disassembler::DisassembleCatTwo(string instruction)
{
    string opCode = instruction.substr(2, 4);
    CategoryTwoDisassembly cat_two_dasm;
    string asm_ins;

    asm_ins = cat_two_dasm.Disassembly(instruction, catTwoOpcodeMap[opCode]);
    return asm_ins;
}

string Disassembler::DisassembleTwosComp(string instruction)
{
    bitset<32> b(instruction);
    string flipped = b.flip().to_string();
    char *ptr;
    int num = std::strtol(flipped.c_str(), &ptr, 2);
    num *= (-1);
    num += -1;
    return to_string(num);
}

Disassembler::~Disassembler()
{
}

class PipeliineUtility
{
private:
    const static inline vector<string> branch_ins = {"J", "JR", "BEQ", "BLTZ", "BGTZ"};  
public:
    static bool IsBranchInstruction(string instruction)
    {
        for (auto s: branch_ins)
        {
            if (instruction.find(s) != string::npos)
            {
                return 1;
            }
        }
        return 0;
    }
    static vector<string> SplitString(string instruction)
    {
        std::vector<std::string> result;
        std::stringstream ss(instruction);
        std::string token;

        while (std::getline(ss, token, ' ')) {
            std::string clean_token;
            for (const auto& c : token) {
                if (std::isalnum(c)) {
                    clean_token += c;
                }
            }
            result.push_back(clean_token);
        }

        return result;
    }

    static bool IsLoadOrStore(string instruction)
    {
        if (instruction.find("LW")!= string::npos ||
            instruction.find("SW") != string::npos)
        {
            return 1;
        }
        return 0;
    }
};

struct Register
{
    bool busy = false;
    int val;
};

class FetchUnit
{
    public:
        string WaitingInstruction;
        string ExecutedInstruction;
        bool Stalled = false;
        bool CanFetch(deque<string> pre_issue_queue)
        {
            if (!Stalled && pre_issue_queue.size() < 4)
            {
                return true;
            }
            return false;
        }
        void Stall(string instruction, deque<string> pre_issue_queue)
        {
            if (PipeliineUtility::IsBranchInstruction(instruction) ||
                    pre_issue_queue.size() >= 4)
            {
                Stalled = true;
            }
            else
            {
                Stalled = false;
            }
        }
        void PrintStatus(ofstream &outFile)
        {
            outFile << "IF Unit:" << endl;
            outFile << "\t" << "Waiting:" << WaitingInstruction << endl;
            outFile << "\t" << "Executed:" << ExecutedInstruction << endl;

        }
};

class Simulation
{
private:
    vector<string> asm_instructions;
    
    vector<int> registers = vector<int>( 32, 0 );
    vector<Register> registerFile;

    int pc = 256; // program counter
    int cycle = 1;

    deque<string> pre_issue_q;
    
    deque<string> pre__alu1_q;
    deque<string> pre__alu2_q;
    deque<string> post__alu2_q;

    deque<string> pre_mem_q;
    deque<string> post_mem_q;

    FetchUnit fetch_unit;

    int current_instruction_idx;

    void StartSimulation();
    void StartSimulation(ofstream& outFile);
    void ExecuteCycle(ofstream& outFile);
    void AddToPreIssue();
    bool isNumber(const std::string& str)
    {
        for (const auto& c : str) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    int extractNumber(const std::string& str)
    {
        std::string numStr;

        for (const auto& c : str) {
            if (std::isdigit(c)) {
                numStr += c;
            }
        }

        return std::stoi(numStr);
    }
    void Decode(string ins)
    {
        vector<string> comps = PipeliineUtility::SplitString(ins);
        string opcode = comps[0];

        // seperate operands from opcode
        vector<string> ops(comps.begin() + 1, comps.end());
        
        string op1 = comps[1];  //register
        string op2;             // register or immediate
        if (comps.size() >= 2)
        {
            op2 = comps[2];
        }
        bool reg_ready = true;
        //if (PipeliineUtility::IsBranchInstruction(opcode))
        //{
            // check if registers are ready
            for (auto op : ops)
            {
                if (reg_ready)
                {
                    if (!isNumber(op))
                    {
                        int reg = extractNumber(op);
                        if (registerFile[reg].busy)
                        {
                            reg_ready = false;
                        }
                    }
                }
            }
        //}
        if (!reg_ready)
        {
            fetch_unit.Stalled = true;
        }
    }
    void PrintFetchUnit(ofstream &outFile)
    {
        outFile << "IF Unit: " << endl;
        outFile << "\t" << "Waiting: " << fetch_unit.WaitingInstruction << endl;
        outFile << "\t" << "Executing: " << fetch_unit.ExecutedInstruction << endl;
    }
    
    void PrintPreIssueQueue(ofstream &outFile)
    {
        // can't have fixed size queue in c++
        int counter = 0;
        outFile << "Pre-Issue Queue:" << endl;
        for (int i = 4; i >= 1; i--)
        {
            if (pre_issue_q.size() >= i)
            {
                outFile <<  "\t" << "Entry " << to_string(counter) <<  ": [" << pre_issue_q[i - 1] << "]" << endl;
            }
            counter++;
        }
        
        // if (pre_issue_q.size() >= 4)
        // {
        //     outFile <<  "\t" << "Entry " << to_string(counter) <<  ": " << pre_issue_q[3] << endl;
        // }
        // if (pre_issue_q.size() >= 3)
        // {
        //     outFile <<  "\t" << "Entry " << to_string(counter) <<  ": " << pre_issue_q[2] << endl;
        // }
        // if (pre_issue_q.size() >= 2)
        // {
        //     outFile <<  "\t" << "Entry " << to_string(counter) <<  ": " << pre_issue_q[1] << endl;
        // }
        // if (pre_issue_q.size() == 3)
        // {
        //     outFile <<  "\t" << "Entry " << to_string(counter) <<  ": " << pre_issue_q[0] << endl;
        // }
        // outFile << "\t" << "Entry 1: " << pre_issue_q[2] << endl;
        // outFile << "\t" << "Entry 2: " << pre_issue_q[1] << endl;
        // outFile << "\t" << "Entry 3: " << pre_issue_q[0] << endl;
    }

    void PrintPreALU1Queue(ofstream &outFile)
    {
        int counter = 0;
        outFile << "Pre-ALU1 Queue:" << endl;
        for (int i = 2; i >= 1; i--)
        {
            if (pre__alu1_q.size() >= i)
            {
                outFile << "\t" << "Entry " << counter << ": " << "[" << pre__alu1_q[i - 1] << "]" << endl;
                counter++;
            }
            
        }
    }

    void PrintPreALU2Queue(ofstream &outFile)
    {
        outFile << "Pre-ALU1 Queue:" << endl;
        int counter = 0;
        for (int i = 2; i >= 1; i--)
        {
            if (pre__alu2_q.size() >= i)
            {
                outFile << "\t" << "Entry " << counter << ": " << "[" << pre__alu2_q[i - 1] << "]" << endl;
                counter++;
            }
        }
        // outFile << "\t" << "Entry 0: " << post__alu2_q[1] << endl;
        // outFile << "\t" <<  "Entry 1" << post__alu2_q[0] << endl;
    }

    void PrintPreMemQueue(ofstream &outFile)
    {
        string to_print = pre_mem_q.size() > 0 ? pre_mem_q[0] : "";
        outFile << "Pre-MEM Queue: " << "[" << to_print << "]" << endl;
    }

    void PrintPostMemQueue(ofstream &outFile)
    {
        string to_print = post_mem_q.size() > 0 ? post_mem_q[0] : "";
        outFile << "Post-MEM Queue: " << "[" << to_print << "]" << endl;
    }

    void PrintPostALU2Queue(ofstream &outFile)
    {
        string to_print = post__alu2_q.size() > 0 ? post__alu2_q[0] : "";
        outFile << "Post-MEM Queue: " << "[" << to_print << "]" << endl;
    }

    void PrintRegisters(ofstream& outFile)
    {
        stringstream line2;
        outFile << endl;
        outFile << "Registers" << endl;
        outFile << "R00:\t" << registerFile[0].val << "\t" << registerFile[1].val << "\t" << registerFile[2].val << "\t" << registerFile[3].val << "\t" << registerFile[4].val << "\t" << registerFile[5].val << "\t" << registerFile[6].val << "\t" << registerFile[7].val << endl;
        outFile << "R08:\t" << registerFile[8].val << "\t" << registerFile[9].val << "\t" << registerFile[10].val << "\t" << registerFile[11].val << "\t" << registerFile[12].val << "\t" << registerFile[13].val << "\t" << registerFile[14].val << "\t" << registerFile[15].val << endl;
        outFile << "R16:\t" << registerFile[16].val << "\t" << registerFile[17].val << "\t" << registerFile[18].val << "\t" << registerFile[19].val << "\t" << registerFile[20].val << "\t" << registerFile[21].val << "\t" << registerFile[22].val << "\t" << registerFile[23].val << endl;
        outFile << "R24:\t" << registerFile[24].val << "\t" << registerFile[25].val << "\t" << registerFile[26].val << "\t" << registerFile[27].val << "\t" << registerFile[28].val << "\t" << registerFile[29].val << "\t" << registerFile[30].val << "\t" << registerFile[31].val << endl;
        outFile << endl;
        outFile << "Data" << endl;
        string d_line1 = "300:	-1	-2	-3	1	2	4	-4	10";
        string d_line2 = "332:	7	9	1	0	-1	1	-1	0";
        outFile << d_line1 << endl;
        outFile << d_line2 << endl;
        outFile << endl;
    }

    void PrintCycleInfo(ofstream &outFile)
    {
        outFile << __hyphens__ << endl;
        string line = "Cycle ";
        line.append(to_string(cycle)).append(":");
        outFile << line << endl;
        outFile << endl;

        PrintFetchUnit(outFile);
        PrintPreIssueQueue(outFile);
        PrintPreALU1Queue(outFile);
        PrintPreMemQueue(outFile);
        PrintPostMemQueue(outFile);
        PrintPreALU2Queue(outFile);
        PrintPostALU2Queue(outFile);

        PrintRegisters(outFile);
    }

public:
    Simulation(vector<string> instructions);
    ~Simulation();
};

void Simulation::AddToPreIssue()
{
    if (pre_issue_q.size() < 4)
    {
        pre_issue_q.push_back(asm_instructions[current_instruction_idx]);
    }
    else
    {
        current_instruction_idx--;
    }
    
}
Simulation::Simulation(vector<string> instructions) : registers(32,0)
{
    registerFile.reserve(32);
    for (int i = 0; i < 32; i++)
    {
        registerFile[0].val = 0;
    }
    
    asm_instructions = instructions;
    current_instruction_idx = 0;
    //registers.reserve(32);
    //vector<int> v(32, 0);
    //registers = v;
    StartSimulation();
}

void Simulation::StartSimulation()
{
    ofstream outFile("simulation.txt");
    if (outFile.is_open())
    {
        StartSimulation(outFile);
    }
}

void Simulation::StartSimulation(ofstream& outFile)
{
    current_instruction_idx = 0;
    while (1)
    {
        ExecuteCycle(outFile);
    }
}
void Simulation::ExecuteCycle(ofstream& outFile)
{
        // mem
    if (!pre_mem_q.empty())
    {
        string mem_ins = pre_mem_q.front();
        if (mem_ins.find("LW") != string::npos)
        {
            post_mem_q.push_back(mem_ins);
        }
        pre_mem_q.pop_front();
    }

        // alu1: sends from pre-alu1 -> pre-mem
    if (!pre__alu1_q.empty())
    {
        string mem_ins = pre__alu1_q.front();
        pre_mem_q.push_back(mem_ins);
        pre__alu1_q.pop_front();
    }

    // alu 2: sends to post alu2 queue
    if (!post__alu2_q.empty())
    {
        string alu2_ins = pre__alu2_q.front();
        post__alu2_q.push_back(alu2_ins);
        pre__alu2_q.pop_front();
    }

        // issue: sends ins to alu1 & alu2
    int issue_counter = 0;
    bool lw_sw_done = false;
    bool non_lwsw_done = false;
    while (!pre_issue_q.empty() && issue_counter < 2)
    {
        string l_ins = pre_issue_q.front();
        if (!lw_sw_done && PipeliineUtility::IsLoadOrStore(l_ins))
        {
            pre__alu1_q.push_back(l_ins);
            lw_sw_done = true;
            issue_counter++;
            pre_issue_q.pop_front();
        }
        else if ((!non_lwsw_done) && (!PipeliineUtility::IsLoadOrStore(l_ins)))
        {
            pre__alu2_q.push_back(l_ins);
            non_lwsw_done = true;
            issue_counter++;
            pre_issue_q.pop_front();
        }
    }

    vector<string> fetched_ins;
    fetched_ins.reserve(2);

    string ins_to_fetch = asm_instructions[current_instruction_idx];
    if (ins_to_fetch.compare("BREAK") == 0)
    {
        fetch_unit.ExecutedInstruction = ins_to_fetch;
        PrintCycleInfo(outFile);
        return;
    }

    // fetch - #1
    if (fetch_unit.CanFetch(pre_issue_q))
    {
        fetched_ins.push_back(asm_instructions[current_instruction_idx]);
        current_instruction_idx++;
    }
    // fetch - #2
    if (fetch_unit.CanFetch(pre_issue_q))
    {
        fetched_ins.push_back(asm_instructions[current_instruction_idx]);
        current_instruction_idx++;
    }
    // if 1st is branch, then discard the rest
    if (PipeliineUtility::IsBranchInstruction(fetched_ins[0]))
    {
        fetched_ins.pop_back();
        current_instruction_idx--;
        /* code */
    }
    // decode
    for (auto ii: fetched_ins)
    {
        if (PipeliineUtility::IsBranchInstruction(ii))
        {
            Decode(ii);
            if (!fetch_unit.Stalled)
            {
                fetch_unit.ExecutedInstruction = ii;
                pc += 4;
            }
            else
            {
                fetch_unit.WaitingInstruction = ii;
            }
        }
        else
        {
            AddToPreIssue();
        }
    }

    PrintCycleInfo(outFile);
    fetched_ins.clear();
}

Simulation::~Simulation()
{
}

int main(int argc, char *argv[])
{
    string input_file = argv[1];
    InputReader in_reader(input_file);
    
    Disassembler dasm(in_reader.instructions);
    dasm.Disassembly();
    
    Simulation pipeline(dasm.asm_instructions);

    return 0;
}