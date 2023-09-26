/*

Creator: failedsyntax @ github
Contributors: 
- ChatGPT for the deviation input value array function

*/

#include <iostream>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <vector>
#include <tuple>
#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#elif __unix__ || __APPLE__
#include <sys/ioctl.h>
#endif

using namespace std;

class Menus {
    public:
    void MainMenu() {
        cout << "1 - Algebra" << endl;
        cout << "2 - Kinematics" << endl;
        cout << "3 - Deviation" << endl;

        cout << "4 - Close" << endl;
    };
    void AlgebraMenu() {
        cout << "1 - Quadratic Formula <A, B, C>" << endl;
        cout << "2 - Vertex Form <A, B, C>" << endl;
        cout << "3 - Return" << endl;
    };
    void KinematicsMenu()
    {
        cout << "1 - 3rd Kinematic <initVel, Accel, Time>" << endl;
        cout << "2 - 3rd Kinematic: Solve for Accel <deltaDistance, initVel, Time>" << endl;
        cout << "3 - Return" << endl;
    };
    void DeviationMenu()
    {
        cout << "1 - Standard Deviation" << endl;
        cout << "2 - Return" << endl;
    };
    void refreshMenu() {
        #ifdef _WIN32 
            system("cls");
        #else 
            system("clear");
        #endif 
            MainMenu();
    };
    void setTitle(const string& Title) {
        #ifdef _WIN32
            SetConsoleTitleA(Title.c_str());
        #elif __unix__ || __APPLE__
            cout << "\033]0;" << Title << "\007";
        #endif
    }
};

class Algebra {
public:
    void Menu()
    {
        cout << "\n1 - Quadratic Formula <A, B, C>" << endl;
        cout << "2 - Vertex Form <A, B, C>" << endl;
        cout << "3 - Return" << endl;
    }

    void QuadraticFormula(float A, float B, float C)
    {
        float Discriminant = (pow(B, 2) - (4 * A * C));
        float sqrtDiscrim = sqrt(abs(Discriminant));

        if (Discriminant > 0)
        { // Real, Different Roots
            float rOne = (-B + sqrtDiscrim) / (2 * A);
            float rTwo = (-B - sqrtDiscrim) / (2 * A);
            cout << "Roots: \n"
                 << fixed << setprecision(2) << rOne << "\n"
                 << fixed << setprecision(2) << rTwo << endl;
        }
        else if (Discriminant == 0)
        { // Real, Same Roots
            float Roots = (-B / (2 * A));
            cout << "Roots: \n"
                 << fixed << setprecision(2) << Roots << endl;
        }
        else
        { // Imaginary Roots
            float Root = (-B / (2 * A));
            cout << "Roots: \n"
                 << fixed << setprecision(2) << Root << "+ i SQRT:" << fixed << setprecision(3) << sqrtDiscrim << "\n"
                 << fixed << Root << "- i SQRT:" << fixed << setprecision(3) << sqrtDiscrim << endl;
        };
    };

    void Quadratic_VertexForm(int A, float B, float C) // Change "A" back to float data type and fix VertexForm_A = "-" + <..>
    {
        float Vertex_X = -B / (2 * A);
        float Vertex_Y = ((A * (pow(Vertex_X, 2))) + (B * Vertex_X) + C);
        string VertexForm_A = "a";
        string Vertex_XSign = "-";
        string Vertex_YSign = "-";
        if (A < 0 && abs(A) > 1)
        {
            VertexForm_A = "-" + to_string(abs(A)); // not sure why this marks as an error but works..
        }
        else if (A < 0 && abs(A) == 1)
        {
            VertexForm_A = "-";
        }
        else
        {
            VertexForm_A = "a";
        };

        if (Vertex_X < 0)
        {
            Vertex_XSign = "+ ";
        }
        else
        {
            Vertex_XSign = "- ";
        };
        if (Vertex_Y < 0)
        {
            Vertex_YSign = "- ";
        }
        else
        {
            Vertex_YSign = "+ ";
        };
        cout << "Vertex: (" << fixed << setprecision(2) << Vertex_X;
        cout << ", " << fixed << setprecision(2) << Vertex_Y << ")" << endl;
        cout << "Vertex Form: f(x) = " << VertexForm_A << "(x " << Vertex_XSign;
        cout << fixed << setprecision(2) << abs(Vertex_X) << ")^2 " << Vertex_YSign;
        cout << fixed << setprecision(2) << abs(Vertex_Y) << endl;
    };
};

class Kinematics {
public:
    void Menu()
    {
        cout << "1 - 3rd Kinematic <initVel, Accel, Time>" << endl;
        cout << "2 - 3rd Kinematic: Solve for Accel <deltaDistance, initVel, Time>" << endl;
        cout << "3 - Return" << endl;
    };

    void ThirdKinematicFormula(float initVelocity, float Acceleration, float Time)
    {
        float Result = 0.00;
        Result = (initVelocity * Time) + (0.5 * (Acceleration * (Time * Time)));
        cout << Result << " m" << endl;
    };

    void ThirdKinematicFormula_SolveForAcceleration(float changeInDistance, float initVelocity, float Time)
    {
        float Result;
        Result = (2 * ((changeInDistance - (initVelocity * Time)) / (Time * Time)));
        cout << Result << " m/s^2" << endl;
    };
};

class Deviation
{
public:
    int valueCount;
    void Menu()
    {
        cout << "1 - Standard Deviation" << endl;
        cout << "2 - Return" << endl;
    };

    float *gatherInputData()
    {
        int index;
        cout << "How many values will be used: "; cin >> valueCount;

        float *valueCountArray = new float[valueCount];

        for (index = 0; index < valueCount; index++)
        {
            cout << "Please input value " << (index + 1) << " / " << valueCount << " and press enter: ";
            cin >> valueCountArray[index];
        };
        return valueCountArray;
    };

    float calcMean(const float *inpVals, int numberOfVals)
    {
        float sum = 0.0f;
        for (int i = 0; i < numberOfVals; ++i)
        {
            sum += inpVals[i];
        };
        return sum / static_cast<float>(numberOfVals);
    };

    float StandardDeviation(const float *InputValues)
    {
        float Mean = calcMean(InputValues, valueCount);

        float squaredSumDiff = 0.0f;
        for (int i = 0; i < valueCount; ++i)
        {
            float diff = InputValues[i] - Mean;
            squaredSumDiff += pow(diff, 2);
        }

        float variance = squaredSumDiff / static_cast<float>(valueCount);
        delete[] InputValues;
        return sqrt(variance);
    };
};

int main() {
    Menus().setTitle("Formula Calculator");
    Menus().refreshMenu(); // Clear console and load menu

    // Create Function Maps
    unordered_map<int, function<void()> > AlgebraMap = { // Algebra Map
        {1, []() {
            float A,B,C;
            std::cout << "Input A: "; cin >> A;
            std::cout << "Input B: "; cin >> B;
            std::cout << "Input C: "; cin >> C;
            Algebra().QuadraticFormula(A, B, C);
        }},
        {2, []() {
            float A,B,C;
            cout << "Input A: "; cin >> A;
            cout << "Input B: "; cin >> B;
            cout << "Input C: "; cin >> C;
            Algebra().Quadratic_VertexForm(A, B, C);
        }},
        {3, []() {
            Menus().refreshMenu();
        }}
    };

    unordered_map<int, function<void()> > KinematicMap = { // Kinematics Map
        {1, []() {
            float initVel, Accel, Time;
            cout << "Input Initial Velocity: "; cin >> initVel;
            cout << "Input Acceleration: "; cin >> Accel;
            cout << "Input Time: "; cin >> Time;
            Kinematics().ThirdKinematicFormula(initVel, Accel, Time);
        }},
        {2, []() {
            float distanceChange, initVel, Time;
            cout << "Input Distance Change: "; cin >> distanceChange;
            cout << "Input Initial Velocity: "; cin >> initVel;
            cout << "Input Time: "; cin >> Time;
            Kinematics().ThirdKinematicFormula_SolveForAcceleration(distanceChange, initVel, Time);
        }},
        {3, []() {
            Menus().refreshMenu();
        }}
    };

    unordered_map<int, function<void()> > DeviationMap = {
        {1, []() {
            Deviation Deviate; // Needs to be required within the lambda scope?
            float Mean, Dev;
            int Precision;
            const float *UserInputs;
            UserInputs = Deviate.gatherInputData();
            Mean = Deviate.calcMean(UserInputs, Deviate.valueCount);
            Dev = Deviate.StandardDeviation(UserInputs);
            cout << "To what precision/digit? "; cin >> Precision;
            cout << "The Standard Deviation is: " << fixed << setprecision(Precision) << Dev << endl;
            cout << "Mean: " << fixed << setprecision(Precision) << Mean << endl;
        }},
        {2, []() {
            Menus().refreshMenu();
        }}
    };

    unordered_map<int, function<void()>> MenuMap = { // Main Menu Map
        {1, [&]() { // Algebra Menu
            int algebraMenuNav;
            do {
                Menus().AlgebraMenu();
                cout << "Choose a option: ";
                cin >> algebraMenuNav; cout << endl;
                auto algebraFunction = AlgebraMap.find(algebraMenuNav);
                if (algebraFunction != AlgebraMap.end()) {
                    algebraFunction -> second();
                } else if (algebraMenuNav == 3) {
                    break;
                } else {
                    cout << "Not a valid selection" << endl; Menus().AlgebraMenu();
                };
            } while (algebraMenuNav != 3);
        }}, // Define the input needed (1), then create an invoking lambda "[]() {}" that runs the code inside
        {2, [&]() {
            int kinematicMenuNav;
            do {
                Menus().KinematicsMenu();
                cout << "Choose a option: ";
                cin >> kinematicMenuNav; cout << endl;
                auto kinematicFunction = KinematicMap.find(kinematicMenuNav);
                if (kinematicFunction != KinematicMap.end()) {
                    kinematicFunction -> second();
                } else if (kinematicMenuNav == 3) {
                    break;
                } else {
                    cout << "Not a valid selection" << endl; Menus().KinematicsMenu();
                };
            } while (kinematicMenuNav != 3);
        }},
        {3, [&]() {
            int deviationMenuNav;
            do {
                Menus().DeviationMenu();
                cout << "Choose a option: ";
                cin >> deviationMenuNav; cout << endl;
                auto deviationFunction = DeviationMap.find(deviationMenuNav);
                if (deviationFunction != DeviationMap.end()) {
                    deviationFunction -> second();
                } else if (deviationMenuNav == 2) {
                    break;
                } else {
                    cout << "Not a valid selection" << endl; Menus().DeviationMenu();
                };
            } while (deviationMenuNav != 2);
        }},
        {4, []() {
            
        }}
    };

    // Gather input from user and check if its within the Menu Map
    int input;
    do {
        cout << "Please choose where to go: ";
        cin >> input; cout << endl;
        auto functionDesired = MenuMap.find(input);
        if (functionDesired != MenuMap.end()) {
            functionDesired->second();
        } else {
            cout << "Please make a valid selection" << endl;
        }
    } while (input != 4);  // Exit loop when the user chooses to close

    return 0;
};