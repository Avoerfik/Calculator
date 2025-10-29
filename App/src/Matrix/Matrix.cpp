#include "../../include/Matrix/Matrix.h"

// Конструктор с размерами
Matrix::Matrix(unsigned int rows, unsigned int cols)
{
    matrix.resize(rows);
    for (unsigned int i = 0; i < rows; ++i)
    {
        matrix[i].resize(cols, "0"); // заполняем нулями или другим значением по умолчанию
    }
}

// Конструктор из вектора
Matrix::Matrix(const std::vector<std::vector<std::string>>& mat) : matrix(mat)
{

}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : matrix(other.matrix)
{

}

// Конструктор перемещения
Matrix::Matrix(Matrix&& other) noexcept : matrix(std::move(other.matrix))
{

}

// Оператор присваивания копированием
Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        matrix = other.matrix;
    }
    return *this;
}

// Оператор присваивания перемещением
Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    if (this != &other)
    {
        matrix = std::move(other.matrix);
    }
    return *this;
}

// Оператор сложения матриц
Matrix Matrix::operator+(const Matrix& other) const
{
    if (rows() != other.rows() || cols() != other.cols())
    {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix result(rows(), cols());

    for (size_t i = 0; i < rows(); ++i)
    {
        for (size_t j = 0; j < cols(); ++j)
        {
            Calculator calc;
            std::stack<std::string> expressionStack = calc.bracketAnalyze(matrix[i][j] + "+" + other.matrix[i][j]);
            std::string val = calc.calculateExpression(expressionStack);
            result.matrix[i][j] = val;
        }
    }

    return result;
}

// Оператор вычитания матриц
Matrix Matrix::operator-(const Matrix& other) const
{
    if (matrix.size() != other.matrix.size() ||
        (matrix.size() > 0 && matrix[0].size() != other.matrix[0].size()))
    {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }

    Matrix result(matrix.size(), matrix.empty() ? 0 : matrix[0].size());

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            Calculator calc;
            std::stack<std::string> expressionStack = calc.bracketAnalyze(matrix[i][j] + "-" + other.matrix[i][j]);
            std::string val = calc.calculateExpression(expressionStack);
            result.matrix[i][j] = val;
        }
    }

    return result;
}

// Оператор умножения матриц
Matrix Matrix::operator*(const Matrix& other) const
{
    if (matrix.empty() || other.matrix.empty() ||
        matrix[0].size() != other.matrix.size())
    {
        throw std::invalid_argument("Matrix dimensions are incompatible for multiplication");
    }

    size_t rows = matrix.size();
    size_t cols = other.matrix[0].size();
    size_t common = matrix[0].size();

    Matrix result(rows, cols);

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            std::string sum = "0";
            for (size_t k = 0; k < common; ++k)
            {
                Calculator calc;
                std::stack<std::string> expressionStack = calc.bracketAnalyze("(" + matrix[i][k] + ")*(" + other.matrix[k][j] + ")");
                std::string val = calc.calculateExpression(expressionStack);
                std::stack<std::string> expressionStackResult = calc.bracketAnalyze("(" + sum + ")+(" + val + ")");
                sum = calc.calculateExpression(expressionStackResult);
            }
            result.matrix[i][j] = sum;
        }
    }

    return result;
}

// Оператор умножения на скаляр
Matrix Matrix::operator*(double scalar) const
{
    Matrix result(matrix.size(), matrix.empty() ? 0 : matrix[0].size());

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            Calculator calc;
            std::stack<std::string> expressionStack = calc.bracketAnalyze(matrix[i][j]);
            std::string val = calc.calculateExpression(expressionStack);
            std::stack<std::string> expressionStackResult = calc.bracketAnalyze(val + "*" + std::to_string(scalar));
            std::string mult = calc.calculateExpression(expressionStackResult);
            result.matrix[i][j] = mult;
        }
    }

    return result;
}

// Дружественная функция для умножения скаляра на матрицу
Matrix operator*(double scalar, const Matrix& mat)
{
    return mat * scalar;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{
    for (const auto& row : mat.matrix)
    {
        for (size_t j = 0; j < row.size(); ++j)
        {
            os << row[j];
            if (j < row.size() - 1)
                os << " ";
        }
        os << "\n";
    }
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Matrix& mat)
{
    try
    {
        mat.matrix.clear();
        std::string line;
        std::size_t rowsCount = 0;

        while (std::getline(is, line) && !line.empty())
        {
            std::vector<std::string> row;
            std::istringstream iss(line);
            std::string element;

            while (iss >> element)
            {
                row.push_back(element);
            }

            if (!row.empty())
            {
                std::vector<std::string> newrow;
                for (const auto& i : row)
                {
                    Calculator calc;
                    std::stack<std::string> expressionStack = calc.bracketAnalyze(i);
                    std::string val = calc.calculateExpression(expressionStack);
                    newrow.push_back(val);
                }

                mat.matrix.push_back(newrow);
                ++rowsCount;
            }
            else
            {
                throw std::runtime_error("Empty row");
            }
        }
        for (size_t i = 0; i < rowsCount; i++)
        {            
            if (mat.matrix[0].size() != mat.matrix[i].size()) throw std::runtime_error("Invalid data format");
        }
        if (mat.matrix.empty()) throw std::runtime_error("Empty matrix");
    }
    catch (const std::exception&)
    {
        throw;
    }
    

    return is;
}