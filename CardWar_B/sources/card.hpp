#pragma once
#include<string>

namespace ariel {
	class Card{
		public:
			Card(std::string, std::string);
			std::string getCardValue();
			std::string getCardShape();	
			
		private:
			std::string cardValue_;
			std::string cardShape_;
	};

};

