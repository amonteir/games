#pragma once

namespace angelogames {
	class Player
	{
	private:
		const char PLAYER_PIECE = 'X';
		//signed int* m_pPlayerMoves;
		
	public:
		int playerMove;

	public:
		Player();
		virtual ~Player();
		char getPlayerPiece() { return PLAYER_PIECE; }
	};
}