#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NAMELEN 50


// struct to store info of customer 
typedef struct _account

{
  int acc_no;
  char name[NAMELEN+1];
  float balance;
  float amount;
  char transaction[10];
  struct _account *next;
}account;



account *start = NULL;


// struct node created for binary search tree
struct node
{
    int data; 
    
    struct node *rchild; 
    
    struct node *lchild;
};

struct node *st = NULL;

// struct node for inserting binary search data
struct node* nnode(int x)
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->data = x;
    p->lchild = NULL;
    p->rchild = NULL;

    return p;
}

// struct node for inserting the node in the tree in right position
struct node* insert(struct node *root, int x)
{
   
	    if(root==NULL)
	    
	        return nnode(x);
	        
	    else if(x>root->data) 
	    
	        root->rchild = insert(root->rchild, x);
	        
	    else 
	    
	        root->lchild = insert(root->lchild,x);
	        
	    return root;
}

// method for printing the tree inorder 
void inOrder(struct node *root)
{
    if(root!=NULL) 
    {
        inOrder(root->lchild);
        
        printf("%d-", root->data); 
        
        inOrder(root->rchild);
    }
}

//method for printing the tree in pre order
void preOrder(struct node *root)
{
	if (root != NULL)
	{
		printf("%d-", root->data);
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
}

//method for printing the tree in post order
void postOrder(struct node *root)
{
	if (root != NULL)
	{
		postOrder(root->lchild);
		postOrder(root->rchild);
		printf("%d-", root->data);
	}
}




// creating a new account's memory allocation and returning the node created for inserting data
  account *createNewAccount()
	  {
	  	account *nn = ( account*)malloc(sizeof(account));
	  	nn -> next = NULL;
	  	return nn;
	  }
	  // method for checking if the linked list is empty or not
	   int isEmpty()
	 {
	 	return start == NULL;
	 }
	 
	 // fucntion to write the account created in the accountinfo.txt file
	 // this function uses fwrite to write the structure directly to txt file 
	 //this way we cannot read the txt file from outside, only by running our function to read, would be able to read the account info
	 void WriteListToFile() {
	FILE *pFile;
	pFile = fopen("Accountsinfo.txt", "w");
	
	if(pFile != NULL) {
		account *currentAccount = createNewAccount();
		currentAccount = start;
	
		account *holdNext = NULL;

		while(currentAccount) {
			holdNext = currentAccount->next;
			
			currentAccount->next = NULL;
			
			
			fseek(pFile, 0, SEEK_END);
		
			fwrite(currentAccount, sizeof(account),1 , pFile);
		
			printf("Writing Account Number  : %d to secure database \n",currentAccount->acc_no);
		
			currentAccount->next = holdNext;
		
			
			holdNext = NULL;
			
			currentAccount = currentAccount->next;
		}
		fclose(pFile);
		pFile = NULL;
	} else {
		printf("FILE OPEN ERROR\n");
	}
	
}

// function to read the accounts info(struct) from the text file one by one as a struct
account *ReadNextFromFile(account *str, FILE *pFile) {
	
	size_t returnValue;
	if(str == NULL) {
		str = createNewAccount();
		returnValue = fread(str, sizeof(account), 1, pFile);
		str->next = NULL;
	
	} else {
		account *indexAccount = str;
		account *newAccount = createNewAccount();
		while(indexAccount->next != NULL) {
			indexAccount = indexAccount->next;
		}
		returnValue = fread(newAccount, sizeof(account), 1, pFile);
		indexAccount->next = newAccount;
		newAccount->next = NULL;
	
	}
	return str;
}

// function to read the account info and using method readnextfromfile to read the structs one by one
void ReadListIn() {
	
	FILE *pFile;
     account *str = start;
	pFile = fopen("Accountsinfo.txt", "r+");
	if(pFile != NULL) {
	  
		CleanUp(str);
		str = NULL;
		
		fseek(pFile, 0, SEEK_END);
		long fileSize = ftell(pFile);
		rewind(pFile);
		
		int numEntries = (int)(fileSize / (sizeof(account)));
		printf("Number of Accounts :%d\n",numEntries);
		
		int loop = 0;
			
		for(loop = 0; loop < numEntries; ++loop) {

			fseek(pFile, (sizeof(account) * loop), SEEK_SET);
			str = ReadNextFromFile(str,pFile);
		}
		start = str;
	
	 fclose(pFile);					
	}  else {
		printf("FILE OPEN ERROR FOR READ\n");
	}
				


}

//  function cleanup to ensure list is empty when getting the data 
void CleanUp(account *str) {
	
	account *freeMe = str;
	account *holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = freeMe->next;
	
		free(freeMe);
		freeMe = holdMe;
	}	
}


// delete Account method for deleting the account from the list
	deleteAccount()
	{
		
		
                        if(isEmpty(start))
						{
							printf("Nothing to delete..");
							return 0;
						}		
		                int id=0;
		                int ctr=1;
		                
		                
		                printf("\n Enter the account number to delete : ");
			            scanf("%d", &id);
			            
					 	account *temp, *next;
						account *del, *prev;
						temp = start;
						while(temp) 
						{
							if(temp->acc_no == id)
							{
								break;
							}
							else
							{
							temp = temp -> next;
							ctr++;
						}
						}
						
				        
						 if(ctr ==1)  
				        {
				        
				        	del = start;
							start = start -> next;
							free(del);
							printf("Account Deleted......");
							WriteListToFile();
							return 0;
				       
						}
						
						if(temp->next == NULL)
						{
						  printf("Account Deleted......");	
						  deleteFromLast();  
						  return 0;
						  	
						}
						else
						{
						
					    next = temp->next->next;
					    del = temp->next;
					    free(del);
					    temp->next = next;
					    printf("Account Deleted......");
					    WriteListToFile();
					   
					}
					}
					
		// if the account is last in the list, it will go to deletefromlast function			
	deleteFromLast()
		{
			if(isEmpty(start))
			{
				printf("Nothing to delete..");
				return 0;
			}
			
			else
			{
				 account* del;
				 account *t;
				 account *prev;
				
				prev = start;
				
				t = start-> next;
				
				while(t -> next)
				{
					t= t->next;
					prev = prev -> next; 
					
				}
				del = t;	
				prev -> next= NULL;
				free(del);
				WriteListToFile();
				
	       	}
	}   
					   
// method to insert Account into the linked list
	int insertFirst()
	{
					 int flag;
		             account *newAccount = createNewAccount();
		             account *t = start;
				     int accountNumber;
				     float balance;
				     srand(time(0));
				     char name[NAMELEN+1];
				  
				    	do {
					 
			   printf("Enter the name of the Accountee :  ");
				  					 	
				   scanf("%s", name);
					  if ( (name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a' && name[0] <= 'z') ) {
					      flag = 1;
					  }
					  else {
					      printf("\tInvalid Format\n");
					  }
					  
					  			  
					  
					} while (flag == 0);
					
				  	strcpy(newAccount->name,name);
				     
				     flag=0;
				     do
				     {
				     fflush(stdin);	
				     printf("How much money you want to deposit to the new account : ");
				     if(scanf("%f", &balance)==1)
				     {
				     	flag=1;
					 }
					 else
					 {
					 	printf("\nWrong input.. Enter a valid number!\n");
					 }
				}while(flag==0);
				     
				     
				     newAccount->balance = balance;
				     newAccount->acc_no = rand() % 100 +1;
					 newAccount->amount = 0;
					 strcpy(newAccount->transaction,"");	  
				     
				     while(t)
						{	
						if(t->acc_no == newAccount->acc_no)
						{
						  newAccount->acc_no = rand() % 100 +1;
					
					  	}
					  	else
					  	{
					  		
					  		t= t->next;	
						   
						}
				 }
			
					if(isEmpty(start))
					{
							start= newAccount;
							
				
					}
					else{
				
					newAccount -> next = start;
					 start = newAccount;
			
				}
					printf("\n Account added successfully!\n Account Details : \n");
					 printf("\n Accountee Name : %s \n Account Number : %d \n Balance : %.2f $ \n ------------------ \n", newAccount->name, newAccount->acc_no, newAccount->balance);
				 		 
				 WriteListToFile();
					return 0;	
	}
	
	
	
	// method to search the Account and displaying the account info 
	account * Search(int accNumber)
	{
		  if(isEmpty(start))
	       {
	       	printf(" List is empty");
	       	return 0;
		   }
		   else{
		    
		    QSort(&start); 
		    account *temp = createNewAccount();
		    
		    
		    account *t;	
			t=start;
			while(t)
			{	
			if(t->acc_no == accNumber)
			{
			    return t;
		  	}
		  	else
		  	{
		  		t= t->next;
			}
	}
		t = NULL;
		return t;
}
}
	
	// method to initiate a transaction by giving option to the user to withdraw or deposit
	int transaction ()
	
	{
		int accNumber;
		float amount;
		float withdrawCheck;
		char ch;
		int flag=0;
		account *acc = createNewAccount();
		printf("Enter your account number:");
		scanf("%d", &accNumber);
		acc = Search(accNumber);
		fflush(stdin);
		
		 if(acc != NULL)
		{
			  	   	
     	printf("Do you want to Withdraw or Deposit ? Enter W/D : ");
		scanf("%c", &ch);
		
		
	   if(ch == 'd' || ch == 'D')
	   {
	   	do{
		  fflush(stdin); 
	   	  printf("Enter the amount to deposit : ");
		  if(scanf("%f", &amount)==1)
		  {
		     flag=1;	
		  }
		  else
		  {
		  	printf("\nWrong Input\n");
		  }
		}  while(flag==0);
		   acc->amount = amount;
		   acc->balance += amount;
		
		   strcpy(acc->transaction,"Deposit");
		   printf("Amount deposited successfully\n");
		   return 0;
	   }
	   
	   else if(ch == 'w' || ch == 'W')
	   {
	   	flag=0;
	   	 	do{
		  fflush(stdin); 
	   	  printf("Enter the amount to Withdraw : ");
		  if(scanf("%f", &amount)==1)
		  {
		     flag=1;	
		  }
		  else
		  {
		  	printf("\nWrong Input\n");
		  }
		}  while(flag==0);
	   
		
		   acc->amount = amount;
		   withdrawCheck = acc->balance;
		   withdrawCheck -= amount;
		    if(withdrawCheck < 0)
		    {
		    	printf("\n Sorry, not enough balance in account to withdraw that amount... \n");
		    	return 0;
			}
		   else
		   {
			   	
		   acc->balance -= amount;
		   strcpy(acc->transaction,"Withdraw");
		   printf("Amount withdrawn successfully \n");
		    WriteListToFile();
		   return 0;
	      }
	   }
	   
	   else
	   {
	   	printf("Please enter a valid input");
	   	return 0;
	   }
	
			     
	 }
	 else
	 {
	 	printf("\nAccount not found !");
	 	return 0;
	 }
		
	
}

// In this method ( Search method return a node containing the the
// account info of the account searched by the account number) 
//then we display the results here in this method
int accountdisplay(){
	
	account *t ;
	
	int a;
	
	printf("Please Input Account Number: ");
	
	scanf("%d",&a);
	
	t = Search(a);

	if(t != NULL){
	
 	printf("\n Account Name : %s \n Account Number : %d \n Balance : %.2f \n Most Recent Transaction : %s of %.2f  $ \n ------------------ \n", t->name, t->acc_no, t->balance, t->transaction, t->amount);
		return 0;
	}
	else{
		printf("NO Account Number Associated ");
		return 0;
	}
} 
   
// method to modify the specific account ( the name of the accountee)   
void modifiycustomeraccount(){
	
	account *t ;
	
	int a;
	int flag;	
	
	char name[NAMELEN+1];
	
	printf("Please Input Account Number To Modify : ");
	
	scanf("%d",&a);
	
	t = Search(a);
	
	if(t != NULL)
	{


	   	do {
		 
		printf("Please Input New Name: ");
				  					 	
		scanf("%s",name);
	    if ( (name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a' && name[0] <= 'z') ) {
	    flag = 1;
	}
	   else {
	    printf("\tInvalid Format\n");
	}
		} while (flag == 0);
					
	strcpy(t->name,name);
	
	printf("Name successfully updated.. ");
	 WriteListToFile();
	return 0;
	
}
else 
    {
        printf("Sorry, No account found for the entered account number.. ");
		return 0;	
	}
}

 
   
    // method to display all the accounts
  	void displayAccounts()
	{
	      
	       if(isEmpty(&start))
	       {
	       	printf("\n No Account found");
		   }
		   else{
		   	
		   	QSort(&start); 
		   	
		    account *t;	
		    
			t=start;
		
			
				while(t != NULL)
			{	
			     printf("\n Account Name : %s \n Account Number : %d \n Balance : %.2f \n Most Recent Transaction : %s of %.2f  $ \n ------------------ \n", t->name, t->acc_no, t->balance, t->transaction, t->amount);
			    t= t->next;	
			    
			
		  	}
		  	printf("\n");
	}
}

// method for creating binary search tree
void BinarySearchTree(){
	
		      if(isEmpty(&start))
			       {
			       	printf("\n No Account found");
				   }
				   else{	  
				    account *t;	
					t=start;
					st = nnode(t->acc_no);
					t = t->next;
				     while(t != NULL)
					{	
					    insert(st,t->acc_no);
					    t= t->next;		
				  	}
				  	
				  	printf("\n Binary Search Tree \n");
				  					  	  
				  	  printf("\nInOrder Prints: \n");	
				  	  inOrder(st);
				  	  
				  	    printf("\nPreOrder Prints:\n");	
				  	  preOrder(st);
				  	  
				  	    printf("\nPostOrder Prints:\n");		
				  	  postOrder(st);
				  	  
		  			  printf("\n");	
				  }
				  
}    



// main method for the menu
int main()
{
	printf("\n--------------------------------------------RBC Bank----------------------------------\n\n\n");
		ReadListIn();
	 char ch;
		do{
			fflush(stdin);
			printf("\n=================================\n");
			printf("a. Add a new Account  \n");
			printf("w. Withdraw/Deposit\n");
			printf("s. Search Customer \n");
			printf("p. Display Accounts \n");
			printf("m. Modify Account \n");	
			printf("d. Delete Account \n");	
			printf("r. BST Display \n");	
			printf("q. Quit \n\n");
		    printf("=================================\n");
			printf("Enter your Choice :");
			scanf("%c", &ch);
			
		
			 
			switch(ch)
			{
				case 'a':
				insertFirst();
				break;
				
				case 'w':
			    transaction();
				break;
				
				case 's':
				accountdisplay();
				break;
				
				case 'm':
				modifiycustomeraccount();
				break;
				
				case 'p':
			  
			   	displayAccounts();	
				break;
				
				case 'd':
				deleteAccount();
				break;
				
				case 'r':
		 		BinarySearchTree();
				break;	
				
			    case 'q':
			    printf("Bye!");
			    break;
					
				
			}
			
			
		}while(ch!='q');
		
	
	
		return 0;	
}


// method for getting the last account in the list for quicksorting
account *getLast(account *current) 
{ 

    while (current != NULL && current->next != NULL) 

    current = current->next; 
 
    return current; 
} 
  
// split method for creating a pivot 
account *split(account *top, account *bottom, account **newTop, account **newBottom) 
{ 
    account *pivot = bottom; 
    account *prev = NULL, *cur = top, *tail = pivot; 
  
   
    while (cur != pivot) 
    { 
        if (cur->acc_no < pivot->acc_no) 
        { 
          
            if ((*newTop) == NULL) 
                (*newTop) = cur; 
  
            prev = cur;   
            cur = cur->next; 
        } 
        else 
        { 
          
            if (prev) 
                
			prev->next = cur->next; 
            account *tmp = cur->next; 
            cur->next = NULL; 
            tail->next = cur; 
            tail = cur; 
            cur = tmp; 
            
        } 
    } 
  
   
    if ((*newTop) == NULL) 
    
        (*newTop) = pivot; 
  
   
    (*newBottom) = tail; 
  
  
    return pivot; 
} 
  
  
// Recursive method for returning the new top node 
account *RecursiveQuickSort(account *top, account *bottom) 
{ 

    if (!top || top == bottom) 
        return top; 
  
    account *newTop = NULL, *newBottom = NULL; 
  

    account *pivot = split(top, bottom, &newTop, &newBottom); 
  

    if (newTop != pivot) 
    { 
    
        account *tmp = newTop; 
        
        while (tmp->next != pivot) 
        
		tmp = tmp->next; 
        
		tmp->next = NULL; 
  
       
        newTop = RecursiveQuickSort(newTop, tmp); 
  
        tmp = getLast(newTop); 
        
        tmp->next =  pivot; 
    } 
  
   
    pivot->next = RecursiveQuickSort(pivot->next, newBottom); 
  
    return newTop; 
} 
  
// method for initiating the quick sort by giving the start and the last node in the list
void QSort() 
{ 
    start = RecursiveQuickSort(start, getLast(start)); 
    return; 
} 



