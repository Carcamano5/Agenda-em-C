#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>
typedef struct{
	int d,m,a;
}Data;

typedef struct{
	char nome[50],fone[15],email[40];
	Data aniv;
}Contato;

int menu(){
	int opcao;
	printf("\n1 - Inserir\n");
	printf("\n2 - Exibir\n");
	printf("\n3 - Alterar\n");
	printf("\n4 - Excluir\n");
	printf("\n5 - Ordenar\n");
	printf("\n6 - Sair\n");
	printf("\nOpcao: ");
	scanf("%d",&opcao);
	return opcao;
}

void inserir()
{
	FILE *arq;
	Contato ctt;
	int pos;
	arq = fopen("Agenda2.bin","ab+");//usamos ab+ pois precisamos fazer duas operações, de leitura e escrita
	if(arq == NULL)
	{
		printf("erro \n");
	}
	else
	{
		do
		{
			system("cls");
			printf("\nInforme nome completo:");fflush(stdin);
			gets(ctt.nome);
			pos = busca(arq, ctt.nome);//busca retorna uma posição binaria caso este nome ja esteja cadastrado, ou um negativo caso não
			if(pos == -1)
			{
				printf("\nInforme o telefone:");fflush(stdin);
				gets(ctt.fone);
				printf("\nInforme a data de aniversario dd mm aaaa: ");
				scanf("%d %d %d", &ctt.aniv.d,&ctt.aniv.m,&ctt.aniv.a);
				printf("\nInforme email:");fflush(stdin);
				gets(ctt.email);
				fwrite(&ctt,sizeof(Contato),1,arq);//escreve no arquivo
			}
			else 
			{
				fseek(arq,pos,0);//posiciona o ponteiro na posição retornada pela função busca, exibindo o nome que ja esta cadastrado
				fread(&ctt,sizeof(Contato),1,arq);
				printf("\n %s (Contato ja cadastrado!)",ctt.nome);
			}
			printf("Deseja continuar? (s)(n)");
		}while(toupper(getche())=='S');
		
	}
	fclose(arq);
}

void exibir()
{
	FILE *arq;
	Contato ctt;
	arq = fopen("Agenda2.bin","rb");
	if(arq == NULL)
	{
		printf("erro \n");
	}
	else
	{
		while(fread(&ctt,sizeof(Contato),1,arq)==1)
		{
			printf("\n Nome: %s", ctt.nome);
			printf("\n Telefone: %s", ctt.fone);
			printf("\n Aniversario: %d/%d/%d", ctt.aniv.d,ctt.aniv.m,ctt.aniv.a);
			printf("\n E-mail: %s", ctt.email);
			printf("\n___________________");
			printf("\n");
		}
		fclose(arq);
	}
	system("pause");
	system("cls");
}

void alterar()
{
	FILE *arq;
	Contato ctt;
	int pos,op;
	arq = fopen("Agenda2.bin","rb+");
	if(arq == NULL)
	{
		printf("erro \n");
	}
	else
	{
			system("cls");
			printf("+++++++Alteracao pelo NOME+++++++\n");
			printf("Alterar dados no nome: ");
			fflush(stdin);
			gets(ctt.nome);
			while(stricmp(ctt.nome, "\0") !=0)
			{
				pos = busca(arq,ctt.nome);//busca se este nome ja esta registrado
				if(pos == -1)
				{
					printf("Nenhum registro encontrado \n");
				}
				else//caso sim
				{
					fseek(arq,pos,0);//posiciona o ponteiro na posição binaria retornadada
					fread(&ctt,sizeof(Contato),1,arq);//le o registro
					printf("\n Nome: %s", ctt.nome);
					printf("\n Telefone: %s", ctt.fone);
					printf("\n Aniversario: %d/%d/%d", ctt.aniv.d,ctt.aniv.m,ctt.aniv.a);
					printf("\n E-mail: %s", ctt.email);
					printf("\n___________________");
					printf("\n");
					printf("\n Deseja alterar: \n1 - Fone \n2 - E-mail \n3 Aniversario: \n");
					scanf("%d",&op);
					switch(op)
					{
						case 1:
							printf("Novo telefone: \n");fflush(stdin);
							gets(ctt.fone);//informamos o novo telefone para o registro
							
							fseek(arq,pos,0);//posicionamos o ponteiro na posição binaria retornada
							
							fwrite(&ctt,sizeof(Contato),1,arq);//sobescrevemos o registro
							printf("Registro atualizado! \n");
							system("cls");
							system("pause");
							break;
							
						case 2:
							printf("Novo Email: \n");fflush(stdin);
							gets(ctt.email);
							fseek(arq,pos,0);
							fwrite(&ctt,sizeof(Contato),1,arq);
							printf("Registro atualizado! \n");
							system("cls");
							system("pause");
							break;
							
						case 3:
							printf("\n NOVA Data (dd mm aaaa): ");
			    			scanf("%d%d%d",&ctt.aniv.d,&ctt.aniv.m,&ctt.aniv.a);
							fseek(arq,pos,0);
							fwrite(&ctt,sizeof(Contato),1,arq);
							printf("Registro Atualizado!\n");
							system("cls");
							system("pause");
							break;
							
					}
					
				}
				getch();
				printf("Alterar dados no nome: ");
				fflush(stdin);
				gets(ctt.nome);
			}
	}
}

void excluir ()
{
	FILE *arq;
	Contato ctt;
	int pos;
	char nome[30];
	arq = fopen("Agenda2.bin","rb");
	if(arq == NULL)
	{
		printf("erro \n");
	}
	else
	{
		printf("Exclusao de contato \n");
		printf("Digite o nome do contato a ser excluido \n");fflush(stdin);
		gets(nome);
		if(stricmp(nome, "\0")!=0)
		{
			pos = busca(arq,nome);
			if(pos == -1)
			{
				printf("contato nao encontrado ");
			}
			else
			{
				fseek(arq,pos,0);
				fread(&ctt,sizeof(Contato),1,arq);
				printf("\n Nome: %s", ctt.nome);
				printf("\n Telefone: %s", ctt.fone);
				printf("\n Aniversario: %d/%d/%d", ctt.aniv.d,ctt.aniv.m,ctt.aniv.a);
				printf("\n E-mail: %s", ctt.email);
				printf("\n___________________");
				printf("\n");
				printf("Deseja excluir? S-N \n");
				if(toupper(getche())=='S')
				{
					FILE *aux;//criamos uma variavel auxiliar para guardar as informações do arquivo original
					aux = fopen("aux.bin","wb");
					rewind(arq);//posicionamos o ponteiro no inicio do arquivo original
					fread(&ctt,sizeof(Contato),1,arq);// lemos o arquivo original
					while(!feof(arq))
					{
						if(strcmp(nome,ctt.nome)!=0)
						{
							fwrite(&ctt,sizeof(Contato),1,aux);//escrevemos no auxiliar
						}
						fread(&ctt,sizeof(Contato),1,arq);//lemos o original
					}
					fclose(arq);
					fclose(aux);
					remove("Agenda2.bin");//excluimos o original
					rename("aux.bin","Agenda2.bin");//renomeamos o auxiliar com o nome do original
					//assim removemos o seguinte registro do arquivo original
				}
			}
		}
	}
	fclose(arq);
	getch();
}

int busca(FILE *arq, char nome[])
{
	Contato ctt;
	rewind(arq);
	fread(&ctt,sizeof(Contato),1,arq);//le
	while(!feof(arq) && stricmp(nome,ctt.nome)!=0)// se nao for final do arquivo ou se os nomes não forem iguais
	{
		fread(&ctt,sizeof(Contato),1,arq);// em quanto as condições do while forem true, ele le 
	}
	if(!feof(arq))// caso não seja retornado um feof(não achou) ele retorna a posição binaria do registro (achou)
	{
		return(ftell(arq) - sizeof(Contato));// retorna a posição binaria
	}
	else
	{
		return -1;// retorna negativo pq n achou
	}
}
/*
	Como funciona o Bubble Sort
	Comparação de pares adjacentes:

	O algoritmo percorre a lista do início ao fim, comparando dois elementos consecutivos.
	Se o primeiro elemento for maior que o segundo (ou não estiver na ordem desejada), eles são trocados.
	Repetição das passadas:

	Após cada passada completa, o maior elemento "flutua" para o final da lista, como uma bolha subindo na água (daí o nome "Bubble Sort").
	Redução da área de varredura:

	A cada nova iteração, o algoritmo ignora os elementos já ordenados no final da lista.
	Condição de parada:

	O algoritmo para quando nenhuma troca é feita durante uma passada, indicando que a lista está ordenada.

*/
void bolha()
{
	Contato ctt, ctt1;
	FILE *arq;
	int i,qntd=0;
	arq = fopen("agenda2.bin","rb+");
	if(arq == NULL)
	{
		printf("Erro \n");
	}
	else
	{
		fseek(arq,0,2);
		qntd = ftell(arq) / sizeof(Contato);//descobrimos a quantidade de registros
		while(qntd > 1)
		{
			for(i=0; i<qntd- 1 ; i++)
			{
				fseek(arq,i*sizeof(Contato),0);//posiciona o ponteiro no i-ésimo registro
				fread(&ctt,sizeof(Contato),1,arq);//le o registro do ponteiro atual
				fseek(arq,(i+1)*sizeof(Contato),0);
				fread(&ctt1,sizeof(Contato),1,arq);
				if(stricmp(ctt.nome, ctt1.nome)>0)//compara duas strings para saber qual é a maior
				{
					//se o registro atual for maior que o proximo ocorre a troca
					fseek(arq,i*sizeof(Contato),0);
					fwrite(&ctt1,sizeof(Contato),1,arq);
					fseek(arq,(i+1)*sizeof(Contato),0);
					fwrite(&ctt,sizeof(Contato),1,arq);
				}
			}
			qntd--;
		}
		
		
	}
	fclose(arq);
	printf("arquivo ordenado \n");
	system("pause");
}
main(){
	
	int opcao;
	do{
		opcao=menu();
		switch (opcao){
			case 1: inserir();
				break;
			case 2: exibir();
				break;
			case 3: alterar();
				system("pause");
				break;	
			case 4: excluir();
				break;
		   	case 5: bolha();
				break;		
			case 6: printf("Obrigada! Saindo...");
				break;
			default: printf("Opcao invalida!");
				break;
		}		
	}while(opcao!=6);
}
