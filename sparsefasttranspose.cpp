#include <iostream>
#include <vector>

using namespace std;

struct SparseMatrix {
    vector<int> row;
    vector<int> col;
    vector<int> val;
    int nonZeroCount;

    SparseMatrix(int n) : nonZeroCount(0) {
        row.reserve(n);
        col.reserve(n);
        val.reserve(n);
    }
};

SparseMatrix denseToSparse(int** denseMatrix, int rows, int cols) {
    SparseMatrix sparseMatrix(rows * cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (denseMatrix[i][j] != 0) {
                sparseMatrix.row.push_back(i);
                sparseMatrix.col.push_back(j);
                sparseMatrix.val.push_back(denseMatrix[i][j]);
                sparseMatrix.nonZeroCount++;
            }
        }
    }

    return sparseMatrix;
}

SparseMatrix fastTranspose(const SparseMatrix& sparseMatrix, int totalRows, int totalCols) {
    SparseMatrix transposedMatrix(sparseMatrix.nonZeroCount);
    vector<int> count(totalCols, 0);

    for (int j = 0; j < sparseMatrix.nonZeroCount; j++) {
        count[sparseMatrix.col[j]]++;
    }

    for (int i = 1; i < totalCols; i++) {
        count[i] += count[i - 1];
    }

    for (int j = sparseMatrix.nonZeroCount - 1; j >= 0; j--) {
        int colIndex = sparseMatrix.col[j];
        int rowIndex = sparseMatrix.row[j];
        int pos = count[colIndex] - 1;

        transposedMatrix.row[pos] = rowIndex;
        transposedMatrix.col[pos] = colIndex;
        transposedMatrix.val[pos] = sparseMatrix.val[j];
        count[colIndex]--;
    }

    transposedMatrix.nonZeroCount = sparseMatrix.nonZeroCount;
    return transposedMatrix;
}

void displaySparseMatrix(const SparseMatrix& sparseMatrix) {
    cout << "Row\tCol\tValue" << endl;
    for (int i = 0; i < sparseMatrix.nonZeroCount; i++) {
        cout << sparseMatrix.row[i] << "\t" << sparseMatrix.col[i] << "\t" << sparseMatrix.val[i] << endl;
    }
}

int main() {
    int rows = 3;
    int cols = 4;

    int** denseMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        denseMatrix[i] = new int[cols] {0};
    }

    denseMatrix[0][1] = 1;
    denseMatrix[1][0] = 2;
    denseMatrix[1][3] = 3;
    denseMatrix[2][2] = 4;

    SparseMatrix sparseMatrix = denseToSparse(denseMatrix, rows, cols);
    cout << "Sparse Matrix:" << endl;
    displaySparseMatrix(sparseMatrix);

    SparseMatrix transposedMatrix = fastTranspose(sparseMatrix, cols, rows);
    cout << "\nTransposed Sparse Matrix:" << endl;
    displaySparseMatrix(transposedMatrix);

    for (int i = 0; i < rows; i++) {
        delete[] denseMatrix[i];
    }
    delete[] denseMatrix;

    return 0;
}

