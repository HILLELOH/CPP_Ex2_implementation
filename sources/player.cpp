
#include "player.hpp"
#include <iostream>
using namespace std;
namespace ariel {
	Player::Player(std::string name){
		isPlayedBefore_ = false;
		name_ = name;
		stacksize_ = 0;
		cardesTaken_ = 0;
		turnWins_ = 0 ;
	}
	
	int Player::stacksize(){
		return this->stacksize_;
	
	}
	
	void Player::Setstacksize(int size){
		this->stacksize_ = size;
	
	}
	
	int Player::cardesTaken(){
		return this->cardesTaken_;
	}
	
	void Player::SetcardesTaken(int add){
		this->cardesTaken_ = add;
	}
	
	bool Player::isPlayedBefore(){
		return this->isPlayedBefore_;
	}
	
	void Player::SetisPlayedBefore(bool b){
		this->isPlayedBefore_ = b;
	}
	
	std::string Player::playerName(){
		return this->name_;
	}
	
	
	std::vector<Card>& Player::getDeck() {
        	return this->deck_;
    	}
    	
    	void Player::setDeck(std::vector<Card>& deck){
    		this->deck_ = deck;
    	}
    	
    	int Player::turnWins(){
    		return this->turnWins_;
    	}
    	
    	
	void Player::setTurnWins(){
		this->turnWins_ ++;
	}

}


