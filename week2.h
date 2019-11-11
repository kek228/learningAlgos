#pragma once

// задача о расписании pair->first: deadline pair->second: price
struct Task {
    Task(int deadline, int price) : _deadline(deadline), _price(price) {}

    int _deadline;
    int _price;
};

size_t scheduleTask(vector <Task> &tasks) {
    vector<bool> usedDates(tasks.size(), false);
    size_t res = 0;
    sort(tasks.begin(), tasks.end(), [](Task &l, Task &r) { return l._price > r._price; });
    for (auto &t: tasks) {
        int index = t._deadline - 1;
        while (index >= 0 && usedDates[index]) {
            --index;
        }
        if (index >= 0) {
            usedDates[index] = true;
            res += t._price;
        }
    }
    return res;
}

// код парсинга файлика
int main() {
    vector <Task> tasks;
    std::ifstream infile("/Users/nikita/CLionProjects/ALGOS/test.txt");
    string input;
    getline(infile, input);
    int n = stoi(input);
    while (n > 0) {
        getline(infile, input);
        vector<int> oneApp = split(input);
        tasks.emplace_back(oneApp[0], oneApp[1]);
        --n;
    }
    cout << scheduleTask(tasks);
    return 0;
}

struct Application {

    Application(int b, int e) : _b(b), _e(e) {}

    int _b;
    int _e;
};

int maxApplications(vector <Application> &applications) {
    sort(applications.begin(), applications.end(),
         [](const Application &f, const Application &s) { return f._e < s._e; });
    int res = 1;
    Application &prev = applications[0];
    for (size_t i = 1; i < applications.size(); ++i) {
        if (applications[i]._b >= prev._e) {
            ++res;
            prev = applications[i];
        }
    }
    return res;
}

int minPetrol(int dst, int cap, vector<int> &petrols) {
    petrols.push_back(dst);
    int res = 0;
    int fuelLeft = cap - petrols[0];
    for (int i = 0; i < petrols.size() - 1; ++i) {
        int delta = petrols[i + 1] - petrols[i];
        if (fuelLeft < delta) {
            fuelLeft = cap - delta;
            ++res;
        } else
            fuelLeft -= delta;
    }
    return res;
}
