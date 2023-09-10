#include "FlagMember.h"

FlagMember::FlagMember(const string& name,int grade, int height)
	: name(name),grade(grade),height(height),taskCount(0){}

string FlagMember::getName() const {
	return name;
}

int FlagMember::getGrade() const {
	return grade;
}

int FlagMember::getHeight() const{
	return height;
}

void FlagMember::setNJunavailableTimes(const vector<int>& njtimes) {
	NJunavailableTimes = njtimes;
}
void FlagMember::setEWunavailableTimes(const vector<int>& ewtimes) {
	EWunavailableTimes = ewtimes;
}

void FlagMember::addNJunavailableTime(int unabletime) {
	NJunavailableTimes.push_back(unabletime);
}
void FlagMember::addEWunavailableTime(int unabletime) {
	EWunavailableTimes.push_back(unabletime);
}

void FlagMember::addNJunavailableTimes(const vector<int>& ewtimes) {
	for (int ewtime : ewtimes) {
		if (find(NJunavailableTimes.begin(), NJunavailableTimes.end(), ewtime) == NJunavailableTimes.end()) {
			NJunavailableTimes.push_back(ewtime);
		}
	}
}


bool FlagMember::isNJtimeUnavailable(int njtime) const {
	for (int t : NJunavailableTimes) {
		if (t == njtime)
			return true;
	}
	return false;
}
bool FlagMember::isEWtimeUnavailable(int ewtime) const {
	for (int t : EWunavailableTimes) {
		if (t == ewtime)
			return true;
	}
	return false;
}

void FlagMember::increaseTaskCount() {
	++taskCount;
}

int FlagMember::getTaskCount() const {
	return taskCount;
}

vector<int> FlagMember::getEWunavailableTimes() const {
	return EWunavailableTimes;
}
vector<int> FlagMember::getNJunavailableTimes() const {
	return NJunavailableTimes;
}