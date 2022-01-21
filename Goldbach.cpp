#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<set>

using namespace std;

class prime_partition {
  public:
	void operator()(int);
	prime_partition();

  private:
	void create_pset();
	void print_partitions();
	bool isprime(int);
	void compute_partitions(vector<int>&, int , int = 0);

	set<int> pset;
	vector< vector<int> >partitions;
	unsigned int maxterm;
};

int main(int argc, char *argv[]){
        prime_partition goldbach;

        int number;
        while (1) {
                cout << "number = ";
                cin >> number;
                if (cin.eof())
                        break;

                goldbach(number);
        }

        cout << "\n";
}

bool prime_partition::isprime(int num){
        int prime = 1;
        int psqrt = sqrt(num) + 1;
        while(++prime <= psqrt){
                if(num % prime == 0)
                        return false;
        }
        return true;
}

void prime_partition::create_pset(){
        pset.clear();
        pset.insert(2);
        for(int i = 2; i < 2000; i++){
                if(isprime(i)){
                        pset.insert(i);
                }
        }
}

prime_partition::prime_partition(){
        create_pset();
}

void prime_partition::operator()(int num){
        if(num < 2 || num >= 2000)
                return;

        if(num % 2 == 0){
                maxterm = 2;
        }
	if(num % 2 != 0){
                maxterm = 3;
	}

        vector<int> vec;
        partitions.clear();
        compute_partitions(vec, num);
        print_partitions();
}

void prime_partition::print_partitions(){
        for(unsigned int i = 0; i < partitions.size(); i++){
                for(unsigned int j = 0; j < partitions[i].size(); j++){
                        cout << partitions[i][j] << ' ';
                }
                cout << endl;
        }
}

void prime_partition::compute_partitions(vector<int>&numbers, int mark, int total){
        if(total == mark && numbers.size() <= maxterm){
                partitions.push_back(numbers);

                if(numbers.size() < maxterm){
                        maxterm = numbers.size();
                        partitions.clear();
                        partitions.push_back(numbers);
                        return;
                }
        }

        if(total > mark || numbers.size() > maxterm){
                return;
        }

        set<int>::iterator start = pset.begin();
        set<int>::iterator end;
        set<int>::iterator ii;
        if(!numbers.size()){
                end = pset.upper_bound(mark);
        }else{
                end = pset.upper_bound(numbers.back());
	}

        for(ii = start; ii != end; ii++){
                numbers.push_back(*ii);
                compute_partitions(numbers,mark, total + (*ii));
                numbers.pop_back();
        }
}