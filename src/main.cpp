#include "defines.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    auto rom = ROM();
    auto ram = RAM();
    auto cpu = CPU();

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename.s>" << endl;
        exit(1);
    }

    string fileName = argv[1];
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Can't open file " << fileName << endl;
        exit(1);
    }

    string line;
    uint8_t out[3] = {0x00, 0x00, 0x00};
    while (getline(file, line)) {
        if (line == "\n" || line == "\r" || line.starts_with("\n") || line.starts_with("\r")) {
            continue;
        }
        cpu.parse(line, out);
        for (uint8_t b : out)
            cout << "0x" << uppercase << setfill('0') << setw(2) << hex << static_cast<int>(b) << " ";

        auto inst = static_cast<uint4_t>(out[0]);
        auto data = out[1];
        auto RS = static_cast<uint3_t>(out[2]);

        cpu.compile(inst, data, RS, rom);
        cout << endl;
    }

    cout << endl << "ROM:" << endl << rom << endl;
    cpu.run(rom, ram);
    cout << "RAM:" << endl << ram << endl;

    file.close();
    return 0;
}