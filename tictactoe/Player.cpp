#include "Player.h"

namespace angelogames {

	Player::Player() {

		m_pPlayerMoves = new signed int[5];

		for (int i = 0; i < 5; i++) {
			m_pPlayerMoves[i] = -1;
		}

	}
	Player::~Player() {
		delete[] m_pPlayerMoves;
	}
	void Player::savePlayerMove(int move) {

		for (int i = 0; i < 5; i++) {
			if (m_pPlayerMoves[i] != -1) {
				m_pPlayerMoves[i] = move;
				break;
			}
		}
	}

	bool Player::checkPlayerMove(int move) {
		for (int i = 0; i < 5; i++) {
			if (m_pPlayerMoves[i] == move) {
				return true;
			}
		}
		return false;
	}

}
