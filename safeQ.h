#ifndef __SAFEQ_H__
#define __SAFEQ_H__

#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <memory>
#include "event.h"

using namespace std;

class SafeMsgQueue{

	public:
		SafeMsgQueue();
		virtual ~SafeMsgQueue();

		void 						SendEvent(shared_ptr<Event> _event);
		shared_ptr<Event> 			ReadEvent();
		queue<shared_ptr<Event>> 	GetQueue()const {return m_eventQ;}

	private:
		pthread_mutex_t 			m_lock;
		pthread_cond_t 				m_condSend;
		pthread_cond_t 				m_condRead;
		queue<shared_ptr<Event>> 	m_eventQ;

		SafeMsgQueue(const SafeMsgQueue& _smq);
		const SafeMsgQueue& operator=(const SafeMsgQueue& _smq);

};

#endif /*__SAFEQ_H__*/
