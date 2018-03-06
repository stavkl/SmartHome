#ifndef __LOADER_H__
#define __LOADER_H__

#include <memory>
#include <vector>
#include <string>
#include <dlfcn.h>

using namespace std;

class HubAPI;
class Agent;
class Configuration;

class Loader{

	public:
		Loader();
		~Loader();
		shared_ptr<Agent> 	CreateInitAgent(shared_ptr<Configuration> _configInfo, HubAPI* _hub);
		void				DestroyAllAgents();
		
	private:
		vector<void*>	l_handles;

		Loader(const Loader& _ldr);
		const Loader& operator=(const Loader& _ldr);
		
};

#endif /*__LOADER_H__*/
