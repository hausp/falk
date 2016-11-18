
#ifndef FALK_EVALUATOR_REAL_HPP
#define FALK_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "array_index.hpp"
#include "base/operators.hpp"
#include "base/types.hpp"
#include "function.hpp"
#include "identifier.hpp"
#include "matrix_index.hpp"
#include "symbol_mapper.hpp"
#include "value.hpp"

namespace falk {
    namespace ev {
        // Responsible for all semantic actions in 'interpreted mode'
        class evaluator {
         public:
            using Type = Type;

            static constexpr auto ADD = 
                operation<op::Arithmetical, 2>{op::Arithmetical::ADD};
            static constexpr auto SUB =
                operation<op::Arithmetical, 2>{op::Arithmetical::SUB};
            static constexpr auto MULT =
                operation<op::Arithmetical, 2>{op::Arithmetical::MULT};
            static constexpr auto DIV =
                operation<op::Arithmetical, 2>{op::Arithmetical::DIV};
            static constexpr auto POW =
                operation<op::Arithmetical, 2>{op::Arithmetical::POW};
            static constexpr auto MOD =
                operation<op::Arithmetical, 2>{op::Arithmetical::MOD};
            static constexpr auto AND =
                operation<op::Logical, 2>{op::Logical::AND};
            static constexpr auto OR =
                operation<op::Logical, 2>{op::Logical::OR};
            static constexpr auto NOT = op::Logical::NOT;
            static constexpr auto ADD_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::ADD_ASSIGN};
            static constexpr auto SUB_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::SUB_ASSIGN};
            static constexpr auto MULT_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::MULT_ASSIGN};
            static constexpr auto DIV_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::DIV_ASSIGN};
            static constexpr auto POW_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::POW_ASSIGN};
            static constexpr auto MOD_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::MOD_ASSIGN};

            // Definitions for parser
            using generic = ev::value;

            using program = generic;
            using command = generic;
            using control = generic;
            using declaration = generic;
            using assignment = generic;
            using identifier = ev::identifier;
            using array_index = ev::array_index;
            using matrix_index = ev::matrix_index;
            using expression = ev::value;
            using value = ev::value;
            using init_list = value; // TODO: change this
            using function = ev::function;
         public:
            program append(program, command);

            array_index make_array_index(value);

            assignment assign(identifier, value);
            assignment assign(identifier, value, falk::op::Arithmetical);

            program create_program();
            command empty_command();
            
            declaration declare_array(const std::string&);
            declaration declare_array(const std::string&, array_index);
            declaration declare_array(const std::string&, init_list);
            
            declaration declare_variable(const std::string&);
            declaration declare_variable(const std::string&, Type);
            declaration declare_variable(const std::string&, value);
            
            declaration declare_matrix(const std::string&);
            declaration declare_matrix(const std::string&, matrix_index);
            declaration declare_matrix(const std::string&, init_list);

            real make_real(const std::string& text);
            complex make_complex(const std::string& text);
            boolean make_boolean(const std::string& yytext);

            matrix_index make_matrix_index(value);
            matrix_index make_matrix_index(value, value);

            control new_line();
            control semicolon();

            identifier retrieve_identifier(const std::string&) { return identifier{}; }
            identifier retrieve_identifier(const std::string&, array_index) { return identifier{}; }
            identifier retrieve_identifier(const std::string&, matrix_index) { return identifier{}; }

            value single_calculation(value value);

            value pow(const value& lhs, const value& rhs);
         private:
            symbol_mapper mapper;
        };


        inline evaluator::real evaluator::make_real(const std::string& text) {
            return std::stod(text);
        }

        inline evaluator::complex evaluator::make_complex(const std::string& text) {
            // TODO
            return std::complex<double>{};
        }

        inline evaluator::boolean evaluator::make_boolean(const std::string& text) {
            return text == "true";
        }

        inline evaluator::control evaluator::new_line() {
            std::cout << "falk> ";
            return control{};
        }

        inline ev::value evaluator::single_calculation(ev::value value) {
            std::cout << "res = " << value << std::endl;
            return value;
        }
    }
}

#endif /* FALK_EVALUATOR_REAL_HPP */
