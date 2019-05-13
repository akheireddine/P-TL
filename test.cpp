#include<iostream> 
#include<memory> 
#include<list>
using namespace std; 

class Toto{
private:

	string mot;
	
public:
	Toto(string m){ mot = m; };
	void print(){ cout<<"coucou"<<endl;};

	string get_mot(){ return mot;};

};

int main(){

	shared_ptr<Toto> pt = make_shared<Toto>("hey");

	cout<<pt.get()<<endl;
	pt->print();
	cout<<pt->get_mot()<<endl;


	list< shared_ptr< Toto > > l_toto;
	
	l_toto.push_back(pt);

	cout<<(*l_toto.begin()).get()<<endl;
	cout<<(*l_toto.begin()).use_count()<<endl;
	
	//pt.reset();


	cout<<(*l_toto.begin()).use_count()<<endl;
	l_toto.clear();

	cout<<pt.use_count()<<endl;
	return 1;
}
