#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const short LOTS = 6, MAX_D = 1000, MIN_D = 0, MAX_O = 100, MIN_O = 0;

void Populator(float* , bool decimal = false);
void Printer(float*);
void distanceCombiner(float*, float*, float*);
void Normalizer(float*, float *);
void coefficientCombiner(float*, float*, float*, float, float);
bool inputValidation(float, float);


int main(){

    //Step one: Generate 3 arrays containing distance_one, occ_rate, distance_two
    float distance_one[LOTS];
    float occupancy_rate[LOTS];
    float distance_two[LOTS];
  
    Populator(distance_one);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Populator(occupancy_rate, true);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Populator(distance_two);
 
  
    cout << "\nPrinting Current Data: \n\n";
    cout << "    1     2     3     4     5     6  LOTS\n";
    Printer(distance_one);
    cout << " DISTANCE 1\n";
    Printer(occupancy_rate);
    cout << " OCCUPANCY RATE\n";
    Printer(distance_two);
    cout << " DISTANCE 2\n\n";

    //Combining distances to normalize data
    float total_distances[LOTS];
    distanceCombiner(distance_one, distance_two,  total_distances);

    cout << "Combining Distance Data...\n";
    cout << "\nPrinting Current Data: \n\n";
    cout << "    1     2     3     4     5     6  LOTS\n";
    Printer(total_distances);
    cout << " TOTAL DISTANCE\n";
    Printer(occupancy_rate);
    cout << " OCCUPANCY RATE\n\n";

    //Normalizing Data
    float normalized_distance[LOTS];
    Normalizer(total_distances, normalized_distance);

    cout << setprecision(3) << fixed;
    cout << "Normalizing Total Distance Data...\n";
    cout << "\nPrinting Current Data: \n\n";
    cout << "    1     2     3     4     5     6  LOTS\n";
    Printer(normalized_distance);
    cout << " NORMALIZED TOTAL DISTANCE\n";
    Printer(occupancy_rate);
    cout << " OCCUPANCY RATE\n\n";

    //Combining Data Using Coefficients d,p

    float combined_results[LOTS];
    cout << "Combining Data Using Coefficients d and p";
    
    /**************************************************************************************/
    coefficientCombiner(normalized_distance, occupancy_rate, combined_results, 0.40, 0.60);
    cout << "\n\nTesting using d = 0.40 and p = 0.60\n";
    cout << "\nPrinting Current Data: \n\n";
    cout << "    1     2     3     4     5     6  LOTS\n";
    Printer(occupancy_rate);
    cout << " OCCUPANCY RATE\n";
    
    cout << setprecision(0);

    Printer(distance_one);
    cout << " DISTANCE 1\n";
    Printer(distance_two);
    cout << " DISTANCE 2\n";
    Printer(total_distances);
    cout << " TOTAL DISTANCE\n\n";
    
    cout << setprecision(3) << fixed;
    Printer(combined_results);
    cout << " Final Results\n";
    
    /**************************************************************************************/
    coefficientCombiner(normalized_distance, occupancy_rate, combined_results, 0.50, 0.50);
    cout << "\n\nTesting using d = 0.50 and p = 0.50\n";
    cout << "\nPrinting Current Data: \n\n";
    cout << "    1     2     3     4     5     6  LOTS\n";
    Printer(occupancy_rate);
    cout << " OCCUPANCY RATE\n";
    
    cout << setprecision(0);

    Printer(distance_one);
    cout << " DISTANCE 1\n";
    Printer(distance_two);
    cout << " DISTANCE 2\n";
    Printer(total_distances);
    cout << " TOTAL DISTANCE\n\n";
    
    cout << setprecision(3) << fixed;
    Printer(combined_results);
    cout << " Final Results\n";
    
    /**************************************************************************************/
    coefficientCombiner(normalized_distance, occupancy_rate, combined_results, 0.45, 0.55);
    cout << "\n\nTesting using d = 0.45 and p = 0.55\n";
    cout << "\nPrinting Current Data: \n\n";
    cout << "    1     2     3     4     5     6  LOTS\n";
    Printer(occupancy_rate);
    cout << " OCCUPANCY RATE\n";
    
    cout << setprecision(0);

    Printer(distance_one);
    cout << " DISTANCE 1\n";
    Printer(distance_two);
    cout << " DISTANCE 2\n";
    Printer(total_distances);
    cout << " TOTAL DISTANCE\n";
    
    cout << setprecision(3) << fixed;
    Printer(combined_results);
    cout << " Final Results\n";
    

    //Trying User-entered values
   float dRate, pRate;
    do{
        cout << "\nEnter a coefficient d for the distance weight and p for the parking weight: \n";
        cout << "\nd: ";
        cin >> dRate;
        cout << "p: ";
        cin >> pRate;
        if(!inputValidation(dRate, pRate))
            cout << "\nINVALID INPUT. VALID RANGE [0 - 1]\n";
    }while(!inputValidation(dRate, pRate));
    
    coefficientCombiner(normalized_distance, occupancy_rate, combined_results, dRate, pRate);
    cout << "\nTesting using d = 0.45 and p = 0.55\n";
    cout << "\nPrinting Current Data: \n\n";
    cout << "    1     2     3     4     5     6  LOTS\n";
    Printer(occupancy_rate);
    cout << " OCCUPANCY RATE\n";
    
    cout << setprecision(0);

    Printer(distance_one);
    cout << " DISTANCE 1\n";
    Printer(distance_two);
    cout << " DISTANCE 2\n";
    Printer(total_distances);
    cout << " TOTAL DISTANCE\n";
    
    cout << setprecision(3) << fixed;
    Printer(combined_results);
    cout << " Final Results\n\n";

    return(0);

    

}

void Populator(float* array_address, bool decimal){
    srand(time(0));
    for(short index = 0; index < LOTS; index++){
        if(!decimal)
            array_address[index] = (rand() % (MAX_D - MIN_D - 1) + MIN_D);
        else{
            array_address[index] = (rand() % (MAX_O - MIN_O - 1) + MIN_O);
            array_address[index] /= 100.0;
        }
    }
}
void Printer(float* array_address){
    for(short index = 0; index < LOTS; index++){
        cout << setw(5) << array_address[index] << " ";
    }
}
void distanceCombiner(float* arg_one, float* arg_two, float* final_answer){
    for(short index = 0; index < LOTS; index++){
        final_answer[index] = arg_one[index] + arg_two[index];
    }
}
void Normalizer(float* non_n_data, float* norm_data){
    float MAX_VALUE = non_n_data[0];
    float MIN_VALUE = non_n_data[0];

    for(short index = 1; index < LOTS; index++){
        if(non_n_data[index] > MAX_VALUE)
            MAX_VALUE = non_n_data[index];
        if(non_n_data[index] < MIN_VALUE)
            MIN_VALUE = non_n_data[index];
    }

    for(short index = 0; index < LOTS; index++){
        norm_data[index] = (non_n_data[index] - MIN_VALUE) / (MAX_VALUE - MIN_VALUE);
    }

}
void coefficientCombiner(float* distance_array, float* occ_array, float* final_results_array, float dval, float pval){

    for(short index =0; index <LOTS; index++){
        final_results_array[index] = distance_array[index] * dval + occ_array[index] * pval;
    }
}
bool inputValidation(float arg_one, float arg_two){
    bool valid = true;
    if(arg_one < 0 || arg_one > 1 || arg_two < 0 || arg_two > 1)
        valid = false;
    return valid;
}
