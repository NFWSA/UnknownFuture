#include <iostream>
#include <string>
#include "SNStateMachine/StateMachine.h"

using namespace std;
using namespace SurgeNight;

template<typename OP, typename MACHINE>
void transMachine(const OP &op, MACHINE &machine)
{
    cout << "++++ state: >" << machine << "<\t" << op << " " << machine(op) << "\t>" << machine << "< ++++" << endl;
}

int main()
{
    {
        StateMachine<string, string> machine = { "ready", "runing", "suspend", "end" };
        machine.addTransTable("ready", {{"select", "runing"}});
        machine.addTransTable("runing", {{"timeout", "ready"}, {"backside", "suspend"}, {"terminate", "end"}});
        machine.addTransTable("suspend", {{"frontside", "ready"}, {"kill", "end"}});
        machine.addTransTable("end", {{"restart", "ready"}});
        cout << "--------- state: >" << machine << "< -----------" << endl;
        auto transMachinne = [](string x, StateMachine<string, string> y) {
                transMachine<string, StateMachine<string, string>>(x, y);
        };
        transMachine("select", machine);
        transMachine("timeout", machine);
        transMachine("select", machine);
        transMachine("backside", machine);
        transMachine("frontside", machine);
        transMachine("select", machine);
        transMachine("terminate", machine);
        transMachine("restart", machine);
        transMachine("select", machine);
        transMachine("backside", machine);
        transMachine("kill", machine);
        transMachine("select", machine);
        transMachine("restart", machine);
        transMachine("timeout", machine);
        transMachine("????", machine);
    }
    enum PERSON_ST { ID_STOP, ID_WALK, ID_RUN, ID_JUMP, ID_JUMPWALK, ID_JUMPRUN };
    enum PERSON_OP { OP_WALK, OP_RUN, OP_JUMP, OP_STOP, OP_FALL };
    {
        StateMachine<int, int> machine = { ID_STOP, ID_WALK, ID_RUN, ID_JUMP, ID_JUMPWALK, ID_JUMPRUN };
        machine.addTransTable(ID_STOP, {{OP_WALK, ID_WALK}, {OP_RUN, ID_RUN}, {OP_JUMP, ID_JUMP}});
        machine.addTransTable(ID_WALK, {{OP_RUN, ID_RUN}, {OP_JUMP, ID_JUMPWALK}, {OP_STOP, ID_STOP}});
        machine.addTransTable(ID_RUN, {{OP_WALK, ID_WALK}, {OP_JUMP, ID_JUMPRUN}, {OP_STOP, ID_STOP}});
        machine.addTransTable(ID_JUMP, {{OP_WALK, ID_JUMPWALK}, {OP_RUN, ID_JUMPRUN}, {OP_FALL, ID_STOP}});
        machine.addTransTable(ID_JUMPWALK, {{OP_RUN, ID_JUMPRUN}, {OP_STOP, ID_JUMP}, {OP_FALL, ID_WALK}});
        machine.addTransTable(ID_JUMPRUN, {{OP_WALK, ID_JUMPWALK}, {OP_STOP, ID_JUMP}, {OP_FALL, ID_RUN}});
        cout << "--------- state: >" << machine << "< -----------" << endl;
        auto transMachinne = [](int x, StateMachine<int, int> y) {
                transMachine<int, StateMachine<int, int>>(x, y);
        };
        transMachine(OP_WALK, machine);
        transMachine(OP_JUMP, machine);
        transMachine(OP_FALL, machine);
        transMachine(OP_RUN, machine);
        transMachine(OP_JUMP, machine);
        transMachine(OP_WALK, machine);
        transMachine(OP_STOP, machine);
        transMachine(OP_FALL, machine);
        transMachine(OP_JUMP, machine);
        transMachine(OP_RUN, machine);
        transMachine(OP_JUMP, machine);
        transMachine(OP_FALL, machine);
        transMachine(OP_STOP, machine);
        transMachine(OP_FALL, machine);
        transMachine(56, machine);
    }
    return 0;
}
