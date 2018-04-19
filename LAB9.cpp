//============================================================================
// Name        : LAB9.cpp
// Author      : QIAN Shiyi & JIN Menghe
// Version     :
// Copyright   : Your copyright notice
// Description : LAB9
//============================================================================

/*
Graba-Graba! You are Minion Jerry! You and your Weapons Team buddies Kevin & Carl are
playing a game of Graba-Graba. On a 15 x 15 factory floor, Dr. Nefario¡¦s wacky weapons
machine spits out weapons on the floor at random! The firepower and weapons it spits out are:
10 FartGun, 9 ShrinkRay, 8, FreezeRay, 7 RocketLauncher, 6 Dynamite, 5 FireExtinguisher, 4 Axe,
3 Scythe, 2 Cleaver, and 1 EggBeater. For each move you make, the probability each weapon
will be spit out is inversely proportional to the firepower, meaning an EggBeater will appear
every move, but a FartGun only every 10 moves! Also, for each move you make, Kevin & Carl
also move. Kevin moves toward the strongest weapon nearby. Carl is not very smart, and
simply moves at random. When you move into a square with a weapon, it is added to your
collection. Each round lasts 10-20 seconds. Go for the gusto! Grab like an octopus!
Make it simple & fun. Use structs Minion and Weapon. Minion contains the name and a
Weapon pointer. The struct Weapon contains the weapon name, firepower, and another
Weapon pointer. Link weapons from one to another in a chain (Optionally: from highest-tolowest).
When the game is over, list the weapons and their total firepower.
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Weapon{
	char WeaponName[15];
	int Power;
	Weapon* next;
};

struct Minion{
	char Name[10];
	int row;
	int col;
	Weapon* first;
};

void InitMap(int map[][15]);
void Display(int map[][15], const Minion x, const Minion y, const Minion z);
bool CheckEmpty(int row, int col, int map[][15], const Minion x, const Minion y, const Minion z);
void SplitWeapon(int map[][15], const Minion x, const Minion y, const Minion z);

int main() {
	// Initialize Minion
	Minion Kevin = {"Kevin", 14, 0, nullptr}, Carl = {"Carl", 14, 7, nullptr}, Jerry = {"Jerry", 14, 14, nullptr};
	// Struct an 15x15 int array and initialize it
	int map[15][15];
	InitMap(map);
	srand(time(NULL));

	return 0;
}

void InitMap(int map[][15]){
	for (int i=0; i<15; i++){
		for (int j=0; j<15; j++){
			map[i][j]=0;
		}
	}
}

void Display(int map[][15], const Minion x, const Minion y, const Minion z){
	for (int i=0; i<15; i++){
		for (int j=0; j<15; j++){
			if ((i==x.row)&&(j==x.col)&&(i==y.row)&&(j==y.col)&&(i==z.row)&&(j==z.row)){
				cout<<"KCJ";
			}
			else if ((i==x.row)&&(j==x.col)&&(i==y.row)&&(j==y.col)&&((i!=z.row)||(j!=z.row))){
				cout<<"KC ";
			}
			else if ((i==x.row)&&(j==x.col)&&(i==z.row)&&(j==z.col)&&((i!=y.row)||(j!=y.row))){
				cout<<"KJ ";
			}
			else if ((i==y.row)&&(j==y.col)&&(i==z.row)&&(j==z.col)&&((i!=x.row)||(j!=x.row))){
				cout<<"CJ ";
			}
			else if ((i==x.row)&&(j==x.col)&&((i!=y.row)||(j!=y.col))&&((i!=z.row)||(j!=z.row))){
				cout<<" K ";
			}
			else if ((i==y.row)&&(j==y.col)&&((i!=x.row)||(j!=x.col))&&((i!=z.row)||(j!=z.row))){
				cout<<" C ";
			}
			else if ((i==z.row)&&(j==z.col)&&((i!=y.row)||(j!=y.col))&&((i!=x.row)||(j!=x.row))){
				cout<<" J ";
			}
			else if (map[i][j]==0){
				cout<<"   ";
			}
			else {
				cout<<" "<<map[i][j]<<" ";
			}
			cout<<"|";
		}
		cout<<endl;
	}
}

void SplitWeapon(int map[][15], const Minion x, const Minion y, const Minion z){
	for (int i=1; i<10; i++){
		int set = rand()%i, row, col;
		if (set==0){
			do {
				row=rand()%15;
				col=rand()%15;
			} while (!CheckEmpty(row, col, map, x, y, z));
			map[row][col]=i;
		}
	}
}

bool CheckEmpty(int row, int col, int map[][15], const Minion x, const Minion y, const Minion z){
	if ((map[row][col]==0)&&((row!=x.row)||(col!=x.col))&&((row!=y.row)||(col!=y.col))&&((row!=y.row)||(col!=y.col))){
		return true;
	}
	else {
		return false;
	}
}

void MoveCarl(int map[][15], Minion& x){

}

void MoveKevin(int map[][15], Minion& x){

}

void MoveJerry(int map[][15], Minion& x){
	char direction;
	cout<<x.Name<<", it is your turn to move!"<<endl;
	do {
		cout<<"Enter \'a\' to move right, enter \'s\' to move downward, enter \'d\' to move left, enter \'w\' to move upward:";
		cin>>direction;
	} while ((direction!='a')||(direction!='s')||(direction!='d')||(direction!='w'));
	if (direction=='a'){
		x.col=(x.col-1<0)?0:x.col-1;
	}
	else if (direction=='s'){
		x.row=(x.row+1>14)?14:x.row+1;
	}
	else if (direction=='d'){
		x.col=(x.col+1>14)?14:x.col+1;
	}
	else {
		x.row=(x.row-1<0)?0:x.row-1;
	}
	// get monster
}
