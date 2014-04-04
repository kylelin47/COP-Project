#ifndef PI_H
#define PI_H


class Pi: public AbstractNumber {
public:
	Pi(const string &input);
	virtual ~Pi();
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

#endif // PI_H
