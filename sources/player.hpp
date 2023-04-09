#pragma once
#include <string>
#include <vector>
#include "card.hpp"
using namespace std;
namespace ariel {
	class Player{ 
		public:
			Player(std::string);
			int stacksize();
			void Setstacksize(int);
			
			int cardesTaken();
			void SetcardesTaken(int);
			
			bool isPlayedBefore();
			void SetisPlayedBefore(bool);
			
			std::string playerName();
			std::vector<Card>& getDeck();
			void setDeck(std::vector<Card>&);
			int turnWins();
			void setTurnWins();
			
		private: 
			int stacksize_;
			int cardesTaken_;
			
			bool isPlayedBefore_;
			
			std::string name_;
			std::vector<Card> deck_;
			int turnWins_;
			
	};

};

