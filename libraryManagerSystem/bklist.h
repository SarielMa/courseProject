
#define data_file "data"
 struct bk_node 
{
	char id[16];
	char name[32];
	char author[16];
	char date[16];
	float price;
	struct bk_node *next;

};
typedef struct bk_node* pr;
typedef struct mem
{
	char name[20];
	int num;
	char telephone[20];
	struct mem *next;

} nod;


pr cleanlist(pr list);
pr createlist(void);
pr createnode(void);
void savelist(pr list);
pr insertnode(pr list,pr node);
pr deletenode(pr list,pr node);
pr querynode(pr list,char *id);
void printnode(pr node);
void printlist(pr list);
void mem(nod *head);
void list(nod *head);
void codef(void);



