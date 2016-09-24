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

    void run_tests(const Container& inputs, const Container& outputs) {
        auto out_it = outputs.begin();
        for (auto in_it = inputs.begin(); in_it != inputs.end(); ++in_it) {
            auto& in = *in_it;
            auto& out = *out_it;
            Connection program("./lukacompiler");
            program.send(in);
            auto output = program.receive();
            if (output.size() < out.size()) {
                ASSERT_EQ(output, out); // for proper reporting
            } else {
                auto padded_output = output.substr(0, out.size());
                ASSERT_EQ(padded_output, out);
            }
            ++out_it;
        }
    }
}

TEST_F(LukaTest, v0_1) {
    Container inputs;
    Container outputs;
    inputs.add("int a&");
    outputs.add("[Line 1] lexical error: unknown symbol &");

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
    run_tests(inputs, outputs);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
