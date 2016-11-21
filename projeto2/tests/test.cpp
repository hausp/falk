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
            Connection program("./bin/execute_me");
            program.send(in + "\n hello darkness my old friend");
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

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v2) {
    Container inputs;
    Container outputs;
    inputs.add("var a@");
    outputs.add("[Line 1] lexical error: unknown symbol @");

    inputs.add("var #####a");
    outputs.add("[Line 1] lexical error: unknown symbol #####");

    inputs.add("var 10b");
    outputs.add("[Line 1] syntax error");

    inputs.add("A = 2");
    outputs.add("[Line 1] semantic error: undeclared variable A");

    inputs.add("var a", "var a");
    outputs.add("[Line 2] semantic error: re-declaration of variable a");

    inputs.add("var a");
    outputs.add("");

    inputs.add("var a = 2");
    outputs.add("");

    inputs.add("array[2] a", "array b = a");
    outputs.add("");

    inputs.add("matrix[2,2] a", "matrix b = a");
    outputs.add("");

    run_tests(inputs, outputs);
}

TEST_F(FalkTest, interpreter_v3) {
    Container inputs;
    Container outputs;
    inputs.add("var a = 2 + 2", "var b = 7 - 4", "a + b");
    outputs.add("res = 7");

    inputs.add("var a = 2", "var b = a ** a", "a * b");
    outputs.add("res = 8");

    inputs.add("array a = [1, 2, 3]", "a + 1");
    outputs.add("res = [2, 3, 4]");

    inputs.add("matrix a = [[1,0,0],[0,1,0],[0,0,1]]", "a * 2");
    outputs.add("res = [[2,0,0],[0,2,0],[0,0,2]]");

    inputs.add("array a = [1, 2, 3]", "array b = [1, 3, 6]", "a + b");
    outputs.add("res = [2, 5, 9]");

    inputs.add("array a = [1, 2, 3]", "array b = [1, 3]", "a + b");
    outputs.add("[Line 3] semantic error: non-compatible size array operation");

    inputs.add("matrix a = [[1,0,0],[0,1,0],[0,0,1]]", "matrix b = [[1,0,0],[0,1,0]]", "a + b");
    outputs.add("[Line 3] semantic error: non-compatible size matrix operation");

    inputs.add("matrix a = [[1,0,0],[0,1,0],[1,0,0]]", "matrix b = [[1,1,1],[0,0,0],[0,0,0]]", "a * b");
    outputs.add("res = [[1,1,1],[0,0,0],[1,1,1]]");

    inputs.add("matrix a = [[1,0,0],[0,1,0],[1,0,0]]", "matrix b = [[1,1],[0,0],[0,0]]", "a * b");
    outputs.add("res = [[1,1],[0,0],[1,1]]");

    inputs.add("matrix a = [[1,0,0],[0,1,0],[1,0,0]]", "matrix b = [[1,1,1],[0,0,0]]", "a * b");
    outputs.add("[Line 3] semantic error: non-compatible size matrix operation");

    run_tests(inputs, outputs);
}

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
