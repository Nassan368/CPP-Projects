/*
Name: Adnan Nassan.
Date: 2024-07-10.
Purpose of the file: is to stores function declaration
*/
#pragma once

#include <utility>
#include <istream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>
#include <map>
#include <set>
#include <unordered_map>
#include <iomanip>
#include <fstream>

/*
 * \fn:  readInput
 * \brief: Reads a sequence of numbers from an input stream and stores them in a vector.
 * \param: input The input stream to read from (e.g., std::cin or an ifstream object).
 * \param: inputNumbers The vector to store the converted double values.
 * \return: void
 * \author: Adnan
 * \date: 2024-07-10
 */
void readInput(std::istream& input, std::vector<double>& inputNumbers);

/*
 * \ calculateRegressionLine
 * \brief: Calculates the regression line for a vector of doubles.
 * \param: data The vector of double values to compute the regression line for.
 * \return: A vector containing the slope and intercept of the regression line.
 * \author: Adnan
 * \date: 2024-07-10
 */

std::vector<double> calculateRegressionLine(const std::vector<double>& data);

/*
 * \fn:  calculateStatistics
 * \brief: Calculates and prints various statistical measures for a vector of doubles.
 * \param: data The vector of double values to calculate statistics for.
 * \return: void
 * \author: Adnan
 * \date: 2024-07-10
 */

void calculateStatistics(const std::vector<double>& data);

/*
 * \fn:  calculateMean
 * \brief: Calculates the mean of a vector of doubles.
 * \param: data The vector of double values to compute the mean for.
 * \return: The mean of the data.
 * \author: Adnan
 * \date: 2024-07-10
 */

double calculateMean(const std::vector<double>& data);

/*
 * \fn:  calculateMedian
 * \brief: Calculates the median of a vector of doubles.
 * \param: data The vector of double values to compute the median for.
 * \return: The median of the data.
 * \author: Adnan
 * \date: Due today
 */

double calculateMedian(std::vector<double> data);

/*
 * \fn:  calculateVariance
 * \brief: Calculates the variance of a vector of doubles.
 * \param: data The vector of double values to compute the variance for.
 * \param: mean The mean of the data.
 * \return: The variance of the data.
 * \author: Adnan
 * \date: 2024-07-10
 */

double calculateVariance(const std::vector<double>& data, double mean);

/*
 * \fn:  calculateStandardDeviation
 * \brief: Calculates the standard deviation of a dataset based on its variance.
 * \param: variance The variance of the data.
 * \return: The standard deviation of the data.
 * \author: Adnan
 * \date: 2024-07-10
 */

double calculateStandardDeviation(double variance);

/*
 * \fn:calculateMode
 * \brief: Calculates the mode(s) of a vector of doubles.
 * \param: data The vector of double values to compute the mode(s) for.
 * \return: A vector containing the mode(s) of the data.
 * \author: Adnan
 * \date: 2024-07-10
 */

std::vector<double> calculateMode(const std::vector<double>& data);

/*
 * \fn:  calculateMeanAbsoluteDeviation
 * \brief: Calculates the mean absolute deviation of a vector of doubles from a specified center.
 * \param: data The vector of double values to compute the mean absolute deviation for.
 * \param: center The center value (mean or median) to compute the deviation from.
 * \return: The mean absolute deviation of the data from the center.
 * \author: Adnan
 * \date: 2024-07-10
 */

double calculateMeanAbsoluteDeviation(const std::vector<double>& data, double center);

/*
 * \fn: calculateOutliers
 * \brief: Identifies the outliers in a vector of doubles.
 * \param: data The vector of double values to identify outliers in.
 * \return: A vector containing the outliers in the data.
 * \author: Adnan
 * \date: 2024-07-10
 */

std::vector<std::vector<double>> calculateOutliersBasedOnMean(const std::vector<double>& data);

