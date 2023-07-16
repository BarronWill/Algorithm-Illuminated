#include <iostream>
#include <vector>

using namespace std;

// Function to split a matrix into quadrants
vector<vector<int>> subtractMatrices(const vector<vector<int>>& X, const vector<vector<int>>& Y);
vector<vector<int>> addMatrices(const vector<vector<int>>& X, const vector<vector<int>>& Y);
void printMatrix(const vector<vector<int>>& matrix);
void splitMatrix(const vector<vector<int>>& X, vector<vector<int>>& A, vector<vector<int>>& B,
                 vector<vector<int>>& C, vector<vector<int>>& D) {
    int n = X.size();
    int half = n / 2;
    
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A[i][j] = X[i][j];
            B[i][j] = X[i][j + half];
            C[i][j] = X[i + half][j];
            D[i][j] = X[i + half][j + half];
        }
    }
}

// Function to merge quadrants into a matrix
void mergeMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B,
                 const vector<vector<int>>& C, const vector<vector<int>>& D,
                 vector<vector<int>>& X) {
    int n = X.size();
    int half = n / 2;
    
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            X[i][j] = A[i][j];
            X[i][j + half] = B[i][j];
            X[i + half][j] = C[i][j];
            X[i + half][j + half] = D[i][j];
        }
    }
}

// Recursive matrix multiplication
vector<vector<int>> recMatMult(const vector<vector<int>>& X, const vector<vector<int>>& Y) {
    int n = X.size();
    
    // Base case: when the matrix is 1x1
    if (n == 1) {
        vector<vector<int>> Z(1, vector<int>(1));
        Z[0][0] = X[0][0] * Y[0][0];
        return Z;
    }
    
    // Splitting X and Y into quadrants
    int half = n / 2;
    vector<vector<int>> A(half, vector<int>(half));
    vector<vector<int>> B(half, vector<int>(half));
    vector<vector<int>> C(half, vector<int>(half));
    vector<vector<int>> D(half, vector<int>(half));
    vector<vector<int>> E(half, vector<int>(half));
    vector<vector<int>> F(half, vector<int>(half));
    vector<vector<int>> G(half, vector<int>(half));
    vector<vector<int>> H(half, vector<int>(half));
    
    splitMatrix(X, A, B, C, D);
    splitMatrix(Y, E, F, G, H);
    
    // Recursive calls for matrix multiplication
    vector<vector<int>> P1 = recMatMult(A, subtractMatrices(F, H));
    vector<vector<int>> P2 = recMatMult(addMatrices(A, B), H);
    vector<vector<int>> P3 = recMatMult(addMatrices(C, D), E);
    vector<vector<int>> P4 = recMatMult(D, subtractMatrices(G, E));
    vector<vector<int>> P5 = recMatMult(addMatrices(A, D), addMatrices(E, H));
    vector<vector<int>> P6 = recMatMult(subtractMatrices(B, D), addMatrices(G, H));
    vector<vector<int>> P7 = recMatMult(subtractMatrices(A, C), addMatrices(E, F));
    
    // Combining the results to form the resulting matrix
    vector<vector<int>> Z(n, vector<int>(n));
    mergeMatrix(addMatrices(subtractMatrices(addMatrices(P5, P4), P2), P6), addMatrices(P1, P2),
                addMatrices(P3, P4), subtractMatrices(subtractMatrices(addMatrices(P1, P5), P3), P7), Z);
    
    return Z;
}

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& X, const vector<vector<int>>& Y) {
    int n = X.size();
    vector<vector<int>> result(n, vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = X[i][j] + Y[i][j];
        }
    }
    
    return result;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& X, const vector<vector<int>>& Y) {
    int n = X.size();
    vector<vector<int>> result(n, vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = X[i][j] - Y[i][j];
        }
    }
    
    return result;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Example usage
    vector<vector<int>> X = { {1, 2}, {3, 4} };
    vector<vector<int>> Y = { {5, 6}, {7, 8} };
    
    vector<vector<int>> Z = recMatMult(X, Y);
    
    cout << "Matrix X:" << endl;
    printMatrix(X);
    
    cout << "Matrix Y:" << endl;
    printMatrix(Y);
    
    cout << "Resultant matrix Z:" << endl;
    printMatrix(Z);
    
    return 0;
}
