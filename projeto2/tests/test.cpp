/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */

#include <gtest/gtest.h>
#include <fstream>
#include <list>
#include "aux/Connection.hpp"

class FalkTest : public ::testing::Test {};

namespace {
    class Container {
     public:
        template<typename... Args>
        void add(Args&&... strings) {
            values.emplace_back();
            internal_add(values.back(), std::forward<Args>(strings)...);
        }

        auto begin() { return values.begin(); }
        auto begin() const { return values.cbegin(); }
        auto end() { return values.end(); }
        auto end() const { return values.cend(); }

     private:
        std::list<std::string> values;

        void internal_add(std::string&) {}

        template<typename... Args>
        void internal_add(std::string& container, const std::string& first, Args&&... strings) {
            container += first + "\n";
            internal_add(container, strings...);
        }
    };

    bool run(const std::string& in, const std::string& actual, const std::string& expected, bool padded) {
        static constexpr auto restore = "\033[0m";
        static constexpr auto red = "\033[;31m";
        static constexpr auto green = "\033[;32m";
        static constexpr auto blue = "\033[;34m";
        if (expected != actual) {
            std::cout << red << "Failure in: " << restore << std::endl << in << std::endl;
            std::cout << green << "Expected: " << restore << std::endl << expected << std::endl;
            std::cout << blue << "Actual: " << restore << std::endl << actual;
            if (padded) {
                std::cout << green << "(...)" << restore;
            }
            std::cout << std::endl;
            return false;
        }
        return true;
    };

    void run_tests(const Container& inputs, const Container& outputs) {
        auto out_it = outputs.begin();
        for (auto in_it = inputs.begin(); in_it != inputs.end(); ++in_it) {
            auto& in = *in_it;
            auto& expected = *out_it;
            Connection program("./bin/falk", "0", "0");
            program.send(in + "\n");
            auto actual = program.receive();

            bool padded = false;
            if (actual.size() >= expected.size()) {
                actual = actual.substr(0, expected.size());
                padded = true;
            }

            if (!run(in, actual, expected, padded)) {
                break;
            }
            ++out_it;
        }
    }

    std::string read_file(const std::string& name) {
        std::string result;
        std::ifstream stream(name, std::ifstream::in);
        if (stream.is_open()) {
            std::stringstream ss;
            result += stream.get();
            while (stream.good()) {
                result += stream.get();
            }
            result = result.substr(0, result.size() - 1);
        } else {
            std::cout << "Couldn't read file '" << name << "'" << std::endl;
        }
        return result;
    }

    void run_test(const std::string& in_file, const std::string& out_file) {
        Connection program("./bin/falk", "0", "0", in_file.c_str());
        auto expected = read_file(out_file);
        auto actual = program.receive();

        bool padded = false;
        if (actual.size() >= expected.size()) {
            actual = actual.substr(0, expected.size());
            padded = true;
        }

        run("[content of " + in_file + "]", actual, expected, padded);
    }
}

TEST_F(FalkTest, interpreter_v0) {
    Container inputs;
    Container outputs;
    inputs.add("2 + 2");
    outputs.add("res = 4");

    inputs.add("2 - 2");
    outputs.add("res = 0");

    inputs.add("2 * 3");
    outputs.add("res = 6");

    inputs.add("2 / 4");
    outputs.add("res = 0.5");

    inputs.add("2 ** 3");
    outputs.add("res = 8");

    inputs.add("40 % 5");
    outputs.add("res = 0");

    inputs.add("40 % 6");
    outputs.add("res = 4");

    inputs.add("2 + 2 * 2 + 2");
    outputs.add("res = 8");

    inputs.add("1/0");
    outputs.add("res = inf");

    inputs.add("-1/0");
    outputs.add("res = -inf");

    inputs.add("0/0");
    outputs.add("res = -nan");

    inputs.add("2 + -1");
    outputs.add("res = 1");

    inputs.add("2 - +1");
    outputs.add("res = 1");

    inputs.add("--1");
    outputs.add("res = 1");

    inputs.add("22i + 38 - 7i + 12");
    outputs.add("res = 50 + 15i");

    inputs.add("-(7 * -1) % 2");
    outputs.add("res = 1");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v1) {
    Container inputs;
    Container outputs;
    inputs.add("2 > 3");
    outputs.add("res = false");

    inputs.add("3 > 2");
    outputs.add("res = true");

    inputs.add("1 <> 1");
    outputs.add("res = false");

    inputs.add("1 == 1");
    outputs.add("res = true");

    inputs.add("1 <> 2");
    outputs.add("res = true");

    inputs.add("true & false");
    outputs.add("res = false");

    inputs.add("true | false");
    outputs.add("res = true");

    inputs.add("1 > [1]");
    outputs.add("[Line 0] semantic error: cannot compare scalar and array");

    inputs.add("1 > [[1]]");
    outputs.add("[Line 0] semantic error: cannot compare scalar and matrix");

    inputs.add("[1] > 1");
    outputs.add("[Line 0] semantic error: cannot compare array and scalar");

    inputs.add("[1] > [[1]]");
    outputs.add("[Line 0] semantic error: cannot compare array and matrix");

    inputs.add("[[1]] > 1");
    outputs.add("[Line 0] semantic error: cannot compare matrix and scalar");

    inputs.add("[[1]] > [1]");
    outputs.add("[Line 0] semantic error: cannot compare matrix and array");

    inputs.add("1", "// ignore this", "2");
    outputs.add("res = 1", "res = 2");

    inputs.add("1", "/* ignore", "this */", "2");
    outputs.add("res = 1", "res = 2");

    inputs.add("1", "/* ignore", "this */ 2");
    outputs.add("res = 1", "res = 2");

    inputs.add("1", "/**/", "2");
    outputs.add("res = 1", "res = 2");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v2) {
    Container inputs;
    Container outputs;
    inputs.add("[[1,2,4],[8,16,32]] * [[1,2,3],[4,5,6],[7,8,9]]");
    outputs.add("res = [[37, 44, 51], [296, 352, 408]]");

    inputs.add("2 * [2,4]");
    outputs.add("res = [4, 8]");

    inputs.add("[2,4] * [[1,2,3],[4,5,6]]");
    outputs.add("res = [[18, 24, 30]]");

    inputs.add("[1,2,3] + [1,2,3,4]");
    outputs.add("[Line 0] semantic error: array size mismatch (3 and 4)");

    inputs.add("[[1,2]] + [[7]]");
    outputs.add("[Line 0] semantic error: column count mismatch (2 and 1)");

    inputs.add("[[1],[2]] + [[42]]");
    outputs.add("[Line 0] semantic error: row count mismatch (2 and 1)");

    inputs.add("[[1,2,3],[4,5,6]] * [[1,2],[3,4]]");
    outputs.add("[Line 0] semantic error: the number of columns of the first "
        "matrix (3) must be equal to the number of rows of the second matrix (2)");

    inputs.add("[242 * 3i] / [[42, 74]]");
    outputs.add("[Line 0] semantic error: illegal operation: matrix division");

    inputs.add("[34i ** 2] % [[25, 9 * 7]]");
    outputs.add("[Line 0] semantic error: illegal operation: matrix modulus");

    inputs.add("[[912873987]] ** [[28 ** 3, 94 % 7]]");
    outputs.add("[Line 0] semantic error: illegal operation: matrix exponentiation");

    inputs.add("(242 * 3i) / [[42, 74]]");
    outputs.add("res = [[0 + 17.2857i, 0 + 9.81081i]]");

    inputs.add("(34i * 2 / 1i) % 25");
    outputs.add("[Line 0] semantic error: illegal operation: complex modulus");

    inputs.add("var a = [2]");
    outputs.add("[Line 0] semantic error: cannot assign array to scalar");

    inputs.add("var a = [[2]]");
    outputs.add("[Line 0] semantic error: cannot assign matrix to scalar");

    inputs.add("array a = 1");
    outputs.add("[Line 0] semantic error: cannot assign scalar to array");

    inputs.add("array a = [[1]]");
    outputs.add("[Line 0] semantic error: cannot assign matrix to array");

    inputs.add("matrix a = 1");
    outputs.add("[Line 0] semantic error: cannot assign scalar to matrix");

    inputs.add("matrix a = [1]");
    outputs.add("[Line 0] semantic error: cannot assign array to matrix");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v3) {
    Container inputs;
    Container outputs;
    inputs.add("var a = 42 * 77", "a");
    outputs.add("res = 3234");

    inputs.add("array a = [20 * 18, 37, 4] + [3, 2, 1]", "a");
    outputs.add("res = [363, 39, 5]");

    inputs.add("matrix a = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]", "a");
    outputs.add("res = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]");

    inputs.add("array a = [3, 5, 7]", "a = 1", "a");
    outputs.add("res = [1, 1, 1]");

    inputs.add("array a = [3, 5, 7]", "a = false", "a");
    outputs.add("res = [0, 0, 0]");

    inputs.add("array a = [3, 5, 7]", "a = 3 + 2i", "a");
    outputs.add("res = [3, 3, 3]");

    inputs.add("matrix a = [[1, 2], [3, 4]]", "a = 42", "a");
    outputs.add("res = [[42, 42], [42, 42]]");

    inputs.add("matrix a = [[1, 2], [3, 4]]", "a = false", "a");
    outputs.add("res = [[0, 0], [0, 0]]");

    inputs.add("matrix a = [[1, 2], [3, 4]]", "a = 3 + 2i", "a");
    outputs.add("res = [[3, 3], [3, 3]]");

    inputs.add("array a = [3, 5, 7]", "a += [1, 2, 3]", "a");
    outputs.add("res = [4, 7, 10]");

    inputs.add("matrix a = [[1,2],[3,4]]", "a += [[1, 0], [0, 1]]", "a");
    outputs.add("res = [[2, 2], [3, 5]]");

    inputs.add("array a = [1, 2, 3, 4, 5]", "a", "res + 1");
    outputs.add("res = [1, 2, 3, 4, 5]", "res = [2, 3, 4, 5, 6]");

    inputs.add("var a = 42", "var b = 2i", "a + b");
    outputs.add("res = 42 + 2i");

    inputs.add("var a = false", "a += 1", "a");
    outputs.add("res = true");

    inputs.add("var a = [1]");
    outputs.add("[Line 0] semantic error: cannot assign array to scalar");

    inputs.add("var a = [[1]]");
    outputs.add("[Line 0] semantic error: cannot assign matrix to scalar");

    inputs.add("array a = 1");
    outputs.add("[Line 0] semantic error: cannot assign scalar to array");

    inputs.add("array a = [[1]]");
    outputs.add("[Line 0] semantic error: cannot assign matrix to array");

    inputs.add("matrix a = 1");
    outputs.add("[Line 0] semantic error: cannot assign scalar to matrix");

    inputs.add("matrix a = [1]");
    outputs.add("[Line 0] semantic error: cannot assign array to matrix");

    inputs.add("matrix a = [[1,2],[3,4]]", "a *= [[1,2,3],[4,5,6]]");
    outputs.add("[Line 1] semantic error: second matrix must be square (found a 2 x 3 matrix instead)");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v4) {
    Container inputs;
    Container outputs;
    inputs.add("if (true):", "2 + 2", ".");
    outputs.add("res = 4");

    inputs.add("if (false):", "2 + 2", ". else:", "3 + 3", ".");
    outputs.add("res = 6");

    inputs.add("var a = 3", "if (a < 10):", "a = 8", ". else:", "a = 13", ".", "a");
    outputs.add("res = 8");

    inputs.add("var a = 42", "if (a < 10):", "a = 8", ". else:", "a = 13", ".", "a");
    outputs.add("res = 13");

    inputs.add("var a = 1", "if (a < 5):", "var a = 10", "if (a > 5):", "1",
        ". else:", "2", ".", "a", ". else:", "3", ".", "a");
    outputs.add("res = 1", "res = 10", "res = 1");

    inputs.add("if ([1]):", "2 + 2", ".");
    outputs.add("[Line 2] semantic error: non-boolean condition");

    inputs.add("if ([[1]]):", "42", ".");
    outputs.add("[Line 2] semantic error: non-boolean condition");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v5) {
    Container inputs;
    Container outputs;
    inputs.add("var a = 1", "while (a < 5):", "a", "a += 1", ".");
    outputs.add("res = 1", "res = 2", "res = 3", "res = 4");

    inputs.add("var a = 1", "while (a < 5):", "a", "a += 1",
        "if (a == 3):", "a += 1", ".", ".");
    outputs.add("res = 1", "res = 2", "res = 4");

    inputs.add("var a = 1", "var b = 9", "while (a != 5 | b != 5):",
        "a ** b", "a += 1", "b -= 1", ".");
    outputs.add("res = 1", "res = 256", "res = 2187", "res = 4096");

    inputs.add("while (false):", "nope", ".", "1");
    outputs.add("res = 1");

    inputs.add("while ([70 * 47]):", "2 + 2", ".");
    outputs.add("[Line 2] semantic error: non-boolean condition");

    inputs.add("while ([[53]]):", "42", ".");
    outputs.add("[Line 2] semantic error: non-boolean condition");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v6) {
    Container inputs;
    Container outputs;
    inputs.add("function f(array a, array b): return a + b.", "f([1, 2], [4, 7])");
    outputs.add("res = [5, 9]");

    inputs.add("function f(matrix a, matrix b): return a + b.", "f([[1, 2]], [[4, 7]])");
    outputs.add("res = [[5, 9]]");

    inputs.add("function f(): return 2.", "function f(): return -1.");
    outputs.add("[Line 1] semantic error: re-declaration of symbol f");

    inputs.add("function f(): return -1.", "var g = 42", "f", "g()");
    outputs.add("[Line 2] semantic error: f is not a variable",
                "[Line 3] semantic error: g is not a function");

    inputs.add("j()");
    outputs.add("[Line 0] semantic error: undeclared function j");

    inputs.add("function f(array[1] x): x.", "f([1,2])");
    outputs.add("[Line 1] semantic error: mismatching array size for parameter "
        "x in function f (expected 1, got 2)");

    inputs.add("function f(matrix[2,3] x): x.", "f([[1,2]])");
    outputs.add("[Line 1] semantic error: mismatching matrix size for parameter "
        "x in function f (expected 2 x 3, got 1 x 2)");

    inputs.add("function f(var x): x.", "f(1, 2)");
    outputs.add("[Line 1] semantic error: mismatching parameter count for "
        "function f (expected 1, got 2)");

    inputs.add("undef f");
    outputs.add("[Line 0] semantic error: undeclared function f");

    inputs.add("var g = 42", "undef g");
    outputs.add("[Line 1] semantic error: g is not a function");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v8) {
    Container inputs;
    Container outputs;
    inputs.add("function sum(array x):", "var c : typeof x[0];",
        "for (e in x): c += e.", "return c.", "sum([1, 2, 3, 4])");
    outputs.add("res = 10");

    inputs.add("auto a = 42", "auto b = [42]", "auto c = [[42]]", "a", "b", "c");
    outputs.add("res = 42", "res = [42]", "res = [[42]]");

    inputs.add("array a = [1, 2]", "var x : typeof a");
    outputs.add("[Line 1] semantic error: typeof expects a scalar");

    inputs.add("matrix a = [[1, 2], [7, 21]]", "var x : typeof a");
    outputs.add("[Line 1] semantic error: typeof expects a scalar");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v9) {
    Container inputs;
    Container outputs;
    inputs.add("array a = [1, 2, 3]", "a[1] = 4", "a");
    outputs.add("res = [1, 4, 3]");

    inputs.add("matrix b = [[1, 0], [0, 1]]", "b[1] = [4, 5]",
        "b[,1] = [7, 8]", "b[1,1] = 3", "b");
    outputs.add("res = [[1, 7], [4, 3]]");

    inputs.add("array[3] a : real", "a");
    outputs.add("res = [0, 0, 0]");

    inputs.add("var x : real", "array[[x]] a : real");
    outputs.add("[Line 1] semantic error: the size must be a scalar");

    inputs.add("var x : real", "matrix[2, [x]] a : real");
    outputs.add("[Line 1] semantic error: the size must be a scalar");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v10) {
    run_test("tests/cases/1.falk", "tests/cases/1.out");
    run_test("tests/cases/2.falk", "tests/cases/2.out");
    run_test("tests/cases/3.falk", "tests/cases/3.out");
}

int main(int argc, char** argv) {
    constexpr double min_version = 0;
    constexpr double latest_stable = 1;

    ::testing::InitGoogleTest(&argc, argv);
    const std::string tests = [&] {
        std::string result;
        double version = (argc == 1) ? latest_stable : std::atof(argv[1]);
        // version = std::min(max_version, std::max(min_version, version));
        version = std::max(min_version, version);
        bool colon = false;
        for (auto i = min_version; i <= version + 0.05; i += 0.1) {
            if (colon) {
                result += ":";
            }
            result += "*interpreter_v" + std::to_string(static_cast<int>((i + 0.05) * 10));
            colon = true;
        }
        return result;
    }();
    if (argc <= 1 || argv[1] != std::string("hardcore")) {
        ::testing::GTEST_FLAG(filter) = tests;
    }
    return RUN_ALL_TESTS();
}
