/*
Name: Adnan Nassan.
Date: 2024-07-10.
Purpose of the file: is to stores the implementation if declaration of the functions
*/

#include "Statistics.hpp"
#include"sorting.hpp"

using namespace std;



void readInput(istream& input, vector<double>& inputNumbers) {
    string s;

    while (input >> s) {
        // Check if the token is "end" to terminate input
        if (s == "end") {
            break;
        }

        // Try to convert the token to a double
        istringstream valueStream(s);
        double value;
        if (valueStream >> value) {
            // If the conversion is successful, add the value to the vector
            inputNumbers.push_back(value);
        }
        // If the conversion fails, the token is ignored
    }

    input.clear(); // Clear the EOF flag if reading from a file
}



double calculateMean(const vector<double>& data) {
    double sum = 0.0;
    for (double value : data) {  // Iterate through each value in the vector
        sum += value;  // Add the value to the sum
    }
    return sum / data.size();  // Return the mean by dividing the sum by the number of elements
}


double calculateMedian(vector<double> data) {
    size_t size = data.size();
    quickSort(data, 0, size - 1);  // Sort the vector using quicksort
    if (size % 2 == 0) {  // If the number of elements is even
        return (data[size / 2 - 1] + data[size / 2]) / 2.0;  // Return the average of the two middle elements
    }
    else {  // If the number of elements is odd
        return data[size / 2];  // Return the middle element
    }
}
double calculateVariance(const vector<double>& data, double mean) {
    double variance = 0.0;
    for (double value : data) {  // Iterate through each value in the vector
        variance += pow(value - mean, 2);  // Add the squared difference from the mean to the variance
    }
    return variance / data.size();  // Return the variance by dividing by the number of elements
}

double calculateStandardDeviation(double variance) {
   
    // Return the square root of the variance
    return sqrt(variance);
}

vector<double> calculateMode(const vector<double>& data) {
    
    vector<double> copied = data;  // Copy the input data to avoid modifying the original
    quickSort(copied, 0, copied.size() - 1);  // Sort the copied data using quicksort
    vector<int> occurs(copied.size(), 1);  // Initialize a vector to store the frequency of each element
                                           // I initialized each element to one because no matter what the lement is, it at least will appear once.

    // Count the occurrences of each element
    for (size_t i = 0; i < copied.size(); ++i) {
        if (i > 0 && copied.at(i) == copied.at(i - 1)) {  // If the current element is the same as the previous one
            occurs.at(i) = occurs.at(i - 1) + 1;  // Increment the count of occurrences
        }
    }

    int max = occurs.at(0);  // Initialize the maximum occurrence count

    // Find the maximum occurrence count
    for (size_t h = 1; h < occurs.size(); ++h) {
        if (max < occurs.at(h)) {
            max = occurs.at(h);  // Update the maximum occurrence count if a larger value is found
        }
    }

    vector<double> result;  // Initialize a vector to store the mode(s)
    // Collect all elements with the maximum occurrence count
    for (size_t i = 0; i < occurs.size(); ++i) {
        if (occurs.at(i) == max) {
            result.push_back(copied.at(i));  // Add the element to the result vector
        }
    }
    int count = 0;// the counter is to check if all the copied vector has the same number of occurnes
    //if all numbers have the same occurnes, means all the copied elements are modes which results in there is no mode
    for (size_t i = 0; i < copied.size(); ++i) {
        for (size_t j = 0; j < result.size(); ++j)
            if (copied[i] == result[j]) {
                count++;
                break;
            
            }
    }

    if (count == copied.size()) { return {}; }


    // Check if the result is valid
    if (result.size() == copied.size() ) {
        return {};  // Return an empty vector if the result is not a valid mode
    }
    else {
        result.push_back(max);  // Add the maximum occurrence count to the result vector
        return result;  // Return the result vector
    }
}




double calculateMeanAbsoluteDeviation(const vector<double>& data, double center) {
    double mad = 0.0;
    for (double value : data) {  // Iterate through each value in the vector
        mad += abs(value - center);  // Add the absolute difference from the center to MAD
    }
    return mad / data.size();  // Return the MAD by dividing by the number of elements
}






vector<double> calculateRegressionLine(const vector<double>& data) {
    double sumX = 0.0, sumY = 0.0, sumX2 = 0.0, sumXY = 0.0;
    vector <double> result(2);
    vector <double> indices;
    int n = data.size();
    
    // Calculate sums for X, Y, X^2, and XY
    for (size_t i = 0; i < n; ++i) {
        indices.push_back(i);
        sumX += i;
        sumY += data[i];
        sumX2 += i * i;
        sumXY += i * data[i];
    
    }


    double meanX = calculateMean(indices);  // Calculate the mean of indices
    double meanY = calculateMean(data);  // Calculate the mean of data values
    double ssxx = sumX2 - n * meanX * meanX;  // Calculate the sum of squares for X
    double ssxy = sumXY - n * meanX * meanY;  // Calculate the sum of products for XY
    double slope = ssxy / ssxx;  // Calculate the slope of the regression line
    double intercept = meanY - slope * meanX;  // Calculate the intercept of the regression line
    
    
    result.at(0) = slope;  // Store the slope in the result vector
    result.at(1) = intercept;  // Store the intercept in the result vector

    return result;

}


vector<vector<double>> calculateOutliersBasedOnMean(const vector<double>& data) {
    vector<vector<double>> outliers(3);  // To store 1x, 2x, and 3x outliers
    if (data.empty()) {
        return outliers;  // Return empty vectors if no data
    }

    double mean = calculateMean(data);  // Calculate mean
    double stddev = calculateStandardDeviation(calculateVariance(data, mean));  // Calculate standard deviation

    for (double value : data) {
        double absDiff = abs(value - mean);  // Absolute difference from mean

        if (absDiff > stddev) {
            outliers[0].push_back(value);  // 1x outlier
        }
        if (absDiff > 2 * stddev) {
            outliers[1].push_back(value);  // 2x outlier
        }
        if (absDiff > 3 * stddev) {
            outliers[2].push_back(value);  // 3x outlier
        }
    }

    return outliers;  // Return the list of outliers
}


void calculateStatistics(const vector<double>& data) {
        
    double mean = calculateMean(data);  // Calculate the mean of the data
    double median = calculateMedian(data);  // Calculate the median of the data
    double variance = calculateVariance(data, mean);  // Calculate the variance of the data
    double stddev = calculateStandardDeviation(variance);  // Calculate the standard deviation of the data
    vector<double> modes = calculateMode(data);  // Calculate the mode(s) of the data
    double meanAbsDevMean = calculateMeanAbsoluteDeviation(data, mean);  // Calculate MAD about the mean
    double meanAbsDevMedian = calculateMeanAbsoluteDeviation(data, median);  // Calculate MAD about the median
    
    double meanAbsMode = 0;
    // the mean about the mode is only found if the there is one mode.
    if (modes.size() == 2) {
         meanAbsMode = calculateMeanAbsoluteDeviation(data, modes[0]);
    }
    vector<double> result = calculateRegressionLine(data);  // Calculate the regression line (slope and intercept)
    vector<vector<double>> outliers = calculateOutliersBasedOnMean(data);  // Calculate the outliers in the data
    
    // Set the output format to fixed with 3 decimal places and print.
    cout << fixed << setprecision(3);
    cout << "---------------------------------------------" << endl;
    cout << setw(34) << left << "#elemnts" << right << setw(10) << data.size()<< endl;
    cout << setw(34) << left << "minimum" << right << setw(10) << *min_element(data.begin(), data.end()) << endl;
    cout << setw(34) << left << "maximum" << right << setw(10) << *max_element(data.begin(), data.end()) << endl;
    cout << setw(34) << left << "mean" << right << setw(10) << mean << endl;
    cout << setw(34) << left << "median" << right << setw(10) << median << endl;
    cout << setw(34) << left << "variance" << right << setw(10) << variance << endl;
    cout << setw(34) << left << "std. dev." << right << setw(10) << stddev << endl;
    cout << "---------------------------------------------" << endl;

    if (modes.empty()) {
        cout << setw(34) << left << "# modes" << right << setw(10) << "no mdes" << endl;
    
    }
    else  {
        cout << setw(34) << left << "# modes" << right << setw(10) <<  modes.size() - 1<< endl;
        cout << setw(34) << left << "mode frequency" << right << setw(10) << modes.back() << endl;
        for (size_t i = 0; i < modes.size() - 1; ++i) {
            cout << setw(34) << left << "mode" << right << setw(10) << modes.at(i) << endl;
        }
       
    }
    cout << "---------------------------------------------" << endl;
    cout << "mean absolute deviations:" << endl;
    cout << setw(34) << left << "...about the mean" << right << setw(10) << meanAbsDevMean << endl;
    cout << setw(34) << left << "...about the median" << right << setw(10) << meanAbsDevMedian << endl;

    if (modes.size() == 2) {
        cout << setw(34) << left << "...about the mode" << right << setw(10) << meanAbsMode << endl;
    }
    cout << "---------------------------------------------" << endl;
    cout << setw(34) << left << "regression slope" << right << setw(10) << result.at(0) << endl;
    cout << setw(34) << left << "regression intercept" << right << setw(10) << result.at(1) << endl;
    cout << "---------------------------------------------" << endl;


    if (outliers[1].size() != 0) {
        cout << setw(31) << left << "Outliers(2x) " << right << setw(6) << "# outliers = " << outliers[1].size() << endl;
        for (double outlier : outliers[1]) {
            cout << setw(34) << "" << right << setw(10) << outlier << endl;
        }
    }

    else {
        cout << setw(34) << left << "Outliers(2x)" << right << setw(10) << "no outliers" << endl;
    }
    
    if (outliers[2].size() != 0) {
        cout << setw(31) << left << "Outliers(3x) " << right << setw(6) << "# outliers = " << outliers[2].size() << endl;
        for (double outlier : outliers[2]) {
            cout << setw(34) << "" << right << setw(10) << outlier << endl;
        }
    }
    else {
        cout << setw(34) << left << "Outliers(3x)" << right << setw(10) << "no outliers" << endl;
    }
    

    cout << "---------------------------------------------" << endl;
}

    

