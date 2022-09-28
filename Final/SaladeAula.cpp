#include "SaladeAula.h"

SaladeAula::SaladeAula():
	Fase()
{

	bg= new Entidade(texturas.getTextura(5), sf::Vector2f(6000.0f, 2000.0f), sf::Vector2f(3000.0f, 0.0f));

	gerarFase(randomEnemies());
}


SaladeAula::~SaladeAula()
{
}

int SaladeAula::randomEnemies()
{
	srand(time(NULL));
	return rand() % 4 ;
}

void SaladeAula::gerarFase(int enemies)
{
	players.inserir(new Player(texturas.getTextura(6), sf::Vector2u(8, 3), 0.1f, 400.0f, 400.0f));
	if(player2)
		players.inserir(new Ricky(texturas.getTextura(13), sf::Vector2u(8, 3), 0.1f, 400.0f, 400.0f, getPlayer(0)->GetPosition()));

	fase1.inserir(new Blackboard(texturas.getTextura(0), sf::Vector2f(600.0f, 10.0f), sf::Vector2f(400.0f, 620.0f)));
	fase1.inserir(new Blackboard(texturas.getTextura(0), sf::Vector2f(600.0f, 10.0f), sf::Vector2f(1200.0f, 620.0f)));
	fase1.inserir(new Blackboard(texturas.getTextura(0), sf::Vector2f(600.0f, 10.0f), sf::Vector2f(2600.0f, 720.0f)));
	fase1.inserir(new Blackboard(texturas.getTextura(0), sf::Vector2f(600.0f, 10.0f), sf::Vector2f(3900.0f, 100.0f)));
	fase1.inserir(new Blackboard(texturas.getTextura(0), sf::Vector2f(600.0f, 10.0f), sf::Vector2f(4900.0f, 720.0f)));
	fase1.inserir(new Blackboard(texturas.getTextura(0), sf::Vector2f(600.0f, 10.0f), sf::Vector2f(5700.0f, 420.0f)));

	fase1.inserir(new Limites(nullptr, sf::Vector2f(6000.0f, 1000.0f), sf::Vector2f(3000.0f, 1500.0f)));//chao
	fase1.inserir(new Limites(nullptr, sf::Vector2f(10.0f, 10000.0f), sf::Vector2f(-5.0f, 1500.0f)));//parede esquerda
	fase1.inserir(new Limites(nullptr, sf::Vector2f(10.0f, 10000.0f), sf::Vector2f(6005.0f, 1500.0f)));//parede direita

	fase1.inserir(new Mesa(texturas.getTextura(1), sf::Vector2f(200.0f, 200.0f), sf::Vector2f(4310.0f, 930.0f)));
	fase1.inserir(new Mesa(texturas.getTextura(1), sf::Vector2f(200.0f, 200.0f), sf::Vector2f(4308.0f, 792.0f)));
	fase1.inserir(new Mesa(texturas.getTextura(1), sf::Vector2f(200.0f, 200.0f), sf::Vector2f(4306.0f, 654.0f)));
	fase1.inserir(new Mesa(texturas.getTextura(1), sf::Vector2f(200.0f, 200.0f), sf::Vector2f(4304.0f, 516.0f)));
	fase1.inserir(new Mesa(texturas.getTextura(1), sf::Vector2f(200.0f, 200.0f), sf::Vector2f(4302.0f, 378.0f)));

	fase1.inserir(new Janela(texturas.getTextura(2), sf::Vector2f(400.0f, 10.0f), sf::Vector2f(3300.0f, 410.0f)));

	fase1.inserir(new Cadeira(texturas.getTextura(3), sf::Vector2f(100.0f, 200.0f), sf::Vector2f(5000.0f, 910.0f),0.6f));

	inimigos.inserir(new PatineteEletrico(texturas.getTextura(4), sf::Vector2f(50.0f, 150.0f), sf::Vector2f(3300.0f, 925.0f)));
	inimigos.inserir(new PatineteEletrico(texturas.getTextura(4), sf::Vector2f(50.0f, 150.0f), sf::Vector2f(5900.0f, 340.0f)));

	inimigos.inserir(new Terraplanista(texturas.getTextura(7), sf::Vector2f(100.0f, 150.0f), sf::Vector2f(800.0f, 925.0f)));
	inimigos.inserir(new Terraplanista(texturas.getTextura(7), sf::Vector2f(100.0f, 150.0f), sf::Vector2f(900.0f, 550.0f)));
	inimigos.inserir(new Terraplanista(texturas.getTextura(7), sf::Vector2f(100.0f, 150.0f), sf::Vector2f(3600.0f, 30.0f)));
	inimigos.inserir(new Terraplanista(texturas.getTextura(7), sf::Vector2f(100.0f, 150.0f), sf::Vector2f(5106.0f, 925.0f)));

	if (enemies <= 1) {
		inimigos.inserir(new Terraplanista(texturas.getTextura(7), sf::Vector2f(100.0f, 150.0f), sf::Vector2f(100.0f, 550.0f)));
		fase1.inserir(new Mochila(texturas.getTextura(11), sf::Vector2f(60.0f, 90.0f), sf::Vector2f(4302.0f, 148.0f)));
	}

	if (enemies >= 1) {
		inimigos.inserir(new Terraplanista(texturas.getTextura(7), sf::Vector2f(100.0f, 150.0f), sf::Vector2f(2350.0f, 640.0f)));
		fase1.inserir(new Mochila(texturas.getTextura(11), sf::Vector2f(60.0f, 90.0f), sf::Vector2f(4900.0f, 680.0f)));
	}
}


void SaladeAula::atualizar( float deltaTime)
{

		for (Inimigo* inimigo : getInimigos())

			inimigo->Update(getPlayer(0), deltaTime);


}

void SaladeAula::ColisaoInimigo()
{
	for(Inimigo* inimigo : getInimigos())
		for (int i = 0; i < getLista().getTamanho(); i++) {
			GerenciadorColisoes aux = inimigo->GetGerenciadorColisoes();
			if (getLista().getElemento(i)->GetGerenciadorColisoes().CheckCollision(aux, direction, 1.0f))
				inimigo->OnCollision(direction);
		}

	for (int j = 15; j < getLista().getTamanho(); j++) {
		getLista().getElemento(j)->setVelocity(sf::Vector2f(getLista().getElemento(j)->getVelocity().x, getLista().getElemento(j)->getVelocity().y + 100.0f));
		for (int i = 0; i < getLista().getTamanho(); i++) {
			GerenciadorColisoes aux = getLista().getElemento(j)->GetGerenciadorColisoes();
			if (i != j) {
				getLista().getElemento(i)->GetGerenciadorColisoes().CheckCollision(aux, direction, 1.0f);
				getLista().getElemento(i)->OnCollision(direction);
			}
		}
		getLista().getElemento(j)->getBody()->move(getLista().getElemento(j)->getVelocity() * 0.01f);
	}
}

void SaladeAula::update( float deltaTime, sf::RenderWindow& window, sf::View& view)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		Ppilha->push_back(new MenuPause(nullptr, sf::Vector2f(1088.0f, 612.0f), sf::Vector2f(544.0f, 596.0f),&view,getPlayer(0)->GetPosition()));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !player2)
	{
		player2 = true;
		players.inserir(new Ricky(texturas.getTextura(13), sf::Vector2u(8, 3), 0.1f, 400.0f, 400.0f,getPlayer(0)->GetPosition()));
	}

	for (Player* pls : getPlayers())
	pls->Update(deltaTime, window);
	atualizar( deltaTime);


	sf::Vector2f direction;

	for (Player* pls : getPlayers())
	pls->setCanJump(false);

	ColisaoInimigo();

	for (Player* pls : getPlayers()) {
		GerenciadorColisoes angry = pls->GetGerenciadorColisoes();
		for (int i = 0; i < getLista().getTamanho(); i++)
			if (getLista().getElemento(i)->GetGerenciadorColisoes().CheckCollision(angry, direction, getLista().getElemento(i)->push))
				pls->OnCollision(direction, false);
	}


	for (Player* pls : getPlayers()) {
		GerenciadorColisoes angry = pls->GetGerenciadorColisoes();
		for (Inimigo* inimigo : getInimigos())
			if (inimigo->GetGerenciadorColisoes().CheckCollision(angry, direction, inimigo->push))
				pls->OnCollision(direction, true);
	}
			
	for (Inimigo* inimigo : getInimigos()) {
		TerraPlana* terraP = inimigo->GetTerraP();
		if (terraP != nullptr) {
			std::vector<TerraPlana*> terraPVect = terraP->getProjeteisTerra();
			for (int i = 0; i < terraPVect.size(); i++)
				for (int j = 0; j < getLista().getTamanho(); j++)
				{
					GerenciadorColisoes terra = terraPVect[i]->GetGerenciadorColisoes();
					if (getLista().getElemento(j)->GetGerenciadorColisoes().CheckCollision(terra, direction, getLista().getElemento(j)->push))
					{
						terraP->OnCollison();
						break;
					}
				}

			for (int i = 0; i < terraPVect.size(); i++)
				for (Player* pls : getPlayers())
				{
					GerenciadorColisoes terra = terraPVect[i]->GetGerenciadorColisoes();
					if (pls->GetGerenciadorColisoes().CheckCollision(terra, direction, inimigo->push))
					{
						terraP->OnCollison();
						pls->OnCollision(direction, true);
						break;
					}
				}
		}

	}

	for (Player* pls : getPlayers()) {
		Giz* proj = pls->GetGiz();
		std::vector<Giz*> projVect = proj->getProjeteisGiz();
		for (int i = 0; i < projVect.size(); i++)
			for (int j = 0; j < getLista().getTamanho(); j++)
			{
				GerenciadorColisoes giz = projVect[i]->GetGerenciadorColisoes();
				if (getLista().getElemento(j)->GetGerenciadorColisoes().CheckCollision(giz, direction, getLista().getElemento(j)->push))
				{
					proj->OnCollison();
					break;
				}
			}

		for (int i = 0; i < projVect.size(); i++) {
			int pos = 0;
			for (Inimigo* inimigo : getInimigos())
			{
				GerenciadorColisoes giz = projVect[i]->GetGerenciadorColisoes();
				if (inimigo->GetGerenciadorColisoes().CheckCollision(giz, direction, inimigo->push))
				{
					proj->OnCollison();
					inimigo->setLife(inimigo->getLife() - 1);

					if (inimigo->getLife() < 1)
						inimigos.deletar(pos);
					break;
				}
				pos++;
			}
		}
	}
	
	sf::Vector2f camera = getPlayer(0)->GetPosition() - view.getCenter();

	if (camera.x > 144.0f || camera.x < -144.0f)
		view.move(sf::Vector2f(400.0f, 0.0f) * deltaTime * (camera.x/abs(camera.x)));

	if (camera.y > 26.0f || camera.y < -150.0f)
		view.move(sf::Vector2f(0.0f, 900.0f) * deltaTime * (camera.y / abs(camera.y)));

	if (view.getCenter().x < 544.0f)
		view.setCenter(sf::Vector2f(544.0f, view.getCenter().y));

	if (view.getCenter().x > 5456.0f)
		view.setCenter(sf::Vector2f(5456.0f, view.getCenter().y));

	if (view.getCenter().y > 596.0f)
		view.setCenter(sf::Vector2f(view.getCenter().x, 596.0f ));

	if (view.getCenter().y < 76.0f)
		view.setCenter(sf::Vector2f(view.getCenter().x, 76.0f));

	for (Player* pls : getPlayers()) {
		if (pls->GetPosition() == sf::Vector2f(5950.0f, 925.0f))
			Ppilha->substituir(new DAFIS(view,player2));

		if (pls->GetVida() <= 0) {
			Ppilha->pop();
		}
	}

	
}
