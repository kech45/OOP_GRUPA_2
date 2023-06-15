#include <iostream>
#include <string>
#include <vector>

class Item {
private:
	std::string name;
	void copy(const Item& obj) {
		name = obj.name;
	}
public:
	Item() = default;
	Item(std::string n)
	{
		name = n;
	}
	Item(const Item& obj) {
		copy(obj);
	}

	const virtual void print() = 0;
	virtual Item* clone()const = 0;

	const std::string getName()
	{
		return name;
	}

};

class TextDoc : public Item {
private:
	std::string content;
public:
	TextDoc() :Item(){}
	TextDoc(std::string n, std::string con) :Item(n) {
		content = con;
	}
	TextDoc(const TextDoc& obj) :Item(obj){
		content = obj.content;
	}

	const virtual void print() override
	{
		std::cout << "Document name: " << getName() << std::endl;
		std::cout << "Document content: " << getContent() << std::endl;
	}
	TextDoc* clone()const override {
		return new TextDoc(*this);
	}
	
	const std::string getContent()
	{
		return content;
	}

};

class Folder : public Item {
private:
	std::vector<const Item*>items;
public:
	Folder() :Item() {}
	Folder(std::string n) :Item(n) {}
	Folder(const Folder& obj) :Item(obj) {
		items = obj.items;
	}

	const virtual void print()override 
	{
		std::cout << "Folder name: " << getName() << std::endl;
		std::cout << "Content: " << std::endl;
		for (size_t i = 0; i < items.size(); i++)
		{
			std::cout << std::endl;
			items.at(i)->clone()->print();
		}
	}
	Folder* clone()const override {
		return new Folder(*this);
	}
	void addItem(const Item& obj) {
		items.push_back(&obj);
	}

	const std::vector<const Item*> getItems() {
		return items;
	}
};





int main()
{
	TextDoc doc1("Akt", "thi shi crazy");
	TextDoc doc2("Johnny Who", "joni e 5 metra visok");
	TextDoc doc3("Kechy", "pechkaaaaaaaaaaaa");
	TextDoc doc4("Proizvodstvo", "neshta, svurzani s proizvodstvo");


	Folder employees("Employees");
	Folder otdeli("Otdeli");

	employees.addItem(doc2);
	employees.addItem(doc3);

	otdeli.addItem(doc4);

	Folder organizaciq("Organization");

	organizaciq.addItem(doc1);
	organizaciq.addItem(employees);
	organizaciq.addItem(otdeli);

	organizaciq.print();
	
}

