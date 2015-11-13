#include "game.h"

void testEvt(Entity *e)
{
    std::cout<<"in test event"<<std::endl;
}

Game::Game()
{
    // GL options flags
    bool ABlendFlag=ABLEND, ATestFlag=ATEST, ZOrderFlag=ZORDER;

    screenW=800;
    screenH=640;
    screenBPP=32;

    // initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
	if(TTF_Init() == -1) {
		std::cerr << "failed to initialize SDL_ttf" << std::endl;
	}
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // initialize screen
    screen=NULL;
    if ((screen=SDL_SetVideoMode(screenW, screenH, screenBPP, SDL_OPENGL)) == NULL)
        std::cerr << "Error" << std::endl << "SDL screen failed to initialize" << std::endl;
    SDL_WM_SetCaption("Knights Realm 0.frickinearly", NULL);

    //initialize OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, screenW, screenH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, screenW, screenH, 0.0f, -100.0f, 100.0f); // -100, 100 are z clip range.. meh
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // enable z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

Game::~Game()
{
    SDL_Quit();
}

void Game::Setup()
{
    frameCap=true;
    fps.Start();

    AddMap("test3.tmx");
    // TODO: delete

	Node* tNode=new Node(150, 50, 5);
	Sprite* sp=new Sprite("testsprite.spr");
	ColRect* tCNode=new ColRect("two", 16, 32, tNode);
	tNode->AddChild(sp);
	tNode->AddChild(tCNode);
	AddEntity(tNode);

	sp->Pose(0);

	playerNode=Node(0, 0, 3);
    player=Player("testplayer.spr");
	playerNode.AddChild(&player);
	ColRect* cNode=new ColRect("one", 16, 16, &playerNode);
	playerNode.AddChild(cNode);

	cTrav=ColTraverser();
	cTrav.AddNode(cNode);
	cTrav.AddNode(tCNode);

	Emitter* testEmitter = new Emitter(&playerNode);
	testEmitter->SetParticleDest(&entities);
	playerNode.AddChild(testEmitter);
    
    evtmgr = new EvtMgr();
	player.SetTag("collidable");
	
	//player.GetScript()->print();
	//player.GetScript()->CallFunction("test", boost::python::object());
}

void Game::Run()
{
    while(Tick()) {
    // frame cap
        if((frameCap == true) && (fps.GetTicks() < 1000/FRAMES_PER_SECOND)) {
            SDL_Delay((1000/FRAMES_PER_SECOND) - fps.GetTicks());
        }
        fps.Start();
    }
    delete this;
}

bool Game::Tick()
{
	// read the keyboard
	keyStates = SDL_GetKeyState(NULL);

    //Frame frame(LoadTexture("font.png"));
    if(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
            return false;
		else if(event.type == SDL_MOUSEMOTION) {
			mouseX=event.motion.x;
			mouseY=event.motion.y;
			playerNode.Face(playerNode.GetX() + (-screenW/2+mouseX), playerNode.GetY() + (-screenH/2+mouseY));
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT)
				mouseLDown=true;
			else if(event.button.button == SDL_BUTTON_RIGHT)
				mouseRDown=true;
		}
        else if(event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_UP: playerNode.SetDY(1); break;
                case SDLK_DOWN: playerNode.SetDY(-1); break;
                //case SDLK_LEFT: playerNode.SetDX(-1); player.SetAnimation(1); player.StartAnimation(); break;
                case SDLK_RIGHT: playerNode.SetDX(1); player.LoopAnimation("move_right"); break;
            }
        }
        else if(event.type == SDL_KEYUP) {
            player.Pose(0);
            playerNode.SetDX(0);
            playerNode.SetDY(0);
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update objects
    map.Update();

	playerNode.Update();

	// check for collision
	cTrav.Traverse(evtmgr);

    // update
    for(GameEntity::iterator it = entities.begin(); it != entities.end(); it++) {
        (*it)->Update();
    }

    // view
    camera.SetPos(-playerNode.GetX()+screen->w/2, -playerNode.GetY()+screen->h/2, camera.GetZ());
    camera.Look();

    // draw
    for(GameEntity::iterator it = entities.begin(); it != entities.end(); it++) {
        (*it)->Draw();
    }
    playerNode.Draw();
    map.Render();

    SDL_GL_SwapBuffers();
    return true;
}

//Game& GetGame() 
//{
//	return game;
//}