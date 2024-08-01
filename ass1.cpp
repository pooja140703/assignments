// used brute force not used Google
// TC=O(nlogn)+O(m)+O(m⋅n 2)=O(mn^2)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void distributeApples(vector<int> &apples, vector<int> &payments, vector<vector<int>> &distribution)
{
    // Sort apples in descending order
    sort(apples.begin(), apples.end(), greater<int>());

    // Calculate total payment
    int totalPayment = 0;
    for (int payment : payments)
    {
        totalPayment += payment;
    }
    int totalWt = 0;
    for (int apple : apples)
    {
        totalWt += apple;
    }

    // Calculate shares
    vector<double> shares(payments.size());
    for (int i = 0; i < payments.size(); ++i)
    {
        shares[i] = (double)payments[i] / totalPayment;
    }
    for (int i = 0; i < payments.size(); ++i)
    {
        std::cout << shares[i] << " " << totalWt;
    }

    // Initialize distributed weights
    vector<int> distributedWeights(payments.size(), 0);

    for (int i = 0; i < distribution.size(); i++)
    {
        //  for (int apple : apples) {
        //  std::cout<<apple<<" ";
        //  }
        distribution[i].push_back(apples[0]);
        distributedWeights[i] += apples[0];
        apples.erase(apples.begin());
        for (int j = 0; j < apples.size(); j++)
        {
            if (distributedWeights[i] + apples[j] <= totalWt * shares[i])
            {
                distribution[i].push_back(apples[j]);
                distributedWeights[i] += apples[j];
                // wt+=apples[j];
                // std::cout<<apples[j]<<" ";
                apples.erase(apples.begin() + j);
                j--;
            }
        }
    }
}

int main()
{
    vector<int> apples;
    cout << "Enter apple weight in grams (-1 to stop): ";
    int weight;
    while (cin >> weight && weight != -1)
    {
        apples.push_back(weight);
        cout << "Enter apple weight in grams (-1 to stop): ";
    }
    vector<int> payments = {50, 30, 20}; // Ram, Sham, Rahim
    vector<vector<int>> distribution(3); // Distribution result

    distributeApples(apples, payments, distribution);

    cout << "Distribution Result :" << endl;
    cout << "Ram: ";
    for (int apple : distribution[0])
    {
        cout << apple << " ";
    }
    cout << endl;

    cout << "Sham: ";
    for (int apple : distribution[1])
    {
        cout << apple << " ";
    }
    cout << endl;

    cout << "Rahim: ";
    for (int apple : distribution[2])
    {
        cout << apple << " ";
    }
    cout << endl;

    return 0;
}
