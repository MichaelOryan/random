/*
Example usage

Morse<std::string>morse_coder(".", "-", " ");
vector<string> v_code = morse_coder.encode("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

std::string code = boost::join(v_code, "");
cout << code << endl;

vector<string> mycode = {"-", "-", "-"};

cout << "decode: " << ":" << morse_coder.decode(mycode) << ":";

*/
#ifndef MORSE_H
#define MORSE_H

#include <vector>
#include <boost/bimap.hpp>


template<class T>
class Morse{

	private:

	enum Symbol {DOT, DASH, SPACE};

	typedef std::vector< Symbol > code_vector;
	typedef boost::bimap< char, code_vector > codex_bimap;
	typedef typename codex_bimap::value_type match;
	typedef boost::bimap< std::string, int > results_bimap;
	typedef results_bimap::value_type position;

	T dot;
	T dash;
	T space;

	code_vector MORSE_A = {DOT, DASH};
	code_vector MORSE_B = {DASH, DOT, DOT, DOT};
	code_vector MORSE_C = {DASH, DOT, DASH, DOT};
	code_vector MORSE_D = {DASH, DOT, DOT};
	code_vector MORSE_E = {DOT};
	code_vector MORSE_F = {DOT, DOT, DASH, DOT};
	code_vector MORSE_G = {DASH, DASH, DOT};
	code_vector MORSE_Ha = {DOT, DOT, DOT, DOT}; //Codeblocks is having some issue with this being MORSE_H
	code_vector MORSE_I = {DOT, DOT};
	code_vector MORSE_J = {DOT, DASH, DASH, DASH};
	code_vector MORSE_K = {DASH, DOT, DASH};
	code_vector MORSE_L = {DOT, DASH, DOT, DOT};
	code_vector MORSE_M = {DASH, DASH};
	code_vector MORSE_N = {DASH, DOT};
	code_vector MORSE_O = {DASH, DASH, DASH};
	code_vector MORSE_P = {DOT, DASH, DASH, DOT};
	code_vector MORSE_Q = {DASH, DASH, DOT, DASH};
	code_vector MORSE_R = {DOT, DASH, DOT};
	code_vector MORSE_S = {DOT, DOT, DOT};
	code_vector MORSE_T = {DASH};
	code_vector MORSE_U = {DOT, DOT, DASH};
	code_vector MORSE_V = {DOT, DOT, DOT, DASH};
	code_vector MORSE_W = {DOT, DASH, DASH};
	code_vector MORSE_X = {DASH, DOT, DOT, DASH};
	code_vector MORSE_Y = {DASH, DOT, DASH, DASH};
	code_vector MORSE_Z = {DASH, DASH, DOT, DOT};

	const char LETTER_A = 'a';
	const char LETTER_B = 'b';
	const char LETTER_C = 'c';
	const char LETTER_D = 'd';
	const char LETTER_E = 'e';
	const char LETTER_F = 'f';
	const char LETTER_G = 'g';
	const char LETTER_H = 'h';
	const char LETTER_I = 'i';
	const char LETTER_J = 'j';
	const char LETTER_K = 'k';
	const char LETTER_L = 'l';
	const char LETTER_M = 'm';
	const char LETTER_N = 'n';
	const char LETTER_O = 'o';
	const char LETTER_P = 'p';
	const char LETTER_Q = 'q';
	const char LETTER_R = 'r';
	const char LETTER_S = 's';
	const char LETTER_T = 't';
	const char LETTER_U = 'u';
	const char LETTER_V = 'v';
	const char LETTER_W = 'w';
	const char LETTER_X = 'x';
	const char LETTER_Y = 'y';
	const char LETTER_Z = 'z';

	codex_bimap codex;
	void init_codex(){
		codex.insert(match(LETTER_A, MORSE_A));
		codex.insert(match(LETTER_B, MORSE_B));
		codex.insert(match(LETTER_C, MORSE_C));
		codex.insert(match(LETTER_D, MORSE_D));
		codex.insert(match(LETTER_E, MORSE_E));
		codex.insert(match(LETTER_F, MORSE_F));
		codex.insert(match(LETTER_G, MORSE_G));
		codex.insert(match(LETTER_H, MORSE_Ha));
		codex.insert(match(LETTER_I, MORSE_I));
		codex.insert(match(LETTER_J, MORSE_J));
		codex.insert(match(LETTER_K, MORSE_K));
		codex.insert(match(LETTER_L, MORSE_L));
		codex.insert(match(LETTER_M, MORSE_M));
		codex.insert(match(LETTER_N, MORSE_N));
		codex.insert(match(LETTER_O, MORSE_O));
		codex.insert(match(LETTER_P, MORSE_P));
		codex.insert(match(LETTER_Q, MORSE_Q));
		codex.insert(match(LETTER_R, MORSE_R));
		codex.insert(match(LETTER_S, MORSE_S));
		codex.insert(match(LETTER_T, MORSE_T));
		codex.insert(match(LETTER_U, MORSE_U));
		codex.insert(match(LETTER_V, MORSE_V));
		codex.insert(match(LETTER_W, MORSE_W));
		codex.insert(match(LETTER_X, MORSE_X));
		codex.insert(match(LETTER_Y, MORSE_Y));
		codex.insert(match(LETTER_Z, MORSE_Z));

	}

	public:
	Morse(T dot, T dash, T space){
		this->dot = dot;
		this->dash = dash;
		this->space = space;
		init_codex();
	}

	std::vector<T> encode(std::string s)
	{
        std::string lower_s;
        for(char c: s)
        {
            lower_s += std::tolower(c);
        }

		std::vector<T> code;

		for(char c : lower_s)
		{
            if(this->codex.left.find(c) != this->codex.left.end())
            {
                code_vector letterCode = this->codex.left.at(c);
                for(Symbol sy : letterCode)
                {
                    code.push_back(symbolToType(sy));
                }
                code.push_back(space);
            }

		}

		return code;
	}

    char decode(std::vector<T> code)
    {

        char letter = ' ';

        code_vector lookUpCode;
        for(T t : code)
        {
            lookUpCode.push_back(typeToSymbol(t));
        }

        if(this->codex.right.find(lookUpCode) != this->codex.right.end())
        {
            letter = this->codex.right.at(lookUpCode);
        }

        return letter;
    }


    T symbolToType(Symbol symbol)
    {

        if(symbol == DOT)
        {
            return this->dot;
        }
        else if(symbol == DASH)
        {
            return this->dash;
        }

        return this->space;

    }

    Symbol typeToSymbol(T t)
    {

        if(t == dot)
        {
            return DOT;
        }
        else if(t == dash)
        {
            return DASH;
        }

        return SPACE;

    }

};


#endif // MORSE_H
