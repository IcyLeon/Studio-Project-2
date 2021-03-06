#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Camera4.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "timer.h"
#include "Objects.h"
#include <sstream>
#include <stdlib.h>

class SceneAssignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_LIGHTBALL,
		GEO_FIST,

		//skybox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		//mudkip
		GEO_MUDKIP_SPHERE,
		GEO_MUDKIP_CHEEKS,
		GEO_MUDKIP_TAIL,
		GEO_MUDKIP_CONE,
		GEO_MUDKIP_WHITE_SPOT,
		GEO_BLACKBALL,
		GEO_MUDKIP_LIGHTER_SPHERE,
		GEO_MUDKIP_EYES,

		//houses
		GEO_HOUSE1, //player's house
		GEO_HOUSE2,
		GEO_HOUSE3,
		GEO_HOUSE4,
		GEO_SHOP_STRUCTURE,
		GEO_SHOP_ROOF,

		//walls
		GEO_OUTERWALLS,

		//others
		GEO_BARREL,
		GEO_CRATE,
		GEO_LAMPPOST,
		GEO_BED,
		GEO_DESK,
		GEO_LAPTOP,
		GEO_HOMELAMP,
		GEO_TREERING,

		//geometries without hitboxes
		GEO_HITBOX,
		GEO_HITBOX2,
		GEO_CONCRETE_PAVEMENT,
		GEO_ROAD,
		GEO_TEXTBACKGROUND,
		GEO_MUDKIP_AVATAR,
		GEO_UIBACKGROUND,
		GEO_LOG,
		GEO_WATERDROP,
		GEO_DOORWAY,
		GEO_HOUSE_WALL,
		GEO_HOUSE_WALL_WINDOW,
		GEO_HOUSE_FLOOR,
		GEO_BOAT,
		GEO_ROCK,
		GEO_GROUND,
		GEO_WATER,
		GEO_TREE,
		

		//text
		GEO_TEXT_CALIBRI,
		GEO_TEXT_COMICSANS,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		//add these enum in UNIFORM_TYPE before U_TOTAL
		//light 1
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		//light 2
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		//light 3
		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		//light 4
		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		//light 5
		U_LIGHT4_POSITION,
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,
		U_LIGHT4_TYPE,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,

		//light 6
		U_LIGHT5_POSITION,
		U_LIGHT5_COLOR,
		U_LIGHT5_POWER,
		U_LIGHT5_KC,
		U_LIGHT5_KL,
		U_LIGHT5_KQ,
		U_LIGHT5_TYPE,
		U_LIGHT5_SPOTDIRECTION,
		U_LIGHT5_COSCUTOFF,
		U_LIGHT5_COSINNER,
		U_LIGHT5_EXPONENT,

		//light 7
		U_LIGHT6_POSITION,
		U_LIGHT6_COLOR,
		U_LIGHT6_POWER,
		U_LIGHT6_KC,
		U_LIGHT6_KL,
		U_LIGHT6_KQ,
		U_LIGHT6_TYPE,
		U_LIGHT6_SPOTDIRECTION,
		U_LIGHT6_COSCUTOFF,
		U_LIGHT6_COSINNER,
		U_LIGHT6_EXPONENT,

		//light 8
		U_LIGHT7_POSITION,
		U_LIGHT7_COLOR,
		U_LIGHT7_POWER,
		U_LIGHT7_KC,
		U_LIGHT7_KL,
		U_LIGHT7_KQ,
		U_LIGHT7_TYPE,
		U_LIGHT7_SPOTDIRECTION,
		U_LIGHT7_COSCUTOFF,
		U_LIGHT7_COSINNER,
		U_LIGHT7_EXPONENT,

		U_LIGHTENABLED,
		U_NUMLIGHTS,

		//for text
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
	enum GAME_STATES
	{
		gs_mainmenu,
		gs_env,
		gs_credits,
		gs_states
	};
	enum EXTRA_OBJECTORHITBOXES //for extra hitboxes
	{
		//objects
		hb_crate1,
		hb_crate2,
		hb_crate3,
		hb_barrel1,
		//house 1
		hb_house1_door,
		hb_house1_wall_back,
		hb_house1_wall_right,
		hb_house1_wall_front,
		hb_house1_wall_front_window1,
		hb_house1_wall_front_window2,
		hb_house1_wall_right_window,
		hb_house1_floor,
		hb_house1_roof,
		//house2
		hb_house2_door,
		hb_house2_wall_back,
		hb_house2_wall_right,
		hb_house2_wall_front,
		hb_house2_wall_front_window1,
		hb_house2_wall_front_window2,
		hb_house2_wall_right_window,
		hb_house2_floor,
		hb_house2_roof,
		hb_table,
		hb_bed,
		hb_lamp,
		hb_lamppost2,
		hb_lamppost3,
		hb_lamppost4,
		hb_tree1,
		hb_tree2,
		hb_tree3,
		hb_tree4,
		hb_newtree5,

		hb_BOAT1,
		hb_ROCK1,
		hb_ROCK2,
		hb_ROCK3,
		hb_ROCK4,
		hb_water,
		hb_side1,
		hb_side2,

		//purely for boundary checking
		hb_house31,
		hb_border_front,
		hb_border_back,
		hb_border_left,
		hb_border_right,
		hb_count
	};
	enum MENUBUTTON
	{
		mb_none,
		mb_start,
		mb_credits,
		mb_quit,
	};
	enum INTERACTIONS
	{
		i_light1,
		i_light2,
		i_light3,
		i_light4,
		i_shop,
		i_plant_tree,
		i_home1_frontdoor,
		i_home1_frontdoor_inside,
		i_home2_frontdoor,
		i_laptop,
		i_home3_back,
		i_home3_garage,
		i_home3_frontdoor,
		i_home4_frontdoor,
		i_home4_backdoor,
		i_exit,
		i_count,
	};
public:
	SceneAssignment2();
	~SceneAssignment2();

	virtual void Init();
	virtual bool Update(double dt);
	virtual bool UpdateMainMenu();
	virtual void UpdateENV(double dt);
	virtual void UpdateCredits(double dt);
	virtual void Render();
	virtual void RenderMainmenu();
	virtual void RenderENV();
	virtual void RenderCredits();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	unsigned gamestate;
	unsigned interact;
	unsigned count;
	Mesh* meshList[NUM_GEOMETRY];
	Objects objectlist[NUM_GEOMETRY];
	Objects otherhitboxes[hb_count];
	Objects interactionhitboxes[i_count];
	Objects player;
	Hitbox fist1, fist2;
	float playerfist1, playerfist2;
	bool playerfist1extend, playerfist2extend;
	Vector3 savedposition, savedtarget;

	float playermovementspeed;
	unsigned playergold, playerpunchpower, playerwater, shopselect, textprogress, pricemultiplier, playerwood, treegrowthstage;
	bool playerhasseed, playerhaskey, lackofmoney, playerboughtitem, lackofwood, playerlost, lackofwater;
	bool house2locked, treeplanted;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	bool resume, escbuttonstate, triedtoopendoor;
	unsigned buttonhover;

	float rotateAngle, gamemovementspeed, playerscore;
	float timesincelastbuttonpress = 0, timesincelastpunch;
	bool DrawAxis, InWindow, mousehidden, renderhitboxes, checkcollision, inshop, ingame, chatting;
	HWND window; RECT rect;
	LPPOINT mousepos;
	Vector3 camerapos;
	bool debug;

	std::ostringstream UIstringoutput;

	Camera4 camera;

	MS modelStack, viewStack, projectionStack;

	float fps;
	std::string fpstext;

	Light light[8];
	
	//functions for rendering
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderSkybox(Vector3 skyboxoffset);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, Vector3 size, Vector3 rotate, float x, float y);
	void RenderMudkip(Vector3 position = Vector3(0, 8, 0), Vector3 rotation = Vector3(0, 0, 0));
};

#endif
