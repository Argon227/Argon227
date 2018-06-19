#pragma once
//Двоичное дерево поиска - это двоичное дерево, для которого выполняются следующие дополнительные условия (свойства дерева поиска): 
//1)Оба поддерева — левое и правое — являются двоичными деревьями поиска.
//2)У всех узлов левого поддерева произвольного узла X значения ключей данных меньше, нежели значение ключа данных самого узла X.
//3)У всех узлов правого поддерева произвольного узла X значения ключей данных больше либо равны, нежели значение ключа данных самого узла X.
#ifndef LAB_11
#define LAB_11
#include <iostream>

#include <cstddef>

#include <fstream>

#include <memory>

using namespace std;



template <typename T>//шаблонизировали класс BinarySearchTree (шаблон - средство для кодирования 
//обобщённых алгоритмов, без привязки к некоторым параметрам);

class BinarySearchTree

{

public:
	//структура — это некое объединение различных переменных (даже с разными типами данных), которому можно присвоить имя (другими словами -
	//-конструкция, которая может агрегировать различные типы данных под одним именем;
	struct Node//структура - узел;

	{
		//умный указатель - класс (обычно шаблонный), имитирующий интерфейс обычного указателя и добавляющий некую новую функциональность, 
		//например проверку границ при доступе или очистку памяти. Владеющий указатель (разновидность умных указателей) -  владеющие указатели 
		//применяются для борьбы с утечками памяти и висячими ссылками. Утечкой памяти называется ситуация, когда в программе нет ни одного 
		//указателя, хранящего адрес объекта, созданного в динамической памяти. Висячей ссылкой называется указатель, ссылающийся на уже 
		//удалённый объект (т. е. удаление или присвоение нового значения указателю будет согласовано с временем жизни объекта);
		//Принцип работы (обычно указатели используются  с объектами, имеющими специальные операции «увеличить число ссылок» или «уменьшить 
		//число ссылок»): При появлении новой ссылки на объект вызывается операция «увеличить число ссылок», а при уничтожении — 
		//-«уменьшить число ссылок». Если в результате операции «уменьшить число ссылок» число ссылок на объект становится равным нулю, то объект удаляется. 
		//Такая методика называется автоматическим подсчётом ссылок.Она согласует число указателей, хранящих адрес объекта, с числом ссылок, 
		//хранящимся в объекте, а при достижении этим числом нулевого значения приводит к удалению объекта.
		//Класс shared_ptr<T> описывает объект, который использует подсчет ссылок для управления ресурсом T. Объект shared_ptr фактически 
		//содержит указатель на ресурс, которым он владеет, или содержит пустой указатель (NULL). при удалении последнего объекта shared_ptr, 
		//обладающего тем или иным ресурсом, данный ресурс освобождается. При конструировании нового объекта создается объект со счетчиком и в 
		//него помещается значение 1. При копировании счетчик увеличивается на 1. При вызове деструктора (или при замене указателя путем 
		//присваивания, или вызова reset), счетчик уменьшается на 1.
		T value_;//число, привязанное к узлу (ключ);

		shared_ptr<Node> left_;//указатель на левый подузел;

		shared_ptr<Node> right_;//указатель на правый подузел;



		Node(T value) : value_(value), left_(nullptr), right_(nullptr) {}//конструктор структуры по умолчанию;



		shared_ptr<Node> copy()

		{

			shared_ptr<Node> cNode(new Node(value_));

			if (left_) cNode->left_ = left_->copy();

			if (right_) cNode->right_ = right_->copy();

			return cNode;

		}//конструктор копирования;



		~Node()

		{

			if (left_)

				left_ = nullptr;

			if (right_)

				right_ = nullptr;

		}//деструктор;

	};



	BinarySearchTree() : root_(nullptr), size_(0) {};//конструктор по умолчанию;


	//Список инициализации — концепция суть которой состоит в том, что структура/класс или массив могут быть созданы передачей 
	//списка аргументов в порядке, соответствующем порядку определения членов структуры. std::initialzer_list<T> в качестве аргумента
	//принимает список неопределенного размера; принцип работы: создается некий промежуточный массив, в который помещаются все элементы 
	//из списка инициализации({…}). После этого конструируется initializer_list, который хранит в себе указатель на начало и конец этого 
	//временного массива. После чего initializer_list передается в конструктор и мы можем делать с ним всё, что захотим.
	BinarySearchTree(const initializer_list<T>& list) : BinarySearchTree()

	{

		for (auto& value : list)//т.к.initializer_list имеет методы begin и end, которые возвращают необходимые итераторы мы можем 
			//использовать его в цикле for нового формата;		
			insert(value);
		


	};//конструктор с помощью списка инициализации;



	BinarySearchTree(const BinarySearchTree& tree)

	{

		size_ = tree.size_;

		root_ = tree.root_->copy();

	}//конструктор копирования для объекта;



	BinarySearchTree(BinarySearchTree&& tree)

	{

		root_ = tree.root_;

		tree.root_ = nullptr;

		size_ = tree.size_;

		tree.size_ = 0;

	}//конструктор копирования по правосторонней ссылке;



	auto size() const noexcept -> size_t //в стандарте c++11 можно объявлять методы таким образом;

	{

		return size_;

	};


	//пусть параметр - ключ K, тогда если дерево пусто, сообщить, что узел не найден, и остановиться.
	//Иначе сравнить K со значением ключа корневого узла X: 
	//1)Если K=X, выдать ссылку на этот узел и остановиться.
	//2)Если K>X, рекурсивно искать ключ K в правом поддереве Т.
	//3)Если K<X, рекурсивно искать ключ K в левом поддереве Т.
	auto find(const T& value) const noexcept -> const T*

	{

		if (size_ == 0) return nullptr;

	shared_ptr<Node> curNode(root_);

	do

	{

		if (value == curNode->value_) return &curNode->value_;

		else if (value < curNode->value_) curNode = curNode->left_;

		else if (value > curNode->value_) curNode = curNode->right_;

	} while (curNode);

	return nullptr;

	}


		//пусть параметр - ключ K, если дерево пусто, заменить его на дерево с одним корневым узлом K;
		//Иначе сравнить K с ключом корневого узла X:
		//1)Если K>X, рекурсивно добавить K в правое поддерево Т.
		//2)Если K<X, рекурсивно добавить K в левое поддерево Т.
		//3)Если K = X, сидим на попе ровно и ничего не делаем.
	auto insert(const T& value) noexcept -> bool

		//try{
			{
				if (size_ == 0)

				{

					root_.reset(new Node(value));

					size_ = 1;

					return true;

				}

				shared_ptr<Node> curNode(root_);

				shared_ptr<Node> prevNode(nullptr);

				while (curNode)

				{

					prevNode = curNode;

					if (value == curNode->value_) return false;

					else if (value < curNode->value_) curNode = curNode->left_;

					else curNode = curNode->right_;

				}

				if (value < prevNode->value_) prevNode->left_.reset(new Node(value));//метод reset() изменяет управляемый объект существующего 
				//shared_ptr(в левый подузел prevNode записываем через конструктор value);

				else prevNode->right_.reset(new Node(value));

				size_++;
			//}catch (ArrayStoreException e) {
			//	continue;
			//}//исключение возникает при попытке записать в ячейку массива ссылку на объект неправильного типа
				//catch (NullPointerException ex) {
				//	continue
				//}//если попытаться использовать в программе ссылку, содержащую значение null, возникнет исключение NullPointerException. 
				//ПРИ ВКЛЮЧЕНИИ В КОД ИСКЛЮЧЕНИЙ ВОЗНИКАЮТ ОШИБКИ;

		return true;

	}


	//пусть параметр - ключ K, если дерево T пусто, остановиться;
	//Иначе сравнить K с ключом X корневого узла n: 
	//1)Если K>X, рекурсивно удалить K из правого поддерева Т;
	//2)Если K<X, рекурсивно удалить K из левого поддерева Т;
	//3)Если K=X, то необходимо рассмотреть три случая:
	//31)Если обоих детей нет, то удаляем текущий узел и обнуляем ссылку на него у родительского узла;
	//32)Если одного из детей нет, то значения полей ребёнка m ставим вместо соответствующих значений корневого узла, затирая 
	//его старые значения, и освобождаем память, занимаемую узлом m;
	//33)Если оба ребёнка присутствуют, то:
	//331)Если левый узел m правого поддерева отсутствует (т. е. n->right->left), то копируем из правого узла в удаляемый K и ссылку 
	//на правый узел правого потомка;
	//332)Иначе (если левый узел m правого поддерева присутствует), то возьмём самый левый узел m, правого поддерева n->right,
	//скопируем данные(кроме ссылок на дочерние элементы) из m в n, затем рекурсивно удалим узел m.
	auto remove(const T& value) -> bool

	{

		if (size_ == 0) return false;

		else if (remove_n(value, root_))

		{

			size_--;

			return true;

		};

	}


	
	auto remove_n(const T& value, shared_ptr<Node>& curNode) -> bool

	{

		if (curNode == nullptr) return false;

		if (value > curNode->value_) return remove_n(value, curNode->right_);

		else if (value < curNode->value_)  return remove_n(value, curNode->left_);

		else

		{

			if ((curNode->left_ == nullptr) && (curNode->right_ == nullptr)) curNode = nullptr;

			else if (curNode->left_ == nullptr) curNode = curNode->right_;

			else if (curNode->right_ == nullptr) curNode = curNode->left_;

			else

			{

				auto parent = curNode;

				auto min = curNode->right_;

				bool check = true;

				while (min->left_)

				{

					if (check) check = false;

					parent = min;

					min = min->left_;

				}

				curNode->value_ = min->value_;

				if (check) parent->right_ = min->right_;

				else parent->left_ = min->right_;

			}

			return true;

		}

	}



	bool osymmetric(ostream& out, shared_ptr<Node> node) const noexcept

	{

		if (node)

		{

			osymmetric(out, node->right_);

			out << node->value_ << ' ';

			osymmetric(out, node->left_);

			return true;

		}
		else return false;

	}



	//bool odirect(ofstream& out, shared_ptr<Node> node) const noexcept

	//{

	//	if (node)

	//	{

	//		out << node->value_ << ' ';

	//		odirect(out, node->left_);

	//		odirect(out, node->right_);

	//		return true;

	//	}
	//	else return false;

	//}



	bool equal(shared_ptr<Node> fnode, shared_ptr<Node> snode) const noexcept

	{

		if (fnode)

			return snode && (fnode->value_ == snode->value_) &&

			equal(fnode->left_, snode->left_) &&

			equal(fnode->right_, snode->right_);

		else if (snode == nullptr) return true;

		else return false;

	}//сравнение 2 узлов;



	auto operator == (const BinarySearchTree& tree) const -> bool

	{

		if (this == &tree) return true;

		else if (size_ == tree.size_) return tree.equal(root_, tree.root_);

		else return false;

	}



	auto operator = (const BinarySearchTree& tree) -> BinarySearchTree&

	{

		if (this == &tree) return *this;

		else

		{

			root_ = nullptr;

			size_ = tree.size_;

			root_ = tree.root_->copy();

			return *this;

		}

	}//без уничтожения параметра-объекта;



	auto operator = (BinarySearchTree&& tree) -> BinarySearchTree&

	{

		if (this == &tree) return *this;

		else

		{

			root_ = nullptr;

			size_ = tree.size_;

			tree.size_ = 0;

			root_ = tree.root_;

			tree.root_ = nullptr;

			return *this;

		}

	}//передача параметра по правосторонней ссылке - компилятор также выделяет место на стеке, однако вызывает уже конструктор перемещения 
	//(отличие от др. видов передачи параметра) вместо конструктора копирования, задача которого — «переместить» все данные из исходного 
	//объекта в новый, превратив первый в «пустышку» (безопасную с точки зрения отсутствия связи с данными нового объекта).



	friend auto operator << (ostream& out, const BinarySearchTree<T>& tree) -> ostream&

	{

		tree.osymmetric(out, tree.root_);

		return out;

	}//вывод при обходе узлов в отсортированном порядке;



	//friend auto operator << (std::ofstream& out, const BinarySearchTree<T>& tree) -> std::ofstream&

	//{

	//	tree.odirect(out, tree.root_);

	//	return out;

	//}//вывод при обходе узлов в порядке: вершина, левое поддерево, правое поддерево (при использовании возникает ошибка);



	friend auto operator >> (istream& in, BinarySearchTree<T>& tree) -> istream&

	{

		T value;

		while (in >> value) tree.insert(value);//равносильно while (1) {
		                                                         //cin >> value;
		                                                         //...
		                                                         //if (!cin) break;
		                                                         //}
		return in;

	}//потоковый ввод;



	~BinarySearchTree()

	{

		root_ = nullptr;

		size_ = 0;

	}//деструктор;



private:

	shared_ptr<Node> root_;//корень (узел в вершине дерева);

	size_t size_;//число элементов в дереве, где size_t - std::size_t – целочисленный беззнаковый тип, может хранить максимальный размер 
	//теоретически возможного объекта любого типа (включая массивы), используется для индексации массивов и счетчиков циклов.

};
#endif LAB_11