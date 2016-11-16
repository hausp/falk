
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

            value make_real(const std::string& text);
            value make_complex(const std::string& text);
            value make_boolean(const std::string& yytext);

            matrix_index make_matrix_index(value);
            matrix_index make_matrix_index(value, value);

            control new_line();
            control semicolon();

            identifier retrieve_identifier(const std::string&);
            identifier retrieve_identifier(const std::string&, array_index);
            identifier retrieve_identifier(const std::string&, matrix_index);

            value single_calculation(value value);

            value pow(const value& lhs, const value& rhs);
         private:
            symbol_mapper mapper;
        };


        inline evaluator::value evaluator::make_real(const std::string& text) {
            return {Type::REAL, std::stod(text), 0};
        }

        inline evaluator::value evaluator::make_complex(const std::string& text) {
            // TODO
            return value{Type::COMPLEX};
        }

        inline evaluator::value evaluator::make_boolean(const std::string& text) {
            if (text == "true") {
                return TRUE;
            }
            return FALSE;
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
