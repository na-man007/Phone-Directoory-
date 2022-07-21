#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
using namespace std;

const int ALPHABET_SIZE = 26; // all a to z characters

struct TrieNode
{
  // Trie is a GRAPH which stores characters
  // an "Array of pointers" to point to other "Trie" nodes
    struct TrieNode *children[ALPHABET_SIZE];

  // If a word ends at a node it is true
    bool is_complete_word;
};


// "get node()" creates a new node and sets the array of pointers to NULL
// and returns a pointer to the newly created node
struct TrieNode *createNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->is_complete_word = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// globally declared root node
struct TrieNode *root = createNode();

// To insert a name string into trie
void insert(string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = createNode();

        pCrawl = pCrawl->children[index];
    }

    // The end of the string entered by user
    pCrawl->is_complete_word = true;
}



// shows the list of all names starting with some PREFIX
void display_contacts_with_prefix(TrieNode *curNode, string prefix)
{
  if (curNode->is_complete_word) // FULL word found
    cout << prefix << endl;

  for (char i = 'a'; i <= 'z'; i++)
  {
    TrieNode *nextNode = curNode->children[i-'a'];
    if (nextNode != NULL)
      display_contacts_with_prefix(nextNode, prefix + (char)i); // recursive call
  }
}





void displayContacts(string str)
{
  TrieNode *prevNode = root; // start from root of trie

  string prefix = "";
  int len = str.length();

  int i;
  for (i=0; i<len; i++)
  {
   cout<<"\n";
    prefix += (char)str[i]; // starts searching from first char of name

    char lastChar = prefix[i]; // rightmost char of prefix

    TrieNode *curNode = prevNode->children[lastChar-'a']; // if it is pointing somewhere

    if (curNode == NULL) // break
    {
      cout << "No Results Found for " << prefix<<"\n";
      i++;
      break;
    }

    cout << "Suggestions based on \"" << prefix
      << "\" are \n";
    display_contacts_with_prefix(curNode, prefix); // displays suggestions for every prefix until
    // the word is found


    prevNode = curNode;
  }


  for (; i<len; i++)
  {
    prefix += (char)str[i];
    cout << "No Results Found for " << prefix<<"\n";
  }
}



// To erase the word from the trie
void delete_number(string str){
  TrieNode *prevNode = root;

  string prefix = "";
  int len = str.length();

  int i;
  // traverse to find the end of word
  for (i=0; i<len; i++)
  {
    prefix += (char)str[i];

    char lastChar = prefix[i];

    TrieNode *curNode = prevNode->children[lastChar-'a'];

    if(i==len-1 and curNode->is_complete_word){
      curNode->is_complete_word=false;// erase the mark which says "End of word"
      curNode=NULL;
      cout<<"Contact is deleted successfully!\n";
      return;
    }

    prevNode = curNode;
  }

}




//Main function that drives the program
int main()
{
  // #ifndef ONLINE_JUDGE
  // freopen ("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  // #endif
  int response=0;
  //  Vector(similar to array) which can store a "Pair of strings" like {name,number}
  vector<pair<string,string>> contacts;


  // Some contacts preinserted

  contacts.push_back({"abcdef","1223455"});insert("abcdef");
  contacts.push_back({"nikhil","1233655"});insert("nikhil");
  contacts.push_back({"ramesh","2224556"});insert("ramesh");




  // Program runs till 6 is not chosen
  while(response!=6){

  printf("\nEnter the action to perform :\n1.Add Contacts\n2.Display Contact\n3.Search Contact\n");
  printf("4.Delete Contact\n5.Edit Contact\n6.Exit\n\n");
  fflush(stdin);
  cin>>response;
  cout<<"response taken";

  // switch case statements for respective responses
  switch(response){
    case 1: {
      string name,number;
      cout<<"Enter NAME :\n";
      cin>>name;
      cout<<"Enter PHONE NUMBER :\n";
      cin>>number;
      contacts.push_back({name,number});
      insert(name);
      cout<<endl<<"contact added successfully.\n Press 1 to proceed further";
      getch();
      break;
    }
    case 2: {
      cout<<"Below is the full list of "<< contacts.size()<<" contacts available :\n";
      for(int i=0;i<contacts.size();i++){
        // Print the pair of strings we have stored until now
        cout<<contacts[i].first<<"   "<<contacts[i].second<<endl;
      }
      cout<<endl<<"enter 1 to proceed further";
      getch();
      break;
    }
    case 3:{
      string query;
       cout<<"Enter a query to search:\n";
       cin>>query;
       displayContacts(query);
       cout<<"enter 1 to proceed further";
       getch();
       break;
    }
    case 4:{
      string name_to_be_deleted;
      cout<<"Enter the name of the contact to be deleted:\n";
      cin>>name_to_be_deleted;
      for(int i=0;i<contacts.size();i++){
        if(contacts[i].first==name_to_be_deleted){
          contacts.erase(contacts.begin() + i);
          break;
        }
      }
      delete_number(name_to_be_deleted);
      cout<<"contact deleted successfully"<<endl;
      cout<<"enter 1 to proceed further";
      break;
    }
    case 5: {
      string name_to_be_edited;
      cout<<"Enter the name of the contact to be edited:\n";
      cin>>name_to_be_edited;
      cout<<"Enter the new Phone Number:\n";
      int new_number;
      cin>>new_number;
      for(int i=0;i<contacts.size();i++){
        if(contacts[i].first==name_to_be_edited){
          contacts[i].second=new_number;break;
        }
      }
      cout<<"Edit successful!\n";
      cout<<"enter 1 to proceed";
      getch();
      break;
    }
    case 6:{
      cout<<"Goodbye!\n";
       break;
    }
    default : break;
  }
  system("CLS");
  //cout<<"screen cleared";
 }

  return 0;
}


