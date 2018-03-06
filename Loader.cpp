#include <memory>
#include <vector>
#include <string>
#include <dlfcn.h>

#include "Agent.h"
#include "HubAPI.h"
#include "configure.h"
#include "Loader.h"

typedef shared_ptr<Agent> (*externCreate)(void);
typedef void (*externDestroy)(shared_ptr<Agent>);

Loader::Loader(){
}

Loader::~Loader(){
}

shared_ptr<Agent> Loader::CreateInitAgent(shared_ptr<Configuration> _configInfo, HubAPI* _hub){
	void* handle;
	const char* error;
	externCreate createSo;
	shared_ptr<Agent> newAgent;

	handle = dlopen(_configInfo->GetType().c_str(), RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "Couldn't open libctest: %s\n", dlerror());
		exit(1);
	}
	l_handles.push_back(handle);

	createSo = (externCreate) dlsym(handle, "create");
	if ((error = dlerror())) {
		cout << "Couldn't find create" << endl;
		exit(1);
	}
	
	newAgent = createSo();
	newAgent->Initialize(_configInfo, _hub);

	return newAgent;
}

void Loader::DestroyAllAgents(){
	for(unsigned int i = 0; i < l_handles.size(); ++i){
		dlclose(l_handles[i]);
	}

}

