/*
 * EXPRESSION EVALUATOR
 *
 *  Created on: 05-01-2012
 *      Author: herop
 */

#include "functions.hpp"

ostream &operator<<(ostream &stream, const lex_sequence op) {
	if (op.element == no)
		stream << op.number;
	else
		stream << op.math_op;
	return stream;
}

vector<lex_sequence> lex_analyse(const string& str)
{
	vector<lex_sequence> lexed;
	vector<lex_sequence> &result = lexed;

	unsigned int i = 0;
	while (i < str.length())
	{
		switch (str.at(i))
		{
		case '+':
			lexed.resize(lexed.size()+1);
			lexed.at(lexed.size()-1).math_op = '+';
			lexed.at(lexed.size()-1).element = op;
			i++;
			break;
		case '-':
			lexed.resize(lexed.size()+1);
			lexed.at(lexed.size()-1).math_op = '-';
			lexed.at(lexed.size()-1).element = op;
			i++;
			break;
		case '*':
			lexed.resize(lexed.size()+1);
			lexed.at(lexed.size()-1).math_op = '*';
			lexed.at(lexed.size()-1).element = op;
			i++;
			break;
		case '/':
			lexed.resize(lexed.size()+1);
			lexed.at(lexed.size()-1).math_op = '/';
			lexed.at(lexed.size()-1).element = op;
			i++;
			break;
		case '(':
			lexed.resize(lexed.size()+1);
			lexed.at(lexed.size()-1).math_op = '(';
			lexed.at(lexed.size()-1).element = op;
			i++;
			break;
		case ')':
			lexed.resize(lexed.size()+1);
			lexed.at(lexed.size()-1).math_op = ')';
			lexed.at(lexed.size()-1).element = op;
			i++;
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			lexed.resize(lexed.size()+1);
			lexed.at(lexed.size()-1).element = no;
			while (i < str.length() && str.at(i) >= '0' && str.at(i) <= '9')
			{
				lexed.at(lexed.size()-1).number.number.append(1, str.at(i));
				i++;
			}
			break;
		default:
			i++;
			break;
		}
	}

	/*CHECK THE VALIDITY OF THE RESULT - PHASE 1*/
	void lex_check(vector<lex_sequence> &lx);
	lex_check(result);

	/*STANDARDIZE THE RESULT*/
	void lex_standardize(vector<lex_sequence> &lx);
	lex_standardize(result);

	/*CHECK THE VALIDITY OF THE RESULT - PHASE 2*/
	void lex_validate(vector<lex_sequence> const &lx);
	lex_validate(result);

	return result;
}

/****************************************************
 * FUNCTION: lex_check() - Check the validity of	*
 * the lexical analysed result	- *PHASE 1*			*
 * FEATURE:											*
 * 		- Check for unbalanced parentheses			*
 * 		- Integrate the sign into the number when	*
 * 		detected									*
 ****************************************************/
void lex_check(vector<lex_sequence> &lx)
{
	int i = 0;
	int open_paren = 0, close_paren = 0;
	while (i < (signed)lx.size())
	{
		//Check for unbalanced parentheses' pairs.
		if (lx.at(i).element == op && lx.at(i).math_op == '(')
			open_paren++;
		else if (lx.at(i).element == op && lx.at(i).math_op == ')')
			close_paren++;

		//Check for negative or positive number with sign
		if (lx.at(i).element == no)
			if (i - 1 >= 0 && (lx.at(i-1).math_op == '+' || lx.at(i-1).math_op == '-'))
				if ( (i - 2 >= 0 && lx.at(i-2).element == op) || i - 2 < 0)
				{
					//Integrate the sign into the number
					if (lx.at(i-1).math_op == '-')
						lx.at(i).number.sign = -1;
					lx.erase(lx.begin()+i-1);	//Delete the redundant element
					continue;
				}
		i++;
	}

	//Report error after checking
	if (open_paren != close_paren)
	{
		cerr << "Unbalanced parentheses!!!" << endl << "Exiting..." << endl;
		exit(1);
	}
}

/****************************************************
 * FUNCTION: lex_standardize()						*
 * USE: Standardize the lexically analysed result	*
 * i.e. Adding multiply operator when meeting 		*
 * implicated condition								*
 ****************************************************/
void lex_standardize(vector<lex_sequence> &lx)
{
	int i = 0;
	while (i < (signed)lx.size())
	{
		if (
				// 1) A number beside an open paren
				(lx.at(i).element == no && i + 1 < (signed)lx.size() && lx.at(i+1).math_op == '(') ||
				// 2)  Close paren beside open paren or a number
				(lx.at(i).math_op == ')' && i + 1 < (signed)lx.size()
					&& (lx.at(i+1).math_op == '(' || lx.at(i+1).element == no)) ||
				// 3) Minus and plus beside open paren and after another operators not parentheses
				((lx.at(i).math_op == '+' || lx.at(i).math_op == '-')
					&& i + 1 < (signed)lx.size() && lx.at(i+1).math_op == '('
					&& ((i - 1 >= 0 && lx.at(i-1).element == op && lx.at(i-1).math_op > ')') || i - 1 < 0))
			)
		{
			//Add multiply operator
			lex_sequence omultiply;
			omultiply.element = op;
			omultiply.math_op = '*';
			lx.insert(lx.begin()+i+1, 1, omultiply);

			//For condition 3: replace the operator by a number (1 or -1)
			if (lx.at(i).math_op == '+'){
				lx.at(i).element = no;
				lx.at(i).math_op = '\0';
				lx.at(i).number = 1;
			}
			if (lx.at(i).math_op == '-') {
				lx.at(i).element = no;
				lx.at(i).math_op = '\0';
				lx.at(i).number = -1;
			}
		}
		i++;
	}
}

/****************************************************
 * FUNCTION: lex_validate() - Check the validity of	*
 * the lexical analysed result	- *PHASE 2*			*
 * FEATURE:											*
 * 		- Check for unbalanced parentheses			*
 * 		- Integrate the sign into the number when	*
 * 		detected									*
 ****************************************************/
void lex_validate(vector<lex_sequence> const &lx)
{
	/*A funtion for display the error and exit the program (only use in this function)*/
	void error();

	/*VALIDITY CHECK*/
	int i = 0;
	while (i < (signed)lx.size())
	{
		switch (lx.at(i).element) {
		case no:
			//At the left side of a number must be an operator not close paren
			if (!((i - 1 < 0)||(i - 1 >= 0 && lx.at(i-1).element == op && lx.at(i-1).math_op != ')')))
				error();
			//At the right side of a number must be an operator not open paren
			if (!((i + 1 >= (signed)lx.size())||(i + 1 < (signed)lx.size() && lx.at(i+1).element == op && lx.at(i+1).math_op != '(')))
				error();
			break;
		case op:
			switch (lx.at(i).math_op) {
			case '+':
			case '-':
			case '*':
			case '/':
				//They must not be at the first position of the expression
				//and at their left must be a number or a right parentheses
				if (!(i-1 >= 0 && (lx.at(i-1).element == no || lx.at(i-1).math_op == ')')))
					error();
				//They must not be at the last position of the expression
				//and at their right must be a number of a left parentheses
				if (!(i + 1 < (signed) lx.size() && (lx.at(i+1).element == no || lx.at(i+1).math_op == '(')))
					error();
				break;
			case '(':
				//It can be at the first position of the expression,
				//or else, at its left must be an operator (not right parentheses)
				if (!((i - 1 < 0)||(i - 1 >= 0 && lx.at(i-1).element == op && lx.at(i-1).math_op != ')')))
					error();
				//It can not be at the two last positions of the expression,
				//and at their right must be a number of another left parentheses)
				if (!(i < (signed)lx.size() - 2 && (lx.at(i+1).element == no || lx.at(i+1).math_op == '(')))
					error();
				break;
			case ')':
				//It can not be at the first position of the expression,
				//and at its left must be a number or another right parentheses
				if (!(i - 1 > 0 && (lx.at(i-1).element == no || lx.at(i-1).math_op == ')')))
					error();
				//It can be at the last position of the expression,
				//ore else, at its right must be an operator (not left parentheses)
				if (!((i + 1 >= (signed)lx.size()) || (i + 1 < (signed)lx.size()  && lx.at(i+1).element == op && lx.at(i+1).element != '(')))
					error();
				break;
			default:
				break;
			};
			break;
		}
		i++;
	}

};

void error() {
	cerr << "Invalid expression..." << endl << "Exiting...";
	exit(1);
};