/*
 * Connection.h
 *
 *  Created on: 28 Feb 2017
 *      Author: sbl
 */

#ifndef LINK_H_
#define LINK_H_

class Link {
    int n1;
    int n2;
public:
	Link(int n1, int n2) : n1(n1), n2(n2){}
	virtual ~Link();
	int getN1() const;
	int getN2() const;
	bool operator==(Link c);
};

#endif /* LINK_H_ */
