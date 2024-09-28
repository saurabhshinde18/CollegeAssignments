#include <iostream>
#include <vector>
using namespace std;

struct SparseMatrixElement {
    int row;
    int col;
    int value;
};

vector<SparseMatrixElement> toSparseMatrix(int denseMatrix[][100], int rows, int cols) {
    vector<SparseMatrixElement> sparseMatrix;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (denseMatrix[i][j] != 0) {
                SparseMatrixElement element = {i, j, denseMatrix[i][j]};
                sparseMatrix.push_back(element);
            }
        }
    }
    return sparseMatrix;
}

vector<SparseMatrixElement> transposeSparseMatrix(const vector<SparseMatrixElement>& sparseMatrix) {
    vector<SparseMatrixElement> transposed;
    for (const auto& element : sparseMatrix) {
        SparseMatrixElement transposedElement = {element.col, element.row, element.value};
        transposed.push_back(transposedElement);
    }
    return transposed;
}

void displaySparseMatrix(const vector<SparseMatrixElement>& sparseMatrix) {
    cout << "Row\tColumn\tValue" << endl;
    for (const auto& element : sparseMatrix) {
        cout << element.row << "\t" << element.col << "\t" << element.value << endl;
    }
}

int main() {
    const int rows = 4;
    const int cols = 4;
    int denseMatrix[100][100] = {
        {0, 0, 3, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 2, 0, 4}
    };
    vector<SparseMatrixElement> sparseMatrix = toSparseMatrix(denseMatrix, rows, cols);
    cout << "Sparse Matrix Representation:" << endl;
    displaySparseMatrix(sparseMatrix);
    vector<SparseMatrixElement> transposedMatrix = transposeSparseMatrix(sparseMatrix);
    cout << "\nTransposed Sparse Matrix Representation:" << endl;
    displaySparseMatrix(transposedMatrix);
    return 0;
}

