#include<bits/stdc++.h>
using namespace std;

class direct // class to store the details of the people in register
{
    string name;
    long long tel;
    int id;

    public:
    direct()
    {
        tel=0;
        id=0;
    }
    friend class TrieNode;
    friend class hashing; // friend class to access private and protected members of other class
};

class TrieNode // the unordered map to store the names using trienode concept
{
    unordered_map<char,TrieNode*> child;
    bool isLast;

    public:
    TrieNode()
    {
        for (char i = 'A'; i <= 'Z'; i++)
		child[i] = NULL;

        isLast=false;
    }
    friend class hashing;
};

class hashing
{
    direct arr[100]; // maximum size of the directory is 100
    string n;
    long long t;
    int i, index;
    public:
    hashing()
    {
        i=0;
        t=0;
    }

    void create(int size) // takes user details as input from user and saves the record in the hashtable
    {
        cout<<"\nEnter ID: ";
        cin>>i;
        cout<<"\nEnter name: ";
        cin>>n;
        cout<<"\nEnter telephone number: ";
        cin>>t;
        index = i % size;
        for(int j=0; j<size; j++)
        {
            if(arr[index].id==0)
            {
                transform(n.begin(), n.end(), n.begin(), ::toupper);
                arr[index].id=i;
                arr[index].name=n;
                arr[index].tel=t;
                break;
            }
            else
            {
                index = (index + 1) % size;
            }

        }
    }

    void search_id(int size) // searches a particular contact on the basis of the id entered by the user
    {
        int index1, i, f=0;
        cout<<"\nEnter the id to be searched: ";
        cin>>i;
        index1=i % size;
        for(int k=0; k<size; k++)
        {
            if(arr[index1].id==i)
            {
                cout<<"\nRecord found \n";
                cout<<"Name: "<<arr[index1].name;
                cout<<"\nID: "<<arr[index1].id;
                cout<<"\nContact number: "<<arr[index1].tel;
                f=1;
                break;
            }
            else
            index1 = (index1+1)%size;
        }
        if(f==0)
        cout<<"Record not found\n";
    }


    void delete_rec(int size) // deletes the record whose id is entered by the user
    {
        int index1, i, f=0;
        cout<<"\nEnter the id of the record to be deleted: ";
        cin>>i;
        index1=i%size;
        for(int k=0; k<size; k++)
        {
            if(arr[index1].id==i)
            {
                cout<<"\nRecord found and deleted successfully\n";
                arr[index1].name=" ";
                arr[index1].id=0;
                arr[index1].tel=0;
                f=1;
                break;
            }
            else
            index1 = (index1+1)%size;
        }
        if(f==0)
        cout<<"\nRecord not found.";
    }

    void update_rec(int size) // updates the record of the person whose id is entered by the user
    {
        int index1, i, f=0;
        cout<<"\nEnter the id of the record that needs to be updated: ";
        cin>>i;
        index1=i%size;
        for(int k=0; k<size; k++)
        {
            if(arr[index1].id==i)
            {
                f=1;
                break;
            }
            else
            {
                index1 = (index1+1)%size;
            }
        }
        if(f==1)
        {
            cout<<"\nEnter name to be updated: ";
            cin>>n;
            cout<<"\nEnter telephone number: ";
            cin>>t;
            arr[index1].name=n;
            arr[index1].tel=t;
            cout<<"\nDetails updated";
        }
        else
        {
            cout<<"\nRecord not found";
        }

    }

    void display_rec(int size) // displays the social register
    {
        cout<<"\n\tID \tNAME \t\tCONTACT NUMBER";
        for(int k=0; k<size; k++)
        {
            if(arr[k].id!=0)
            {
                cout<<"\n\t"<<arr[k].id<<"\t"<<arr[k].name<<"\t\t"<<arr[k].tel;
            }
        }
    }

    TrieNode *root = NULL;//initializing the root node here so that it doesn't have to be passed to all functions

    void insertIntoTrie(int n)//inserts all contacts into the trie
    {
        root = new TrieNode();
        for(int i=0; i<n; i++)
        {
            transform(arr[i].name.begin(), arr[i].name.end(), arr[i].name.begin(), ::toupper);
            insert_name(arr[i].name);//each contact is inserted into the trie one by one
        }
    }

    void insert_name(string s)//inserts a contact name in trie
    {
        int l=s.length();
        TrieNode *itr = root;//itr iterates through the trie nodes
        for(int i=0; i<l; i++)
        {
            TrieNode *next = itr->child[s[i]];
            if(next==NULL)
            {
                next = new TrieNode();
                itr->child[s[i]]=next;//inserts into the map if next node is not found
            }
            itr=next;
            if(i==(l-1))
                itr->isLast=true;//when the end of string is reached, the last ndoe is marked true
        }
    }

    void display_query(string q)//displays suggestions for every character the user enters in string q
    {
        int i;
        TrieNode *prev = root;
        string prefix = "";
        int l = q.length();
        for( i=0; i<l; i++)
        {
            prefix += (char)q[i];
            char lastchar = prefix[i];
            TrieNode *curNode = prev->child[lastchar];
            if (curNode == NULL)
		    {
			    cout << "\nNo Results Found for "  << prefix << "\n";
			    i++;
			    break;
		    }
            cout << "\nSuggestions based on " << prefix << " are"<< "\n";//if a suggested name is found
            displayContactsUtil(curNode, prefix); //then the contact details are displayed by this function

            prev=curNode;
        }
        for (; i<l; i++)
	    {
		    prefix += (char)q[i];
		    cout << "\nNo Results Found for " << prefix << " are" << "\n";
	    }
    }

    void displayContactsUtil(TrieNode *curNode, string prefix)//displays all the contact details with repect to prefix
    {
        if (curNode->isLast)
		    cout << prefix << endl;

        // Find all the adjacent nodes to the current
        // node and then call the function recursively
        // This is similar to performing DFS on a graph
        for (char i = 'A'; i <= 'Z'; i++)
	    {
		    TrieNode *nextNode = curNode->child[i];
		    if (nextNode != NULL)
			    displayContactsUtil(nextNode, prefix + (char)i);
	    }
    }

};
int main()
{
    //cout << "\033[2J\033[1;1H";
    int size, ch;
    string query;
    hashing h;
    cout<<"Enter size of the Social Register: ";
    cin>>size;
    for(int k=0; k<size; k++)
    {
        h.create(size);
    }
    cout<<"\nEnter 1 to display all the records";
    cout<<"\nEnter 2 to search the record";
    cout<<"\nEnter 3 to delete the record";
    cout<<"\nEnter 4 to update the record";
    cout<<"\nEnter 5 to display all the records according to the string entered by the user";
    cout<<"\nEnter 0 to exit";
    while(true)
    {
        cout<<"\n\nEnter your choice ";
        cin>>ch;
        if(ch==1)
        h.display_rec(size);
        if(ch==2)
        h.search_id(size);
        if(ch==3)
        h.delete_rec(size);
        if(ch==4)
        h.update_rec(size);
        if(ch==5)
        {
            cout<<"\nEnter the query to be searched: ";
            cin>>query;
            transform(query.begin(), query.end(), query.begin(), ::toupper);
            h.insertIntoTrie(size);
            h.display_query(query);
        }
        if(ch==0)
        break;
    }
    return 0;
}
