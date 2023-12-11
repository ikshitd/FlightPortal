#include <bits/stdc++.h> 
#include <fstream> 
using namespace std ; 

typedef long long ll ; 
typedef long double ld ; 

const ll INF = 1e18 ;

class Graph{

private: 

	int v ;
	// graph if of the form --> <source , <duration <ticket fare , destination>>> 
	unordered_map <string , vector<pair<int , pair<int , string>>>> gr ; 

	// to keep a status of each city 
	unordered_map <string , bool> visited ;
	unordered_map <string , bool> visi ;
	vector <string> cities = {"Bombay" , "Chennai" , "Kolkata" , "Hyderabad" , "Ahmedabad" , "Kerela" , "Pune" , "Delhi" , "Banglore" , "London" , "NewYork" , "Manchester" , "Rome" , "Italy" , "NewZealand" , "Qatar" , "Dubai" , "Paris"} ; 

public :

	Graph(){
		this -> v = cities.size() ; 
	}

	// adds an edge to the graph 
	// undirected graph 
	void addedge(string source , string destination , int weight , int time){
		gr[source].push_back(make_pair(time , make_pair(weight , destination))) ; 
		gr[destination].push_back(make_pair(time , make_pair(weight , source)))  ;
	}
	
	// initializes the graph with the given set of data 
	void init(){
		addedge("Delhi" , "Bombay" , 12000 , 360) ; 
		addedge("Chennai" , "Delhi" , 12121 , 500) ;
		addedge("Chennai" , "Hyderabad" , 200 , 100) ; 
		addedge("London" , "Delhi" , 70000 , 800) ; 
		addedge("Hyderabad" , "Manchester" , 232323 , 600) ; 
		addedge("Bombay" , "Hyderabad" , 8000 , 200) ;
		addedge("Chennai" , "Qatar" , 20000 , 280) ; 
		addedge("Qatar" , "NewYork" , 30000 , 900) ; 
		addedge("NewYork" , "Manchester" , 20000 , 400) ; 
		return ;
	}

	// to display the list of active airports in the program 
	void display_airports(){
		cout << "The list of active airports are : \n" ;
		for(auto city : cities){
			if(gr[city].size() != 0){
				cout << city << "   " ; 
			} 
		}
		cout << "\n\n" ; 
		return ;
	}

	// to print the duration of the flight in hrs formant
	void print_time(int x){
		cout << (((x / 60) / 10 == 0) ? "0" : "") << (x / 60) << ":" << (x % 60) << (((x % 60) % 60 == 0)? "0" : "") << " hrs\n" ;
		return ;
	}

	// to display the routes of the flights along with the ticket fare and the duration of the flight 
	void display_flight_routes(){
		cout << "List of Active flight routes are : \n\n" ; 
		cout 
			<< left 
			<< setw(20)
			<< "From" 
			<< left 
			<< setw(20)
			<< "To" 
			<< left 
			<< setw(20) 
			<< "Ticket Fare"
			<< left 
			<< setw(20)
			<< "Duration" 
			<< "\n" ; 

		cout << "\n" ;
		for(auto city : cities){
			for(auto x : gr[city]){
				cout
					<< left 
					<< setw(20)
					<< left
					<< city 
					<< left 
					<< setw(20) 
					<< left
					<< x.second.second 
					<< left 	
					<< setw(20)
					<< x.second.first  ;
				print_time(x.first) ;
			}
			if(gr[city].size() != 0){
				cout << "-------------------------------------------------------------------------------------------\n" ;
			} 
		}
		cout << "\n" ; 
		return ;
	}

	// function to find the cost and the total duration of the flight for a particular path from source to destination 
	// takes in the path as an argument 
	// returns <duration , fare> 
    pair <ll , ll>  find_total(vector <string> path){
		ll total_duration = 0 ;
		ll total_cost = 0 ;
		for(int i = 0 ; i < path.size()  - 1 ; i++){
			for(auto x : gr[path[i]]){
				if(x.second.second == path[i + 1]){
					total_cost += x.second.first ;
					total_duration += x.first ;
					continue ;
				}
			}
		}
		return {total_duration , total_cost} ;
	}

	// prints the path from a particular source to the destination 
	int print_path(string source , string current , map <string , string> parent , bool find_cost = false){
		vector <string> order ;
		string current_location = current ; 
		while(current_location != source){
			order.push_back(current_location) ; 
			current_location = parent[current_location]  ; 
		}
		order.push_back(source) ; 
		reverse(order.begin() , order.end()) ; 
		for(auto way : order){
			cout << way << " " ;
		}
		cout << "\n" ; 
		
		// calls the find_total function to get the duration and fare of the flight --> <duration , fare> 
		pair <ll , ll> res  = find_total(order); 
		if(find_cost == true){
			cout << "The total fare is : " << res.second << "\n" ; 
			cout << "The total flight duration is : " << (res.first / 60) << ":" << (res.first % 60) << " hrs.\n\n" ;
		}
		return  res.second ;
	}

	// breadth first search algorithm to find a particular path from a source to the destination with the minimum number of nodes / cities in between them 
	// also prints the calculated path 
	int bfs(string source , string destination){
		queue <string> q ; 
		unordered_map <string , bool> vis ;
		map <string , string> new_parent ; 
		vis[source] = true ; 
		new_parent[source] = source ;
		q.push(source) ;
		while(!q.empty()){
			string f = q.front()  ; 
			q.pop() ; 
			for(auto  val : gr[f]){
				if(!vis[val.second.second]){
					q.push(val.second.second) ;
					vis[val.second.second] = true ;
					new_parent[val.second.second] = f; 
				}
			}
		}
		cout << "The path with the minimum number of cities in between : " ;
		return print_path(source , destination , new_parent , true) ;
	}

	// helper function
	// dfs algorithm to print the path , from source to each node with the minimum time duration
	void dfs2(string source , string current , map <string , ll> time_taken , map <string , string> parent){
		cout
			<< left 
			<< setw(40) 
			<< current
			<< left 
			<< setw(40) 
			<< time_taken[current] ; 
			print_path(source , current , parent) ;
			cout << "\n" ; 

		visi[current] = true ;
		for(auto x : gr[current]){
			if(!visi[x.second.second]){
				dfs2(source , x.second.second , time_taken , parent) ;
			}
		}
		return ;
	}

	// helper function 
	// dfs algorithm to print the path , from source to each node with the minimum  fare
	void dfs(string source , string current , map <string , ll> cost , map <string , string> parent){
		cout
			<< left 
			<< setw(40) 
			<< current
			<< left 
			<< setw(40) 
			<< cost[current] ; 
			print_path(source , current , parent) ;
			cout << "\n" ; 

		visited[current] = true ;
		for(auto x : gr[current]){
			if(!visited[x.second.second]){
				dfs(source , x.second.second , cost , parent) ;
			}
		}
		return ;
	}
	
	// find the minimum fare or the minimum time duration from the source to every other nodes 
	// uses dfs and dfs2 to recursively print the data 
	int dijkstra(string source , string destination , bool reduce_time = false , bool reduce_cost = false){

		map <string , ll>  cost ; // keeps the minimum fare from source to every other city <city , min_fare>  
		map <string , ll> time_taken ; // keeps the minimum time duration of flight to every other city  <city , min_duration> 
		set <pair<int , string>> s ; // maintaining a set 
		map <string , string> parent ; // to store the path in case of cost_minimization  
		map <string , string> new_parent ; // to store the path in case of minimizing the duration of the flight 

		// to check if the source if invalid 
		auto find_source = gr.find(source) ; 
		if(find_source == gr.end()){
			cout << "Invalid Locations \n\n" ;
			return false;
		}

		// initlizing the cost and time_taken with large values
		for(auto val : cities){
			cost[val] = INF ;
			time_taken[val] = INF ;
		}	
		
		parent[source] = source ;
		cost[source] = 0 ;
		time_taken[source] = 0 ; 
		s.insert({0, source}); 

		while(!s.empty()){
			auto it = s.begin() ; 
			string node = it -> second ; 
			ll cost_till_now , time_till_now ;
			
			// if the task is to minimize the duration of the flight 
			if(reduce_time){
				time_till_now = it -> first ;
			}
			
			// if the task is to minimize the ticket fare of the flight 
			if(reduce_cost){
				cost_till_now = it -> first ; 
			}
			s.erase(it) ; 

			for(auto val : gr[node]){
				string neighbour = val.second.second ; 
				int  currentedge = val.second.first ; 
				int current_time = val.first ; 

				// if the task is to minimize the ticket fare of the flight 
				if(reduce_cost){
					if(cost_till_now + 	currentedge < cost[neighbour]){
						auto f = s.find(make_pair(cost[neighbour]  , neighbour)) ;
						if(f != s.end()){
							s.erase(f) ; 
						}
						parent[neighbour] = node ;
						cost[neighbour] = cost_till_now + currentedge ; 
						s.insert(make_pair(cost[neighbour]  , neighbour)) ;
					}
				} 

				// if the task is to minimize the duration of the flight 
				if(reduce_time){
					if(time_till_now + current_time < time_taken[neighbour]){
						auto f = s.find(make_pair(time_taken[neighbour] , neighbour)) ;
						if(f != s.end()){
							s.erase(f) ;
						}
						new_parent[neighbour] = node ; 
						time_taken[neighbour] = time_till_now + current_time ; 
						s.insert(make_pair(time_taken[neighbour] , neighbour)) ;
					}
				}
			}
		}
		auto find_key = gr.find(destination) ;
		if(find_key == gr.end()){
			if(reduce_cost){
				cout 
					<< left 
					<< setw(40) 
					<< "\nDestination"
					<< left 
					<< setw(40) 
					<< "Total minimum fare"
					<< left 
					<< setw(40) 
					<< "Path with the minimum fare\n\n" ; 

				dfs(source , source , cost , parent) ; 
			} 
			if(reduce_time){
				cout 
					<< left 
					<< setw(40) 
					<< "\nDestination"
					<< left 
					<< setw(40) 
					<< "Total Minimum flight duration (minutes..)"
					<< left 
					<< setw(40) 
					<< "Path with the minimum flight duration\n\n" ; 

				dfs2(source , source , time_taken , new_parent) ; 
			}
			return 0 ; 
		}
		else{
			if(reduce_cost){
				cout << "\nPath with the minimum fare : " ; 
				print_path(source , destination  , parent) ; 
				cout << "\n" ; 
				cout << "Total minimum fare : " << cost[destination] << "\n" ; 
				return cost[destination] ;
			} 
			if(reduce_time){
				cout << "\nPath with the shortest flight duration : " ; 
				print_path(source , destination  , new_parent) ; 
				cout << "\n" ; 
				cout << "Total flight duration : " << (time_taken[destination] / 60) << ":" << (time_taken[destination] % 60) << "hrs.\n\n" ; 
				return time_taken[destination] ; 
			}
		}
	}
} ;

// converts the string in the desired format ((delhi , delhi) --> delhi) 
// takes in a string as an argument  and returns the modified string
string transform_string(string a){
	transform(a.begin() , a.end() , a.begin() ,  ::tolower) ; 
	a[0] = a[0] - 32 ;
	return a ;
}

class encryption{
private: 
	int key  ;
public :
	encryption(){
		int x = (rand() % 8) + 1 ;
		this -> key = 5 ; 
	}
	string encoding(string s){
		for(int i = 0 ; i < (int) s.size() ; i++){
			if((s[i] >= 'a' && s[i] <= 'z') or (s[i] >= 'A' && s[i] <= 'Z')){
				s[i] = char(s[i] + key)  ; 
			} 
		}
		return s ;

	}
	string decoding(string s){
		for(int i =0 ; i < (int) s.size() ; i++){
			if((s[i] >= 'a' && s[i] <= 'z') or (s[i] >= 'A' && s[i] <= 'Z')){
				s[i] = char(s[i] - key)  ; 
			} 
		}
		return s ;
	}
}encrypt ;  


class user_login{
private : 
	string user_name , password ; 
	bool logged_in = false ;

public : 

	bool get_logged_in(){
		return logged_in ; 
	}
	
	bool check_password(string s){
		bool special_char = false ; 
		bool integer = false ; 
		for(auto x : s){
			if(x >= '0' && x <= '9'){
				integer = true ;
			}
			else if((x >= 'a' && x <= 'z') or (x >= 'A' and x <= 'Z')){
				continue ;
			}
			else{
				special_char = true ;
			}
		}
		return ((special_char == true && integer == true) ? true : false) ;
	}

	void get_details(){
		while(true){
			cout << "Enter the user_name and the password" << "\n" ; 
			cin >> user_name ; 
			cin >> password ;
			if(check_password(password)){
				ifstream checkfile (user_name + ".txt") ; 
				if(!checkfile){
					ofstream outfile (user_name + ".txt") ;
					outfile << encrypt.encoding(user_name) << "\n" << encrypt.encoding(password) ;
					outfile.close() ;
				} 
				else{
					cout << "Look's like you are already registered ! Try logging in \n" ; 
				}
				checkfile.close() ;
				break ;
			} 
			else{
				cout << "The password must contain a number and a special character\n" ; 
			}
		}
		return ; 
	}

	void new_password(){
		while(true){
			cout << "Enter the username : " ; 
			string user_name ; 
			cin >> user_name ; 
			ifstream check_file (user_name + ".txt") ; 
			if(!check_file){
				cout << "The user name entered is incorrect ! Try again ! " << "\n" ; 
				cout << "Would you like to try again ? " << "\n" ; 
				string s ; 
				cin >> s ; 
				check_file.close() ; 
				if(transform_string(s) == "Yes"){
					continue ;
				}
				else{
					break ;
				}
			}
			else{
				ofstream pass_file (user_name + ".txt" ,ios::out | ios::trunc) ;
				cout << "Enter the new password : " << "\n" ; 
				string newpassword ; 
				cin >> newpassword ;
				pass_file << encrypt.encoding(user_name) << "\n" << encrypt.encoding(newpassword) ; 
				pass_file.close() ; 
				cout << "Password successfully changed ! " << "\n" ; 
				check_file.close() ; 
				break ;
			}
		} 
		return ;
	}

	void login(){
		string username , pass ;
		cout << "Enter the user_name and the password" << "\n" ; 
		cin >> username ; 
		cin >> pass ;
		ifstream inputfile (username + ".txt") ; 
		if(!inputfile){
			cout << "The user is not registered ! Try registering yourself " << "\n" ;
			inputfile.close() ;
			return ;
		}
		string a , b ;
		getline(inputfile , a) ; 
		getline(inputfile , b) ;

		if(username == encrypt.decoding(a) and pass == encrypt.decoding(b)){
			cout << "Login Successful !" << "\n" ;
			logged_in = true ;
		}
		else{
			cout << "Login failed ! Try again" << "\n" ; 
			cout << "Forgot password ? Yes or No ? " << "\n"; 
			string s ; 
			cin >> s ; 
			s = transform_string(s) ; 
			if(s == "Yes"){
				new_password() ;
			}
		}
		inputfile.close() ;
		return ;
	}

	bool give_options(bool payment = false){
		while(true){
			if(get_logged_in() == true){
				break ;
			}
			cout << "1 : register \n" ; 
			cout << "2 : login \n" ; 
			if(payment == false){
				cout << "3 : skip for now \n" ; 
			} 
			int g ; 
			cin >> g ; 
			if(g == 1){
				get_details() ;
			}
			else if(g == 2){
				login() ;
			}
			else{
				if(payment == false){
					break ;
				}
				else{
					cout << "Do you want to cancel the booking ? " << "\n" ;
					string s ; 
					cin >> s ; 
					s = transform_string(s) ; 
					if(s == "Yes"){
						return false ;
					}
				}
			}
		} 
		return true ;
	}
	
	const string generate_random(){
		int a = (rand() % 9999) + 1 ; 
		return to_string(a) ;
	}

	void get_otp(){
		ofstream new_file ("otp.txt" , ios::out) ; 
		string a = generate_random() ;
		new_file << a << "\n" ; 
		new_file.close() ;
		return ;
	}
	bool validate(){
		while(true){
			ifstream infile ("otp.txt" , ios::in) ;
			cout << "Enter the otp : \n" ; 
			string s ; 
			cin >> s ; 
			string o ; 
			getline(infile , o) ; 
			infile.close() ;
			if(s == o){
				cout << "Validation successful ! " << "\n" ; 
				return true ;
			}
			else{
				cout << "The otp you have entered is incorrect" << "\n" ; 
				cout << "Do you want to resend the otp \n" ; 
				string s ; 
				cin >> s ; 
				s = transform_string(s) ; 
				if(s == "Yes"){
					get_otp() ;  
					continue ; 
				}
				else{
					return false ; 
				}
			}
		}
	}

}user_details;

bool approve(int x , bool reduce_time = false , bool reduce_fare = false){

	bool a = user_details.get_logged_in() ;
	if(user_details.get_logged_in() == false){
		a = user_details.give_options(true) ; 
	}
	if(a){
		cout << "Enter the number of passengers : \n" ; 
		int number ; 
		cin >> number ; 
		cout << "The total check out amt . : " << number * x << "\n" ;
		cout << "Do you want to continue ? " << "\n" ; 
		string s ; 
		cin >> s ; 
		s = transform_string(s) ; 
		if(s == "Yes"){
			user_details.get_otp() ;
			user_details.validate() ;
			return true ;
		}
		else{
			return false ;
		}
		return true ;
	}
	else{
		return false ;
	}
}

bool book_tickets(){
	cout << "Book Now ? Yes or No" << "\n" ; 
	string s  ;
	cin >> s ;
	s = transform_string(s) ; 
	return (s == "Yes" ? true : false) ;
}

void solve(){

	// graph declaration
	Graph g ; 
	// graph initialization
	g.init() ; 

	cout << " _____ _____ _____ _____ " << '\n';
    cout << "|     |     |     |     |" << '\n';
    cout << "| W   | E   | L   | C   |" << '\n';
    cout << "|   O |   M |   E |     |" << '\n';
    cout << "|     |     |     |     |" << '\n';
    cout << "|     |   T |   O |     |" << '\n';
    cout << "|_____|_____|_____|_____|" << '\n';
    cout << "|     |     |     |     |" << '\n';
    cout << "| T   | H   | E   |     |" << '\n';
    cout << "|     |     |     |     |" << '\n';
    cout << "| F   | L   | I   | G   |" << '\n';
    cout << "|     |  H  |  T  |     |" << '\n';
    cout << "|_____|_____|_____|_____|" << '\n';
    cout << "|     |     |     |     |" << '\n';
    cout << "| P   | O   | R   | T   |" << '\n';
    cout << "|     |  A  |  L  |     |" << '\n';
    cout << "|     |     |     |     |" << '\n';
    cout << "|_____|_____|_____|_____|" << '\n';

	user_details.give_options() ; 

	string source , destination ;
	ll duration , fare ;
	bool is_fine = true  ;
	while(true){
		cout << "1 : Display the cities \n"; 
		cout << "2 : Display the active flight routes \n" ; 
		cout << "3 : Flight with minimum number of stops \n" ; 
		cout << "4 : Flight with minimum flight duration : \n" ; 
		cout << "5 : Flight with minimum fare : \n" ; 
		int t ; 
		cin >> t ; 
		switch(t){
			case 1 : 
				g.display_airports() ; 
				continue ;
			case 2 : 
				g.display_flight_routes() ;
				continue ;
			case 3 : 
				cout << "Enter the source and Destination :\n" ; 
				cin >> source >> destination ;
				fare = g.bfs(transform_string(source) , transform_string(destination));
				if(!fare){
					is_fine = false ; 
					break ;
				}
				else{
					if(book_tickets()){
						if(approve(fare , false , false )){ return ; }
					}
				}
				continue ;

			case 4 : 
				cout << "Enter the source and destination :\n" ; 
				cin >> source >> destination ; 
				duration = g.dijkstra(transform_string(source) , transform_string(destination) , false , true);
				if(!duration){
					is_fine = false ;
					break ;
				}	
				else{
					if(book_tickets()){
						if(approve(duration , true , false)){ return ; }
					}
				}
				continue ;
			case 5 :
				cout << "Enter the source and destination :\n" ; 
				cin >> source >> destination ; 
				fare = g.dijkstra(transform_string(source) , transform_string(destination) , false , true); 
				if(!fare){
					is_fine = false ;
					break ;
				}	
				else{
					if(book_tickets()){
						if(approve(fare , false , true)){ return ; }
					}
				}
				continue ;
			default :
				is_fine = false ;
				break ;
		}
		if(is_fine == false){
			break ;
		}
	} 
	return ;
} 

int32_t main(){
	solve() ; 
	return 0;
}
