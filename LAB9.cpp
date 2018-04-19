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
#include <stdio.h>
#include <cstring>
using namespace std;

struct Weapon{
	char WeaponName[20];
	int Power;
	Weapon* next;
};

struct Minion{
	char Name[10];
	int row;
	int col;
	int TotalPower;
	Weapon* first;
};

void InitMap(int map[][15]);
void InitWeapons(char weapons[][20]);
void Display(int map[][15], const Minion x, const Minion y, const Minion z);
bool CheckEmpty(int row, int col, int map[][15], const Minion x, const Minion y, const Minion z);
void SpitWeapon(int map[][15], const Minion x, const Minion y, const Minion z);
void GetWeapon(char weapons[][20], int map[][15], Minion& x);
void ShowResult(const Minion x, const Minion y, const Minion z);

int main() {
	// Initialize Minion
	Minion Kevin = {"Kevin", 14, 0, 0, nullptr}, Carl = {"Carl", 14, 7, 0, nullptr}, Jerry = {"Jerry", 14, 14, 0, nullptr};
	// Struct an 15x15 int array and initialize it
	int map[15][15];
	InitMap(map);
	// Struct an array for weapon names
	char weapons[10][20];
	InitWeapons(weapons);
	srand(time(NULL));
	time_t start=time(nullptr);
	while (time(nullptr)-start<90){ // total play time
		time_t RoundStart = time(nullptr);
		OneRound(map, weapons, Kevin, Carl, Jerry);
		while (time(nullptr)-RoundStart<10){}; // pause if above actions take less than 10 seconds
	}
	ShowResult(Kevin, Carl, Jerry);
	return 0;
}

void InitMap(int map[][15]){
	for (int i=0; i<15; i++){
		for (int j=0; j<15; j++){
			map[i][j]=0;
		}
	}
}
void InitWeapons(char weapons[][20]){
	// 10 FartGun, 9 ShrinkRay, 8, FreezeRay, 7 RocketLauncher, 6 Dynamite, 5 FireExtinguisher, 4 Axe,
	// 3 Scythe, 2 Cleaver, and 1 EggBeater
	strcpy(weapons[0], "EggBeater");
	strcpy(weapons[1], "Cleaver");
	strcpy(weapons[2], "Scythe");
	strcpy(weapons[3], "Axe");
	strcpy(weapons[4], "FireExtinguisher");
	strcpy(weapons[5], "Dynamite");
	strcpy(weapons[6], "RocketLauncher");
	strcpy(weapons[7], "FreezeRay");
	strcpy(weapons[8], "ShrinkRay");
	strcpy(weapons[9], "FartGun");
}
void Display(int map[][15], const Minion x, const Minion y, const Minion z){
	cout<<"Total Power \t"<<x.Name<<": "<<x.TotalPower<<"\t"<<y.Name<<": "<<y.TotalPower<<"\t"<<z.Name<<": "<<z.TotalPower<<endl;
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
			else if (map[i][j]==10){
				cout<<"10 ";
			}
			else {
				cout<<" "<<map[i][j]<<" ";
			}
			cout<<"|";
		}
		cout<<endl;
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
void SpitWeapon(int map[][15], const Minion x, const Minion y, const Minion z){
	for (int i=1; i<=10; i++){
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
void GetWeapon(char weapons[][20], int map[][15], Minion& x){
	for (int i=1; i<=10; i++){
		if (map[x.row][x.col]==i){ // when Jerry runs into a weapon
			x.TotalPower +=i; // add to total power of collection
			Weapon* p = new Weapon; // create a new weapon struct, p is the address of this struct
			strcpy(p->WeaponName, weapons[i-1]); // fill the struct information
			p->Power = i;
			p->next = nullptr; // it is the last object of the linked list
			// NOTE: at this time, the newly created object is not yet part of the list
			for (Weapon* pp = x.first; pp; pp=pp->next){ // trace to the last object of the list created
				if (pp==nullptr){
					pp = p; // add the new struct to the end of the list
					break;  // that is, to make the "Weapon* next" to be the address of the new object
				}
			}
			delete p;
			map[x.row][x.col]=0;
			break;
		}
	}
}

void MoveCarl(int map[][15], char weapons[][20], Minion& x){
	int direction = rand()%4;
	if (direction==0){
		x.col=(x.col-1<0)?0:x.col-1;
	}
	else if (direction==1){
		x.row=(x.row+1>14)?14:x.row+1;
	}
	else if (direction==2){
		x.col=(x.col+1>14)?14:x.col+1;
	}
	else {
		x.row=(x.row-1<0)?0:x.row-1;
	}
	// get weapon
	GetWeapon(weapons, map, x);
}

void MoveKevin(int map[][15], char weapons[][20], Minion& x){
	// ???
	GetWeapon(weapons, map, x);
}

void MoveJerry(int map[][15], char weapons[][20], Minion& x){
	// move
	char direction;
	cout<<x.Name<<", it is your turn to move!"<<endl;
	do {
		cout<<"Enter \'a\' to move right, enter \'s\' to move downward, enter \'d\' to move left, enter \'w\' to move upward:";
		cin>>direction;
	} while ((direction!='a')&&(direction!='s')&&(direction!='d')&&(direction!='w'));
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
	// get weapon
	GetWeapon(weapons, map, x);
}

void OneRound(int map[][15], char weapons[][20], Minion& Kevin, Minion& Carl, Minion& Jerry){
	SpitWeapon(map, Kevin, Carl, Jerry);
	Display(map, Kevin, Carl, Jerry);
	MoveKevin(map, weapons, Kevin);
	MoveCarl(map, weapons, Carl);
	MoveJerry(map, weapons, Jerry);
	Display(map, Kevin, Carl, Jerry);
}

void ShowResult(const Minion x, const Minion y, const Minion z){

}
