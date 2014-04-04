#ifndef E_H
#define E_H


class E: public AbstractNumber {
public:
	E(const string &input);
	virtual ~E();
	vector<AbstractNumber*> add(AbstractNumber *number);
	vector<AbstractNumber*> multiply(AbstractNumber *number);
	vector<AbstractNumber*> divide(AbstractNumber *number);
	string toString();
	double toDouble();
	bool simplify();
	string getName();

private:
	double value;
};

#endif // E_H
