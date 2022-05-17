#pragma once
#include <iostream>

using namespace std;

class ComputerRoom {
private:
	int m_RoomId;
	int m_MaxCapacity;
	bool RoomIsFree;

public :
	ComputerRoom();
	ComputerRoom(int id, int maxCapacity, bool flag);
	int getRoomId() const;
	void setRoomId(int id);
	int getMaxCapacity() const ;
	void setMaxCapacity(int maxCapacity);
	bool getRoomIsFree() const;
	void setRoomIsFree(bool flag);
};

