#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>

using namespace std;

class Event{
	
	public:
		Event(){}
		virtual ~Event(){}

		virtual void SetEventFloor(string _topic) = 0;
		virtual void SetEventRoom(string _room) = 0;
		virtual void SetEventTopic(string _topic) = 0;
		virtual void SetEventTime() = 0;
		virtual string GetEventFloor()const = 0;
		virtual string GetEventRoom()const = 0;
		virtual string GetEventTopic()const = 0;
		virtual string GetEventTime()const = 0;
		virtual string GetEventOperation()const = 0;

};


#endif /*__EVENT_H__*/
