#include "computerRoom.h"

ComputerRoom::ComputerRoom() {
	this->m_RoomId = 0;
	this->m_MaxCapacity = 0;
	this->RoomIsFree = true;
}
ComputerRoom::ComputerRoom(int id, int maxCapacity, bool flag) {
	this->m_RoomId = id;
	this->m_MaxCapacity = maxCapacity;
	this->RoomIsFree = flag;
}
int ComputerRoom::getRoomId() const {
	return this->m_RoomId;
}
void ComputerRoom::setRoomId(int id) {
	this->m_RoomId = id;
}
int ComputerRoom::getMaxCapacity() const {
	return this->m_MaxCapacity;
}
void ComputerRoom::setMaxCapacity(int maxCapacity) {
	this->m_MaxCapacity = maxCapacity;
}
bool ComputerRoom::getRoomIsFree() const {
	return this->RoomIsFree;
}
void ComputerRoom::setRoomIsFree(bool flag) {
	this->RoomIsFree = flag;
}