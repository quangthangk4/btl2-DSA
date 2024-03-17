/*
! Võ Tiến ..............
* Võ Tiến ..............
~ Võ Tiến ..............
& Võ Tiến ..............
TODO Võ Tiến ..............
*/

#include "main.h"


int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;


class RESTAURANT_Sukuna{
	class Node;
private:
	vector<Node* > areaTable;  //! nơi lưu trữ các khu vực
	list<Node* > LRU; 		  //!  Least Recently Used này là cơ chế khu vực nào có khác vào nhà hàng lâu nhất
private:

	//* hàm gợi ý của anh thôi dùng hay không thì tùy các bạn nha -> nên suy nghĩ khác
	// bool Compere(int index1, int index2)
	// {

	// }
	int vitri(int id){
		int i = 0;
		for(Node*& a:LRU){
			if(a->ID == id) return i;
			i++;
		}
		return -1;
	}
	void ReHeap_down(int index)
	{
		//TODO: với giá trị xét là areaTable[index].size()
		//TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		//TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khách vào gần nhất dùng list<Node* > LRU;
		//TODO: ví dụ khu A và khu B có số khách bằng nhau nếu khu A mới có khách vào thì so sánh min heap thì khu B đang nhỏ hơn khu A nên ở trên khu A
		int n = areaTable.size();
		int mini = index;
		int left = 2*index+1;
		int right = 2*index + 2;
		if(left < n && areaTable[left]->size() < areaTable[mini]->size()) mini = left;
		else if(left < n && areaTable[left]->size() == areaTable[mini]->size()){
			if(vitri(areaTable[left]->ID) > vitri(areaTable[mini]->ID)) mini = left;
		}
		if(right < n && areaTable[right]->size() < areaTable[mini]->size()) mini = right;
		else if(right < n && areaTable[right]->size() == areaTable[mini]->size()){
			if(vitri(areaTable[right]->ID)  > vitri(areaTable[mini]->ID)) mini = right;
		}
		if(mini != index){
			swap(areaTable[index],areaTable[mini]);
			ReHeap_down(mini);
		}
	}

	void ReHeap_up(int index)
	{
		//TODO: với giá trị xét là areaTable[index].size()
		//TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		//TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khách vào gần nhất
		//TODO: này xử lí tương tự reheap_down
		int parent=(index-1)/2;
		if (parent>=0 && areaTable[index]->size()<areaTable[parent]->size())
		{
			swap(areaTable[index],areaTable[parent]);
			ReHeap_up(parent);
		}
		else if (parent>=0 && areaTable[index]->size()==areaTable[parent]->size())
		{
			if (vitri(areaTable[index]->ID) > vitri(areaTable[parent]->ID))
			{
				swap(areaTable[index],areaTable[parent]);
				ReHeap_up(parent);
			}
			else
				return;
		}
		else	
			return;
	}

	//* nếu node chưa tồn tại trong LRU thì thêm vô nếu tồn tại thì dịch nó lên đầu danh sách
	void moveTop(Node* node)
	{	
		//TODO: BƯỚC 1 Tìm vị trí của node trong danh sách
		for(list<Node*>::iterator it = LRU.begin(); it != LRU.end();it++){
			if((*it)->ID == node->ID){
				LRU.erase(it);
				break;
			}
		}
		//TODO: BƯỚC 2 nếu nó tồn tại thì dịch nó lên đầu danh sách, nếu không thì insert ở đầu danh sách
		LRU.push_front(node);
	}

	//* xóa một node ra khỏi danh sách liên kết không gần gọi delete nha vì đã dùng bên dưới hàm xóa
    void removeNode(Node* node)
	{
		//TODO: 
		LRU.remove(node);
	}
public:
	RESTAURANT_Sukuna(){}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;
		//TODO TODO TODO TODO TODO bước 1
		for(int i = 0 ;i < areaTable.size();i++){
			if(areaTable[i]->ID == ID){
				index = i;
				break;
			}
		}
		//*bước 2: xem thử có khu này trong heap chưa để thêm vô 
		if(index == -1){
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}
		//*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào và tiến hàn reheap down bàn này xuống vì có số khách đông hơn
		else 
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}

	void remove_KEITEIKEN(int number)
	{
		if(areaTable.size() <= 0) return;

		//* đuổi num khách hàng tại num khu vực
		int numberRemove = number;
		while(areaTable.size() != 0 && number != 0){
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			solution << "remove customers in the area ID = " << areaTable[0]->ID << ": ";
			areaTable[0]->remove(numberRemove);
			solution << "\n";

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
			if(areaTable[0]->size() == 0)
			{
				swap(areaTable[0], areaTable[areaTable.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];

				//! xóa trong heap nữa
				areaTable.pop_back();
			}
			this->ReHeap_down(0);
			number --;
		}
 	}
//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void print_pre_order(int index, int number)
	{	
		if(index >= this->areaTable.size()) return;

		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_CLEAVE(int number)
	{
		if(number <= 0) return;

		solution << "Heap : ";
		for(auto it : this->areaTable)
		{
			int order = 0;
			for (auto ix : LRU) {
				if (ix == it) break;
				++order;
			}
			solution << it->ID << "(len="<< it->size() <<",index=" << order <<")" << " ";
		}
		solution << "\n";

		solution << "Heap : ";
		for(auto it : this->areaTable) solution << it->ID  << " ";
		solution << "\n";

		solution << "list LRU : ";
		for(auto it : LRU) solution << it->ID << " ";
		solution << "\n";


		print_pre_order(0, number);
	}
//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	class Node{
	private:
		int ID;					//! ID của bàn đó
		list<int> head; 		//! lưu danh sách các result của khách hàng
		friend class RESTAURANT_Sukuna;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		//* thêm vô đầu danh sách
		void insert(int result){head.push_front(result);}
		//* xóa ở cuối với số lượng là number cơ chế FIFO vô sớm thì cút sớm
		void remove(int number)
		{
			//TODO: xóa number khác hàng ở cuối danh sách tương ứng với vô sớm nhất 
			//^ gợi ý dùng hàm của linklist có sẵn
			//* thêm solution << head.back() << " "; để in ra
			if(number > this->size()) number = this->size();
			for(int i = 0 ;i < number;i++){
				solution << head.back() << " ";
				head.pop_back();
			}

		}
		//* print ra number khách hàng mới đến gần nhất theo cơ chế LIFO các khách hàng gần nhất
		void print(int number)
		{
			solution << "customers in the area ID = " << ID << ": ";
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				solution << *it << " ";
			}
			solution << "\n";
		}

	};

};


//* nhà hàng của sư phụ GOJO
class RESTAURANT_Gojo{
	class Tree_BST;
private:
	//* cứ hiểu mỗi phần tử areaTable là các khu ăn trong đó sẽ có 1 nhân viên quản lí thêm vào và xóa ra chủ không cần quản lí mấy này
	vector<Tree_BST> areaTable;
public:
	RESTAURANT_Gojo():areaTable(MAXSIZE + 1){}
	void insertAreaTable(int result)
	{
		//* khách mới vô thích chọn khu có ID = result % MAXSIZE + 1 dắt nó tới chỗ đó rồi nén vô cho nhân viên khu đó xử lí
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result); 
	}

	void remove_KOKUSEN()
	{
		//* tới từng khu ăn kêu nhân viên tìm thằng nào gián điệp đấm nó rồi đuổi cổ nó đi
		for(int i = 1; i < MAXSIZE + 1; i++) areaTable[i].remove();
 	}

	void print_LIMITLESS(int number)
	{
		//* tới khu number kêu nhân viên liệt kê tất cả khách hàng ra 
		if(number <= 0 || number > MAXSIZE) return; //! quá kí tự
		areaTable[number].print();
	}
private:
	//* Tree_BST giống như các nhân viên
	class Tree_BST{
		class Node;
	private:
		Node* root;	//! cây của khách hàng vị trí khách hàng
		queue<int> queueTime; //! thời gian khách hàng đến có thể hiểu như là sổ ghi thông tin khách hàng
	public:
		Tree_BST():root(nullptr){}
		int size(){
			return queueTime.size();
		}

	//^hàm thêm ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên được chủ giao cho bố trí khách hàng có result
		Node* insert_recursive(Node* node, int result)
		{
			//TODO TODO TODO  TODO TODO TODO  
			if(node == nullptr){
				node = new Node(result);
				return node;
			}
			else if(result < node->result){
				node->left = insert_recursive(node->left,result);
			}
			else{
				node->right = insert_recursive(node->right,result);
			}
			return node;
		}
		void insert(int result){
			root = insert_recursive(root, result);
			queueTime.push(result);
		}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//^hàm xóa ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên sẽ tới tận nơi đuổi cổ khách hàng gián điệp ra khỏi nhà hàng với result là khách hàng gián điệp
		Node* remove_recursive(Node* node,int result)
		{	
			//TODO TODO TODO  TODO TODO TODO  
			if(node == nullptr) return node;
			else if(result < node->result){
				node->left = remove_recursive(node->left,result);
			}
			else if(result > node->result){
				node->right = remove_recursive(node->right,result);
			}
			else{
				if(node->left == nullptr || node->right == nullptr){
					Node* del = node;
					node = (node->left == nullptr)? node->right : node->left;
					delete del;
					return node;
				}
				else{
					Node* current = node->right;
					while(current->left != nullptr){
						current = current->left;
					}
					node->result = current->result;
					node->right = remove_recursive(node->right,current->result);
				}
			}
			return node;
 		}
		int CountNode(Node* node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}
		unsigned long long permutationFormula(int x, int n)
		{
			//!TODO TÍNH C(n,x)= x!(n-x)!/n! công thức chỉnh hợp
			vector<vector<long long>> v(n+1,vector<long long>(x+1,0));
			for(int i = 0;i <= n;i++){
				for(int j = 0;j <= min(i,x) ;j++){
					if(j == 0 || j == i) v[i][j] = 1;
					else v[i][j] = v[i-1][j-1] + v[i-1][j];
				}
			}
			return v[n][x];
		}
		unsigned long long DFS(Node* node)
		{
			if(node == NULL) return 1;
			//TODO TODO TODO  TODO TODO TODO  đệ quy
			int leftsize = CountNode(node->left);
			int rightsize = CountNode(node->right);
			return permutationFormula(leftsize,leftsize+rightsize) * DFS(node->left) * DFS(node->right);
		}
		//* nhân viên sẽ liệt kê ra các khách hàng gián điệp để dễ dàng đuổi
		void remove(){
			if(this->size() == 0) return; //! trường hợp rỗng bỏ qua
			//* bước 1: đếm số lượng node cần xóa
			//^ tìm hiểu : https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/
			//TODO: tính số lượng number
			unsigned long long number = DFS(root);
			//*: trường hợp mà postoder cũng tạo ra một cây giống đó thì chỉ có 1 node -> nên không tính
			if(this->size() == 1) return;

			//* bước 2: xóa node trong cây với số lượng đã tính trên
			//* kiểm tra xem đã xóa đủ số lượng chưa hay cây đã hết node để xóa
			while(number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();			//! tìm khách hàng đầu tiên được lưu trong sổ và lấy được vị trí nó rồi
				queueTime.pop(); 						//! xóa nó khỏi sổ
				root = remove_recursive(root ,temp);	//! tới chỗ nó cho nó cút khỏi nhà hàng
				number --;
			}
		}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* hàm này theo trung thứ tự (in-order) thôi không gì khó hết
		string print_recursive(Node* node)
		{
			if(node == nullptr) return "NULL"; //! trường hợp dừng print

			string left = print_recursive(node->left);
			solution << node->result << " ";
			string right = print_recursive(node->right);
			

			if(node->left == nullptr && node->right == nullptr) return to_string(node->result); //! tr
			return to_string(node->result)+"("+left +","+right+")";
		}
		void print(){
			//! trường hợp rỗng bỏ qua
			if(this->size() == 0){
				solution << "EMPTY" ;
				return;
			}
			solution << "inoder: ";
			string s = print_recursive(root);
			solution << "\nTree: " << s;
			std::queue<int> tempQueue = queueTime;
			solution << "\nQueue: ";
			while (!tempQueue.empty()) {
				solution << tempQueue.front() << " ";
				tempQueue.pop();
			}
		}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	private:
		class Node{
		private:
			int result;
			Node* left;
			Node* right;
			friend class Tree_BST;
		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};

bool sosanh(pair<char,int>& a,pair<char,int>& b){
		if(a.second > b.second) return true;
		else if(a.second == b.second){
			if(a.first >= 'a' && a.first <='z' && b.first >='a' && b.first <= 'z' 
			|| a.first >= 'A' && a.first <='Z' && b.first >='A' && b.first <= 'Z'){
				if(a.first < b.first) return false;
				return true;
			}
			else{
				if(a.first >='a') return false;
				return true;
			}
		}
		return false;
}

class HuffTree_AVL{
	class Node;
private:
	Node* root = nullptr;
public:
	vector<pair<char, int>> string_Processing(string& name)
	{
		//TODO: implement string_Processing
		//* bước 1: liệt kê tuần suất xuất hiện của các kí tự riêng biệt trong tên của khách hàng (phân biệt hoa và thường)
		//* tạo thành một danh sách theo vị trí của các kí tự vào trước và vào sau 
		//! VD : name = "aDdbaaabbb" -> kết quả bước này: freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
		//TODO
		vector<pair<char, int>> freq_prev;
		int len = name.length();
		for (int i = 0; i < len; i++) {
			char check = name[i];
			bool found = false;
			for (auto& p : freq_prev) {
				if (p.first == check) {
					p.second++;
					found = true;
					break;
				}
			}
			if (!found) {
				freq_prev.push_back({check, 1});
			}
		}

		//* bước 2: mã hóa Caesar chuỗi name thành chuỗi mới và mã hóa luôn freq_prev 
		//! VD : name = "aDdbaaabbb", freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
		//! kq : name = "eEefeeefff", freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}]
		//TODO
		for(int i =0;i < len;i++){
			int k;
			for(auto &a : freq_prev){
				if(a.first == name[i]){
					k = a.second;
					break;
				}
			}
			if(name[i] >= 'a' && name[i] <= 'z') name[i] = (name[i] - 'a' + k) % 26 + 'a';
			else if(name[i] >= 'A' && name[i] <= 'Z') name[i] = (name[i] - 'A' + k) % 26 + 'A';
		}
		for(int i = 0;i < freq_prev.size();i++){
			if(freq_prev[i].first >= 'a' && freq_prev[i].first <= 'z') freq_prev[i].first = (freq_prev[i].first - 'a' + freq_prev[i].second) % 26 + 'a';
			else if(freq_prev[i].first >= 'A' && freq_prev[i].first <= 'Z') freq_prev[i].first = (freq_prev[i].first - 'A' + freq_prev[i].second) % 26 + 'A';
		}

		//* bước 3: công dồn freq_prev với các kí tự giống nhau sau khi mã hóa
		//^ chú ý cộng dồn lên phái đầu ví dụ dưới 'e' có 2 chỗ nên ta chọn đầu vector để giữ lại
		//! vd freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}] -> kq:  freq = [{e,5}, {E,1}, {f,4}]
		//TODO
		vector<pair<char, int>> freq;
		for(int i = 0;i < freq_prev.size();i++){
			bool check = false;
			for(int j = 0 ;j < freq.size();j++){
				if(freq_prev[i].first == freq[j].first){
					freq[j].second += freq_prev[i].second;
					check = true;
					break;
				} 
			}
			if(check == false) freq.push_back({freq_prev[i]});
		}

		//* bước 4: sort chuỗi freq mới tìm được phía trên theo chiều giảm dần
		//^ chú ý nếu tuần suất hiện bằng nhau thì kí tự nào lớn hơn thì lớn hơn, kí tự hoa lớn hơn kí tự thường
		//TODO
		sort(freq.begin(),freq.end(),sosanh);

		return freq;
	}


	int chieucao(Node* node){
		return (node == nullptr)? 0: node->height;
	}
	int balance(Node* node){
		return chieucao(node->right) - chieucao(node->left);
	}
	Node* rotateLeft(Node*& node,int& count){
		if(count >= 3) return node;
		count++;
		Node* current = node->right;
		node->right = current->left;
		current->left = node;
		// update height node and current;
		node->height = 1 + max((node->left == nullptr)? 0 : node->left->height, (node->right == nullptr)? 0 : node->right->height);
		current->height = 1 + max((current->left == nullptr)? 0 : current->left->height, (current->right == nullptr)? 0 : current->right->height);
		node = current;
		return node;
	}
	Node* rotateRight(Node*& node,int& count){
		if(count >= 3) return node;
		count++;
		Node* current = node->left;
		node->left = current->right;
		current->right = node;
		node->height = 1 + max((node->left == nullptr)? 0 : node->left->height, (node->right == nullptr)? 0 : node->right->height);
		current->height = 1 + max((current->left == nullptr)? 0 : current->left->height, (current->right == nullptr)? 0 : current->right->height);
		node = current;
		return node;
	}

	Node* balanceNode(Node*& node, int& count) 
	{
		//TODO
		int canbang = balance(node);
		if(canbang < -1){
			if(balance(node->left) <= 0) 
				return rotateRight(node,count);
			else{
				node->left = rotateLeft(node->left,count);
				return rotateRight(node,count);
			}
		}
		else if(canbang > 1){
			if(balance(node->right) >= 0) 
				return rotateLeft(node,count);
			else{
				node->right = rotateRight(node->right,count);
				return rotateLeft(node,count);
			}
		}
		return node;
	}

	//* tiến hành đệ quy theo preOrder -> nếu count >= 3 thì dừng lại không cân bằng nữa
	Node* balanceTree(Node*& node, int& count)
	{
		//TODO
		if(count >= 3 || node == nullptr) return node;
		balanceNode(node,count);
		balanceTree(node->left,count);
		balanceTree(node->right,count);
		return node;
	}

	void updateHeight(Node*& node){
		if(node == nullptr) return;
		updateHeight(node->left);
		updateHeight(node->right);
		node->height = 1 + max(chieucao(node->left),chieucao(node->right));
	}

	Node* buildHuff(vector<pair<char, int>> freq)
	{
		//* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
		//TODO: này không làm được đăng kí môn đi nha
		vector<Node*> build;
		for(int i = 0;i < freq.size();i++){
			Node* newnode = new Node(freq[i].second,freq[i].first,nullptr,nullptr);
			newnode->height = 1;
			build.push_back(newnode);
		}
		while(build.size() > 1)
		{
			//TODO: lấy ra node nhỏ nhất thứ nhất và nhỏ nhất thứ 2 (phần tử cuối vector)
			//TODO: tạo ra node nới có con bên trái là node nhỏ nhất và bên phải là node nhỏ nhất thứ 2 -> cập nhật weight, height của node mới
			//^ chú ý : cập nhật height, weight
			int count = 0;
			Node* newNode = nullptr;
			Node* left = build[build.size()-1];
			Node* right = build[build.size()-2];
			build.pop_back();
			build.pop_back();
			newNode = new Node(left->weight + right->weight,'\0',left,right);
			newNode->height = 1 + max(chieucao(left),chieucao(right));
			
			newNode = balanceTree(newNode,count);
			updateHeight(newNode);
			//TODO: đưa node mới vào trong vector -> đảm bảo vector luôn giảm dần như ban đầu
			//^ chú ý nếu bằng nhau thì xem như node mới luôn lớn hơn các node bằng giá trị weight -> ý là xếp nó gần head hơn
			if(build.size() == 0){
				build.push_back(newNode);
				break;
			}
			bool check = false;
			for(int i = 0;i < build.size();i++){
				if(newNode->weight >= build[i]->weight){
					build.insert(build.begin()+i,newNode);
					check = true;
					break;
				}
			} 
			if(check == false) build.push_back(newNode);
		}		
		return build[0];
	}


	//* TIẾN HÀNH đệ quy để lấy ra ra kết quả encoding
	//^ chú ý: cứ node bên trái thì mã hóa là '0', node bên phải mã hóa là '1'.
	void encodingHuffman_rec(vector<string>& encoding, Node* node, string s = "")
	{
		//TODO 
		if(node == nullptr) return;
		if(node->isChar()){
			encoding[node->c] = s;
		}
		encodingHuffman_rec(encoding,node->left,s+'0');
		encodingHuffman_rec(encoding,node->right,s + '1');
	}
	//* đầu vào là 1 cây và name đã được mã hóa Caesar -> đầu ra là result kết quả cần tìm.
	int encodingHuffman(Node * root,string nameCaesar)
	{
		if(root->left == nullptr && root->right == nullptr) return 0;

		//* bước 1: lấy chuỗi kết quả của các kí tự đã mã hóa
		//* ví dụ cây 2('a', 'b') ta lưu encoding['a'] = '0' và encoding['b'] = '1'
		vector<string> encoding(256, "");
		encodingHuffman_rec(encoding, root);

		//* bước 2 lấy ra 10 kí tự nhị phân cuối sau khi mã hóa nameCaesar thành mã nhị phân lấy từ phải đên trái 
		//! VD : 00000000000000000001 -> kq: 10000000000
		//^ chú ý: đừng có mà giải mã hết nameCaesar -> giải mã khi nào đủ 10 kí tự nhị phân là dừng
		//TODO
		string a = ""; 
		for(int i = nameCaesar.length()-1;i >= 0;i--){
			a = encoding[nameCaesar[i]] + a;
			if(a.length() >= 10) break;
		}
		int dem = 0;
		string copy = "";
		for(int i = a.length()-1;i>=0;i--){
			copy += a[i];
			dem++;
			if(dem == 10) break;
		}

		//* bước 3 mã hóa binary sang thập phân -> này ez rồi
		int result = 0;
		//TODO 
		int size = copy.length();
		for(int i = 0 ;i < size;i++){
			if(copy[i] == '1') result += pow(2,size - 1 - i);
		}
		//* kiểm tra test thôi nếu bạn thầy mình bị sai
		// cout << "nameCaesar = " << nameCaesar << endl;
		// cout << "encoding : ";
		// for(int i = 0; i < encoding.size(); i++) 
		// {
		//     if(encoding[i] != "") cout << char(i) << "=" << encoding[i] << " - ";
		// }
		// cout << "\nbinary = " << binary << endl;
		// cout << "result = " << result << endl;
		//********************

		return result;
	}

	int encode(string name){

		if(name.length() < 3) return -1;

		//* bước 1 xử lí chuỗi thu được list để tới phần sau
		vector<pair<char, int>> freq = this->string_Processing(name);
		
		solution << "freq     : {";
		for(int i = 0 ;i < freq.size();i++){
			if(i == freq.size() -1) solution << "{" << "'" << freq[i].first << "'" << "," << freq[i].second << "}" ;
			else solution << "{" << "'" << freq[i].first << "'" << "," << freq[i].second << "},";

		}
		solution << "}" << endl;
		//* bước 2 xây dựng cây huff
		root = this->buildHuff(freq);
	
		if(root->left == nullptr && root->right == nullptr) return 0; //! trường hợp chỉ có 1 node
		this->print();
		
		
		//* bước 3 mã hóa.
		solution << "name   = " << name << endl;
		int result = this->encodingHuffman(root ,name);
		solution << "result = " << result << endl;
		return -1;
	}

	void rec_print(const Node* tree) {
		if (tree == nullptr) {
			return;
		}
		if(tree->c) solution << "[" << tree->weight << "," << tree->c << "]";
		else solution << "[" << tree->weight << "]";
		
		if (tree->left != nullptr || tree->right != nullptr) {
			solution << "(";
			rec_print(tree->left);
			solution << ",";
			rec_print(tree->right);
			solution << ")";
		}
	}
	
	void print()
	{	
		//* print theo chiều rộng anh có hướng dẫn rồi queue
		//* khi in chuyển từ cout << "char-freq/n" thành solution << "char-freq/n" cho anh dễ test
		solution << "root : ";
		rec_print(root);
		solution << '\n';
	}

private:
	class Node{
	public:
		int weight;
		int height;
		char c;
		Node* left;
		Node* right;
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ): height(1), weight(weight), c(c), left(left), right(right) {}
		bool isChar() const { return c != '\0'; }
	};
};


class JJK_RESTAURANT_OPERATIONS
{
private:
	HuffTree_AVL New_customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;
	
public:

	void LAPSE(string name)
	{
		//* mã hóa HuffTree_AVL kết quả là 10 kí tự nhị phân cuối chuyển sang thập phân
		int result = New_customers_arrive.encode(name);
		return;
	}	

	//* xử lí nhà hàng gojo
	void KOKUSEN(){}
	void LIMITLESS(int num){}
	
	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num){}
	void CLEAVE(int num){}

	//* xử lý HuffTree_AVL
	void HAND(){New_customers_arrive.print();}
};


