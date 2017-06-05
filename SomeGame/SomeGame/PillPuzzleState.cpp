#include "PillPuzzleState.h"
#include "Application.h"
#include "MenuState.h"

PillPuzzleState::PillPuzzleState(Application * app) : IState(app)
{
	//Initialize the board
	_numViruses = 20;
	blockSize = 32;
	blocksX = 8;
	blocksY = 16;
	float leftMost = (_app->Width() / 2) - 4 * blockSize;
	float topMost = (_app->Height() / 2) - 8 * blockSize;
	for (int i = 0; i < blocksX; i++)
	{
		for (int j = 0; j < blocksY; j++)
		{
			board[i][j].setSize({ blockSize, blockSize });
			board[i][j].setFillColor(sf::Color::Black);
			board[i][j].setPosition({ leftMost + i * blockSize, topMost + j * blockSize });
		}
	}

	for (int i = 0; i < _numViruses; i++)
	{
		int x = 0;
		int y = 0;
		do
		{
			x = rand() % blocksX;
			y = (rand() % (blocksY - 4)) + 4;
		
		} while (board[x][y].getFillColor() != sf::Color::Black);

		const char* textures[] = { "Textures/yellowvirus.png", "Textures/bluevirus.png", "Textures/redvirus.png", "Textures/greenvirus.png" };
		sf::Color colors[] = { sf::Color::Yellow ,sf::Color::Blue ,sf::Color::Red ,sf::Color::Green };
		int col = rand() % 4;

		board[x][y].setFillColor(colors[col]);
		board[x][y].setTexture(&(_app->Textures()->GetTexture(textures[col])));
	}
	
	_indexer.x1 = 4;
	_indexer.y1 = 1;
	_indexer.x2 = 5;
	_indexer.y2 = 1;
	_indexer.col1 = sf::Color::Yellow;
	_indexer.col2 = sf::Color::Red;

	
}

PillPuzzleState::~PillPuzzleState()
{
}

void PillPuzzleState::Update()
{
	if (_app->Events()->KeySinglePress(sf::Keyboard::Escape))
		_app->ChangeState(new MenuState(_app));

	float dt = _clock.restart().asSeconds();
	_moveDownAcc += dt;
	
	bool lateralMovement = false;
	if (_app->Events()->KeySinglePress(sf::Keyboard::Right))
	{
		MoveRight();
		lateralMovement = true;
	}
	if (_app->Events()->KeySinglePress(sf::Keyboard::Left))
	{
		MoveLeft();
		lateralMovement = true;
	}
	if (_app->Events()->KeySinglePress(sf::Keyboard::D))
	{
		RotateCW();
	}
	if ((_app->Events()->KeySinglePress(sf::Keyboard::Down) || _moveDownAcc >= _moveDownTime) && !lateralMovement)
	{
		_moveDownAcc = 0;
		if (!MoveDown())
		{
			UpdateBoard();
			ResetIndexer();
		}
	}
	

}

void PillPuzzleState::Draw()
{

	for (int i = 0; i < blocksX; i++)
	{
		for (int j = 0; j < blocksY; j++)
		{
			if (board[i][j].getFillColor() != sf::Color::Black)
				_app->Render(board[i][j]);

		}
	}

}

void PillPuzzleState::RotateCW()
{
	if (_indexer.Horizontal())
	{
		if (_indexer.y1 > 0 && board[_indexer.HighestX()][_indexer.y1 - 1].getFillColor() == sf::Color::Black)
		{
			board[_indexer.LowestX()][_indexer.y1].setFillColor(sf::Color::Black);
			board[_indexer.HighestX()][_indexer.y1 - 1].setFillColor(_indexer.LowestXColor());
			_indexer.RotateClockWise();
		}
	}
	else
	{
		if (_indexer.HighestX() + 1 < blocksX && board[_indexer.HighestX() + 1][_indexer.LowestY()].getFillColor() == sf::Color::Black)
		{
			board[_indexer.x1][_indexer.HighestY()].setFillColor(sf::Color::Black);
			board[_indexer.x1 + 1][_indexer.LowestY()].setFillColor(_indexer.HighestYColor());
			_indexer.RotateClockWise();
		}
	}
}

void PillPuzzleState::RotateCCW()
{
}

bool PillPuzzleState::MoveDown()
{
	if (_indexer.LowestY() == blocksY - 1 || board[_indexer.x1][_indexer.LowestY() + 1].getFillColor() != sf::Color::Black || board[_indexer.x2][_indexer.LowestY() + 1].getFillColor() != sf::Color::Black)
		return false;

	if (_indexer.Horizontal())
	{
		board[_indexer.x1][_indexer.y1 + 1].setFillColor(_indexer.col1);
		board[_indexer.x2][_indexer.y2 + 1].setFillColor(_indexer.col2);
		board[_indexer.x1][_indexer.y1].setFillColor(sf::Color::Black);
		board[_indexer.x2][_indexer.y2].setFillColor(sf::Color::Black);
	}
	else
	{	
		board[_indexer.x1][_indexer.LowestY() + 1].setFillColor(board[_indexer.x1][_indexer.LowestY()].getFillColor());
		board[_indexer.x1][_indexer.LowestY()].setFillColor(board[_indexer.x1][_indexer.LowestY() - 1].getFillColor());
		board[_indexer.x1][_indexer.LowestY() - 1].setFillColor(sf::Color::Black);
	}
	_indexer.IncrementY();
	return true;
}

bool PillPuzzleState::MoveRight()
{
	if (_indexer.HighestX() == blocksX - 1 || board[_indexer.HighestX() + 1][_indexer.y1].getFillColor() != sf::Color::Black || board[_indexer.HighestX() + 1][_indexer.y2].getFillColor() != sf::Color::Black)
		return false;

	if (_indexer.Horizontal())
	{
		board[_indexer.HighestX() + 1][_indexer.y1].setFillColor(board[_indexer.HighestX()][_indexer.y1].getFillColor());
		board[_indexer.HighestX()][_indexer.y1].setFillColor(board[_indexer.HighestX() - 1][_indexer.y1].getFillColor());
		board[_indexer.HighestX() - 1][_indexer.y1].setFillColor(sf::Color::Black);
	}
	else
	{
		board[_indexer.x1 + 1][_indexer.y1].setFillColor(_indexer.col1);
		board[_indexer.x2 + 1][_indexer.y2].setFillColor(_indexer.col2);
		board[_indexer.x2][_indexer.y2].setFillColor(sf::Color::Black);
		board[_indexer.x1][_indexer.y1].setFillColor(sf::Color::Black);
	}
	_indexer.IncrementX();
	return true;
}

bool PillPuzzleState::MoveLeft()
{
	if (_indexer.LowestX() == 0 || board[_indexer.LowestX() - 1][_indexer.y1].getFillColor() != sf::Color::Black || board[_indexer.LowestX() - 1][_indexer.y2].getFillColor() != sf::Color::Black)
		return false;

	if (_indexer.Horizontal())
	{
		board[_indexer.LowestX() - 1][_indexer.y1].setFillColor(board[_indexer.LowestX()][_indexer.y1].getFillColor());
		board[_indexer.LowestX()][_indexer.y1].setFillColor(board[_indexer.LowestX() + 1][_indexer.y1].getFillColor());
		board[_indexer.LowestX() + 1][_indexer.y1].setFillColor(sf::Color::Black);
	}
	else
	{
		board[_indexer.x1 - 1][_indexer.y1].setFillColor(_indexer.col1);
		board[_indexer.x2 - 1][_indexer.y2].setFillColor(_indexer.col2);
		board[_indexer.x2][_indexer.y2].setFillColor(sf::Color::Black);
		board[_indexer.x1][_indexer.y1].setFillColor(sf::Color::Black);
	}
	_indexer.DecrementX();
	return true;
}

void PillPuzzleState::UpdateBoard()
{
	
	int sameleft1 = 0;
	int sameright1 = 0;
	int sameup1 = 0;
	int samedown1 = 0;
	int sameleft2 = 0;
	int sameright2 = 0;
	int sameup2 = 0;
	int samedown2 = 0;
	int i;
	i = 1;
	while (_indexer.x1 - i >= 0 && board[_indexer.x1 - i][_indexer.y1].getFillColor() == _indexer.col1)
	{
		i++;
		sameleft1++;
	}
	i = 1;
	while (_indexer.x2 - i >= 0 && board[_indexer.x2 - i][_indexer.y2].getFillColor() == _indexer.col2)
	{
		i++;
		sameleft2++;
	}
	i = 1;
	while (_indexer.x1 + i < blocksX && board[_indexer.x1 + i][_indexer.y1].getFillColor() == _indexer.col1)
	{
		i++;
		sameright1++;
	}
	i = 1;
	while (_indexer.x2 + i > 0 && board[_indexer.x2 + i][_indexer.y2].getFillColor() == _indexer.col2)
	{
		i++;
		sameright2++;
	}
	i = 1;
	while (_indexer.y1 - i >= 0 && board[_indexer.x1][_indexer.y1 - i].getFillColor() == _indexer.col1)
	{
		i++;
		sameup1++;
	}
	i = 1;
	while (_indexer.y2 - i >= 0 && board[_indexer.x2][_indexer.y2 - i].getFillColor() == _indexer.col2)
	{
		i++;
		sameup2++;
	}
	i = 1;
	while (_indexer.y1 + i < blocksY && board[_indexer.x1][_indexer.y1 + i].getFillColor() == _indexer.col1)
	{
		i++;
		samedown1++;
	}
	i = 1;
	while (_indexer.y2 + i < blocksY && board[_indexer.x2][_indexer.y2 + i].getFillColor() == _indexer.col2)
	{
		i++;
		samedown2++;
	}

	if (sameright1 + sameleft1 + 1 >= 4)
	{
		for (int i = _indexer.x1 - sameleft1; i <= _indexer.x1 + sameright1; i++)
		{
			board[i][_indexer.y1].setFillColor(sf::Color::Black);
			board[i][_indexer.y1].setTexture(nullptr);

		}
	}
	if (sameright2 + sameleft2 + 1 >= 4)
	{
		for (int i = _indexer.x2 - sameleft2; i <= _indexer.x2 + sameright2; i++)
		{
			board[i][_indexer.y2].setFillColor(sf::Color::Black);
			board[i][_indexer.y2].setTexture(nullptr);

		}
	}
	if (sameup1 + samedown1 + 1 >= 4)
	{
		for (int i = _indexer.y1 - sameup1; i <= _indexer.y1 + samedown1; i++)
		{
			board[_indexer.x1][i].setFillColor(sf::Color::Black);
			board[_indexer.x1][i].setTexture(nullptr);
		}
	}
	if (sameup2 + samedown2 + 1 >= 4)
	{
		for (int i = _indexer.y2 - sameup2; i <= _indexer.y2 + samedown2; i++)
		{
			board[_indexer.x2][i].setFillColor(sf::Color::Black);
			board[_indexer.x2][i].setTexture(nullptr);
		}
	}


}

void PillPuzzleState::ResetIndexer()
{
	_indexer.x1 = 4;
	_indexer.y1 = 1;
	_indexer.x2 = 5;
	_indexer.y2 = 1;

	sf::Color colors[] = { sf::Color::Yellow ,sf::Color::Blue ,sf::Color::Red ,sf::Color::Green };

	_indexer.col1 = colors[rand() % 4];
	_indexer.col2 = colors[rand() % 4];
}
