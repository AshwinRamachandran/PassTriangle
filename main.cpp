#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <string.h>

using namespace std;

int** mat;
unsigned int num_lines;

/* allocates a triangular matrix with num_lines rows */
void allocateMat() {
    mat = new int*[num_lines];
    for (unsigned int i = 0; i < num_lines; ++i)
        mat[i] = new int[(i + 1)];
}

/* free dynamically allocated memory */
void cleanup() {
    for (unsigned int i = 0; i < num_lines; ++i)
        delete[] mat[i];
}

/* returns the number of non-empty lines in a specified file */
int getLinesInFile(ifstream& infile) {
    string line;
    unsigned int lines = 0;
    
    while (getline(infile, line)) {
        if (line.length() != 0)
            ++lines;
    }
    
    infile.clear();
    infile.seekg(0, ios::beg);
    
    return lines;
}

/* computes the longest path in the triangle with a single pass */
int longestPathSum() {
    int max = INT_MIN;
    
    for (unsigned int i = 1; i < num_lines; ++i) {
        for (unsigned int j = 0; j <= i; j++) {
            /* Compute sum so far by investigating the value of a cell's
             * possible predecessors. Cells on the border only have a single
             * predecessor in the path */
            
            if (j == 0) { // left border of triangle - use value directly above
                mat[i][j] += mat[i - 1][j];
            }
            else if (j == i) { // right border - use value at the top left
                mat[i][j] += mat[i - 1][j - 1];
            }
            else { // has two possible predecessors
                int path1 = mat[i][j] + mat[i - 1][j]; // directly above
                int path2 = mat[i][j] + mat[i - 1][j - 1]; // top left
                
                if (path1 > path2)
                    mat[i][j] = path1;
                else
                    mat[i][j] = path2;
            }
            
            /* for the last row, find the maximum value --> this is the longest
             * path value */
            if (i == (num_lines - 1)) {
                if (mat[i][j] > max)
                    max = mat[i][j];
            }
        }
    }
    
    return max;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Please enter an input file name." << endl;
        return -1;
    }
    
    ifstream infile(argv[1]);
    
    num_lines = getLinesInFile(infile);
    allocateMat();
    
    string line;
    int row = 0;
    int col = 0;
    while (getline(infile, line)) {
        if (line.length() != 0) {
            char* dup = strdup(line.c_str());
            char* line_comps = strtok(dup, " "); // split around space
            
            while (line_comps != NULL) { // populate the matrix
                string num_str(line_comps);
                int num = atoi(num_str.c_str());
                mat[row][col] = num;
                line_comps = strtok(NULL, " ");
                
                ++col;
            }
            
            free(dup);
            
            col = 0;
            ++row;
        }
    }
    
    cout << longestPathSum() << endl;
    
    cleanup();
    infile.close();
    
	return 0;
}
