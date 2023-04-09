#pragma once
#include "player.hpp"
#include "card.hpp"
namespace ariel {
	class Game{
		public:
			Game(Player&, Player&);
			void playTurn();
			void printLastTurn();
			void playAll();
			void printWiner();
			void printLog();
			void printStats();
			
			Player* FirstPlayer();
			//void SetFirstPlayer(Player&);
			Player* SecondPlayer();
			//void SetSecondPlayer(Player7);
			
			Card pop(std::vector<Card>&);
			std::vector<std::string>& getTurns();
			void insertTurn(std::string, Card, Card, std::string);
			
			//help function
			int getActualNumber(std::string);
			void setPlayersAfterTurn(int, int);
			std::string concDraw(std::string, Card, Card);
			int turnDraws();
			void setTurnDraws();
			
			int turnPlayed();
			void setTurnPlayed();
			
		
		private:
			Player* player1_;
			Player* player2_;
			std::vector<std::string> turns_;
			int draws_;
			int turnPlayed_;
					
			
	};	

};
