#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class MissionManager {
private:
    string missionState;

public:
    MissionManager();
    void updateMission(string objectName, double confidence, double distance);
    string getMissionState();
};

int main() {
    string objectName;
    double confidence, distance;

    cout << "=== ORCA MISSION ===" << endl;

    cout << "INPUT Object : ";
    cin >> objectName;

    cout << "Confidence: ";
    cin >> confidence;

    cout << "Distance (m): ";
    cin >> distance;

    MissionManager manager;

    cout << endl;
    manager.updateMission(objectName, confidence, distance);

    return 0;
}

MissionManager::MissionManager() {
    missionState = "IDLE";
}

void MissionManager::updateMission(string objectName, double confidence, double distance) {
    cout << "OUTPUT :" << endl;

    if (objectName == "None" || objectName == "none") {
        missionState = "SEARCHING";

        cout << "Object detected : None" << endl;
        cout << "Mission State : " << missionState << endl;
        cout << "Action : SEARCH FOR TARGET" << endl;
        return;
    }

    cout << fixed << setprecision(2);

    cout << "Object detected : " << objectName << endl;
    cout << "Confidence : " << confidence << endl;
    cout << "Distance : " << distance << " m" << endl;

    if (confidence < 0.70) {
        missionState = "SEARCHING";
        cout << "\nMission State : " << missionState << endl;
        cout << "Action : SEARCH FOR TARGET" << endl;
    }
    else if (distance <= 0.5) {
        missionState = "MISSION_COMPLETE";
        cout << "\nMission State : " << missionState << endl;
        cout << "Action : MISSION COMPLETE" << endl;
    }
    else if (distance <= 2.0) {
        missionState = "APPROACHING";
        cout << "\nMission State : " << missionState << endl;
        cout << "Action : APPROACH TARGET" << endl;
    }
    else {
        missionState = "DETECTED";
        cout << "\nMission State : " << missionState << endl;
        cout << "Action : APPROACH TARGET" << endl;
    }
}

string MissionManager::getMissionState() {
    return missionState;
}