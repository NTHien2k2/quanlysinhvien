#include<iostream>
#include<string.h>
using namespace std;
struct thongTin {
    string Name;
    string Phone;
    string Email;
};
typedef struct thongTin TT;
typedef struct node1 NODE1;
struct node1 {
    TT data;
    NODE1 *Next;
};
struct list {
    NODE1 *pHead;
    NODE1 *pTail;
};
typedef struct list LIST;
typedef struct node2 NODE2;
struct node2 {
        string DATA;
        NODE2 *left, *right;
    };
typedef NODE2* TREE;
////////////////////////
void createList(LIST &l) {
    l.pHead = NULL;
    l.pTail = NULL;
}
NODE1 *createNode(TT x) {
    NODE1 *p = new NODE1;
    p->data = x;
    p->Next = NULL;
    return p;
}
void insertTail(LIST &l, NODE1 *p) {
    if (l.pHead == NULL) {
        l.pHead = l.pTail = p;
    } else {
        l.pTail->Next = p;
        l.pTail = p;
    }
}
void printList(LIST l) {
    for (NODE1 *k = l.pHead; k != NULL; k = k->Next) {
        cout << k->data.Name << ' ' << 
                k->data.Phone << ' ' <<
                k->data.Email << endl;
    }
}
void sortingList(LIST &l){
    for (NODE1 *k = l.pHead; k != NULL; k = k->Next) {
        for (NODE1 *q = k->Next; q != NULL; q = q->Next){
            if (k->data.Name > q->data.Name) {
                string t;
                t = k->data.Name;
                k->data.Name = q->data.Name;
                q->data.Name = t;
            }
        }
    }
}
void deleteHead(LIST &l) {
    if (l.pHead == NULL) return;
    NODE1 *p = l.pHead;
    l.pHead = l.pHead->Next;
    delete p;
}
void deleteTail(LIST &l) {
    if (l.pHead == NULL) return;
    for (NODE1 *k = l.pHead; k != NULL; k = k->Next) {
        if (k->Next == l.pTail) {
            delete l.pTail;
            k->Next = NULL;
            l.pTail = k;
        }
    }
}
void DeleteNode(LIST &l, string s) {
    if (l.pHead->data.Name == s) {
        deleteHead(l);
        return;
    }
    if (l.pTail->data.Name == s) {
        deleteTail(l);
        return;
    }
    NODE1 *g = new NODE1; 
    for (NODE1 *k = l.pHead; k != NULL; k = k->Next) {
        if (k->data.Name == s) {
           g->Next = k->Next;
           delete k;
        }
        g = k;
    }

}
///////////////////////////////
void CreateTree(TREE &t) {
        t = NULL;
}
void addNodeinTree(TREE &t, string y) {
    if (t == NULL) {
        NODE2 *p1 = new NODE2;
            p1->DATA = y;
            p1->left = NULL;
            p1->right = NULL;
            t = p1;
    } else { 
        if (t->DATA > y){
            addNodeinTree(t->left, y);
        } else {
            if (t->DATA < y) addNodeinTree(t->right, y);
        }
    }
}
void print_VLR(TREE t) {
    if (t != NULL) {
        cout << t->DATA <<' ';
        print_VLR(t->left);
        print_VLR(t->right);
    }
}
void buildTree(TREE &t, string y) {
        addNodeinTree(t, y);
}
void saveTree(TREE t, string v, FILE *f) {
    if (t != NULL) {
        fwrite(&v, sizeof(v), 1, f);
        saveTree(t->left, v, f);
        saveTree(t->right, v, f);
    }
}
void ghifileNP(LIST &l, TREE &namefield, TREE &phonefield, TREE &emailfield) {
	FILE *f = fopen("danhba.bin", "wb");
	if (f == NULL) {
		cout << "KHONG MO DUOC FILE";
		return;
	}
	TT u;
	for (NODE1 *k = l.pHead; k != NULL; k = k->Next) {
		u.Name = k->data.Name;
		u.Phone = k->data.Phone;
		u.Email = k->data.Email;
		fwrite(&u, sizeof(u), 1, f);
	}
	string v;
	saveTree(namefield, v, f);
	saveTree(phonefield, v, f);
	saveTree(emailfield, v, f);
    fclose(f);
}
void Menu(LIST &l, TREE &namefield, TREE &phonefield, TREE &emailfield) {
    while (true) {
        system("cls");
        cout << "\t =============MENU=============" << endl;
        cout << "1. Them lien he" << endl;   
        cout << "2. Xoa lien he" << endl;
        cout << "3. Sua lien he" << endl;
        cout << "4. Xuat danh ba" << endl;
        cout << "5. Xuat cay nhi phan" << endl;
        cout << "0. Ket thuc." << endl;
        cout << "\t ==============================";
        int luachon;
        cout <<"\nNhap lua chon: ";
        cin >> luachon;
            if (luachon < 0 || luachon > 5) {
                cout << "Lua chon khong hop le!" << endl;
                system("pause");
            } else 
            if (luachon == 1) {
                TT x;
                cout << "Name: ";
                cin >> x.Name;
                cout << endl << "Phone: ";
                cin >> x.Phone;
                cout << endl << "Email: ";
                cin >> x.Email;
                NODE1 *p = createNode(x);
                insertTail(l, p);
            } else if (luachon == 2) {
                cout << "Nhap ten can xoa: ";
                string s1;
                cin >> s1;
                DeleteNode(l, s1);
            }else if (luachon == 3) {
                cout << "Nhap ten can sua: ";
                string s2;
                cin >> s2;
                for (NODE1 *k = l.pHead; k != NULL; k = k->Next){
                    if (k->data.Name == s2) {
                        cout << "Name: ";
                        cin >> k->data.Name;
                        cout << endl << "Phone: ";
                        cin >> k->data.Phone;
                        cout << endl << "Email: ";
                        cin >> k->data.Email;
                    }
                }
            } else if (luachon == 4) {
                sortingList(l);
                printList(l);
                system("pause");
            } else if (luachon == 5) {
                for (NODE1* k = l.pHead; k != NULL; k = k->Next) {
                    buildTree(namefield, k->data.Name);
                    buildTree(phonefield, k->data.Phone);
                    buildTree(emailfield, k->data.Email);   
                }
                print_VLR(namefield);cout << endl;
                print_VLR(phonefield);cout << endl;
                print_VLR(emailfield); cout << endl;
                system("pause");
            } else if (luachon == 0) {
                    sortingList(l);
                    ghifileNP(l, namefield, phonefield, emailfield);
                    break;
                }

        }
}
int main() {
    LIST l;
    TREE namefield;
    TREE phonefield;
    TREE emailfield;	
    CreateTree(namefield);
    CreateTree(phonefield);
    CreateTree(emailfield);
    createList(l);
    Menu(l, namefield, phonefield, emailfield);
    system("pause");
    return 0;
}