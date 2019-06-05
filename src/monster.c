#include "monster.h"
#include "draw.h"

Monster* createMonster(int index, int begin, TypeMonster type, Node* direction, float X, float Y, Monster** list){
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
			monster-> pdv = 50;
			monster-> pdvMax = 50;
			monster-> resistance = 1;
			monster-> vitesse = 0.5;
			monster-> gain = 50;
			break;

		case BLEU:
			monster-> pdv = 70;
			monster-> pdvMax = 70;
			monster-> resistance = 2;
			monster-> vitesse = 1;
			monster-> gain = 100;
			break;

		case MASSACREUR:
			monster-> pdv = 100;
			monster-> pdvMax = 100;
			monster-> resistance = 3;
			monster-> vitesse = 1.5;
			monster-> gain = 150;
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

void constructMonster(Monster ** list)
{
	GLuint monster_texture;
	Monster *tmp = *list;
	//monster_texture = Texture_Load("./images/crabe_rouge.png", 31, 31);
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
		float L = (0.05*tmp->pdv)/tmp->pdvMax;
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

TypeMonster chooseMonster(int vague)
{
	TypeMonster type;
	int choix = vague;
	if( vague%5 == 0)
	{
		type = MASSACREUR;
	}
	if( vague%2 == 0)
	{
		type = BLEU;
	}
	else
	{
		type = ROUGE;
	}
	/*
	switch (vague)
	{
	case 1:
		type = ROUGE;
		break;
	case 2:
		type = BLEU;
		break;
	case 3:
		type = MASSACREUR;
		break;
	
	default:
		break;
	}
	*/
	return type;
}

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
