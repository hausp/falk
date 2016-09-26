/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */

#include <gtest/gtest.h>
#include <list>
#include "Connection.hpp"

class LukaTest : public ::testing::Test {};

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

    void run(const std::string& in, const std::string& actual, const std::string& expected) {
        if (expected != actual) {
            std::cout << "Failure in: " << std::endl << in << std::endl;
            std::cout << "Expected: " << std::endl << expected << std::endl;
            std::cout << "Actual: " << std::endl << actual << std::endl;
            ASSERT_TRUE(false);
        }
    };

    void run_tests(const Container& inputs, const Container& outputs) {
        auto out_it = outputs.begin();
        for (auto in_it = inputs.begin(); in_it != inputs.end(); ++in_it) {
            auto& in = *in_it;
            auto& expected = *out_it;
            Connection program("./lukacompiler");
            program.send(in);
            auto actual = program.receive();
            if (actual.size() < expected.size()) {
                run(in, actual, expected);
                // ASSERT_EQ(actual, expected); // for proper reporting
            } else {
                auto padded_actual = actual.substr(0, expected.size());
                run(in, padded_actual, expected);
                // ASSERT_EQ(padded_actual, expected);
            }
            ++out_it;
        }
    }
}

TEST_F(LukaTest, v0_1) {
    Container inputs;
    Container outputs;
    inputs.add("int a@");
    outputs.add("[Line 1] lexical error: unknown symbol @");

    inputs.add("int #####a");
    outputs.add("[Line 1] lexical error: unknown symbol #####");

    inputs.add("int 10b");
    outputs.add("[Line 1] syntax error");

    inputs.add("A = 2");
    outputs.add("[Line 1] semantic error: undeclared variable A");

    inputs.add("int a, a");
    outputs.add("[Line 1] semantic error: re-declaration of variable a");

    inputs.add("int a_");
    outputs.add("int var: a_");

    inputs.add("int BB, c");
    outputs.add("int var: BB, c");

    inputs.add("int d=0, e1 = 1");
    outputs.add("int var: d = 0, e1 = 1");

    inputs.add("int a_", "a_ = 2");
    outputs.add("int var: a_", "= a_ 2");

    inputs.add("int a", "a = 2 * 3");
    outputs.add("int var: a", "= a * 2 3");

    inputs.add("int a, d = 1", "a = d + 2 * 3");
    outputs.add("int var: a, d = 1", "= a + d * 2 3");

    inputs.add("int a", "int 10b");
    outputs.add("[Line 2] syntax error", "int var: a");

    inputs.add("int a = -1");
    outputs.add("int var: a = -1");

    inputs.add("int a", "a = -2-3");
    outputs.add("int var: a", "= a - -u 2 3");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v0_2) {
    Container inputs;
    Container outputs;
    inputs.add("float f=1.0, g=0., h=.10, i");
    outputs.add("float var: f = 1.0, g = 0., h = .10, i");

    inputs.add("bool b = true");
    outputs.add("bool var: b = true");

    inputs.add("float f, g, h, i", "i = -f/2.1");
    outputs.add("float var: f, g, h, i", "= i / -u f 2.1");

    inputs.add("float i", "bool b", "b = ! i > 0.0 | (i < -2.3)");
    outputs.add("float var: i", "bool var: b", "= b | ! > i 0.0 < i -u 2.3");

    inputs.add("int a = 1.0");
    outputs.add("[Line 1] semantic error: attribution operation expected integer but received float");

    inputs.add("int a", "a = a + true");
    outputs.add("[Line 2] semantic error: addition operation expected integer but received boolean", "int var: a");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v0_3) {
    Container inputs;
    Container outputs;
    inputs.add("int i, j", "float f", "j = [int] [int] i + f");
    outputs.add("int var: i, j", "float var: f", "= j [int] [int] + [float] i f");

    inputs.add("int i, j", "i = [int] j");
    outputs.add("int var: i, j", "= i [int] j");

    inputs.add("float f", "bool b", "b = b & [bool] f");
    outputs.add("float var: f", "bool var: b", "= b & b [bool] f");

    inputs.add("float f", "bool b", "f = ([float] b) + 0.0");
    outputs.add("float var: f", "bool var: b", "= f + [float] b 0.0");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v0_4) {
    Container inputs;
    Container outputs;
    inputs.add("int a, b, c", "if a > b", "then {", "if (a > 0)", "then {", "c = 10", "}", "}");
    outputs.add("int var: a, b, c", "if: > a b", "then:", "  if: > a 0", "  then:", "    = c 10");

    inputs.add("bool b, d", "if b", "then {", "d = true", "} else {", "d = false", "}");
    outputs.add("bool var: b, d", "if: b", "then:", "  = d true", "else:", "  = d false");

    inputs.add("int a = 0", "if a");
    outputs.add("[Line 2] semantic error: test operation expected boolean but received integer", "int var: a");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v0_5) {
    Container inputs;
    Container outputs;
    inputs.add("int i", "for i = 0, i < 10, i = i + 1 {", "float j", "}");
    outputs.add("int var: i", "for: = i 0, < i 10, = i + i 1", "do:", "  float var: j");

    inputs.add("int i", "for , i < 10, i = i + 2 {", "}");
    outputs.add("int var: i", "for: , < i 10, = i + i 2", "do:");

    inputs.add("int i", "for , i < 10, {", "}");
    outputs.add("int var: i", "for: , < i 10,", "do:");

    inputs.add("int i", "for i = 0, , i = i + 1 {", "}");
    outputs.add("[Line 2] syntax error", "int var: i");

    run_tests(inputs, outputs);
}

int main(int argc, char** argv) {
    constexpr auto min_version = 0.1;
    constexpr auto max_version = 0.3;

    ::testing::InitGoogleTest(&argc, argv);
    const std::string tests = [&] {
        std::string result;
        double version = (argc == 1) ? max_version : std::atof(argv[1]);
        version = std::min(max_version, std::max(min_version, version));
        bool colon = false;
        for (auto i = min_version; i <= version + 0.05; i += 0.1) {
            if (colon) {
                result += ":";
            }
            result += "*_" + std::to_string(static_cast<int>(i * 10));
            colon = true;
        }
        return result;
    }();
    ::testing::GTEST_FLAG(filter) = tests;
    return RUN_ALL_TESTS();
}
