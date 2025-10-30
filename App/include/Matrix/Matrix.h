#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <stdexcept>

#include "CalculatorMatrix.h"

class Matrix : public CalculatorMatrix
{
public:
    // Конструктор по умолчанию (добавлен для полноты)
    Matrix() = default;

    // Конструктор с размерами
    Matrix(std::size_t rows, std::size_t cols);

    // Конструктор из вектора
    Matrix(const std::vector<std::vector<std::string>>& mat);

    // Конструктор копирования
    Matrix(const Matrix& other);

    // Конструктор перемещения
    Matrix(Matrix&& other) noexcept;

    // Оператор присваивания копированием
    Matrix& operator=(const Matrix& other);

    // Оператор присваивания перемещением
    Matrix& operator=(Matrix&& other) noexcept;

    // Оператор сложения матриц
    Matrix operator+(const Matrix& other) const;

    // Оператор вычитания матриц
    Matrix operator-(const Matrix& other) const;

    // Оператор умножения матриц
    Matrix operator*(const Matrix& other) const;

    // Оператор умножения на скаляр
    Matrix operator*(double scalar) const;

    // Дружественная функция для умножения скаляра на матрицу
    friend Matrix operator*(double scalar, const Matrix& mat);

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

    // Оператор ввода
    friend std::istream& operator>>(std::istream& is, Matrix& mat);

    // Методы для получения размеров
    size_t rows() const { return matrix.size(); }
    size_t cols() const { return matrix.empty() ? 0 : matrix[0].size(); }

    // Методы доступа к элементам
    std::string& at(std::size_t i, std::size_t j) { return matrix[i][j]; }
    const std::string& at(std::size_t i, std::size_t j) const { return matrix[i][j]; }

private:
    std::vector<std::vector<std::string>> matrix;
};

#endif // !MATRIX_H