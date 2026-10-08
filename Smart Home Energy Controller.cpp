#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SmartHomeEnergyController {
private:
    double powerLimit;
    vector<string> appliances;
    vector<double> power;
    vector<bool> status;

public:
    SmartHomeEnergyController(double limit) {
        powerLimit = limit;
    }

    void addAppliance(string name, double powerRating) {
        appliances.push_back(name);
        power.push_back(powerRating);
        status.push_back(false);
    }

    void turnOn(int index) {
        if (index < 0 || index >= appliances.size()) {
            cout << "Invalid appliance number!" << endl;
            return;
        }

        double currentPower = getTotalPower();

        if (currentPower + power[index] <= powerLimit) {
            status[index] = true;
            cout << appliances[index] << " turned ON." << endl;
        } else {
            cout << "Cannot turn ON " << appliances[index] << "." << endl;
            cout << "Power limit would be exceeded!" << endl;
        }
    }

    void turnOff(int index) {
        if (index < 0 || index >= appliances.size()) {
            cout << "Invalid appliance number!" << endl;
            return;
        }

        status[index] = false;
        cout << appliances[index] << " turned OFF." << endl;
    }

    double getTotalPower() {
        double total = 0;

        for (int i = 0; i < appliances.size(); i++) {
            if (status[i]) {
                total += power[i];
            }
        }

        return total;
    }

    void displayStatus() {
        cout << "\n----- Smart Home Energy Controller -----" << endl;

        for (int i = 0; i < appliances.size(); i++) {
            cout << i + 1 << ". "
                 << appliances[i] << " - "
                 << power[i] << " W - ";

            if (status[i])
                cout << "ON";
            else
                cout << "OFF";

            cout << endl;
        }

        cout << "\nTotal Power Used : "
             << getTotalPower() << " W" << endl;

        cout << "Power Limit      : "
             << powerLimit << " W" << endl;

        if (getTotalPower() >= powerLimit) {
            cout << "Warning: Power limit reached!" << endl;
        } else {
            cout << "Status: Power consumption is within limit." << endl;
        }
    }
};

int main() {

    // Maximum allowed home power
    SmartHomeEnergyController home(2000);

    // Add appliances
    home.addAppliance("Fan", 75);
    home.addAppliance("Light", 20);
    home.addAppliance("Refrigerator", 300);
    home.addAppliance("TV", 120);
    home.addAppliance("Air Conditioner", 1500);
    home.addAppliance("Washing Machine", 500);

    // Turn ON appliances
    home.turnOn(0);  // Fan
    home.turnOn(1);  // Light
    home.turnOn(2);  // Refrigerator
    home.turnOn(3);  // TV
    home.turnOn(4);  // Air Conditioner

    // Display system status
    home.displayStatus();

    // Try to turn ON washing machine
    cout << "\nTrying to turn ON Washing Machine..." << endl;
    home.turnOn(5);

    // Display final status
    home.displayStatus();

    return 0;
}
