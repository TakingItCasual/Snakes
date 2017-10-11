/*
* Cpp/SDL game based on Nokias Snake.
* Copyright (C) 2011-2013 TakingItCasual

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//The variable classes
#include "Variables/Food.h"
#include "Graphics/GraphicFiles_Vars.h"
#include "Variables/InternalRandom.h"
#include "Variables/LoopControl.h"
#include "Variables/OptionsRandom.h"
#include "Variables/Map.h"
#include "Variables/MidVars.h"
#include "Variables/Snake.h"
#include "Variables/Timer.h"

//System(s)
#include "Systems/GMI_Vars.h"

//Contains functions used in main.
#include "Functions/Files.h"
#include "Functions/FoodSystem.h"
#include "Functions/GameOver.h"
#include "Graphics/GraphicFiles_Main.h"
#include "Functions/Initializers.h"
#include "Functions/Input.h"
#include "Functions/Menu.h"
#include "Functions/NPC.h"
#include "Functions/Tail.h"

//The Game
int main(int argc, char* args[]) {

	Food Food;
	GraphicFiles_Vars GF_Var;
	InternalRandom IRand;
	LoopControl Loop;
	OptionsRandom ORand;
	Map Map;
	MidVars MidVar;
	Snake Snake;
	Timer Timer;

	GMI_Vars GMI_Var;

	Files File;
	FoodSys FoodSys;
	GameOver GameOver;
	GraphicFiles_Main GF_Main;
	Initializers Init;
	Input Input;
	Menu Menu;
	NPC NPC;
	Tail Tail;

	//External variables initializers.
	Init.ExternalVariableInitializers(Food, GMI_Var, IRand, Loop, Map, ORand, Snake);
	//Gets saved options from a txt file.
	File.ReadOptionsFile(IRand, Map, MidVar, ORand, Snake);
	//Gets high scores from a txt file.
	File.ReadHighScoresFile(IRand, MidVar);
	//Initializes SDL
	GF_Main.init_SDL(GMI_Var, GF_Var);
	//Gets snake movement controls from a txt file.
	File.ReadInputASCII(GF_Var, MidVar);
	//The program (re)start point.
	while (Loop.getGameReset()) {
		//Menu, where the user can customize and start the game.
		Menu.MainMenu(GMI_Var, GF_Var, IRand, Loop, Map, MidVar, ORand);
		//Saves Options to a txt file.
		File.WriteOptionsFile(Map, ORand, Snake);
		//Saves snake movement controls to a txt file.
		File.WriteInputASCII(GF_Var);
		if (Loop.getGameReset()) {
			//Initializes SDL components for the game loop.
			GF_Main.init_SDL_GameLoop(GMI_Var, GF_Var, Map, ORand);
			//Reads saved game txt file if game is loaded.
			File.ReadSavedGame(Food, IRand, Map, MidVar, ORand, Snake);
			//Defaults variables for the game loop.
			Init.InternalVariableInitializers(Food, GMI_Var, GF_Var, IRand, Loop, Map, ORand, Snake);
			//Constructes the borders of the map.
			Init.MapBorderBuild(IRand, Map);
			//Initializers for the game loop.
			Init.FunctionInitializers(Food, IRand, Map, ORand, Snake, Timer);
			//The game loop.
			while (!Loop.getExitState()) {
				//SDL based input system.
				Input.GetInput(GMI_Var, GF_Var, IRand, Loop, Map, ORand, Snake, Timer);
				//Saves game on exit if user chooses to.
				File.WriteSavedGame(Food, IRand, Loop, Map, ORand, Snake);
				//NPC AI
				NPC.NPC_Move(Food, Map, ORand, Snake);
				//Checks user input.
				Tail.ProcessUserInput(IRand, Loop, Map, ORand, Snake);
				//Deletes the snake right after death.
				Tail.DeleteSnakeTail(IRand, Map, ORand, Snake);
				//Places the food onto the map and processes it.
				FoodSys.FoodProcess(Food, GF_Var, IRand, Loop, Map, ORand, Snake);
				//Keeps the tail of the Snake the same size (becomes larger as you eat).
				Tail.TailLengthMaintainer(IRand, Map, ORand, Snake);
				//Draws the SDL game loop screen.
				GF_Main.UpdateGameScreen(GMI_Var, GF_Var, Food, Loop, Map, ORand, Snake);
				//Exits the game loop if a right condition is met.
				GameOver.GameLoopExit(IRand, Loop, Map, ORand, Snake);
			}
			GF_Main.quit_SDL_GameLoop(GF_Var);
		}
		//Saves high scores to a txt file.
		File.WriteHighScoresFile(IRand, Loop, MidVar, ORand);
		//Tells you how you exited the game loop and shows final score(s).
		GameOver.GameOverMessage(GMI_Var, GF_Var, IRand, Loop, Map, ORand);
	}
	//Quits SDL
	GF_Main.quit_SDL(GF_Var, ORand);

	return 0;
}
