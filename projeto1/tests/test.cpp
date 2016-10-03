/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */

#include <gtest/gtest.h>
#include <list>
#include "aux/Connection.hpp"

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
            Connection program("./lukacompiler");
            program.send(in);
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
}

TEST_F(LukaTest, v1) {
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

TEST_F(LukaTest, v2) {
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

TEST_F(LukaTest, v3) {
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

    inputs.add("float k", "k = k + 1", "k = 1 + k");
    outputs.add("float var: k", "= k + k [float] 1", "= k + [float] 1 k");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v4) {
    Container inputs;
    Container outputs;
    inputs.add("int a, b, c", "if a > b", "then {", "if (a > 0)", "then {", "c = 10", "}", "}");
    outputs.add("int var: a, b, c", "if: > a b", "then:", "  if: > a 0", "  then:", "    = c 10");

    inputs.add("bool b, d", "if b", "then {", "d = true", "} else {", "d = false", "}");
    outputs.add("bool var: b, d", "if: b", "then:", "  = d true", "else:", "  = d false");

    inputs.add("int a = 0", "if a", "then {", "}");
    outputs.add("[Line 4] semantic error: test operation expected boolean but received integer", "int var: a = 0");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v5) {
    Container inputs;
    Container outputs;
    inputs.add("int i", "for i = 0, i < 10, i = i + 1 {", "float j", "}");
    outputs.add("int var: i", "for: = i 0, < i 10, = i + i 1", "do:", "  float var: j");

    inputs.add("int i", "for , i < 10, i = i + 2 {", "}");
    outputs.add("int var: i", "for: , < i 10, = i + i 2", "do:");

    inputs.add("int i", "for , i < 10, {", "}");
    outputs.add("int var: i", "for: , < i 10, ", "do:");

    inputs.add("int i", "for i = 0, , i = i + 1 {", "}");
    outputs.add("[Line 2] syntax error", "int var: i");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v6) {
    Container inputs;
    Container outputs;
    inputs.add("int i", "if true", "then {", "  float i = 0.0", "}");
    outputs.add("int var: i", "if: true", "then:", "  float var: i = 0.0");

    inputs.add("int i", "for i = 0, i < 2, i = i + 2 {", "  int a", "}", "bool a = true");
    outputs.add("int var: i", "for: = i 0, < i 2, = i + i 2", "do:", "  int var: a", "bool var: a = true");

    inputs.add("if true", "then {", "  int i", "}", "i = 3");
    outputs.add("[Line 5] semantic error: undeclared variable i", "if: true", "then:", "  int var: i");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v7) {
    Container inputs;
    Container outputs;
    inputs.add("bool fun f()", "bool fun f() {", "  ret false", "}");
    outputs.add("bool fun: f (params: )", "  ret false");

    inputs.add("bool fun f() {",
               "  ret true",
               "}",
               "if f()",
               "then {",
               "  int a = 0",
               "  int fun f2(int x) {",
               "    int a",
               "    a = x + 1",
               "    ret a",
               "  }",
               "  a = f2(a)",
               "}");
    outputs.add("bool fun: f (params: )",
                "  ret true",
                "if: f[0 params]",
                "then:",
                "  int var: a = 0",
                "  int fun: f2 (params: int x)",
                "    int var: a",
                "    = a + x 1",
                "    ret a",
                "  = a f2[1 params] a");

    inputs.add("bool fun f() {", "}");
    outputs.add("[Line 2] syntax error");

    inputs.add("bool fun f() {", "ret false", "int a = 0", "}");
    outputs.add("[Line 3] syntax error");

    inputs.add("int fun f()");
    outputs.add("[Line 2] semantic error: function f is declared but never defined");

    inputs.add("int fun f()", "int fun f()");
    outputs.add("[Line 2] semantic error: re-declaration of function f");

    inputs.add("int fun f(int x, int y) {", "ret 2", "}", "int a", "a = f(0.0, 0)");
    outputs.add("[Line 5] semantic error: parameter x expected integer but received float",
                "int fun: f (params: int x, int y)",
                "  ret 2",
                "int var: a");

    inputs.add("bool fun x(int a)", "bool b", "b = x()");
    outputs.add("[Line 3] semantic error: function x expects 1 parameters but received 0");

    inputs.add("int fun f()", "int fun f(int x) {", "  ret x", "}");
    outputs.add("[Line 4] semantic error: re-declaration of function f");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v8) {
    Container inputs;
    Container outputs;
    inputs.add("int a(10)",
               "bool p(10)",
               "int i",
               "for i = 0, i < 10, i = i + 1 {",
               "  a(i) = i",
               "  if a(i) / 2 == 0",
               "  then {",
               "    p(i) = true",
               "  } else {",
               "    p(i) = false",
               "  }",
               "}");
    outputs.add("int array: a (size: 10)",
                "bool array: p (size: 10)",
                "int var: i",
                "for: = i 0, < i 10, = i + i 1",
                "do:",
                "  = [index] a i i",
                "  if: == / [index] a i 2 0",
                "  then:",
                "    = [index] p i true",
                "  else:",
                "    = [index] p i false");

    inputs.add("int a(10)", "a(false) = 1");
    outputs.add(
        "[Line 2] semantic error: index operator expects integer but received boolean",
        "int array: a (size: 10)");

    inputs.add("int a(1.5)");
    outputs.add("[Line 1] syntax error");

    run_tests(inputs, outputs);
}

TEST_F(LukaTest, v10) {
    Container inputs;
    Container outputs;
    inputs.add("int i", "int ref p", "p = addr i", "i = ref p + 1");
    outputs.add("int var: i", "int ref var: p", "= p [addr] i", "= i + [ref] p 1");

    inputs.add("int i", "int ref p(2)", "p(0) = addr i", "p(1) = addr i",
        "int ref ref p2", "p2 = addr p(0)");
    outputs.add("int var: i", "int ref array: p (size: 2)",
        "= [index] p 0 [addr] i", "= [index] p 1 [addr] i",
        "int ref ref var: p2", "= p2 [addr] [index] p 0");

    inputs.add("int i = 0", "int ref p", "p = i");
    outputs.add(
        "[Line 3] semantic error: attribution operation expected integer pointer but received integer",
        "int var: i = 0", "int ref var: p");

    inputs.add("int i", "i = ref i");
    outputs.add(
        "[Line 2] semantic error: reference operation expects a pointer",
        "int var: i");

    inputs.add("bool ref b", "b = addr true");
    outputs.add(
        "[Line 2] syntax error");

    run_tests(inputs, outputs);
}

int main(int argc, char** argv) {
    constexpr auto min_version = 0.1;
    constexpr auto latest_stable = 0.8;

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
            result += "*v" + std::to_string(static_cast<int>((i + 0.05) * 10));
            colon = true;
        }
        return result;
    }();
    ::testing::GTEST_FLAG(filter) = tests;
    return RUN_ALL_TESTS();
}
