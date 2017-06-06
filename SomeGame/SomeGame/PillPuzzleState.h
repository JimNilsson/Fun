#ifndef _PILL_PUZZLE_H_
#define _PILL_PUZZLE_H_

#include "IState.h"
#include <SFML\Graphics.hpp>

class PillPuzzleState : public IState
{
public:
	PillPuzzleState(Application* app);
	~PillPuzzleState();

	virtual void Update();
	virtual void Draw();


private:

	sf::Clock _clock;
	sf::RectangleShape board[8][16];
	unsigned _numVirusClusters;
	int blocksX;
	int blocksY;
	float blockSize;
	bool _gameWon = false;
	bool _gameLost = false;

	struct Indexer
	{
		int x1, x2;
		int y1, y2;
		sf::Color col1, col2;
		bool Horizontal() const
		{
			if (x1 - x2 != 0)
				return true;
			return false;
		}
		
		void IncrementY()
		{
			y1++; y2++;
		}



		
		sf::Color LowestXColor() const { return x1 < x2 ? col1 : col2; };
		sf::Color LowestYColor() const { return y1 > y2 ? col1 : col2; };
		sf::Color HighestXColor() const { return x1 > x2 ? col1 : col2; };
		sf::Color HighestYColor() const { return y1 < y2 ? col1 : col2; };
		int LowestY() const { return std::max(y1, y2); };
		int HighestY() const { return std::min(y1, y2); };
		int LowestX() const { return std::min(x1, x2); };
		int HighestX() const { return std::max(x1, x2); };
		void IncrementX() { x1++; x2++; };
		void DecrementX() { x1--; x2--; };
		void RotateClockWise() {
			if (Horizontal())
			{
				if (x1 < x2)
				{
					y1 = y2 - 1;
					x1 = x2;
				}
				else
				{
					y2 = y1 - 1;
					x2 = x1;
				}
			}
			else
			{
				if (y1 < y2)
				{
					x2 = x1 - 1;
					y1 = y2;
				}
				else
				{
					x1 = x2 - 1;
					y2 = y1;
				}
			}
		}
	};
	Indexer _indexer;
	float _moveDownTime = 1.0f;
	float _moveDownAcc = 0.0f;


	void RotateCW();
	void RotateCCW();
	bool MoveDown();
	bool MoveRight();
	bool MoveLeft();
	void UpdateBoard();
	void ResetIndexer();



};


#endif

