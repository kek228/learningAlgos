#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iterator>
#include <set>
//#include <optional>
#include <stdint.h>
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <functional>

using namespace std;


u_int16_t toMask(unordered_map<string, int> &ids, const vector<string> &skills) {
    u_int16_t res = 0;
    for (const auto &skill: skills) {
        int id = ids[skill];
        res |= 1 << id;
    }
    return res;
}

vector<int> smallestSufficientTeam(vector<string> &req_skills, vector<vector<string>> &people) {
    int size = req_skills.size();
    if (!size)
        return {};

    u_int16_t trg = 0;
    for (int i = 0; i < size; ++i)
        trg |= 1 << i;

    unordered_map<string, int> ids;
    for (int i = 0; i < req_skills.size(); ++i) {
        ids[req_skills[i]] = i;
    }
    vector<u_int16_t> masks;
    for (const auto &skills: people) {
        u_int16_t mask = toMask(ids, skills);
        masks.push_back(mask);
    }

    int ressize = numeric_limits<int>::max();
    vector<int> res;
    unordered_map<u_int16_t, vector<int>> skillsToTeams;
    for (int i = 0; i < masks.size(); ++i) {
        if (masks[i] == 0)
            continue;
        if (masks[i] == trg)
            return {i};

        auto sameSkillsTeam = skillsToTeams.find(masks[i]);
        if (sameSkillsTeam == skillsToTeams.end()) {
            skillsToTeams[masks[i]] = {i};
        } else {
            if (sameSkillsTeam->second.size() != 1) {
                sameSkillsTeam->second = {i};
            }
        }

        for (auto &skillTeam: skillsToTeams) {
            uint16_t newSkills = skillTeam.first | masks[i];
            if (newSkills != skillTeam.first) {
                sameSkillsTeam = skillsToTeams.find(newSkills);
                // если такого набора скилов еще нет
                if (sameSkillsTeam == skillsToTeams.end()) {
                    auto newTeam = skillTeam.second;
                    newTeam.push_back(i);
                    skillsToTeams[newSkills] = newTeam;
                    if (newSkills == trg) {
                        if (newTeam.size() < ressize) {
                            ressize = newTeam.size();
                            res = newTeam;
                        }
                    }
                }
                    // если есть
                else {
                    if (sameSkillsTeam->second.size() > skillTeam.second.size() + 1) {
                        sameSkillsTeam->second = skillTeam.second;
                        sameSkillsTeam->second.push_back(i);
                        if (sameSkillsTeam->first == trg && sameSkillsTeam->second.size() < ressize) {
                            ressize = sameSkillsTeam->second.size();
                            res = sameSkillsTeam->second;
                        }
                    }
                }
            }
        }
    }
    return res;
}

int main() {
//    vector<string> req_skills = {"java", "nodejs", "reactjs"};
//    vector<vector<string>> people = {{"java"}, {"nodejs"}, {"nodejs", "reactjs"}};

//    vector<string> req_skills = {"algorithms","math","java","reactjs","csharp","aws"};
//    vector<vector<string>> people = {{"algorithms","math","java"},
//                                     {"algorithms","math","reactjs"},
//                                     {"java","csharp","aws"},
//                                     {"reactjs","csharp"},
//                                     {"csharp","math"},
//                                     {"aws","java"}};

    vector<string> req_skills = {"hkyodbbhr", "p", "biflxurxdvb", "x", "qq", "yhiwcn"};

    vector<vector<string>> people = {{"yhiwcn"},
                                     {},
                                     {},
                                     {},
                                     {"biflxurxdvb", "yhiwcn"}, // 4
                                     {"hkyodbbhr"},
                                     {"hkyodbbhr",   "p"}, //
                                     {"hkyodbbhr"},
                                     {},
                                     {"yhiwcn"},
                                     {"hkyodbbhr",   "qq"},
                                     {"qq"},
                                     {"hkyodbbhr"},
                                     {"yhiwcn"},
                                     {},
                                     {"biflxurxdvb"},
                                     {},
                                     {"hkyodbbhr"},
                                     {"hkyodbbhr",   "yhiwcn"},
                                     {"yhiwcn"},
                                     {"hkyodbbhr"},
                                     {"hkyodbbhr",   "p"},
                                     {},
                                     {},
                                     {"hkyodbbhr"},
                                     {"biflxurxdvb"},
                                     {"qq",          "yhiwcn"},
                                     {"hkyodbbhr",   "yhiwcn"},
                                     {"hkyodbbhr"},
                                     {},
                                     {},
                                     {"hkyodbbhr"},
                                     {},
                                     {"yhiwcn"},
                                     {},
                                     {"hkyodbbhr"},
                                     {"yhiwcn"},
                                     {"yhiwcn"},
                                     {},
                                     {},
                                     {"hkyodbbhr",   "yhiwcn"},
                                     {"yhiwcn"},
                                     {"yhiwcn"},
                                     {},
                                     {},
                                     {},
                                     {"yhiwcn"},
                                     {},
                                     {"yhiwcn"},
                                     {"x"},
                                     {"hkyodbbhr"},
                                     {},
                                     {},
                                     {"yhiwcn"},
                                     {},
                                     {"biflxurxdvb"},
                                     {},
                                     {},
                                     {"hkyodbbhr",   "biflxurxdvb", "yhiwcn"},
                                     {}};

    auto res = smallestSufficientTeam(req_skills, people);
    for (auto n: res)
        cout << n << ' ';

    cout << endl;
    for (auto v:  people[4]) {
        cout << v.data() << ' ';
    }
    cout << endl;

    for (auto v:  people[6]) {
        cout << v.data() << ' ';
    }
    cout << endl;

    for (auto v:  people[10]) {
        cout << v.data() << ' ';
    }
    cout << endl;

    for (auto v:  people[49]) {
        cout << v.data() << ' ';
    }
    cout << endl;

    return 0;
}