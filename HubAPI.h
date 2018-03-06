#ifndef __HUBAPI_H__
#define __HUBAPI_H__

#include "event.h"

#include <memory>
#include <string>
#include <time.h> 
#include <unistd.h>
#include <pthread.h>

using namespace std;

class Agent;
class SafeMsgQueue;


class HubAPI{

	public:
		HubAPI(){};
		virtual ~HubAPI(){}
		virtual void Publish(shared_ptr<Event> event) = 0;
		virtual void Subscribe(shared_ptr<Agent> _agent) = 0;

	private:
		HubAPI(const HubAPI& _hubApi);
		const HubAPI& operator=(const HubAPI& _hubApi);
};

#endif /*__HUBAPI_H__*/
