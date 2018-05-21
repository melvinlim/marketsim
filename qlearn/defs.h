#ifndef _DEFS_H
#define _DEFS_H
//#define HUMAN
//#define DEBUG
#define VISIONX 5
#define VISIONY 5
//#define STATEVARS (VISIONX*VISIONY)
#define STATEVARS 166
#define ACTIONVARS 3
#define RANDSCALING 10
#define MEMORYSIZE 1000
#define BATCHSIZE 100
#define ALPHA 0.1
#define GAMMA (0.01/(double)BATCHSIZE)
#define LAMBDA_DECAY (0.008/(double)BATCHSIZE)
#define DISCOUNT 0.8
#define HIDDENUNITS 100
#ifdef HUMAN
	#define TRAININGTIME 0
#else
	#define TRAININGTIME 2000
//	#define TRAININGTIME 0
#endif
#define TIMELIMIT 10

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

typedef int Action;
struct Info{
	double state[STATEVARS];
	double nextState[STATEVARS];
	Action action;
	double reward;
	Info &operator=(const Info &x){
		for(int i=0;i<STATEVARS;i++){
			state[i]=x.state[i];
			nextState[i]=x.nextState[i];
		}
		action=x.action;
		reward=x.reward;
		return *this;
	}
};
#endif
