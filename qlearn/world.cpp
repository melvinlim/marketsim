#include"world.h"
void World::updateState(){
	int i=playerObject.i;
	int j=playerObject.j;
	double *p=state;
	char tmp;
	for(int m=0;m<vision.nRows;m++){
		for(int n=0;n<vision.nCols;n++){
			tmp=world(i+m-(vision.nRows/2),j+n-(vision.nCols/2));
			switch(tmp){
				case'.':
				case'@':
					*p++=0;
				break;
				case'<':
					*p++=1.;
				break;
				default:
					*p++=-1.;
			}
			vision(m,n)=tmp;
		}
	}
#ifdef DEBUG
	displayMat(vision);
//	debugState();
#endif
}
void World::debugState(){
	for(int i=0;i<STATEVARS;i++){
		if(i%vision.nCols==0){
			printf("\n");
		}
		printf("%2.2f ",state[i]);
	}
	printf("\n");
}
void World::displayMat(const Matrix<char> &m){
	for(int i=0;i<m.nRows;i++){
		for(int j=0;j<m.nCols;j++){
			printf("%c",m(i,j));
		}
		printf("\n");
	}
}
World::World():
	world(10,10),
	vision(VISIONX,VISIONY)
{
	nRows=nCols=10;
	reset();
}
void World::reset(){
	generateWorld();
	srand(time(0));
	int i=2+random()%(nRows-3);
	int j=2+random()%(nCols-3);
	world(i,j)=' ';
	i=2+random()%(nRows-3);
	j=2+random()%(nCols-3);
	world(i,j)=' ';
	i=1+random()%(nRows-2);
	j=1+random()%(nCols-2);
	placeObject(playerObject,i,j);
	int t=0;
	do{
		t=1+random()%(nRows-2);
	}while(t==i);
	i=t;
	j=1+random()%(nCols-2);
	placeObject(stairs,i,j);
	updateState();
}
int World::movePlayer(int i,int j){
	int i0=playerObject.i;
	int j0=playerObject.j;
	if(world(i,j)==' ')	return -1;
	int result=0;
	if(i==stairs.i&&j==stairs.j)	result=1;
	world(i0,j0)='.';
	placeObject(playerObject,i,j);
	return result;
}
void World::generateWorld(){
	//for(int i=0;i<world.nRows;i++){
	//	for(int j=0;j<world.nCols;j++){
	for(int j=0;j<world.nCols;j++){
		world(0,j)=' ';
	}
	for(int i=1;i<world.nRows-1;i++){
		world(i,0)=' ';
		for(int j=1;j<world.nCols-1;j++){
			world(i,j)='.';
		}
		world(i,world.nCols-1)=' ';
	}
	for(int j=0;j<world.nCols;j++){
		world(world.nRows-1,j)=' ';
	}
}
World::~World(){}
void World::placeObject(Object &obj,int i,int j){
	world(i,j)=obj.self;
	obj.i=i;
	obj.j=j;
}
void World::display(){
	displayMat(vision);
	//displayMat(world);
/*
	for(int i=0;i<nRows;i++){
		for(int j=0;j<nCols;j++){
			printf("%c",world(i,j));
		}
		printf("\n");
	}
*/
}
