#include "monster.h"
#include "draw.h"

// création du monstre
Monster* createMonster(int nbvague,int index, int begin, TypeMonster type, Node* direction, float X, float Y, Monster** list){
	if (direction == NULL)
	{
		fprintf(stderr, "erreur\n");
		exit(1);
	}

	Monster* monster = (Monster*)malloc(sizeof(Monster));
	if(monster == NULL){
		fprintf(stderr, "erreur allocation\n");
		exit(1);
	}

	monster->indexBegin = begin;
	monster->indexMonster = index;
	monster->type = type;
	monster->X = X;
	monster->Y = Y;
	monster->direction = direction;

	switch(type){
		case ROUGE:
			monster-> pdv = 80 + 10*nbvague;
			monster-> pdvMax = 50 + 10*nbvague;
			monster-> resistance = 1;
			monster-> vitesse = 0.5;
			monster-> gain = 10;
			break;

		case BLEU:
			monster-> pdv = 100 + 10*nbvague;
			monster-> pdvMax = 70+ 10*nbvague;
			monster-> resistance = 2;
			monster-> vitesse = 1;
			monster-> gain = 25;
			break;

		case MASSACREUR:
			monster-> pdv = 150 + 10*nbvague;
			monster-> pdvMax = 100+ 10*nbvague;
			monster-> resistance = 3;
			monster-> vitesse = 1.5;
			monster-> gain = 50;
			break;

		default:
			break;
	}

	monster->next = NULL;
	Monster* tmp = *list;
	if(tmp == NULL){
		*list = monster;
	}
	else{
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = monster;
	}


	return monster;
}

// construit le monstre
void constructMonster(Monster ** list)
{
	GLuint monster_texture;
	Monster *tmp = *list;
	while(tmp != NULL)
	{
		switch(tmp->type){
            case ROUGE:
                monster_texture = Texture_Load("./images/crabe_rouge.png", 31, 31);
                break;
            case BLEU:
                monster_texture = Texture_Load("./images/crabe_bleu.png", 31, 31);
                break;
            case MASSACREUR:
                monster_texture = Texture_Load("./images/crabe_massacreur.png", 31, 31);
                break;
            default:
                break;
        
        }

		float Y = 1 - (tmp->Y/630.0);
		float X = tmp->X/630.0;
		float L = (0.02*tmp->pdv)/tmp->pdvMax;

		// on affiche la barre de vie du monstre
		glPushMatrix();
			glTranslatef(X+0.05, Y+0.025, 0.0);
			glPushMatrix();
				glScalef(L, 0.01, 0.0);
				drawSquare(1);
			glPopMatrix();
		glPopMatrix();
		
		drawMap(monster_texture, X, Y, 0.05, 0.05);
		tmp = tmp->next;
	}
}

// définit le type du monstre en fonction de la vague
TypeMonster chooseMonster(int vague)
{
	TypeMonster type;
	if( vague%5 == 0)
	{
		type = MASSACREUR;
	}
	else if( vague%2 == 0)
	{
		type = BLEU;
	}
	else
	{
		type = ROUGE;
	}
	return type;
}

// cherche un monstre
Monster * getMonster(int index, Monster *listMonster)
{
	if(listMonster == NULL)
    {
        fprintf(stderr,"Erreur liste NULL\n");
        return NULL;
    }
    else
    {
        Monster * actuel = listMonster;
        while (actuel != NULL)
        {
            if(actuel->indexMonster == index)
            {
                return actuel;
            }
            actuel = actuel->next;
        }
        return NULL;
    }
}

// supprime le monstre de la liste
Monster* deleteMonster(Monster *monstre, Monster *listMonster)
{
	Monster * deleteM = getMonster(monstre->indexMonster, listMonster);
	Monster *list = listMonster;
	if(listMonster == NULL)
	{
		fprintf(stderr, "Erreur liste NULL\n");
		exit(1);
	}
	if(listMonster == monstre)
	{
		deleteM = listMonster;
		if(listMonster->next != NULL)
		{
			listMonster = listMonster->next;
			free(deleteM);
			return listMonster;
		}
		else
		{
			free(deleteM);
			return NULL;
		}
	}

	while(listMonster->next != NULL)
	{
		if(listMonster->next == monstre)
		{
			deleteM = listMonster->next;
			if(deleteM->next != NULL)
			{
				listMonster->next = deleteM->next;
			}
			else
			{
				listMonster->next = NULL;
				break;
			}
			free(deleteM);
		}
	
		listMonster = listMonster->next;
	}
		
	return list;
}
