#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

const int CYLINDERS = 5000;
const int REQUESTS = 1000;

// ====================== FCFS ======================
pair<int, vector<int>> fcfs(int head, const vector<int>& req) {
    int movement = 0;
    int current = head;
    vector<int> path;
    path.push_back(current);

    for (int r : req) {
        movement += abs(r - current);
        current = r;
        path.push_back(current);
    }
    return {movement, path};
}

// ====================== SCAN ======================
pair<int, vector<int>> scan(int head, const vector<int>& req) {
    int movement = 0;
    int current = head;
    vector<int> path;
    path.push_back(current);

    vector<int> left, right;

    for (int r : req) {
        if (r >= head) right.push_back(r);
        else left.push_back(r);
    }

    sort(right.begin(), right.end());
    sort(left.begin(), left.end(), greater<int>());

    for (int r : right) {
        movement += abs(r - current);
        current = r;
        path.push_back(current);
    }

    movement += abs(4999 - current);
    current = 4999;
    path.push_back(current);

    for (int r : left) {
        movement += abs(current - r);
        current = r;
        path.push_back(current);
    }

    return {movement, path};
}

// ====================== C-SCAN ======================
pair<int, vector<int>> cscan(int head, const vector<int>& req) {
    int movement = 0;
    int current = head;
    vector<int> path;
    path.push_back(current);

    vector<int> left, right;

    for (int r : req) {
        if (r >= head) right.push_back(r);
        else left.push_back(r);
    }

    sort(right.begin(), right.end());
    sort(left.begin(), left.end());

    for (int r : right) {
        movement += abs(r - current);
        current = r;
        path.push_back(current);
    }

    movement += abs(4999 - current);
    current = 4999;
    path.push_back(current);

    movement += 4999;
    current = 0;
    path.push_back(current);

    for (int r : left) {
        movement += abs(r - current);
        current = r;
        path.push_back(current);
    }

    return {movement, path};
}

// ====================== WRITE CSV ======================
void write_csv(const string& filename, const vector<int>& data) {
    ofstream file(filename);
    for (int x : data) file << x << "\n";
    file.close();
}

// ====================== MAIN ======================
int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "USO: disk.exe <posicion_inicial>\n";
        return 1;
    }

    int head = atoi(argv[1]);

    srand(time(NULL));

    vector<int> requests;
    requests.reserve(REQUESTS);

    for (int i = 0; i < REQUESTS; i++)
        requests.push_back(rand() % CYLINDERS);

    auto [mov_fcfs, path_fcfs] = fcfs(head, requests);
    auto [mov_scan, path_scan] = scan(head, requests);
    auto [mov_cscan, path_cscan] = cscan(head, requests);

    cout << "=== DISK SCHEDULING SIMULATOR ===\n";
    cout << "FCFS movimiento: " << mov_fcfs << "\n";
    cout << "SCAN movimiento: " << mov_scan << "\n";
    cout << "C-SCAN movimiento: " << mov_cscan << "\n";

    write_csv("fcfs_path.csv", path_fcfs);
    write_csv("scan_path.csv", path_scan);
    write_csv("cscan_path.csv", path_cscan);

    ofstream results("resultados.csv");
    results << mov_fcfs << "\n" << mov_scan << "\n" << mov_cscan << "\n";
    results.close();

    // ===== Ejecutar Python automáticamente =====
    system("python generate_graphs.py");

    return 0;
}
