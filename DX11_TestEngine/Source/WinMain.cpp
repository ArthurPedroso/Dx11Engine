#include "MainApp.h"
//-----A FAZER-----//
// Fazer tarefa de LMA
	//desenhar poligono qtd indeterminada de vertices -ok
	//operacoes lineares de espaco local para viewport -ok
	//armazenamento em padrao JSON -ok
	//editor com mouse -ok
	//lista ligada como estrutura de dados -menos eficiente, descartado
//Terefa CGPI:
	// Renderizar Cubo/objeto 3d
	// Controle de camera com WASD
	// Operacoes 3d nos objetos


int CALLBACK WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	MainApp app(0.002f);
	return app.Run();
}