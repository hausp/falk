/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */

#include <gtest/gtest.h>
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
            Connection program("./bin/falk", "0");
            program.send(in + "\n");
            auto actual = program.receive();

            // std::cout << "satan: [" << actual << "]" << std::endl;
            actual = actual.substr(6);

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
}

TEST_F(FalkTest, interpreter_v1) {
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

TEST_F(FalkTest, interpreter_v3) {
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

    // TODO: wtf?
    // inputs.add("(34i * 2 / 1i) % [[25, 9 * 7]]");
    // outputs.add("res = [[68 + 0i, 68 + 0i]]");

    // TODO: wtf?
    // inputs.add("912873987 ** [[28 ** 3, 94 % 7]]");
    // outputs.add("[Line 0] semantic error: illegal operation: matrix exponentiation");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v4) {
    Container inputs;
    Container outputs;
    inputs.add("var a = 42 * 77", "a");
    outputs.add("falk> res = 3234");

    inputs.add("array a = [20 * 18, 37, 4] + [3, 2, 1]", "a");
    outputs.add("falk> res = [363, 39, 5]");

    inputs.add("matrix a = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]", "a");
    outputs.add("falk> res = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]");

    // TODO: wtf?
    // inputs.add("var a = 42", "var b = 2i", "a + b");
    // outputs.add("falk> falk> res = 42 + 2i");

    inputs.add("var a = false", "a += 1", "a");
    outputs.add("falk> falk> res = true");

    inputs.add("var a = [5]");
    outputs.add("[Line 0] semantic error: cannot assign array to scalar");

    inputs.add("var a = [[5]]");
    outputs.add("[Line 0] semantic error: cannot assign matrix to scalar");

    inputs.add("array a = 5");
    outputs.add("[Line 0] semantic error: cannot assign scalar to array");

    inputs.add("array a = [[5]]");
    outputs.add("[Line 0] semantic error: cannot assign matrix to array");

    inputs.add("matrix a = 42");
    outputs.add("[Line 0] semantic error: cannot assign scalar to matrix");

    inputs.add("matrix a = [42]");
    outputs.add("[Line 0] semantic error: cannot assign array to matrix");

    // TODO: test other assignment types
    // inputs.add("");
    // outputs.add("");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v5) {
    Container inputs;
    Container outputs;
    inputs.add("if (true):", "2 + 2", ".");
    outputs.add("res = 4");

    inputs.add("if (false):", "2 + 2", ". else:", "3 + 3", ".");
    outputs.add("res = 6");

    // inputs.add("");
    // outputs.add("");

    // inputs.add("");
    // outputs.add("");

    // inputs.add("");
    // outputs.add("");

    // inputs.add("");
    // outputs.add("");

    // inputs.add("");
    // outputs.add("");

    run_tests(inputs, outputs);
}

// TEST_F(FalkTest, interpreter_v98) {
//     Container inputs;
//     Container outputs;
//     inputs.add("var a@");
//     outputs.add("[Line 1] lexical error: unknown symbol @");

//     inputs.add("var #####a");
//     outputs.add("[Line 1] lexical error: unknown symbol #####");

//     inputs.add("var 10b");
//     outputs.add("[Line 1] syntax error");

//     inputs.add("A = 2");
//     outputs.add("[Line 1] semantic error: undeclared variable A");

//     inputs.add("var a", "var a");
//     outputs.add("[Line 2] semantic error: re-declaration of variable a");

//     inputs.add("var a");
//     outputs.add("");

//     inputs.add("var a = 2");
//     outputs.add("");

//     inputs.add("array[2] a", "array b = a");
//     outputs.add("");

//     inputs.add("matrix[2,2] a", "matrix b = a");
//     outputs.add("");

//     run_tests(inputs, outputs);
// }

// TEST_F(FalkTest, interpreter_v99) {
//     Container inputs;
//     Container outputs;
//     inputs.add("var a = 2 + 2", "var b = 7 - 4", "a + b");
//     outputs.add("res = 7");

//     inputs.add("var a = 2", "var b = a ** a", "a * b");
//     outputs.add("res = 8");

//     inputs.add("array a = [1, 2, 3]", "a + 1");
//     outputs.add("res = [2, 3, 4]");

//     inputs.add("matrix a = [[1,0,0],[0,1,0],[0,0,1]]", "a * 2");
//     outputs.add("res = [[2,0,0],[0,2,0],[0,0,2]]");

//     inputs.add("array a = [1, 2, 3]", "array b = [1, 3, 6]", "a + b");
//     outputs.add("res = [2, 5, 9]");

//     inputs.add("array a = [1, 2, 3]", "array b = [1, 3]", "a + b");
//     outputs.add("[Line 3] semantic error: non-compatible size array operation");

//     inputs.add("matrix a = [[1,0,0],[0,1,0],[0,0,1]]", "matrix b = [[1,0,0],[0,1,0]]", "a + b");
//     outputs.add("[Line 3] semantic error: non-compatible size matrix operation");

//     inputs.add("matrix a = [[1,0,0],[0,1,0],[1,0,0]]", "matrix b = [[1,1,1],[0,0,0],[0,0,0]]", "a * b");
//     outputs.add("res = [[1,1,1],[0,0,0],[1,1,1]]");

//     inputs.add("matrix a = [[1,0,0],[0,1,0],[1,0,0]]", "matrix b = [[1,1],[0,0],[0,0]]", "a * b");
//     outputs.add("res = [[1,1],[0,0],[1,1]]");

//     inputs.add("matrix a = [[1,0,0],[0,1,0],[1,0,0]]", "matrix b = [[1,1,1],[0,0,0]]", "a * b");
//     outputs.add("[Line 3] semantic error: non-compatible size matrix operation");

//     run_tests(inputs, outputs);
// }

int main(int argc, char** argv) {
    constexpr auto min_version = 0.1;
    constexpr auto latest_stable = 0.1;

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
    ::testing::GTEST_FLAG(filter) = tests;
    return RUN_ALL_TESTS();
}
