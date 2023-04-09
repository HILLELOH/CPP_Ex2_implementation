#include "game.hpp"
#include "card.hpp"
#include <iostream>
#include <stdexcept>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;
namespace ariel {
	Game::Game(Player& p1, Player& p2){
		this->player1_= &p1;
		this->player2_= &p2;
		// check if this player is allow to play
		if(!FirstPlayer()->isPlayedBefore() && !SecondPlayer()->isPlayedBefore()){
			FirstPlayer()->SetisPlayedBefore(true);
			SecondPlayer()->SetisPlayedBefore(true);
		}
		else{	
			throw std::invalid_argument("ERROR: one of the players is already in a game");
		}
			
		
		//create a deck with all possible cards
		std::vector<std::string> cards = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "PRINCE", "QUEEN", "KING"};
		std::vector<std::string> shapes = {"Heart", "Diamond", "Club", "Spade"};
		
		
		vector<Card> deck;
		for (int i = 0; i <= 12; i++) {
		    for (int j = 0; j <= 3; j++) {
			Card card{cards.at(static_cast<unsigned long>(i)), shapes.at(static_cast<unsigned long>(j))};
			deck.push_back(card);
		    }
		}
		
		
		
		// shuffle the deck
		std::random_device rand;
		std::default_random_engine rng(rand());
		std::shuffle(deck.begin(), deck.end(), rng);
		
		//split deck to two
		std::vector<Card> player1_deck(deck.begin(), deck.begin() + deck.size() / 2);
		std::vector<Card> player2_deck(deck.begin() + deck.size() / 2, deck.end());
		
		FirstPlayer()->setDeck(player1_deck);
		SecondPlayer()->setDeck(player2_deck);
		
		FirstPlayer()->SetcardesTaken(0);
		FirstPlayer()->Setstacksize(26);
		
		SecondPlayer()->SetcardesTaken(0);
		SecondPlayer()->Setstacksize(26);
		
		draws_=0;
		turnPlayed_=0;
		
	}
	
	int Game::getActualNumber(std::string strNum){
		std::vector<std::string> vals = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "PRINCE", "QUEEN", "KING"};
		
		int i = 1;
		while(strNum != vals.at(static_cast<unsigned long>(i-1))){
			i++;
		}
		return i;
	}
	
	void Game::setPlayersAfterTurn(int cardsCounter, int num){ //1-firstPlayer, 2-SecondePlayer
		if(num == 1){
			FirstPlayer()->Setstacksize(FirstPlayer()->stacksize() - cardsCounter);
			SecondPlayer()->Setstacksize(SecondPlayer()->stacksize() - cardsCounter);
				
			FirstPlayer()->SetcardesTaken(FirstPlayer()->cardesTaken() + cardsCounter*2); //only one winner each turn twice the cards he throw from his deck 
			FirstPlayer()->setTurnWins();
			
		}
		
		else if(num == 2){
			FirstPlayer()->Setstacksize(FirstPlayer()->stacksize() - cardsCounter);
			SecondPlayer()->Setstacksize(SecondPlayer()->stacksize() - cardsCounter);
				
			SecondPlayer()->SetcardesTaken(SecondPlayer()->cardesTaken() + cardsCounter*2); //only one winner each turn twice the cards he throw from his deck 
			SecondPlayer()->setTurnWins();
		}
		
	}
	
	void Game::playTurn(){
		if(FirstPlayer() == SecondPlayer()){
			throw std::invalid_argument("ERROR: Player can't play vs himself!");
		}
		if(FirstPlayer()->stacksize() + SecondPlayer()->stacksize() == 0){
			FirstPlayer()->SetisPlayedBefore(false);
			SecondPlayer()->SetisPlayedBefore(false);
			//cout << "the game alredy over! (players state game is false and allow to play another game)" << endl;
			throw std::invalid_argument("WARNING: the game already over!");
		}
		int cardsCounter = 1;
		
		
		bool isEmpty = false;
		int saveBeforeUpdate = 0;
		
		int val1;
		int val2;
		
		
		if(FirstPlayer()->getDeck().empty() && SecondPlayer()->getDeck().empty()){
			saveBeforeUpdate = 0;
			isEmpty = true;
			val1 = 0;
			val2 = 0;
		}
		
		Card firstPlayerCard = pop(FirstPlayer()->getDeck());
		Card secondPlayerCard = pop(SecondPlayer()->getDeck());
		
		if(!isEmpty){
			
			val1 = getActualNumber(firstPlayerCard.getCardValue());
			val2 = getActualNumber(secondPlayerCard.getCardValue());
			setTurnPlayed();
		
		}
		
		std::string draw = "";
		//cout << val1 << ", " <<  val2 << ", " << isEmpty <<endl;
		
		while(val1 == val2 && !isEmpty){
			//cout << "intloop" <<endl;
			draw = concDraw(draw, firstPlayerCard, secondPlayerCard);
			setTurnDraws();
			//cout << draw <<endl;
			if(FirstPlayer()->getDeck().empty() && SecondPlayer()->getDeck().empty()){
				saveBeforeUpdate = cardsCounter;
				isEmpty = true;
				val1 = 0;
				val2 = 0;
				break;
			}
			
			val1 = getActualNumber(pop(FirstPlayer()->getDeck()).getCardValue()); //first player put a card face down.
			val2 = getActualNumber(pop(SecondPlayer()->getDeck()).getCardValue()); ////second player put a card face down.
			cardsCounter += 1;
			
			if(FirstPlayer()->getDeck().empty() && SecondPlayer()->getDeck().empty()){
				saveBeforeUpdate = cardsCounter;
				isEmpty = true;
				val1 = 0;
				val2 = 0;
				break;
			}
			
				
			firstPlayerCard = pop(FirstPlayer()->getDeck());
			secondPlayerCard = pop(SecondPlayer()->getDeck());
			val1 = getActualNumber(firstPlayerCard.getCardValue()); //first player put a card face up.
			val2 = getActualNumber(secondPlayerCard.getCardValue()); //second player put a card face up.
			
			
			cardsCounter += 1;
		}
		if(!isEmpty){
			if(val1 == 1){ 
				if(val2 == 2){ // val2 win
					insertTurn(draw, firstPlayerCard, secondPlayerCard, SecondPlayer()->playerName());
					setPlayersAfterTurn(cardsCounter, 2);
				}
			
				else{ //val1 win
					insertTurn(draw, firstPlayerCard, secondPlayerCard, FirstPlayer()->playerName());
					setPlayersAfterTurn(cardsCounter, 1);
					
				}
			}
		
			else if(val2 == 1){ 
				if(val1 == 2){ // val1 win
					insertTurn(draw, firstPlayerCard, secondPlayerCard, FirstPlayer()->playerName());
					setPlayersAfterTurn(cardsCounter, 1);
				}
			
				else{ //val2 win
					insertTurn(draw, firstPlayerCard, secondPlayerCard, SecondPlayer()->playerName());
					setPlayersAfterTurn(cardsCounter, 2);
				}
			}
		
			else if(val1 > val2){ //val1 win
				insertTurn(draw, firstPlayerCard, secondPlayerCard, FirstPlayer()->playerName());
				setPlayersAfterTurn(cardsCounter, 1);
			}
			
			else if(val2 > val1){ //val2 win
				insertTurn(draw, firstPlayerCard, secondPlayerCard, SecondPlayer()->playerName());
				setPlayersAfterTurn(cardsCounter, 2);
			}
		
		}
		
		else{
			firstPlayerCard = Card("NULL - turn finished without cards", "");
			secondPlayerCard = Card("NULL - turn finished without cards", "");
			insertTurn(draw, firstPlayerCard, secondPlayerCard, FirstPlayer()->playerName());
			insertTurn(draw, firstPlayerCard, secondPlayerCard, SecondPlayer()->playerName());
			setPlayersAfterTurn(saveBeforeUpdate, 2);
		}
		
		
		

	}
	
	void Game::printLastTurn(){
		if(!getTurns().empty()){
			cout << getTurns().back() << endl;
		}
		
		else{
		
			//throw std::invalid_argument("ERROR: no turn was played until now!");
			cout << "ERROR: no turn was played until now!" << endl;
		}
		
	}
	
	void Game::playAll(){
		while(FirstPlayer()->stacksize() > 0){
			playTurn();
		}
	}
	
	void Game::printWiner(){
		if(FirstPlayer()->cardesTaken() + SecondPlayer()->cardesTaken() == 52){
			if(FirstPlayer()->cardesTaken() > SecondPlayer()->cardesTaken()){
				cout << FirstPlayer()->playerName() << endl;
			}
			else if (FirstPlayer()->cardesTaken() < SecondPlayer()->cardesTaken()){
				cout << SecondPlayer()->playerName() << endl;
			}
			else{
				cout << FirstPlayer()->playerName() + " and "  + SecondPlayer()->playerName()<< endl;
			}
		}
		
		else{
			cout << "The game isn't over yet!" << endl;
		}
	}
	
	void Game::printLog(){
		for (auto turn = getTurns().rbegin(); turn != getTurns().rend(); ++turn) {
        		std::cout << *turn << endl;
   		}
	}
	
	void Game::printStats(){
		cout << "Stats: " << endl;
		cout << "	" << "Game stats: " << endl;	
		cout << "		" << "Turns: " + std::to_string(turnPlayed()) << endl;
		cout << "		" << "Draws: " + std::to_string(turnDraws()) << endl;
		cout << "		" << "Draws rate: " + std::to_string(static_cast<float>(turnDraws())/static_cast<float>(turnPlayed())*100.0) + "%" << endl << endl;
	
		cout << "	" << "Player stats: " << endl;	
		cout << "		" << "First Player: " << endl;
		cout << "			" << "Name: " + FirstPlayer()->playerName() << endl;
		cout << "			" << "Stack size: " + std::to_string(FirstPlayer()->stacksize()) << endl;
		cout << "			" << "Cardes Taken: " + std::to_string(FirstPlayer()->cardesTaken()) << endl;
		cout << "			" << "Turn winnings: " + std::to_string(FirstPlayer()->turnWins())<< endl;
		cout << "			" << "Win rate (percent): " + std::to_string(static_cast<float>(FirstPlayer()->turnWins())/static_cast<float>(turnPlayed())*100.0) + "%"<< endl<< endl;

		
		cout << "		" << "Second Player: " << endl;
		cout << "			" << "Name: " + SecondPlayer()->playerName() << endl;
		cout << "			" << "Stack size: " + std::to_string(SecondPlayer()->stacksize()) << endl;
		cout << "			" << "Cardes Taken: " + std::to_string(SecondPlayer()->cardesTaken()) << endl;
		cout << "			" << "Turn winnings: " + std::to_string(SecondPlayer()->turnWins())<< endl;
		cout << "			" << "Win rate (percent): " + std::to_string(static_cast<float>(SecondPlayer()->turnWins())/static_cast<float>(turnPlayed())*100.0) + "%"<< endl;
	}
	
	Player* Game::FirstPlayer(){
		return this->player1_;
	}		

	Player* Game::SecondPlayer(){
		return this->player2_;
	}	
	
	Card Game::pop(std::vector<Card>& deck) {
		Card firstCard("", "");
		if(!deck.empty()){
			firstCard = deck.front();
			deck.erase(deck.begin());
		}

		return firstCard;
	}
	
	std::vector<std::string>& Game::getTurns(){
		return this->turns_;
	}
	
	std::string Game::concDraw(std::string draw, Card card1, Card card2){
		std::string firstName = FirstPlayer()->playerName();
		std::string firstValue = card1.getCardValue();
		std::string firstShape = card1.getCardShape();
		
		std::string secondName = SecondPlayer()->playerName();
		std::string secondValue = card2.getCardValue();
		std::string secondShape = card2.getCardShape();
		
		return draw + firstName +" played "+ firstValue + " of " + firstShape + ", " + secondName +" played "+ secondValue + " of " + secondShape + ". Draw. ";
			
	}
	
	void Game::insertTurn(std::string draw, Card card1, Card card2, std::string winner){
		std::string firstName = FirstPlayer()->playerName();
		std::string firstValue = card1.getCardValue();
		std::string firstShape = card1.getCardShape();
		
		std::string secondName = SecondPlayer()->playerName();
		std::string secondValue = card2.getCardValue();
		std::string secondShape = card2.getCardShape();
		
		std::string turn = draw + firstName +" played "+ firstValue + " of " + firstShape + ", " + secondName +" played "+ secondValue + " of " + secondShape + ". " + winner + " wins.";
		getTurns().insert(getTurns().begin(), turn); 
		
	}	
	
	int Game::turnDraws(){
		return this->draws_;
	}
	
	void Game::setTurnDraws(){
		this->draws_ ++;
	}
	
	int Game::turnPlayed(){
		return this->turnPlayed_;
	}
	
	void Game::setTurnPlayed(){
		this->turnPlayed_++;
	}
	

}
