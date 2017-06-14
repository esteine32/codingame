#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdlib.h>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int cardToValue(string card)
{
    int value = 0;

    switch(card[0]){
    case '1':
    	value = 10;
    	break;
    case 'J':
    	value = 11;
    	break;
    case 'Q':
    	value = 12;
    	break;
    case 'K':
    	value = 13;
    	break;
    case 'A':
    	value = 14;
    	break;
    default:
    	value = atoi(&card[0]);
    	break;
    }
        
    return value;
}

int battle(int cardP1, int cardP2){
	int result = 0;

	if(cardP1 > cardP2){
		result = 1;
	}else if(cardP1 < cardP2){
		result = 2;
	}

	return result;
}

void handCardsToWinner(deque<int>& winner, deque<int>& p1, deque<int>& p2, int noCardsInBattle){
	for(int i = 0; i<noCardsInBattle; ++i){
		winner.push_back(p1.front());
		p1.pop_front();
	}

	for(int i = 0; i<noCardsInBattle; ++i){
		winner.push_back(p2.front());
		p2.pop_front();
	}
}

int main()
{
	deque<int> p1;
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string card;
        cin >> card; cin.ignore();
        p1.push_back(cardToValue(card));
    }
    
    deque<int> p2;
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string card;
        cin >> card; cin.ignore();
        p2.push_back(cardToValue(card));
    }

    int rounds = 0;
    while(!p1.empty() && !p2.empty()){
    	++rounds;

    	int noCardsInBattle = 1;
    	int winner = battle(p1.front(), p2.front());

    	//war
    	while(winner == 0){
    		noCardsInBattle += 4;
    		if(p1.size() >= noCardsInBattle && p2.size() >= noCardsInBattle){
    			winner = battle(p1[noCardsInBattle-1], p2[noCardsInBattle-1]);
    		}else{
    			break; //even game
    		}
    	}

    	if(winner == 1){
    		handCardsToWinner(p1, p1, p2, noCardsInBattle);
    	}else if(winner == 2){
    		handCardsToWinner(p2, p1, p2, noCardsInBattle);
    	}else{
    		break;
    	}
    }

    if(p2.empty()){
        cout << 1 << " " << rounds << endl;
    }else if(p1.empty()){
        cout << 2 << " " << rounds << endl;
    }else{
    	cout << "PAT" << endl;
    }
}
