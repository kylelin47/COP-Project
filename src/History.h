/*
 * History.h
 *
 *  Created on: Apr 12, 2014
 *      Author: Alex
 */

#ifndef HISTORY_H_
#define HISTORY_H_
#include <vector>
#include <string>
namespace std {

class History {
public:
	History();
	virtual ~History();
	string getHistory();
	void addHistory(string input);
	void setHistroy(int historyNum);
	vector<string> history;

private:
	int historyNum;
};

} /* namespace std */

#endif /* HISTORY_H_ */
