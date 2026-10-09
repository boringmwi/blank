#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// COMPUTE HISTOGRAM
vector<double> getNormalizedHistogram(const string& filePath) {
    vector<double> histogram(26, 0.0);
    ifstream infile(filePath);
// ERROR HANDLING
    if (!infile) {
        cout << "Error: Could not open file at " << filePath << endl;
        return histogram;
    }

    char ch;
    double totalLetters = 0.0;

    // READ FILE AND FIND LETTER OCCURENCES
    while (infile.get(ch)) {
    // ANY CHAR OUTSIZE OF LETTER ASCII VALUES IS IGNORED
        if (ch >= 'A' && ch <= 'Z') {
    // INCREASE THE VALUE IN LETTER'S BIN BY 1
            histogram[ch - 'A']++;
    // INCREASE THE TOTAL LETTERS VALUE BY 1
            totalLetters++;
    // SAME AS ABOVE JUST FOR LOWER CASE LETTERS
        } else if (ch >= 'a' && ch <= 'z') {
            histogram[ch - 'a']++;
            totalLetters++;
        }
    }
    // CLOSE FILE AS WE ARE NO LONGER READING IT 
    infile.close();

    // NORMALIZE HISTOGRAM
    if (totalLetters > 0.0) {
    // FOR EACH BIN IN THE HISTOGRAM DIVIDE BY TOTAL LETTERS TO NORMALIZE
        for (int i = 0; i < 26; i++) {
            histogram[i] /= totalLetters;
        }
    }

    return histogram;
}

// COMPUTE EUCLIDEAN DISTANCE OF HISTOGRAMS
double computeEuclideanDistance(const vector<double>& h1, const vector<double>& h2) {
    double sumOfSquaredDifferences = 0.0;

    for (int j = 0; j < 26; j++) {
    // FIND DIFFERENCE BETWEEN HISTOGRAM BINS -> bin A1 - bin A2
        double diff = h1[j] - h2[j];
        // ADD SQUARE OF THE DIFF 
        sumOfSquaredDifferences += diff * diff; 
    }

    // SQUARE ROOT SUM OF SQUARED DIFFERENCES TO FIND EUCLIDEAN DISTANCE
    return sqrt(sumOfSquaredDifferences);
}

int main() {
    // INPUT TWO TEXT FILES TO COMPARE
    string path1;
    string path2;

    cout << "Enter the file path of the first text file:" << endl;
    cin >> path1;
    cout << "Enter the file path of the second text file:" << endl;
    cin >> path2;
    // GETTING NORMALIZED HISTOGRAMS OF EACH TEXT FILE
    vector<double> hist1 = getNormalizedHistogram(path1);
    vector<double> hist2 = getNormalizedHistogram(path2);
    // GETTING THE EUCLIDEAN DISTANCE
    double distance = computeEuclideanDistance(hist1, hist2);
    // COUT RESULTS
    cout << "Euclidean Distance: " << distance << endl;

    return 0;
}