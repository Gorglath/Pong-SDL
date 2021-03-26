#ifndef ID_PONG_PADDLEINPUT_H
#define ID_PONG_PADDLEINPUT_H

struct PaddleInput
{
public:
	bool MoveUp = false;
	bool MoveDown = false;
	bool MoveLeft = false;
	bool MoveRight = false;
	bool Select = false;
};
#endif // !ID_PONG_INPUTMANAGER_H

