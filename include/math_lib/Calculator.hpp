#pragma once

#include <stdexcept>
#include <climits>
#include <string>



// Твоя структура с понятными именами полей
struct CalculationData {
    std::string operation;
    int first_number;    // Вместо a
    int second_number;   // Вместо b
    int factorial_n;     // Вместо n
};

namespace math_lib {

class Calculator {
public:
    // Помечаем методы как const, так как они не меняют состояние объекта
    // inline необходим для header-only библиотек
    inline int calculate(const CalculationData &data) const {
        if (data.operation == "add")  return add(data.first_number, data.second_number);
        if (data.operation == "sub")  return sub(data.first_number, data.second_number);
        if (data.operation == "mul")  return mul(data.first_number, data.second_number);
        if (data.operation == "div")  return div(data.first_number, data.second_number);
        if (data.operation == "pow")  return pow(data.first_number, data.second_number);
        if (data.operation == "fact") return fact(data.factorial_n);

        throw std::runtime_error("Unsupported operation: " + data.operation);
    }

    inline int add(int a, int b) const {
        if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
            throw std::overflow_error("Addition overflow");
        }
        return a + b;
    }

    inline int sub(int a, int b) const {
        if ((b > 0 && a < INT_MIN + b) || (b < 0 && a > INT_MAX + b)) {
            throw std::overflow_error("Subtraction overflow");
        }
        return a - b;
    }

    inline int mul(int a, int b) const {
        if (a > 0 && b > 0 && a > INT_MAX / b) throw std::overflow_error("Multiplication overflow");
        if (a > 0 && b < 0 && b < INT_MIN / a) throw std::overflow_error("Multiplication overflow");
        if (a < 0 && b > 0 && a < INT_MIN / b) throw std::overflow_error("Multiplication overflow");
        if (a < 0 && b < 0 && (a == INT_MIN || b == INT_MIN || -a > INT_MAX / -b)) {
            throw std::overflow_error("Multiplication overflow");
        }
        return a * b;
    }

    inline int div(int a, int b) const {
        if (b == 0) throw std::runtime_error("Division by zero");
        if (a == INT_MIN && b == -1) throw std::overflow_error("Division overflow");
        return a / b;
    }

    inline int pow(int base, int exp) const {
        if (exp < 0) throw std::runtime_error("Negative exponent not supported");
        if (exp == 0) return 1;
        int res = 1;
        for (int i = 0; i < exp; ++i) res = mul(res, base);
        return res;
    }

    inline int fact(int n) const {
        if (n < 0) throw std::runtime_error("Factorial of negative number");
        if (n == 0 || n == 1) return 1;
        return mul(n, fact(n - 1));
    }
};

} // namespace math_lib
