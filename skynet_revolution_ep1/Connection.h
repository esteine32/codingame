/*
 * Connection.h
 *
 *  Created on: 28 Feb 2017
 *      Author: sbl
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

class Connection {
    int n1;
    int n2;
public:
	Connection(int n1, int n2) : n1(n1), n2(n2){}
	virtual ~Connection();
	int getN1() const;
	int getN2() const;
};

#endif /* CONNECTION_H_ */
