#include <iostream>
#include <iomanip>  // for std::setw and std::setprecision

using namespace std;

const int NUM_TIMESTEPS = 50000;
const double DELTA_T = 1e-10;
const double FINAL_TIME = 5e-6;
const double R = 1000.0;       // Ohms
const double C = 100e-12;      // Farads
const double I_CONST = 1e-2;   // Amps
const double V0 = 10.0;        // Volts

struct _capacitor
{
    double* time;
    double* voltage;
    double* current;
    double C;
};
typedef struct _capacitor Capacitor;

// Function to simulate constant current source charging
void simulateConstantCurrent(Capacitor& cap) {
    for (int i = 1; i <= NUM_TIMESTEPS; ++i) {
        cap.time[i] = cap.time[i - 1] + DELTA_T;
        cap.current[i] = I_CONST;
        cap.voltage[i] = cap.voltage[i - 1] + cap.current[i - 1] * DELTA_T / cap.C;

        if (i % 200 == 0) {
            cout << "[Constant Current] Step: " << setw(5) << i
                 << " | Time: " << cap.time[i]
                 << " | Voltage: " << cap.voltage[i]
                 << " | Current: " << cap.current[i] << endl;
        }
    }
}

// Function to simulate constant voltage source charging
void simulateConstantVoltage(Capacitor& cap) {
    for (int i = 1; i <= NUM_TIMESTEPS; ++i) {
        cap.time[i] = cap.time[i - 1] + DELTA_T;
        cap.current[i] = cap.current[i - 1] - (cap.current[i - 1] / (R * cap.C)) * DELTA_T;
        cap.voltage[i] = V0 - cap.current[i] * R;

        if (i % 200 == 0) {
            cout << "[Constant Voltage] Step: " << setw(5) << i
                 << " | Time: " << cap.time[i]
                 << " | Voltage: " << cap.voltage[i]
                 << " | Current: " << cap.current[i] << endl;
        }
    }
}

int main() {
    // Allocate memory for the structure
    Capacitor capConstCurrent, capConstVoltage;

    // Common setup
    capConstCurrent.C = C;
    capConstVoltage.C = C;

    capConstCurrent.time = new double[NUM_TIMESTEPS];
    capConstCurrent.voltage = new double[NUM_TIMESTEPS];
    capConstCurrent.current = new double[NUM_TIMESTEPS];

    capConstVoltage.time = new double[NUM_TIMESTEPS];
    capConstVoltage.voltage = new double[NUM_TIMESTEPS];
    capConstVoltage.current = new double[NUM_TIMESTEPS];

    // Initialize time arrays
    capConstCurrent.time[0] = 0.0;
    capConstVoltage.time[0] = 0.0;

    // Initial conditions
    capConstCurrent.voltage[0] = 0.0;
    capConstCurrent.current[0] = I_CONST;

    capConstVoltage.voltage[0] = 0.0;
    capConstVoltage.current[0] = V0 / R;

    // Run simulations
    cout << fixed << setprecision(6);
    simulateConstantCurrent(capConstCurrent);
    simulateConstantVoltage(capConstVoltage);

    // Free memory
    delete[] capConstCurrent.time;
    delete[] capConstCurrent.voltage;
    delete[] capConstCurrent.current;

    delete[] capConstVoltage.time;
    delete[] capConstVoltage.voltage;
    delete[] capConstVoltage.current;

    return 0;
}

