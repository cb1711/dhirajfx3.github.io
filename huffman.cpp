#include<bits/stdc++.h>
using namespace std ;
#define pb push_back
#define mp make_pair
#define ll long long int
#define vi vector<ll>
#define vvi vector<vi>
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define _intt int t=0;cin>>t;while(t--)
#define pb push_back
#define pii pair<int,int>
#define mod 1000000007
#define mp make_pair
#define fir first
#define sec second
#define testing int t=0;cin>>t;while(t)


bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.sec < b.sec);
}

bool isitPrime(ll n)
{
    ll j=0;
    for(j=2;j*j<=n;j++) if(n%j==0) break;
    if(j*j>n) return true;
    else return false;
}
ll gcd(ll a, ll b)
{
  ll c = a % b;
  while(c != 0){a = b;b = c;c = a % b;}
  return b;
}
ll Com(ll n, ll k)
{
    if (k > n) return 0;
    ll r = 1;
    for (ll d = 1; d <= k; ++d) {r *= n--;r /= d;}
    return r;
}

long long modexpo(long long a,long long b,int n)
{
    long long d=1;
    while(b)
    {
        if(b%2)
        {
            d=(d*a)%n;
        }
        b>>=1;
        a=(a*a)%n;
    }
    return d;
}

ll maxi(ll x,ll y)
{
    if(x>y) return x;
    else return y;
}
struct MinHeapNode
{
    char data;
    unsigned char_freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned char_freq)
    {
        left = right = NULL;
        this->data = data;
        this->char_freq = char_freq;
    }
};

struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->char_freq > r->char_freq);
    }
};

void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}


void HuffmanCodes(char data[], int char_freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], char_freq[i]));

    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->char_freq + right->char_freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    printCodes(minHeap.top(), "");
}

int main()
{
    int n;
    cout<<"Enter the number of characters :\n";
    cin>>n;
    char char_array[n];int char_freq[n];
    cout<<"Enter the characters and there frequency int the format----> char[space]freq\n";
    for(int i=0;i<n;i++)
    {
        cin>>char_array[i]>>char_freq[i];
    }
    int size = sizeof(char_array) / sizeof(char_array[0]);

    HuffmanCodes(char_array, char_freq, size);

    return 0;
}
