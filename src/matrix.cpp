#include <iostream>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;

struct Dimensions{
    size_t rows;
    size_t columns;
};

class Matrix {
public:
    vector<vector<float>> matrix;
    
    Matrix(vector<vector<float>> matrix) : matrix(matrix) {}
    Matrix() : matrix() {}

    void print() const {
        for (auto i : this->matrix) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    Dimensions getDim() const {
        Dimensions dimensions = {this->matrix.size(), this->matrix[0].size()};
        return dimensions;
    }

    static Matrix dot(const Matrix& m1, const Matrix& m2) {
        Dimensions dim1 = m1.getDim();
        Dimensions dim2 = m2.getDim();
        if (dim1.columns != dim2.rows) {
            cout << "invalid dimensions" << endl;
            return Matrix();
        }
        vector<vector<float>> temp(dim1.rows, vector<float>(dim2.columns, 0));

        for (int i = 0; i < dim1.rows; ++i) {
            for (int j = 0; j < dim2.columns; ++j) {
                for (int k = 0; k < dim1.columns; ++k) {
                    temp[i][j] += (m1.matrix[i][k] * m2.matrix[k][j]);
                }
            }
        }
        return Matrix(temp);
    }
};

// Binding code
namespace py = pybind11;

PYBIND11_MODULE(matrix_module, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<>())
        .def(py::init<const vector<vector<float>>&>())
        .def("print", &Matrix::print)
        .def("getDim", &Matrix::getDim)
        .def_static("dot", &Matrix::dot);
}
