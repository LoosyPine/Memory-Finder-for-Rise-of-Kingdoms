#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

DWORD GetProcessID(LPCWSTR gameName = L"templait");
unsigned long long FindStats(HANDLE& game_process, unsigned long long adr, const unsigned long long prev);
void FindMark(HANDLE& game_process, vector<unsigned long long>& vOutput);


int main()
{
    DWORD process_id  = GetProcessID(L"Rise of Kingdoms");
    HANDLE game_process = OpenProcess(PROCESS_ALL_ACCESS, true, process_id);
    vector<unsigned long long> output;
    FindMark(game_process, output);
    return 0;
}

DWORD GetProcessID(LPCWSTR gameName)
{
    HWND game_window = FindWindow(NULL, gameName);

    DWORD process_id = 0;
    GetWindowThreadProcessId(game_window, &process_id);

    return process_id;
}

unsigned long long FindStats(HANDLE& game_process, unsigned long long adr, const unsigned long long prev)
{
    unsigned long long result = 0;
    unsigned long long end_adr = adr - 0x8;
    DWORD bytes_read = 0;

    unsigned long long max = 0;
    for (unsigned long long int i = adr - 0x4A; i <= end_adr - 0x8; i += 0x1)
    {
        ReadProcessMemory(game_process, (void*)(i), &result, 8, (SIZE_T*)bytes_read);
        if (result > max && result < prev)
        {
            max = result;
        }
    }

    return max;
}

void FindMark(HANDLE& game_process, vector<unsigned long long>& vOutput)
{

    unsigned long long find_value = 0;
    DWORD bytes_read = 0;
    //Начальный адрес(ищем по топ 1 игрока в ЧитЕнжин)
    unsigned long long adress = 0x21C7DC48E10;
    //Вектор с байтами строки для ориентира в памяти
    vector<unsigned long long> vSequence = { 0x7B, 0x22, 0x61, 0x76, 0x61, 0x74, 0x61, 0x72 };
    //Предыдущее число(сначала равно оччкам топ1 + 1 )
    unsigned long long prev = 6245602073;
    //Основной цикл
    int i = 0;
    int pos = 1;
    while (pos <= 999)
    {
        //Читаем память по байтово
        ReadProcessMemory(game_process, (void*)(adress), &find_value, 1, (SIZE_T*)bytes_read);
        adress += 0x1;
        //Ищем наш ориентир
        if (find_value == vSequence[i])
            ++i;
        else
            i = 0;
        //Если нашли ориентир
        if (i == vSequence.size() - 1)
        {
            unsigned long long temp = 0;
            temp = FindStats(game_process, adress, prev);
            cout << pos << " FIND: " << temp << endl;
            ++pos;
            prev = temp;
            i = 0;
        }

    }
}
